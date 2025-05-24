# 🐦 Flappy Bird Game com Raylib

Um jogo clássico desenvolvido com a biblioteca **Raylib** em C, explorando os principais conceitos da linguagem.

## 📹 Demonstração

[Demonstração do Jogo](https://youtu.be/MuBmDDfsPHM) - Veja o jogo funcionando

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

### 1. Clone o repositório:

```bash
git clone https://github.com/gabrielfranca10/flappy-bird-game
```

### 2. Acesse o diretório `build`:

```bash
cd flappy-bird-game/build
```

### 3. Gere os arquivos de build com Premake:

```bash
./premake5 gmake2
```

### 4. Volte para a raiz do projeto:

```bash
cd ..
```

### 5. Compile o projeto:

```bash
ctrl+shift+b ou make
```

### 6. Execute o jogo:

```bash
./bin/Debug/flappy-bird-game
```

---

## 🎮 Como Jogar

- Pressione a **barra de espaço** para fazer o pássaro voar.
- O objetivo é **passar entre os canos** sem bater.
- A cada cano ultrapassado, você **ganha pontos**.
- O jogo termina quando o pássaro colide com um cano ou o chão.

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

## SLIDES

- https://www.canva.com/design/DAGl9oDItTA/czAjUKksZqC44ttbDm5qhw/edit
