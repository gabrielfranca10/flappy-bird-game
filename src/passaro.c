#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>  // Para fabs
#include "raylib.h"
#include "../include/passaro.h"
#include "../include/cano.h"

#define GRAVIDADE 0.8f
#define FORCA_PULO -10.0f
#define VELOCIDADE_MAX 15.5f
#define LARGURA_CANO 40

// Inicialização do pássaro
void inicializarPassaro(Passaro* p, float x, float y) {
    p->x = x;
    p->y = y;
    p->velocidadeY = 0;

    // Agora só duas texturas: bird2 e bird3
    p->frames[0] = LoadTexture("resources/bird2.png"); // Queda
    p->frames[1] = LoadTexture("resources/bird3.png"); // Pulo

    p->largura = p->frames[0].width;
    p->altura = p->frames[0].height;

    p->frameAtual = 0;  // Começa caindo
    p->rotacao = 0.0f;
}

void atualizarPassaro(Passaro* p) {
    p->velocidadeY += GRAVIDADE;
    if (p->velocidadeY > VELOCIDADE_MAX) {
        p->velocidadeY = VELOCIDADE_MAX;
    }
    p->y += p->velocidadeY;

    // Troca de frame baseado na velocidade vertical
    if (p->velocidadeY < 0) {
        p->frameAtual = 1;  // Pulando (bird3.png)
    } else {
        p->frameAtual = 0;  // Caindo (bird2.png)
    }

    // Rotação suave igual antes
    float alvoRotacao = (p->velocidadeY < 0) ? -30.0f : 90.0f;
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

    Vector2 origem = { p->largura / 2.0f, p->altura / 2.0f };

    Rectangle source = { 0.0f, 0.0f, (float)texture.width, (float)texture.height };
    Rectangle dest = { p->x + p->largura / 2.0f, p->y + p->altura / 2.0f, p->largura, p->altura };

    DrawTexturePro(texture, source, dest, origem, p->rotacao, WHITE);

}

void descarregarPassaro(Passaro* p) {
    for (int i = 0; i < 2; i++) {  // só 2 texturas
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

    // Colisão com o chão ou teto
    if (hitboxY < 0 || hitboxY + hitboxAltura > alturaTela) {
        return true;
    }

    // Colisão com os canos
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
