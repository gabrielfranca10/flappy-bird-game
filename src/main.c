#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include "../include/cano.h"
#include "../include/passaro.h" // Inclua o header do passaro

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;
    const int larguraCano = 60;

    InitWindow(screenWidth, screenHeight, "Flappy Bird - Raylib");
    SetTargetFPS(60);

    srand(time(NULL));

    // Cria lista de canos
    Cano* lista = NULL;
    adicionarCano(&lista, 300, screenHeight, 150);
    adicionarCano(&lista, 500, screenHeight, 150);
    adicionarCano(&lista, 700, screenHeight, 150);

    // Cria o pássaro
    Passaro passaro;
    passaro.x = 100;
    passaro.y = screenHeight / 2;
    passaro.largura = 34; // ajuste conforme seu sprite
    passaro.altura = 24;  // ajuste conforme seu sprite
    passaro.velocidadeY = 0;

    bool gameOver = false;

    while (!WindowShouldClose()) {
        if (!gameOver) {
            // Atualiza o pássaro
            atualizarPassaro(&passaro);

            // Pulo
            if (IsKeyPressed(KEY_SPACE)) {
                pularPassaro(&passaro);
            }

            // Atualiza canos (se tiver lógica de movimento)
            atualizarCanos(&lista);

            // Checa colisão
            if (checarColisao(&passaro, lista, screenHeight)) {
                gameOver = true;
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Desenha canos
        desenharCanos(lista, screenHeight);

        // Desenha pássaro
        desenharPassaro(&passaro);

        if (gameOver) {
            DrawText("Game Over! Pressione R para reiniciar", 200, 250, 30, RED);
            if (IsKeyPressed(KEY_R)) {
                // Reinicia o jogo
                passaro.x = 100;
                passaro.y = screenHeight / 2;
                passaro.velocidadeY = 0;
                gameOver = false;
                // Reinicie os canos se necessário
            }
        }

        DrawText("Flappy Bird (Raylib)", 280, 20, 20, DARKGRAY);

        EndDrawing();
    }

    liberarCanos(lista);
    CloseWindow();
    return 0;
}