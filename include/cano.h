#ifndef CANO_H
#define CANO_H

typedef struct Cano {
    int x; //posição horizontal
    int buracoY; //posição vertical onde o buraco começa
    int alturaBuraco; //Altura do buraco
    struct Cano *proximo;
} Cano;

//Manipulações dos canos
Cano* criarCano(int x, int alturaTela, int alturaBuraco);
void adicionarCano(Cano** inicio, int x, int alturaTela, int alturaBuraco);
void atualizarCanos(Cano** inicio);
void desenharCanos(Cano* inicio, int alturaTela);
void removerCanos(Cano** inicio);
void liberarCanos(Cano* incio);

#endif //CANO_H