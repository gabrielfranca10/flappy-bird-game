#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "../include/passaro.h"
#include "../include/cano.h"

#define GRAVIDADE 0.8f
#define FORCA_PULO -10.0f
#define VELOCIDADE_MAX 15.5f
#define LARGURA_CANO 40

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
}

void pularPassaro(Passaro* p) {
    p->velocidadeY = FORCA_PULO;
}

void desenharPassaro(Passaro *p, Texture2D texture, float escala) {
    p->largura = (int)(texture.width * escala);
    p->altura  = (int)(texture.height * escala);

    DrawTextureEx(texture, (Vector2){p->x, p->y}, 0.0f, escala, WHITE);
}

bool checarColisao(Passaro* p, Cano* canos, int alturaTela) {
    float margemX = p->largura * 0.15f;
    float margemY = p->altura * 0.15f;

    float hitboxX = p->x + margemX;
    float hitboxY = p->y + margemY;
    float hitboxLargura = p->largura - 2 * margemX;
    float hitboxAltura  = p->altura  - 2 * margemY;

    if (hitboxY < 0 || hitboxY + hitboxAltura > alturaTela) {
        return true;
    }

    Cano* atual = canos;
    while (atual != NULL) {
        if (hitboxX + hitboxLargura > atual->x && hitboxX < atual->x + LARGURA_CANO) {
            if (hitboxY < atual->buracoY || hitboxY + hitboxAltura > atual->buracoY + atual->alturaBuraco) {
                return true;
            }
        }
        atual = atual->proximo;
    }
    return false;
}
