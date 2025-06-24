![4](https://github.com/user-attachments/assets/233420a2-5476-41e2-8d49-dc13fc635aa0)

# **Sobre o jogo**
Em *Tux vs. Bloatware*, você é o querido pinguim Tux — o grande símbolo dos resistentes e resilientes usuários de Linux. 
Em uma missão no espaço cibernético, com a nave danificada após uma tentativa errônea de instalar o Windows 11, você enfrentará fases desafiadoras em busca de um objetivo vital: **recuperar o pen drive de instalação do Linux** para consertar sua nave!
Desvie dos obstáculos e não hesite em disparar contra o chefe final. 
Mas cuidado: quanto mais próximo do objetivo, maior o risco da **temida tela azul**...

Que a força do Kernel esteja com você!

# **Criadores**
- Thiago Felipe Alves do Carmo (thiago-fealves)
- Gabriel Alves (369gabriel, 369wn)
- Pedro Borsatto (sraverage)
- Arthur Cordeiro (CORDEIRIN)
- Deivid Rafael (Deivid-rafael)

## **Índice**

* [Allegro](#Allegro)
* [Instalação do Jogo](#instalacao-do-jogo)
    * [Compilação](#compilacao)
    * [Execução](#execucao)
* [Como Jogar](#como-jogar)
    * [Start](#start)
    * [Pause](#pause)
    * [Menu Principal](#menu-principal)
    * [Jogar Novamente](#jogar-novamente)
    * [Sair](#sair)
    * [Movimentação](#movimentacao)
* [Testes](#testes)
* [Documentação](#documentacao)
* [Remover Arquivos Auxiliares](#remover-arquivos-auxiliares)

### **Ferramentas:**
___
**Linguagem:** C++17

**Biblioteca:** Allegro 5

**Compilação:** make

**Documentação:** Doxygen

**Testes Unitários:** Doctest

### **Allegro**
___
Allegro (Atari Low-Level Game Routines) é uma biblioteca gráfica open source, multiplataforma e orientada à criação de jogos e aplicações multimídia. Escrita originalmente em C, ela oferece uma interface simples e eficiente para lidar com gráficos, som, entrada do usuário, temporização e muito mais.
Desenvolvida com foco em desempenho e portabilidade, a Allegro é utilizada principalmente por desenvolvedores que buscam controle direto sobre os elementos básicos de um jogo 2D, sem depender de engines complexas.

**Mais sobre a biblioteca:**
🔗 [https://liballeg.org](https://liballeg.org)
🔗 [https://en.wikipedia.org/wiki/Allegro_(software_library)](https://en.wikipedia.org/wiki/Allegro_(software_library))

# **Instalação do jogo:**
Requisitos:
- Allegro5
- libpqxx
- make

Primeiro, clone o repositório e entre em sua pasta raiz:

```bash
git clone https://github.com/thiago-fealves/Tux-vs-Bloatware.git
cd Tux-vs-Bloatware
```

Compilação:
* Linux:
```bash
make
```
Ou, para compilar e executar:

```bash
make && ./main
```

**Execução**
```bash
./main
```

## **Como jogar:**
### **Start:**
Pressione o botão PLAY com o botão do mouse esquerdo para começar o jogo.

### **Pause:**
Não há botão de pausa! Ao pressionar ESC, você é direcionado à tela de Game Over.

### **Menu principal:**
Para retornar ao menu principal, pressione o botão RETURN MENU.

### **Jogar novamente:**
Para jogar novamente, pressione o botão PLAY AGAIN.

### **Sair:**
Para sair do jogo, pressione o botão EXIT GAME ou o X no canto inferior esquerdo.

### **Movimentação:**
**Fase 1 e 2:**
- Pressione D para se mover para a direita ou use seta para a direita.

**Fase 3:**
- Pressione A para se mover para a esquerda ou use seta para a esquerda.
- Pressione D para se mover para a direita ou use seta para a direita.
- Pressione W para se mover para cima ou use seta para cima.
- Pressione S para se mover para baixo ou use seta para baixo.
- Pressione a barra de espaço do teclado para atirar os projéteis (combate fase 3). 

**Observação:** Você terá 3 vidas. Caso seja acertado por 3 projéteis inimigos ou encostar no chefe final… Game Over!

## **Testes**
Para compilar e executar os testes, use o comando:

```bash
make test
```
## **Documentação:**
O projeto já acompanha os arquivos Doxyfile devidamente configurados mas você pode compilar manualmente também com:
```bash
doxygen Doxyfile
```

## **Remover arquivos auxiliares:**
Para limpar os object files (.o):

```Bash
make clean
```
