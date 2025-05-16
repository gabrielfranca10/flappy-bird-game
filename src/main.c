#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include "../include/cano.h"
#include "../include/passaro.h"

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define ALTURA_BURACO 150
#define DISTANCIA_ENTRE_CANOS 200
#define LARGURA_CANO 40

int main(void) {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Flappy Bird - Raylib");
    SetTargetFPS(60);

    srand(time(NULL));

    // Pássaro
    Passaro passaro;
    passaro.x = 100;
    passaro.y = SCREEN_HEIGHT / 2;
    passaro.largura = 34;
    passaro.altura = 24;
    passaro.velocidadeY = 0;

    // Canos
    Cano* listaCanos = NULL;
    adicionarCano(&listaCanos, 400, SCREEN_HEIGHT, ALTURA_BURACO);
    adicionarCano(&listaCanos, 600, SCREEN_HEIGHT, ALTURA_BURACO);
    adicionarCano(&listaCanos, 800, SCREEN_HEIGHT, ALTURA_BURACO);

    int framesDesdeUltimoCano = 0;
    bool gameOver = false;

    while (!WindowShouldClose()) {
        if (!gameOver) {
            atualizarPassaro(&passaro);

            if (IsKeyPressed(KEY_SPACE)) {
                pularPassaro(&passaro);
            }

            atualizarCanos(&listaCanos);

            // Gera novo cano a cada DISTANCIA_ENTRE_CANOS pixels
            framesDesdeUltimoCano++;
            if (framesDesdeUltimoCano >= DISTANCIA_ENTRE_CANOS) {
                adicionarCano(&listaCanos, SCREEN_WIDTH, SCREEN_HEIGHT, ALTURA_BURACO);
                framesDesdeUltimoCano = 0;
            }

            if (checarColisao(&passaro, listaCanos, SCREEN_HEIGHT)) {
                gameOver = true;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        desenharCanos(listaCanos, SCREEN_HEIGHT);
        desenharPassaro(&passaro);

        if (gameOver) {
            DrawText("Game Over! Pressione R para reiniciar", 180, 250, 30, RED);
            if (IsKeyPressed(KEY_R)) {
                passaro.x = 100;
                passaro.y = SCREEN_HEIGHT / 2;
                passaro.velocidadeY = 0;
                gameOver = false;

                liberarCanos(listaCanos);
                listaCanos = NULL;
                adicionarCano(&listaCanos, 400, SCREEN_HEIGHT, ALTURA_BURACO);
                adicionarCano(&listaCanos, 600, SCREEN_HEIGHT, ALTURA_BURACO);
                adicionarCano(&listaCanos, 800, SCREEN_HEIGHT, ALTURA_BURACO);
                framesDesdeUltimoCano = 0;
            }
        }

        DrawText("Flappy Bird (Raylib)", 280, 20, 20, DARKGRAY);
        EndDrawing();
    }

    liberarCanos(listaCanos);
    CloseWindow();
    return 0;
}
