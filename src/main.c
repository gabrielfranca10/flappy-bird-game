#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "../include/cano.h"
#include "../include/passaro.h"

#define SCREEN_WIDTH 1920
#define SCREEN_HEIGHT 1080
#define ALTURA_BURACO 300
#define DISTANCIA_ENTRE_CANOS 500
#define LARGURA_CANO 100

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

    Texture2D background = LoadTexture("resources/background.jpg");
    Texture2D birdTexture = LoadTexture("resources/bird.png");
    float escalaPassaro = 0.25f;

    Passaro passaro;
    passaro.x = 1300;
    passaro.y = SCREEN_HEIGHT / 2;
    passaro.largura = birdTexture.width * escalaPassaro;
    passaro.altura = birdTexture.height * escalaPassaro;
    passaro.velocidadeY = 0;

    Cano* listaCanos = NULL;
    adicionarCano(&listaCanos, SCREEN_WIDTH, SCREEN_HEIGHT, ALTURA_BURACO);
    int framesDesdeUltimoCano = 0;
    int pontuacao = 0;
    bool gameOver = false;

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawTextureEx(background, (Vector2){0, 0}, 0.0f, 1.0f, WHITE);

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

        desenharCanos(listaCanos, SCREEN_HEIGHT);
        desenharPassaro(&passaro, birdTexture, escalaPassaro);

        char textoPontuacao[20];
        sprintf(textoPontuacao, "Pontos: %d", pontuacao);
        DrawText(textoPontuacao, 20, 20, 30, DARKBLUE);

        if (gameOver) {
            DrawText("Game Over! Pressione R para reiniciar", 180, 250, 30, RED);
            if (IsKeyPressed(KEY_R)) {
                passaro.x = 1300;
                passaro.y = SCREEN_HEIGHT / 2;
                passaro.velocidadeY = 0;
                gameOver = false;
                pontuacao = 0;

                liberarCanos(listaCanos);
                listaCanos = NULL;
                adicionarCano(&listaCanos, SCREEN_WIDTH, SCREEN_HEIGHT, ALTURA_BURACO);
                framesDesdeUltimoCano = 0;
            }
        }

        DrawText("Flappy Bird (Raylib)", 280, 560, 20, DARKGRAY);
        EndDrawing();
    }

    liberarCanos(listaCanos);
    UnloadTexture(birdTexture);
    UnloadTexture(background);
    CloseWindow();
    return 0;
}
