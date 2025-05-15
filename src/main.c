
#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include "../include/cano.h"

int main(void) {
    const int screenWidth = 800;
    const int screenHeight = 600;
    const int larguraCano = 60;

    InitWindow(screenWidth, screenHeight, "Teste desenharCanos - Raylib");
    SetTargetFPS(60);

    srand(time(NULL));

    // Cria lista de canos
    Cano* lista = NULL;
    adicionarCano(&lista, 300, screenHeight, 150);
    adicionarCano(&lista, 500, screenHeight, 150);
    adicionarCano(&lista, 700, screenHeight, 150);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Chame sua função de desenhar canos (adaptada para Raylib)
        desenharCanos(lista, screenHeight);

        DrawText("Testando desenharCanos (Raylib)", 180, 20, 20, DARKGRAY);

        EndDrawing();
    }

    liberarCanos(lista);
    CloseWindow();
    return 0;
}