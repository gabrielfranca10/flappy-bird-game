#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "../include/passaro.h"
#include "../include/cano.h"

#define GRAVIDADE 0.35f      // Gravidade mais leve para queda mais lenta
#define FORCA_PULO -7.0f     // Pulo menos forte para subir devagar
#define VELOCIDADE_MAX 6.5f  // Limite de velocidade para evitar queda rápida demais
#define LARGURA_CANO 40      // Consistente com o cano.h

void inicializarPassaro(Passaro* p, float x, float y) {
    p->x = x;
    p->y = y;
    p->velocidadeY = 0;
    p->largura = 20;
    p->altura = 20;
}

void atualizarPassaro(Passaro* p) {
    p->velocidadeY += GRAVIDADE;

    if (p->velocidadeY > VELOCIDADE_MAX) {
        p->velocidadeY = VELOCIDADE_MAX;
    }

    p->y += p->velocidadeY;

    // REMOVIDO: p->x += 1; // Flappy Bird não anda para frente, só o cenário que se move
}

void pularPassaro(Passaro* p) {
    p->velocidadeY = FORCA_PULO;
}

void desenharPassaro(Passaro* p) {
    DrawRectangle(p->x, p->y, p->largura, p->altura, YELLOW);
}

bool checarColisao(Passaro* p, Cano* canos, int alturaTela) {
    // Colisão com o topo e o chão da tela
    if (p->y < 0 || p->y + p->altura > alturaTela) {
        return true;
    }

    Cano* atual = canos;

    while (atual != NULL) {
        // Verifica se o pássaro está na faixa horizontal do cano
        if (p->x + p->largura > atual->x && p->x < atual->x + LARGURA_CANO) {
            // Verifica se o pássaro está fora do buraco (colidiu)
            if (p->y < atual->buracoY || p->y + p->altura > atual->buracoY + atual->alturaBuraco) {
                return true;
            }
        }
        atual = atual->proximo;
    }
    return false;
}
