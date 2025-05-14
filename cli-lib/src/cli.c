#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include "cli.h"

static struct termios old_termios;

void cliIniciar() {
    // Salva o estado atual do terminal
    tcgetattr(STDIN_FILENO, &old_termios);
    
    // Cria uma cópia para modificar
    struct termios new_termios = old_termios;

    // Desabilita buffer de linha e eco
    new_termios.c_lflag &= ~(ICANON | ECHO);

    // Aplica as alterações
    tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);

    // Esconde o cursor
    printf("\033[?25l");
}

void cliRestaurar() {
    // Restaura estado original do terminal
    tcsetattr(STDIN_FILENO, TCSANOW, &old_termios);

    // Mostra o cursor de volta
    printf("\033[?25h");
}

void cliLimparTela() {
    // Limpa a tela inteira e move o cursor para o canto superior esquerdo
    printf("\033[2J\033[H");
}

void cliMoverCursor(int x, int y) {
    // Move o cursor para (x, y). Lembrando que o canto superior esquerdo é (1,1)
    printf("\033[%d;%dH", y, x);
}

void cliPausar() {
    // Aguarda uma tecla ser pressionada
    getchar();
}
