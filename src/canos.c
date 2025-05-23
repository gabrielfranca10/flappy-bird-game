#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/cano.h"
#include "../include/config.h"
#include "raylib.h"


Cano *criarCano(int x, int alturaTela, int alturaBuraco) {
    Cano* novo = malloc(sizeof(Cano));
    if (!novo) return NULL;

    novo->x = x;
    novo->alturaBuraco = alturaBuraco;
    novo->buracoY = rand() % (alturaTela - alturaBuraco - MARGEM_TOPO_BASE) + MARGEM_TOPO_BASE;
    novo->pontuado = false;  
    novo->proximo = NULL;

    return novo;
}

void adicionarCano(Cano** inicio, int x, int alturaTela, int alturaBuraco) {
    Cano* novo = criarCano(x, alturaTela, alturaBuraco);
    if (!novo) return;

    novo->proximo = *inicio;
    *inicio = novo;
}

void atualizarCanos(Cano** inicio) {
    Cano* atual = *inicio;

    while (atual != NULL) {
        atual->x -= VELOCIDADE_CANO; 
        atual = atual->proximo;
    }

    removerCanos(inicio); 
}

void desenharCanos(Cano* inicio, int alturaTela) {
    while (inicio != NULL) {
        
        Color corpoCanoTopo = (Color){80, 200, 80, 255};     
        Color corpoCanoBase = (Color){100, 255, 100, 255};   
        Color sombraTopo = (Color){50, 150, 50, 200};        

        int topoAltura = 20;
        int topoLarguraExtra = 10;

        
        DrawRectangleGradientV(inicio->x, 0, LARGURA_CANO, inicio->buracoY, corpoCanoTopo, corpoCanoBase);

        
        DrawRectangle(inicio->x - topoLarguraExtra / 2,
                      inicio->buracoY - topoAltura,
                      LARGURA_CANO + topoLarguraExtra,
                      topoAltura,
                      sombraTopo);

        
        DrawRectangleGradientV(inicio->x,
                              inicio->buracoY + inicio->alturaBuraco,
                              LARGURA_CANO,
                              alturaTela - (inicio->buracoY + inicio->alturaBuraco),
                              corpoCanoBase,
                              corpoCanoTopo);

        
        DrawRectangle(inicio->x - topoLarguraExtra / 2,
                      inicio->buracoY + inicio->alturaBuraco,
                      LARGURA_CANO + topoLarguraExtra,
                      topoAltura,
                      sombraTopo);

        
       

        inicio = inicio->proximo;
    }
}


void removerCanos(Cano** inicio) {
    while (*inicio != NULL && (*inicio)->x + LARGURA_CANO < 0) {
        Cano* temp = *inicio;
        *inicio = (*inicio)->proximo;
        free(temp);
    }
}


void liberarCanos(Cano* inicio) {
    while (inicio != NULL) {
        Cano* temp = inicio;
        inicio = inicio->proximo;
        free(temp);
    }
}
