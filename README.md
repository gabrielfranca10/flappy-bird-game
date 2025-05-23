# 🐦 Flappy Bird Game com Raylib

Um jogo clássico desenvolvido com a biblioteca **Raylib** em C, explorando os principais conceitos da linguagem.

## 📹 Demonstração

[![Demonstração do Jogo](http://img.youtube.com/vi/<COLOQUE_AQUI_O_ID_DO_VIDEO>/0.jpg)](https://www.youtube.com/watch?v=<COLOQUE_AQUI_O_ID_DO_VIDEO>)

👉 [Assista ao vídeo do jogo rodando!](https://www.youtube.com/watch?v=<COLOQUE_AQUI_O_ID_DO_VIDEO>)

---

## ✅ Plataforma Suportada

- ✅ **Linux**
---

## 📦 Dependências

Antes de compilar, instale as dependências da Raylib para o seu sistema operacional:

### 🐧 Linux (raylib-Dependencias)

1. sudo apt install build-essential git

2. sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev

---

## 🚀 Como Rodar o Jogo

### Clone o repositorio

    
    git clone https://github.com/gabrielfranca10/flappy-bird-game


1.  Abra o terminal e vá para o diretório `build`:

    ```bash
    cd build
    ```

2.  Gere os arquivos de build com Premake:

    ```bash
    ./premake5 gmake2
    ```

3.  Volte para a raiz do projeto:

    ```bash
    cd ..
    ```

4.  Compile o projeto:

    ```bash
    ctrl+shift+b no terminal
    ```

5.  Execute o jogo:

    ```bash
    ./bin/Debug/flappy-bird-game
    ```

## ⚙️ Recursos Usados

- [Raylib](https://www.raylib.com/) - biblioteca gráfica
- [Premake](https://premake.github.io/) - para geração de Makefiles
- [Make](https://www.gnu.org/software/make/) - para compilação

---

## 💡 Conceitos de Programação Utilizados

Este projeto demonstra o uso dos seguintes conceitos de programação em C:

- **Estruturas (`struct`)**:
    - Definição de `struct Cano` (em `include/cano.h`) para representar os canos do jogo.
    - Definição de `typedef struct { ... } Passaro;` (em `include/passaro.h`) para representar o pássaro.

- **Ponteiros**:
    - Manipulação de listas de canos: `Cano*`, `Cano**` (em `src/cano.c`).
    - Funções que recebem ponteiros para structs, como `void inicializarPassaro(Passaro* p, float x, float y);` (em `src/passaro.c`).
    - Manipulação do pássaro: `Passaro*` (em `src/passaro.c`).

- **Alocação Dinâmica de Memória**:
    - Criação de novos canos com `malloc`: `Cano* novo = malloc(sizeof(Cano));` (em `src/cano.c`).

- **Listas Encadeadas**:
    - A lista de canos é implementada como uma lista encadeada, onde `struct Cano` possui um campo `struct Cano *proximo;` (em `include/cano.h`).
    - Funções como `adicionarCano`, `removerCanos`, `liberarCanos` manipulam a lista encadeada (em `src/cano.c`).

- **Matrizes**:
    - Utilização de uma matriz para armazenar o histórico das pontuações: `char historico[MAX_HISTORICO][128];` (em `src/main.c`).

- **Escrita e Leitura em Arquivo**:
    - Escrita de pontuações nos arquivos "data/scores.txt" e "data/history.txt" (em `src/geral.c`):
        ```c
        FILE* fscore = fopen("data/scores.txt", "a");
        FILE* fhist = fopen("data/history.txt", "a");
        ```
    - Leitura do arquivo "data/history.txt" para carregar o histórico de pontuações (em `src/geral.c`):
        ```c
        FILE *f = fopen("data/history.txt", "r");
        ```
        Lê linhas para mostrar o histórico.
