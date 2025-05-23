#ifndef CANO_H
#define CANO_H

#include <stdbool.h> 

typedef struct Cano {
    int x;                
    int buracoY;          
    int alturaBuraco;     
    bool pontuado;        
    struct Cano *proximo;
} Cano;

Cano* criarCano(int x, int alturaTela, int alturaBuraco);
void adicionarCano(Cano** inicio, int x, int alturaTela, int alturaBuraco);
void atualizarCanos(Cano** inicio);
void desenharCanos(Cano* inicio, int alturaTela);
void removerCanos(Cano** inicio);
void liberarCanos(Cano* inicio);

#endif 
