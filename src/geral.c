#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "raylib.h"
#include "../include/geral.h"
#include "../include/config.h"


void salvarPontuacao(int pontos) {
    FILE *fscore = fopen("data/scores.txt", "a");
    if (fscore) {
        fprintf(fscore, "%d\n", pontos);
        fclose(fscore);
    }

    FILE *fhist = fopen("data/history.txt", "a");
    if (fhist) {
        time_t agora = time(NULL);
        char data[30];
        strftime(data, 30, "%Y-%m-%d %H:%M:%S", localtime(&agora));
        fprintf(fhist, "[%s] Pontuação: %d\n", data, pontos);
        fclose(fhist);
    }
}


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


void carregarHistorico(char historico[][128], int *linhasHistorico) {
    FILE *f = fopen("data/history.txt", "r");
    *linhasHistorico = 0;
    
    if (f) {
        while (*linhasHistorico < MAX_HISTORICO && 
               fgets(historico[*linhasHistorico], 128, f)) {
            (*linhasHistorico)++;
        }
        fclose(f);
    }
}


void desenharTextoCentralizado(const char *texto, int y, int tamanho, Color cor) {
    int largura = MeasureText(texto, tamanho);
    DrawText(texto, SCREEN_WIDTH/2 - largura/2, y, tamanho, cor);
}