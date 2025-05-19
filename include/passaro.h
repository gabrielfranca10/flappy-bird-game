#ifndef PASSARO_H
#define PASSARO_H
#include "cano.h"
#include "raylib.h"

typedef struct Passaro {
    float x, y;
    float velocidadeY;
    float velocidadeX;
    float largura, altura;
} Passaro;

// Manipulações do passaro
void inicializarPassaro(Passaro* p, float x, float y);
void pularPassaro(Passaro* p);
void atualizarPassaro(Passaro* p);
void desenharPassaro(Passaro *p, Texture2D texture, float escala);
bool checarColisao(Passaro* p, Cano* canos, int alturaTela);

#endif // PASSARO_H