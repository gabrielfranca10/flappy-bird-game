#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>  
#include "raylib.h"
#include "../include/passaro.h"
#include "../include/cano.h"
#include "../include/config.h"

void inicializarPassaro(Passaro* p, float x, float y) {
    p->x = x;
    p->y = y;
    p->velocidadeY = 0;

    p->frames[0] = LoadTexture("resources/bird2.png"); 
    p->frames[1] = LoadTexture("resources/bird3.png"); 

    p->largura = p->frames[0].width;
    p->altura = p->frames[0].height;

    p->frameAtual = 0;  
    p->rotacao = 0.0f;
}

void atualizarPassaro(Passaro* p) {
    p->velocidadeY += GRAVIDADE;
    if (p->velocidadeY > VELOCIDADE_MAX) {
        p->velocidadeY = VELOCIDADE_MAX;
    }
    p->y += p->velocidadeY;

    if (p->velocidadeY < 0) {
        p->frameAtual = 1;  
    } else {
        p->frameAtual = 0;  
    }

    float alvoRotacao;
    if (p->velocidadeY < 0) {
        alvoRotacao = -30.0f;
    } else {
        alvoRotacao = 90.0f;
    }
    float velocidadeRotacao = 6.0f;
    p->rotacao += (alvoRotacao - p->rotacao) * velocidadeRotacao * GetFrameTime();

    if (p->rotacao < -30.0f) p->rotacao = -30.0f;
    if (p->rotacao > 90.0f) p->rotacao = 90.0f;
}

void pularPassaro(Passaro* p) {
    p->velocidadeY = FORCA_PULO;
}

void desenharPassaro(Passaro *p, float escala) {
    Texture2D texture = p->frames[p->frameAtual];
    p->largura = (int)(texture.width * escala);
    p->altura = (int)(texture.height * escala);

    Vector2 origem;
    origem.x = p->largura / 2.0f;
    origem.y = p->altura / 2.0f;

    Rectangle source;
    source.x = 0.0f;
    source.y = 0.0f;
    source.width = (float)texture.width;
    source.height = (float)texture.height;

    Rectangle dest;
    dest.x = p->x + p->largura / 2.0f;
    dest.y = p->y + p->altura / 2.0f;
    dest.width = p->largura;
    dest.height = p->altura;

    DrawTexturePro(texture, source, dest, origem, p->rotacao, WHITE);
}

void descarregarPassaro(Passaro* p) {
    for (int i = 0; i < 2; i++) {  
        UnloadTexture(p->frames[i]);
    }
}

bool checarColisao(Passaro* p, Cano* canos, int alturaTela) {
    float margemX = p->largura * 0.15f;
    float margemY = p->altura * 0.15f;

    float hitboxX = p->x + margemX;
    float hitboxY = p->y + margemY;
    float hitboxLargura = p->largura - 2 * margemX;
    float hitboxAltura  = p->altura - 2 * margemY;

    if (hitboxY < 0 || hitboxY + hitboxAltura > alturaTela) {
        return true;
    }

    Cano* atual = canos;
    while (atual != NULL) {
        bool colisaoX = hitboxX + hitboxLargura > atual->x && hitboxX < atual->x + LARGURA_CANO;
        bool colisaoY = hitboxY < atual->buracoY || hitboxY + hitboxAltura > atual->buracoY + atual->alturaBuraco;

        if (colisaoX && colisaoY) {
            return true;
        }

        atual = atual->proximo;
    }

    return false;
}