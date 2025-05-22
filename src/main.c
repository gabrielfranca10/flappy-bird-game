#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "../include/cano.h"
#include "../include/passaro.h"

// Constantes
#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define ALTURA_BURACO 300
#define DISTANCIA_ENTRE_CANOS 100
#define LARGURA_CANO 100
#define MAX_HISTORICO 10

typedef enum { MENU, JOGO, GAME_OVER, HISTORICO, SAIR } EstadoJogo;

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
    SetExitKey(KEY_NULL);  // <- Impede ESC de fechar o jogo automaticamente
    InitAudioDevice();
    SetTargetFPS(60);
    srand(time(NULL));

    // Recursos gráficos
    Texture2D background = LoadTexture("resources/background.png");
    Texture2D birdTexture = LoadTexture("resources/bird.png");
    const float escalaPassaro = 0.25f;

    // Sons
    Sound somSeleciona = LoadSound("resources/select.wav");
    Sound somMove = LoadSound("resources/move.wav");

    // Passaro
    Passaro passaro = {1300, SCREEN_HEIGHT / 2, birdTexture.width * escalaPassaro, birdTexture.height * escalaPassaro, 0};

    // Canos
    Cano* listaCanos = NULL;
    int framesDesdeUltimoCano = 0;

    // Estado do jogo
    EstadoJogo estado = MENU;
    int opcaoSelecionada = 0;
    int pontuacao = 0;

    // Histórico
    char historico[MAX_HISTORICO][128];
    int linhasHistorico = 0;

    // Animação do título
    float titleScale = 1.0f;
    bool aumentando = true;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(background, (Vector2){0, 0}, 0.0f, 1.0f, WHITE);

        if (estado == MENU) {
            // Animação do título
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
                       (Vector2){SCREEN_WIDTH/2 - larguraTitulo * titleScale/2, SCREEN_HEIGHT/2 - 250},
                       60 * titleScale, 2, DARKBLUE);

            const char *opcoes[] = {"Jogar", "Pontuações", "Sair"};

            for (int i = 0; i < 3; i++) {
                Color cor = (i == opcaoSelecionada) ? RED : WHITE;

                if (i == opcaoSelecionada) {
                    DrawRectangle(SCREEN_WIDTH/2 - 120, SCREEN_HEIGHT/2 - 50 + i * 70, 240, 50, Fade(LIGHTGRAY, 0.3f));
                }

                DrawText(opcoes[i], SCREEN_WIDTH/2 - MeasureText(opcoes[i], 40)/2, SCREEN_HEIGHT/2 - 40 + i * 70, 40, cor);
            }

            if (IsKeyPressed(KEY_DOWN)) {
                opcaoSelecionada = (opcaoSelecionada + 1) % 3;
                PlaySound(somMove);
            } else if (IsKeyPressed(KEY_UP)) {
                opcaoSelecionada = (opcaoSelecionada + 2) % 3;
                PlaySound(somMove);
            } else if (IsKeyPressed(KEY_ENTER)) {
                PlaySound(somSeleciona);
                if (opcaoSelecionada == 0) {
                    estado = JOGO;
                    reiniciarJogo(&passaro, &listaCanos, &pontuacao, &framesDesdeUltimoCano);
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
        else if (estado == JOGO) {
            atualizarPassaro(&passaro);

            if (IsKeyPressed(KEY_SPACE)) {
                pularPassaro(&passaro);
            }

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

            // Atualiza pontuação
            for (Cano* atual = listaCanos; atual != NULL; atual = atual->proximo) {
                if (!atual->pontuado && atual->x + LARGURA_CANO < passaro.x) {
                    pontuacao++;
                    atual->pontuado = true;
                }
            }

            desenharCanos(listaCanos, SCREEN_HEIGHT);
            desenharPassaro(&passaro, birdTexture, escalaPassaro);

            char textoPontuacao[20];
            sprintf(textoPontuacao, "Pontos: %d", pontuacao);
            DrawText(textoPontuacao, 20, 20, 30, DARKBLUE);
        }
        else if (estado == GAME_OVER) {
            desenharCanos(listaCanos, SCREEN_HEIGHT);
            desenharPassaro(&passaro, birdTexture, escalaPassaro);

            char textoPontuacao[20];
            sprintf(textoPontuacao, "Pontos: %d", pontuacao);
            DrawText(textoPontuacao, 20, 20, 30, DARKBLUE);

            DrawText("Game Over!", SCREEN_WIDTH/2 - 150, SCREEN_HEIGHT/2 - 100, 45, RED);
            DrawRectangle(SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT/2, 515, 50, RED);
            DrawText("Pressione R para reiniciar ou ESC para voltar", SCREEN_WIDTH/2 - 180, SCREEN_HEIGHT/2 + 10, 20, WHITE);

            if (IsKeyPressed(KEY_R)) {
                estado = JOGO;
                reiniciarJogo(&passaro, &listaCanos, &pontuacao, &framesDesdeUltimoCano);
            }
            if (IsKeyPressed(KEY_ESCAPE)) {
                estado = MENU;
            }
        }
        else if (estado == HISTORICO) {
            DrawText("Histórico de Pontuações:", SCREEN_WIDTH/2 - 300, 100, 40, DARKBLUE);

            for (int i = 0; i < linhasHistorico; i++) {
                DrawRectangleLines(SCREEN_WIDTH/2 - 320, 160 + i * 40, 640, 30, GRAY);
                DrawText(historico[i], SCREEN_WIDTH/2 - 310, 165 + i * 40, 25, WHITE);
            }

            DrawText("Pressione ESC para voltar", SCREEN_WIDTH/2 - 200, SCREEN_HEIGHT - 100, 30, WHITE);

            if (IsKeyPressed(KEY_ESCAPE)) {
                estado = MENU;
            }
        }
        else if (estado == SAIR) {
            break;
        }

        DrawText("Flappy Bird (Raylib)", 20, SCREEN_HEIGHT - 40, 20, DARKGRAY);
        EndDrawing();
    }

    // Liberação de recursos
    liberarCanos(listaCanos);
    UnloadTexture(birdTexture);
    UnloadTexture(background);
    UnloadSound(somMove);
    UnloadSound(somSeleciona);
    CloseAudioDevice();
    CloseWindow();

    return 0;
}
