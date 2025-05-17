#ifndef PASSARO_H
#define PASSARO_H
#include "cano.h"

typedef struct Passaro {
    float x, y;
    float velocidadeY;
    float largura, altura;
} Passaro;

//Manipulações do passaro
void inicializarPassaro(Passaro* p, float x, float); //ok
void pularPassaro(Passaro* p); //ok
void atualizarPassaro(Passaro* p); //ok
void pularPassaro(Passaro* p); //ok
void desenharPassaro(Passaro *p, Texture2D texture, float escala);
bool checarColisao(Passaro* p, Cano* canos, int alturaTela); //ok


#endif //PASSARO_H
