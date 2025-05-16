#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "raylib.h"
#include "../include/passaro.h"
#include "../include/cano.h"

void inicializarPassaro(Passaro* p, float x, float y) {
    p->x = x;
    p->y = y;
    p->velocidadeY = 0;
    p->largura = 20;
    p->altura = 20;
}

void atualizarPassaro (Passaro* p) {
    p->velocidadeY += 0.5; //Gravidade
    p->y += p->velocidadeY;
    p->x += 1; //Movimento para frente (ajustar velocidade)
}

void pularPassaro(Passaro* p) {
    p->velocidadeY = -8; //Força do pulo
}

void desenharPassaro(Passaro* p) {
    DrawRectangle(p->x, p->y, p->largura, p->altura, YELLOW);
}

bool checarColisao(Passaro* p, Cano* canos, int alturaTela) {
    //Checa a colisao do passaro com o cano
    if (p->y < 0 || p->y + p->altura > alturaTela) {
        return  true;
    }
    
    Cano * atual = canos;

    //Checa colisão com cada cano
    while (atual != NULL) {
        //Verifica se o passaro esta na mesma coluna do cano (AJUSTAR PARA LARGURA DO CANO)
        if (p->x + p->largura > atual->x && p->x < atual->x + 40) {
            //Checa se esta fora do buraco
            if (p->y < atual->buracoY || p->y + p->altura > atual->buracoY + atual->alturaBuraco) {
                return true; //Colidiu com o cano
            }
        }
        atual = atual->proximo;
    }
    return  false;
}
