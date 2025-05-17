#ifndef CANO_H
#define CANO_H

#include <stdbool.h> // Necessário para usar bool

typedef struct Cano {
    int x;                // posição horizontal
    int buracoY;          // posição vertical onde o buraco começa
    int alturaBuraco;     // altura do buraco
    bool pontuado;        // se o pássaro já pontuou passando por esse cano
    struct Cano *proximo;
} Cano;

// Manipulações dos canos
Cano* criarCano(int x, int alturaTela, int alturaBuraco);
void adicionarCano(Cano** inicio, int x, int alturaTela, int alturaBuraco);
void atualizarCanos(Cano** inicio);
void desenharCanos(Cano* inicio, int alturaTela);
void removerCanos(Cano** inicio);
void liberarCanos(Cano* inicio);

#endif // CANO_H
