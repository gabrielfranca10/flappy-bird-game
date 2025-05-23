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

```bash
sudo apt install build-essential git
sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev libwayland-dev libxkbcommon-dev
```

---

## 🚀 Como Rodar o Jogo

### Clone o repositório:

```bash
git clone https://github.com/gabrielfranca10/flappy-bird-game
```

1. Abra o terminal e vá para o diretório `build`:

```bash
cd build
```

2. Gere os arquivos de build com Premake:

```bash
./premake5 gmake2
```

3. Volte para a raiz do projeto:

```bash
cd ..
```

4. Compile o projeto:

> Pressione `Ctrl+Shift+B` no terminal (se estiver usando VS Code com tasks)  
> ou use o comando:

```bash
make
```

5. Execute o jogo:

```bash
./bin/Debug/flappy-bird-game
```

---

## ⚙️ Recursos Usados

- [Raylib](https://www.raylib.com/) — biblioteca gráfica  
- [Premake](https://premake.github.io/) — geração de Makefiles  
- [Make](https://www.gnu.org/software/make/) — compilação  

---

## 👨‍💻 Equipe de Desenvolvimento

- Fernando Soares da Silva  
- Gabriel França de Albuquerque Pernambuco  
- Luis Guilherme Alves Lauria Soares
