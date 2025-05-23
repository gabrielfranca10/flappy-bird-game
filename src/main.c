#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include "../include/cano.h"
#include "../include/passaro.h"
#include "../include/config.h"
#include "../include/geral.h"  

typedef enum { MENU, PREPARADO, CONTAGEM, JOGO, GAME_OVER, HISTORICO, SAIR } EstadoJogo;


const Color AZUL_CUSTOM = {53, 172, 176, 255};
const char *OPCOES_MENU[] = {"Jogar", "Pontuações", "Sair"};
const int NUM_OPCOES = 3;

int main(void) {
    
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird - Raylib");
    SetExitKey(KEY_NULL);
    
    SetTargetFPS(60);
    srand(time(NULL));

    
    Texture2D background = LoadTexture("resources/background.png");
    
    
    
    
    Passaro passaro;
    inicializarPassaro(&passaro, 1300, SCREEN_HEIGHT / 2);
    const float escalaPassaro = 0.25f;
    
    Cano* listaCanos = NULL;
    int framesDesdeUltimoCano = 0;
    int pontuacao = 0;
    
    
    EstadoJogo estado = MENU;
    int opcaoSelecionada = 0;
    
    
    char historico[MAX_HISTORICO][128];
    int linhasHistorico = 0;
    
    
    float titleScale = 1.0f;
    bool aumentando = true;
    int contagem = 3;
    float tempoContagem = 0.0f;

    
    while (!WindowShouldClose()) {
        float deltaTime = GetFrameTime();

        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawTextureEx(background, (Vector2){0, 0}, 0.0f, 1.0f, WHITE);

        switch (estado) {
            case MENU: {
                
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
                          60 * titleScale, 2, AZUL_CUSTOM);

                
                for (int i = 0; i < NUM_OPCOES; i++) {
                    if (i == opcaoSelecionada) {
                        DrawRectangle(SCREEN_WIDTH/2 - 120, SCREEN_HEIGHT/2 - 50 + i * 70, 240, 50, Fade(LIGHTGRAY, 0.3f));
                    }
                    DrawText(OPCOES_MENU[i], SCREEN_WIDTH/2 - MeasureText(OPCOES_MENU[i], 40)/2, 
                             SCREEN_HEIGHT/2 - 40 + i * 70, 40, AZUL_CUSTOM);
                }

                
                if (IsKeyPressed(KEY_DOWN)) {
                    opcaoSelecionada++;
                    if (opcaoSelecionada >= NUM_OPCOES) opcaoSelecionada = 0;
                    
                } else if (IsKeyPressed(KEY_UP)) {
                    opcaoSelecionada--;
                    if (opcaoSelecionada < 0) opcaoSelecionada = NUM_OPCOES - 1;
                    
                } else if (IsKeyPressed(KEY_ENTER)) {
                    
                    if (opcaoSelecionada == 0) {
                        estado = PREPARADO;
                    } else if (opcaoSelecionada == 1) {
                        estado = HISTORICO;
                        carregarHistorico(historico, &linhasHistorico);
                    } else {
                        estado = SAIR;
                    }
                }
                break;
            }
            
            case PREPARADO: {
                desenharTextoCentralizado("Preparado para jogar? Pressione ESPACO para iniciar!", 
                                         SCREEN_HEIGHT/2 - 50, 40, AZUL_CUSTOM);
                desenharPassaro(&passaro, escalaPassaro);

                if (IsKeyPressed(KEY_SPACE)) {
                    reiniciarJogo(&passaro, &listaCanos, &pontuacao, &framesDesdeUltimoCano);
                    contagem = 3;
                    tempoContagem = 0.0f;
                    estado = CONTAGEM;
                }
                break;
            }
            
            case CONTAGEM: {
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
                    desenharTextoCentralizado(texto, SCREEN_HEIGHT/2 - 50, 100, AZUL_CUSTOM);
                }
                desenharPassaro(&passaro, escalaPassaro);
                break;
            }
            
            case JOGO: {
                
                atualizarPassaro(&passaro);
                if (IsKeyPressed(KEY_SPACE)) pularPassaro(&passaro);
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
                DrawText(textoPontuacao, 20, 20, 30, AZUL_CUSTOM);
                break;
            }
            
            case GAME_OVER: {
                
                desenharCanos(listaCanos, SCREEN_HEIGHT);
                desenharPassaro(&passaro, escalaPassaro);

                
                char textoPontuacao[30];
                sprintf(textoPontuacao, "Pontos: %d", pontuacao);
                desenharTextoCentralizado(textoPontuacao, SCREEN_HEIGHT/2 - 100, 40, AZUL_CUSTOM);

                
                desenharTextoCentralizado("Game Over! Pressione ESPACO para reiniciar, ENTER para voltar ao menu ou ESC para sair.", 
                                         SCREEN_HEIGHT/2, 30, AZUL_CUSTOM);

                
                if (IsKeyPressed(KEY_SPACE)) {
                    reiniciarJogo(&passaro, &listaCanos, &pontuacao, &framesDesdeUltimoCano);
                    estado = CONTAGEM;
                    contagem = 3;
                    tempoContagem = 0.0f;
                } else if (IsKeyPressed(KEY_ENTER)) {
                    liberarCanos(listaCanos);
                    listaCanos = NULL;
                    estado = MENU;
                    opcaoSelecionada = 0;
                } else if (IsKeyPressed(KEY_ESCAPE)) {
                    estado = SAIR;
                }
                break;
            }
            
            case HISTORICO: {
                DrawText("Historico das Ultimas Pontuacoes:", 50, 50, 40, AZUL_CUSTOM);
                for (int i = 0; i < linhasHistorico; i++) {
                    DrawText(historico[i], 50, 100 + i * 30, 25, DARKGRAY);
                }
                DrawText("Pressione ESC para voltar", 50, SCREEN_HEIGHT - 50, 25, AZUL_CUSTOM);

                if (IsKeyPressed(KEY_ESCAPE)) estado = MENU;
                break;
            }
            
            case SAIR:
                goto cleanup;
        }

        EndDrawing();
    }

cleanup:

    liberarCanos(listaCanos);
    descarregarPassaro(&passaro);
    UnloadTexture(background);
    CloseWindow();

    return 0;
}