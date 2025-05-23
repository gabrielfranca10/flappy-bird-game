#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "../include/cano.h"
#include "../include/passaro.h"
#include "../include/config.h"

// Constantes
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define ALTURA_BURACO 300
#define DISTANCIA_ENTRE_CANOS 100
#define LARGURA_CANO 100
#define MAX_HISTORICO 10

typedef enum { MENU, PREPARADO, CONTAGEM, JOGO, GAME_OVER, HISTORICO, SAIR } EstadoJogo;

// Cor personalizada azul #35acb0
const Color azulCustom = {53, 172, 176, 255};

// Função para salvar pontuação no histórico e score
void salvarPontuacao(int pontos) {
    FILE* fscore = fopen("data/scores.txt", "a");
    if (fscore != NULL) {
        fprintf(fscore, "%d\n", pontos);
        fclose(fscore);
    }

    FILE* fhist = fopen("data/history.txt", "a");
    if (fhist != NULL) {
        time_t agora = time(NULL);
        struct tm *tm_info = localtime(&agora);
        char data[30];
        strftime(data, 30, "%Y-%m-%d %H:%M:%S", tm_info);
        fprintf(fhist, "[%s] Pontuação: %d\n", data, pontos);
        fclose(fhist);
    }
}

// Função para reiniciar o jogo
void reiniciarJogo(Passaro *passaro, Cano **listaCanos, int *pontuacao, int *framesDesdeUltimoCano) {
    passaro->x = 1300;
    passaro->y = SCREEN_HEIGHT / 2;
    passaro->velocidadeY = 0;
    *pontuacao = 0;
    *framesDesdeUltimoCano = 0;

    liberarCanos(*listaCanos);
    *listaCanos = NULL;
    adicionarCano(listaCanos, SCREEN_WIDTH, SCREEN_HEIGHT, ALTURA_BURACO);
}

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird - Raylib");
    SetExitKey(KEY_NULL);
    InitAudioDevice();
    SetTargetFPS(60);
    srand(time(NULL));

    Texture2D background = LoadTexture("resources/background.png");
    const float escalaPassaro = 0.25f;

    Sound somSeleciona = LoadSound("resources/select.wav");
    Sound somMove = LoadSound("resources/move.wav");

    Passaro passaro;
    inicializarPassaro(&passaro, 1300, SCREEN_HEIGHT / 2);

    Cano* listaCanos = NULL;
    int framesDesdeUltimoCano = 0;

    EstadoJogo estado = MENU;
    int opcaoSelecionada = 0;
    int pontuacao = 0;
    int dificuldade = 1; // fixa para médio, pode ajustar aqui se quiser

    // Histórico
    char historico[MAX_HISTORICO][128];
    int linhasHistorico = 0;

    // Animação do título
    float titleScale = 1.0f;
    bool aumentando = true;

    int contagem = 3;
    float tempoContagem = 0.0f;

    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(background, (Vector2){0, 0}, 0.0f, 1.0f, WHITE);

        if (estado == MENU) {
            // Animação título
            if (aumentando) {
                titleScale += 0.005f;
                if (titleScale >= 1.2f) aumentando = false;
            } else {
                titleScale -= 0.005f;
                if (titleScale <= 1.0f) aumentando = true;
            }

            const char *titulo = "FLAPPY BIRD";
            int larguraTitulo = MeasureText(titulo, 60);
            DrawTextEx(GetFontDefault(), titulo,
                       (Vector2){SCREEN_WIDTH/2 - larguraTitulo * titleScale/2 + 30, SCREEN_HEIGHT/2 - 500},
                       60 * titleScale, 2, azulCustom);

            const char *opcoes[] = {"Jogar", "Pontuações", "Sair"};

            for (int i = 0; i < 3; i++) {
                Color cor = azulCustom;

                if (i == opcaoSelecionada) {
                    DrawRectangle(SCREEN_WIDTH/2 - 120, SCREEN_HEIGHT/2 - 50 + i * 70, 240, 50, Fade(LIGHTGRAY, 0.3f));
                }

                DrawText(opcoes[i], SCREEN_WIDTH/2 - MeasureText(opcoes[i], 40)/2, SCREEN_HEIGHT/2 - 40 + i * 70, 40, cor);
            }

            if (IsKeyPressed(KEY_DOWN)) {
                opcaoSelecionada = opcaoSelecionada + 1;
                if (opcaoSelecionada >= 3) {
                    opcaoSelecionada = 0;
                }
                PlaySound(somMove);
            } else if (IsKeyPressed(KEY_UP)) {
                opcaoSelecionada = opcaoSelecionada - 1;
                if (opcaoSelecionada < 0) {
                    opcaoSelecionada = 2;
                }
                PlaySound(somMove);
            } else if (IsKeyPressed(KEY_ENTER)) {
                PlaySound(somSeleciona);
                if (opcaoSelecionada == 0) {
                    estado = PREPARADO;
                } else if (opcaoSelecionada == 1) {
                    estado = HISTORICO;

                    FILE *f = fopen("data/history.txt", "r");
                    linhasHistorico = 0;
                    if (f != NULL) {
                        char linha[128];
                        while (fgets(linha, sizeof(linha), f) != NULL && linhasHistorico < MAX_HISTORICO) {
                            strcpy(historico[linhasHistorico], linha);
                            linhasHistorico++;
                        }
                        fclose(f);
                    }
                } else if (opcaoSelecionada == 2) {
                    estado = SAIR;
                }
            }
        }
        else if (estado == PREPARADO) {
            const char *msg = "Preparado para jogar? Pressione ESPACO para iniciar!";
            int larg = MeasureText(msg, 40);
            DrawText(msg, SCREEN_WIDTH/2 - larg/2, SCREEN_HEIGHT/2 - 50, 40, azulCustom);

            desenharPassaro(&passaro, escalaPassaro);

            if (IsKeyPressed(KEY_SPACE)) {
                reiniciarJogo(&passaro, &listaCanos, &pontuacao, &framesDesdeUltimoCano);
                contagem = 3;
                tempoContagem = 0.0f;
                estado = CONTAGEM;
            }
        }
        else if (estado == CONTAGEM) {
            tempoContagem += deltaTime;

            if (tempoContagem >= 1.0f) {
                contagem--;
                tempoContagem = 0.0f;
            }

            if (contagem <= 0) {
                estado = JOGO;
            } else {
                char texto[16];
                sprintf(texto, "%d", contagem);
                int larg = MeasureText(texto, 100);
                DrawText(texto, SCREEN_WIDTH/2 - larg/2, SCREEN_HEIGHT/2 - 50, 100, azulCustom);
            }

            desenharPassaro(&passaro, escalaPassaro);
        }
        else if (estado == JOGO) {
            atualizarPassaro(&passaro);

            if (IsKeyPressed(KEY_SPACE)) {
                pularPassaro(&passaro);
            }

            // Aqui chama atualizarCanos sem parâmetro, que usa dificuldade fixa internamente
            atualizarCanos(&listaCanos);

            framesDesdeUltimoCano++;
            if (framesDesdeUltimoCano >= DISTANCIA_ENTRE_CANOS) {
                adicionarCano(&listaCanos, SCREEN_WIDTH, SCREEN_HEIGHT, ALTURA_BURACO);
                framesDesdeUltimoCano = 0;
            }

            if (checarColisao(&passaro, listaCanos, SCREEN_HEIGHT)) {
                estado = GAME_OVER;
                salvarPontuacao(pontuacao);
            }

            for (Cano* atual = listaCanos; atual != NULL; atual = atual->proximo) {
                if (!atual->pontuado && atual->x + LARGURA_CANO < passaro.x) {
                    pontuacao++;
                    atual->pontuado = true;
                }
            }

            desenharCanos(listaCanos, SCREEN_HEIGHT);
            desenharPassaro(&passaro, escalaPassaro);

            char textoPontuacao[20];
            sprintf(textoPontuacao, "Pontos: %d", pontuacao);
            DrawText(textoPontuacao, 20, 20, 30, azulCustom);
        }
        else if (estado == GAME_OVER) {
            desenharCanos(listaCanos, SCREEN_HEIGHT);
            desenharPassaro(&passaro, escalaPassaro);

            char textoPontuacao[30];
            sprintf(textoPontuacao, "Pontos: %d", pontuacao);
            int largPontuacao = MeasureText(textoPontuacao, 40);
            DrawText(textoPontuacao, SCREEN_WIDTH/2 - largPontuacao/2, SCREEN_HEIGHT/2 - 100, 40, azulCustom);

            const char *msgGameOver = "Game Over! Pressione ESPACO para reiniciar, ENTER para voltar ao menu ou ESC para sair.";
            int largMsg = MeasureText(msgGameOver, 30);
            DrawText(msgGameOver, SCREEN_WIDTH/2 - largMsg/2, SCREEN_HEIGHT/2, 30, azulCustom);

            if (IsKeyPressed(KEY_SPACE)) {
                reiniciarJogo(&passaro, &listaCanos, &pontuacao, &framesDesdeUltimoCano);
                estado = CONTAGEM;
                contagem = 3;
                tempoContagem = 0.0f;
            }
            else if (IsKeyPressed(KEY_ENTER)) {
                liberarCanos(listaCanos);
                listaCanos = NULL;
                estado = MENU;
                opcaoSelecionada = 0;
            }
            else if (IsKeyPressed(KEY_ESCAPE)) {
                estado = SAIR;
            }
        }
        else if (estado == HISTORICO) {
            DrawText("Historico das Ultimas Pontuacoes:", 50, 50, 40, azulCustom);

            for (int i = 0; i < linhasHistorico; i++) {
                DrawText(historico[i], 50, 100 + i * 30, 25, DARKGRAY);
            }

            DrawText("Pressione ESC para voltar", 50, SCREEN_HEIGHT - 50, 25, azulCustom);

            if (IsKeyPressed(KEY_ESCAPE)) {
                estado = MENU;
            }
        }
        else if (estado == SAIR) {
            break;
        }

        EndDrawing();
    }

    // Limpar tudo antes de sair
    liberarCanos(listaCanos);
    UnloadTexture(background);
    UnloadSound(somSeleciona);
    UnloadSound(somMove);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}