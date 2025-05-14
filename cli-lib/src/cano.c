#include <stdio.h>
#include <stdio.h>
#include "cano.h"
#include "cli.h"

Cano* criarCano(int x, int alturaTela, int alturaBuraco) {
    Cano* novo = malloc(sizeof(Cano));
    novo->x = x;
    novo->alturaBuraco = alturaBuraco;
    novo->buracoY = rand() % (alturaTela - alturaBuraco - 4) + 2;
    novo->prox = NULL;
    return novo;
}

void adicionar_cano(Cano** inicio, int x, int alturaTela, int alturaBuraco) {
    Cano* novo = criarCano(x, alturaTela, alturaBuraco);
    novo->prox = *inicio;
    *inicio = novo;
}

void atualizar_cano (Cano** inicio) {
    Cano* atual = *inicio;
    while(atual != NULL) {
        atual->x--;
        atual = atual->prox;
    }
    removerCanos(inicio);
}

void desenharCanos (Cano* inicio, int alturaTela) {
    while (inicio != NULL) {
        for (int i = 0; i< alturaTela; i++) {
            if (i < inicio->buracoY || i > inicio->buracoY + inicio->alturaBuraco) {
                cliMoverCursor(inicio->x, i);
                printf("|");
            }
        }
        inicio = inicio->prox;
    }
}

void removerCanos(Cano** inicio) {
    while(*inicio != NULL && (*inicio)->x < 0) {
        Cano* temp = *inicio;
        *inicio = (*inicio)->prox;
        free(temp);
    }
}

void liberarCanos(Cano* inicio) {
    while(inicio != NULL) {
        Cano* temp = inicio;
        inicio = inicio->prox;
        free(temp);
    }
}