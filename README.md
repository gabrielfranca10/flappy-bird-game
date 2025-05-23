# 🎮 Meu Jogo com Raylib

Um jogo desenvolvido com **Raylib** utilizando os principais conceitos de C:

## 📹 Demonstração

👉 [Assista ao vídeo do jogo rodando!](COLOQUE_AQUI_O_LINK_DO_VIDEO)

---

## ✅ Plataformas Suportadas

- ✅ **Linux**
- ✅ **MacOS**
- ✅ **Windows** (com MinGW-W64)

---

## 🚀 Como Rodar o Jogo

### 🐧 Linux

1. Abra o terminal e vá para o diretório `build`:

   ```bash
   cd build

    Gere os arquivos de build com premake:

./premake5 gmake2

Volte para a raiz do projeto:

cd ..

Compile o projeto:

    run make

    run ./bin/Debug/flappy-bird-game

🍏 MacOS

    Abra o terminal e vá para o diretório build:

cd build

Gere os arquivos de build:

./premake5.osx gmake2

Volte para a raiz:

cd ..

Compile:

    run make

    run ./bin/Debug/flappy-bird-game

🪟 Windows (MinGW-W64)

    Baixe o W64devkit ou use o MinGW-W64 que vem com o instalador do Raylib.

    Adicione à sua variável de ambiente PATH:

C:\raylib\w64devkit\bin

No terminal, vá até a pasta build:

cd build

Gere os arquivos de build:

premake5.exe gmake2

Volte para a raiz:

cd ..

Compile com:

    run mingw32-make.exe

    run bin\Debug\flappy-bird-game.exe


⚙️ Recursos Usados

    Raylib - biblioteca gráfica

    Premake - para geração de Makefiles

    Make - para compilação
