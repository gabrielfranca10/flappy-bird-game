#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "cano.h"
#include "cli.h"

int main() {
    srand(time(NULL)); // para gerar canos com buracos aleatórios

    cli_iniciar();
    cli_limpar_tela();

    Cano* lista = NULL;

    // Adiciona 3 canos em posições diferentes
    adicionar_cano(&lista, 40, 20, 5);
    adicionar_cano(&lista, 60, 20, 5);
    adicionar_cano(&lista, 80, 20, 5);

    desenhar_canos(lista, 20); // desenha na tela
    cli_mover_cursor(0, 21);   // move o cursor abaixo para não sobrescrever
    cli_pausar();              // espera o usuário apertar uma tecla

    liberar_canos(lista);
    cli_restaurar(); // volta à tela normal

    return 0;
}
