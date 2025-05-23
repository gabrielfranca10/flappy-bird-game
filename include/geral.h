#ifndef GERAL_H
#define GERAL_H

#include "raylib.h"
#include "../include/cano.h"
#include "../include/passaro.h"
#include "../include/config.h"

#define MAX_HISTORICO 10

void salvarPontuacao(int pontos);

void reiniciarJogo(Passaro *passaro, Cano **listaCanos, int *pontuacao, int *framesDesdeUltimoCano);

void carregarHistorico(char historico[][128], int *linhasHistorico);

void desenharTextoCentralizado(const char *texto, int y, int tamanho, Color cor);

#endif 