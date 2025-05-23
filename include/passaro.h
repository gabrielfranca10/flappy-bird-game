#ifndef PASSARO_H
#define PASSARO_H
#include "cano.h"
#include "raylib.h"

typedef struct {
    float x, y;
    float velocidadeY;
    int largura, altura;
    Texture2D frames[3]; // 3 frames do pássaro
    int frameAtual;
    float tempoFrame;    // tempo entre frames (ex: 0.15f)
    float timerAnimacao; // acumula o tempo para trocar de frame
    float rotacao; // <-- novo campo
} Passaro;

// Manipulações do passaro
void inicializarPassaro(Passaro* p, float x, float y);
void pularPassaro(Passaro* p);
void atualizarPassaro(Passaro* p);
void desenharPassaro(Passaro *p, float escala);
void descarregarPassaro(Passaro* p);
bool checarColisao(Passaro* p, Cano* canos, int alturaTela);

#endif // PASSARO_H