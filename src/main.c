#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "../include/cano.h"
#include "../include/passaro.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define ALTURA_BURACO 150
#define DISTANCIA_ENTRE_CANOS 300
#define LARGURA_CANO 40

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

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird - Raylib");
    SetTargetFPS(60);
    srand(time(NULL));

    // Carrega a textura do pássaro e define escala
    Texture2D birdTexture = LoadTexture("resources/bird.png");
    float escalaPassaro = 0.045f;

    // Pássaro
    Passaro passaro;
    passaro.x = 100;
    passaro.y = SCREEN_HEIGHT / 2;
    passaro.largura = birdTexture.width * escalaPassaro;
    passaro.altura = birdTexture.height * escalaPassaro;
    passaro.velocidadeY = 0;

    // Canos
    Cano* listaCanos = NULL;
    // REMOVE AS INICIALIZAÇÕES MANUAIS
    // adicionarCano(&listaCanos, 400, SCREEN_HEIGHT, ALTURA_BURACO);
    // adicionarCano(&listaCanos, 600, SCREEN_HEIGHT, ALTURA_BURACO);
    // adicionarCano(&listaCanos, 800, SCREEN_HEIGHT, ALTURA_BURACO);

    int framesDesdeUltimoCano = 0;
    int pontuacao = 0;
    bool gameOver = false;

    // Adiciona o primeiro cano no início
    adicionarCano(&listaCanos, SCREEN_WIDTH, SCREEN_HEIGHT, ALTURA_BURACO);
    framesDesdeUltimoCano = 0;

    while (!WindowShouldClose()) {
        if (!gameOver) {
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
                gameOver = true;
                salvarPontuacao(pontuacao);
            }

            Cano* atual = listaCanos;
            while (atual != NULL) {
                if (!atual->pontuado && atual->x + LARGURA_CANO < passaro.x) {
                    pontuacao++;
                    atual->pontuado = true;
                }
                atual = atual->proximo;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        desenharCanos(listaCanos, SCREEN_HEIGHT);

        // Desenha o pássaro com textura e escala
        desenharPassaro(&passaro, birdTexture, escalaPassaro);

        // Mostrar pontuação
        char textoPontuacao[20];
        sprintf(textoPontuacao, "Pontos: %d", pontuacao);
        DrawText(textoPontuacao, 20, 20, 30, DARKBLUE);

        if (gameOver) {
            DrawText("Game Over! Pressione R para reiniciar", 180, 250, 30, RED);
            if (IsKeyPressed(KEY_R)) {
                passaro.x = 100;
                passaro.y = SCREEN_HEIGHT / 2;
                passaro.velocidadeY = 0;
                gameOver = false;
                pontuacao = 0;

                liberarCanos(listaCanos);
                listaCanos = NULL;
                // REPOSICIONA O PRIMEIRO CANO
                adicionarCano(&listaCanos, SCREEN_WIDTH, SCREEN_HEIGHT, ALTURA_BURACO);
                framesDesdeUltimoCano = 0;
            }
        }

        DrawText("Flappy Bird (Raylib)", 280, 560, 20, DARKGRAY);
        EndDrawing();
    }

    liberarCanos(listaCanos);
    UnloadTexture(birdTexture);
    CloseWindow();
    return 0;
}