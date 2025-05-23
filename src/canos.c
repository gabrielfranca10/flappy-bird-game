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
        // Cores roxas e detalhes
        Color corpoCanoTopo = (Color){120, 60, 180, 255};     // Roxo escuro
        Color corpoCanoBase = (Color){180, 120, 255, 255};    // Roxo claro
        Color sombraTopo = (Color){80, 40, 120, 200};         // Sombra topo roxa
        Color bordaCano = (Color){60, 30, 90, 255};           // Borda escura
        Color brilho = (Color){220, 180, 255, 100};           // Brilho lateral

        int topoAltura = 20;
        int topoLarguraExtra = 10;
        int borda = 3;

        // --- Cano de cima ---
        // Corpo com gradiente roxo
        DrawRectangleGradientV(inicio->x, 0, LARGURA_CANO, inicio->buracoY, corpoCanoTopo, corpoCanoBase);
        // Borda esquerda
        DrawRectangle(inicio->x, 0, borda, inicio->buracoY, bordaCano);
        // Borda direita
        DrawRectangle(inicio->x + LARGURA_CANO - borda, 0, borda, inicio->buracoY, bordaCano);
        // Brilho lateral esquerda
        DrawRectangle(inicio->x + 5, 5, 6, inicio->buracoY - 10, brilho);

        // Topo arredondado (sombra)
        DrawRectangle(inicio->x - topoLarguraExtra / 2,
                      inicio->buracoY - topoAltura,
                      LARGURA_CANO + topoLarguraExtra,
                      topoAltura,
                      sombraTopo);
        // Borda do topo
        DrawRectangleLines(inicio->x - topoLarguraExtra / 2,
                           inicio->buracoY - topoAltura,
                           LARGURA_CANO + topoLarguraExtra,
                           topoAltura,
                           bordaCano);

        // --- Cano de baixo ---
        // Corpo com gradiente invertido
        DrawRectangleGradientV(inicio->x,
                              inicio->buracoY + inicio->alturaBuraco,
                              LARGURA_CANO,
                              alturaTela - (inicio->buracoY + inicio->alturaBuraco),
                              corpoCanoBase,
                              corpoCanoTopo);
        // Borda esquerda
        DrawRectangle(inicio->x,
                      inicio->buracoY + inicio->alturaBuraco,
                      borda,
                      alturaTela - (inicio->buracoY + inicio->alturaBuraco),
                      bordaCano);
        // Borda direita
        DrawRectangle(inicio->x + LARGURA_CANO - borda,
                      inicio->buracoY + inicio->alturaBuraco,
                      borda,
                      alturaTela - (inicio->buracoY + inicio->alturaBuraco),
                      bordaCano);
        // Brilho lateral esquerda
        DrawRectangle(inicio->x + 5,
                      inicio->buracoY + inicio->alturaBuraco + 5,
                      6,
                      alturaTela - (inicio->buracoY + inicio->alturaBuraco) - 10,
                      brilho);

        // Topo arredondado (sombra)
        DrawRectangle(inicio->x - topoLarguraExtra / 2,
                      inicio->buracoY + inicio->alturaBuraco,
                      LARGURA_CANO + topoLarguraExtra,
                      topoAltura,
                      sombraTopo);
        // Borda do topo
        DrawRectangleLines(inicio->x - topoLarguraExtra / 2,
                           inicio->buracoY + inicio->alturaBuraco,
                           LARGURA_CANO + topoLarguraExtra,
                           topoAltura,
                           bordaCano);

        // --- Detalhe extra: círculos de brilho nos topos ---
        DrawCircle(inicio->x + LARGURA_CANO / 2, inicio->buracoY - topoAltura / 2, 8, brilho);
        DrawCircle(inicio->x + LARGURA_CANO / 2, inicio->buracoY + inicio->alturaBuraco + topoAltura / 2, 8, brilho);

        // --- Detalhe extra: linhas horizontais para dar textura ---
        for (int i = 20; i < inicio->buracoY - 20; i += 30) {
            DrawLine(inicio->x + 8, i, inicio->x + LARGURA_CANO - 8, i, Fade(brilho, 0.3f));
        }
        for (int i = inicio->buracoY + inicio->alturaBuraco + 20; i < alturaTela - 20; i += 30) {
            DrawLine(inicio->x + 8, i, inicio->x + LARGURA_CANO - 8, i, Fade(brilho, 0.3f));
        }

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
