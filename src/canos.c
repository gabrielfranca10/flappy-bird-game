#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/cano.h"
#include "raylib.h"

#define LARGURA_CANO 100
#define MARGEM_TOPO_BASE 4  // Margem para evitar buracos colados nas bordas
#define VELOCIDADE_CANO 5

// Cria um novo cano com posição e buraco aleatórios
Cano *criarCano(int x, int alturaTela, int alturaBuraco) {
    Cano* novo = malloc(sizeof(Cano));
    if (!novo) return NULL;

    novo->x = x;
    novo->alturaBuraco = alturaBuraco;
    novo->buracoY = rand() % (alturaTela - alturaBuraco - MARGEM_TOPO_BASE) + MARGEM_TOPO_BASE;
    novo->pontuado = false;  // Inicializa como não pontuado
    novo->proximo = NULL;

    return novo;
}

// Insere o novo cano no início da lista encadeada
void adicionarCano(Cano** inicio, int x, int alturaTela, int alturaBuraco) {
    Cano* novo = criarCano(x, alturaTela, alturaBuraco);
    if (!novo) return;

    novo->proximo = *inicio;
    *inicio = novo;
}

// Atualiza a posição dos canos e remove os que saíram da tela
void atualizarCanos(Cano** inicio) {
    Cano* atual = *inicio;

    while (atual != NULL) {
        atual->x -= VELOCIDADE_CANO; // Move o cano para a esquerda
        atual = atual->proximo;
    }

    removerCanos(inicio); // Remove os que saíram completamente da tela
}

// Desenha todos os canos da lista
void desenharCanos(Cano* inicio, int alturaTela) {
    while (inicio != NULL) {
        // Cores para o gradiente do corpo do cano
        Color corpoCanoTopo = (Color){80, 200, 80, 255};     // Verde escuro (topo do gradiente)
        Color corpoCanoBase = (Color){100, 255, 100, 255};   // Verde claro (base do gradiente)
        Color sombraTopo = (Color){50, 150, 50, 200};        // Sombra topo mais escura

        int topoAltura = 20;
        int topoLarguraExtra = 10;

        // Cano superior com gradiente vertical
        DrawRectangleGradientV(inicio->x, 0, LARGURA_CANO, inicio->buracoY, corpoCanoTopo, corpoCanoBase);

        // Topo do cano superior com sombra
        DrawRectangle(inicio->x - topoLarguraExtra / 2,
                      inicio->buracoY - topoAltura,
                      LARGURA_CANO + topoLarguraExtra,
                      topoAltura,
                      sombraTopo);

        // Cano inferior com gradiente vertical invertido
        DrawRectangleGradientV(inicio->x,
                              inicio->buracoY + inicio->alturaBuraco,
                              LARGURA_CANO,
                              alturaTela - (inicio->buracoY + inicio->alturaBuraco),
                              corpoCanoBase,
                              corpoCanoTopo);

        // Topo do cano inferior com sombra
        DrawRectangle(inicio->x - topoLarguraExtra / 2,
                      inicio->buracoY + inicio->alturaBuraco,
                      LARGURA_CANO + topoLarguraExtra,
                      topoAltura,
                      sombraTopo);

        // HITBOX DEBUG (opcional, tire depois)
        /*
        DrawRectangleLines(inicio->x, 0, LARGURA_CANO, inicio->buracoY, RED);
        DrawRectangleLines(inicio->x,
                           inicio->buracoY + inicio->alturaBuraco,
                           LARGURA_CANO,
                           alturaTela - (inicio->buracoY + inicio->alturaBuraco), RED);
        */

        inicio = inicio->proximo;
    }
}

// Remove canos que saíram completamente da tela
void removerCanos(Cano** inicio) {
    while (*inicio != NULL && (*inicio)->x + LARGURA_CANO < 0) {
        Cano* temp = *inicio;
        *inicio = (*inicio)->proximo;
        free(temp);
    }
}

// Libera toda a lista de canos
void liberarCanos(Cano* inicio) {
    while (inicio != NULL) {
        Cano* temp = inicio;
        inicio = inicio->proximo;
        free(temp);
    }
}
