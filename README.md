# 🐦 Flappy Bird Game com Raylib

Um jogo clássico desenvolvido com a biblioteca **Raylib** em C, explorando os principais conceitos da linguagem.

## 📹 Demonstração

[![Demonstração do Jogo](http://img.youtube.com/vi/<COLOQUE_AQUI_O_ID_DO_VIDEO>/0.jpg)](https://www.youtube.com/watch?v=<COLOQUE_AQUI_O_ID_DO_VIDEO>)

👉 [Assista ao vídeo do jogo rodando!](https://www.youtube.com/watch?v=<COLOQUE_AQUI_O_ID_DO_VIDEO>)

---

## ✅ Plataformas Suportadas

- ✅ **Linux**
- ✅ **MacOS**
- ✅ **Windows** (com MinGW-W64)

---

## 📦 Dependências

Antes de compilar, instale as dependências da Raylib para o seu sistema operacional:

### 🐧 Linux

Veja as instruções detalhadas e dependências necessárias no [guia oficial da Raylib para Linux](https://github.com/raysan5/raylib/wiki/Working-on-GNU-Linux).

### 🍏 MacOS

Veja as instruções detalhadas e dependências necessárias no [guia oficial da Raylib para macOS](https://github.com/raysan5/raylib/wiki/Working-on-macOS).

### 🪟 Windows

Veja as instruções detalhadas e dependências necessárias no [guia oficial da Raylib para Windows](https://github.com/raysan5/raylib/wiki/Working-on-Windows).

---

## 🚀 Como Rodar o Jogo

### Clone o repositorio

    ```bash
    git clone https://github.com/gabrielfranca10/flappy-bird-game
    ``` 

### 🐧 Linux

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
    make
    ```

5.  Execute o jogo:

    ```bash
    ./bin/Debug/flappy-bird-game
    ```

### 🍏 MacOS

1.  Abra o terminal e vá para o diretório `build`:

    ```bash
    cd build
    ```

2.  Gere os arquivos de build:

    ```bash
    ./premake5.osx gmake2
    ```

3.  Volte para a raiz:

    ```bash
    cd ..
    ```

4.  Compile:

    ```bash
    make
    ```

5.  Execute o jogo:

    ```bash
    ./bin/Debug/flappy-bird-game
    ```

### 🪟 Windows (MinGW-W64)

1.  Baixe o [W64devkit](https://github.com/skeeto/w64devkit) ou use o MinGW-W64 que vem com o instalador do Raylib.

2.  Adicione o diretório `bin` do MinGW-W64 à sua variável de ambiente `PATH`:

    ```
    C:\raylib\w64devkit\bin
    ```

3.  No terminal, vá até a pasta `build`:

    ```bash
    cd build
    ```

4.  Gere os arquivos de build:

    ```bash
    premake5.exe gmake2
    ```

5.  Volte para a raiz:

    ```bash
    cd ..
    ```

6.  Compile com:

    ```bash
    mingw32-make.exe
    ```

7.  Execute o jogo:

    ```bash
    bin\Debug\flappy-bird-game.exe
    ```

---

## ⚙️ Recursos Usados

- [Raylib](https://www.raylib.com/) - biblioteca gráfica
- [Premake](https://premake.github.io/) - para geração de Makefiles
- [Make](https://www.gnu.org/software/make/) - para compilação
