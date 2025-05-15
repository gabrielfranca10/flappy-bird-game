#include <stdio.h>
#include <stdlib.h>
#include "../include/cano.h"
#include "raylib.h"

Cano *criarCano(int x, int alturaTela, int alturaBuraco) {
    Cano* novo = malloc(sizeof(Cano));

    if (!novo) {
        return NULL; // caso a posição não seja uma posição "nova"
    }

    novo->x = x;
    novo->alturaBuraco = alturaBuraco;
    novo->buracoY = rand() % (alturaTela - alturaBuraco - 4) + 2; // Evita criar buracos colados na borda
    novo->proximo = NULL;

    return novo;
}

void adicionarCano(Cano** inicio, int x, int alturaTela, int alturaBuraco) {
    Cano* novo = criarCano(x, alturaTela, alturaBuraco);

    if (!novo) { //Caso nao seja uma posição "nova" return NULL
        return;
    }

    novo->proximo = *inicio; //Caso seja uma posição válida, faz o novo cano apontar para o proximo cano
    *inicio = novo; // faz o ponteiro de inicio apontar para o novo cano
}

void atualizarCanos(Cano** inicio) {
    Cano* atual = *inicio;
    
    while(atual != NULL) {
        atual->x--; //Diminui a posição horizontal do cano, fazendo o cano andar para esquerda
        atual = atual->proximo; //Passa para o próximo cano da lista 4 
    }
    removerCanos(inicio);
}

void desenharCanos(Cano* inicio, int alturaTela) {
    while (inicio != NULL) {
        // Desenha o cano de cima
        DrawRectangle(inicio->x, 0, 40, inicio->buracoY, GREEN);
        // Desenha o cano de baixo
        DrawRectangle(inicio->x, inicio->buracoY + inicio->alturaBuraco, 40, alturaTela - (inicio->buracoY + inicio->alturaBuraco), GREEN);

        inicio = inicio->proximo;
    }
}

void removerCanos(Cano** inicio) {

    while(*inicio != NULL && (*inicio)->x < 0) {
        Cano* temp = *inicio;
        *inicio = (*inicio)->proximo;
        free(temp);
    }
}

void liberarCanos(Cano* inicio) {

    while(inicio != NULL) {
        Cano* temp = inicio;
        inicio = inicio->proximo;
        free(temp);
    }
}