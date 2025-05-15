/*
Raylib example file.
This is an example main file for a simple raylib project.
Use this as a starting point or replace it with your code.

by Jeffery Myers is marked with CC0 1.0. To view a copy of this license, visit https://creativecommons.org/publicdomain/zero/1.0/

*/

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

int main (void) {
	
	// Inicializando o  tamanho da tela do jogo
	const int screenWidth = 800; 
	const int screenHeight = 600;

	InitWindow(screenWidth, screenHeight, "Flappy Bird - Raylib");

	while (!WindowShouldClose()) {
		BeginDrawing();
		ClearBackground(RAYWHITE);

		DrawText("Seja bem-vindo, Flappy Bird", 190, 200, 20, LIGHTGRAY);

		EndDrawing();
	}

	CloseWindow();
	return 0;
}
