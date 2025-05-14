#ifndef CANO_H
#define CANO_H

typedef struct Pipe {
    int x; // posição horizontal na tela
    int buracoY; //  posição vertical onde o buraco começa (gap)
    int alturaBuraco; // altura total do buraco por onde o passasaro passa
    struct Cano *prox; // ponteiro para o proximo cano (lista encadeada)
} Cano;

// Funçẽs para manipular os canos 
Cano* criarCano (int x, int alturaTela, int alturaBuraco);
void adicionarCano(Cano** inicio, int x, int alturaTela, int alturaBrucao);
void atualizarCanos(Cano** inicio);
void desenharCanos(Cano* inicio, int alturaTela);
void removerCanos(Cano** inicio);
void liberarCanos(Cano* incio);

#endif // PIPE_H
