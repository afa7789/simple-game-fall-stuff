

# Magic Journey Throught Nothing

## Descrição

![alt text](https://github.com/afa7789/simple-game-fall-stuff/master/printGame1.png)

Magic Journey é apenas um jogo simples, de desviar de objetos que caem de cima, foi feito em .c e opengl, com algumas outras blibiotecas como soil e etc. E foi a primeira experiência complicada que tive de programação. Obviamente é um programa sem muita documentação, e com escopo reduzido

## Pré Requisitos

- opengl
- soil
- etc

## Rodando o Jogo 

como Rodar o Jogo no windows:

`gcc tp1_teste4.c -o tp4 -D FREEGLUT_STATIC -lSOIL -lfreeglut_static -lopengl32 -lwinmm -lgdi32 -Wl,--subsystem,windows`

como rodar o jogo no linux:

`ainda não o fiz`

## Commandos do Jogo:

p > o jogo é pausado.

r clicado duas vezes >  o jogo é reiniciado.

esc > uma vez o jogo é desligado.

TECLA S >> aumenta dificuldade colocando mais quadrados a cair. (Growth Hack)

## Como Jogar: 

Desvie de tudo, vai morrer quando ser acertado depois de X vezes.

### Observação :

Na pasta imagens de fundo estão as imagens que eu teria usado no fundo mas como ficou muito ruim e travando a movimentação do meu carinha retirei.

Tem o Tp4-teste que foi uma das implementações (não a ultima de teste de fundo) que eu tentei implementar um ambiente de fundo no jogo. Não funcionou e a minha tese do porque é que a placa de vido integrada e o processador do computador que usei para programar eram muito fracas e dessa forma não conseguem processar a mudança conforme era necessária p/ obter o efeito desejado ruim.

O tp4-teste e reespectivamente o tp4 que é o exe tem um 500x500. E estava realmente desagradavel de jogar em meu computador.

Portanto o JOGO.exe e a versãofinal.c foram as versões que eu resolvi enviar.
