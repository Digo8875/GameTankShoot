#include "bibliotecas.h"
#include "funcoes.h"

//Função para inicializar o tank...
void inicializarTank(tankDados *tank)
{
    tank->tamX = 36;  //Largura do Tank
    tank->tamY = 43;  //Altura do Tank

    tank->posX = 382;
    tank->posY = 557;

    tank->posX2 = tank->posX + tank->tamX;
    tank->posY2 = tank->posY + tank->tamY;

    tank->vida = 3;

    tank->imagem = al_load_bitmap("Sprites/tank/tank5.png");
};

//Função para inicializar um tijolo...
tijoloDados *inicializarTijolo()
{
    tijoloDados *tijolo = new tijoloDados;

    tijolo->tamX = 80;  //Largura do Tijolo
    tijolo->tamY = 63;  //Altura do Tijolo

    //Gerar posilçao aleatória do tijolo
    int posAleatoria;
    posAleatoria = rand() % (LARGURA_TELA - tijolo->tamY);

    tijolo->posX = posAleatoria;
    tijolo->posY = 0;

    tijolo->posX2 = tijolo->posX + tijolo->tamX;
    tijolo->posY2 = tijolo->posY + tijolo->tamY;

    tijolo->vida = 1;

    tijolo->imagem = al_load_bitmap("Sprites/tijolo/tijolo1.png");

    return tijolo;
};

//Função para inicializar um tiro...
balaCanhaoDados *inicializarBalaCanhao(tankDados *tank)
{
    balaCanhaoDados *balaCanhao = new balaCanhaoDados;

    balaCanhao->tamX = 11;  //Largura do Tijolo
    balaCanhao->tamY = 30;  //Altura do Tijolo

    balaCanhao->posX2 = ((tank->posX + tank->posX2)/2) + (balaCanhao->tamX/2) ;
    balaCanhao->posY2 = tank->posY;

    balaCanhao->posX = balaCanhao->posX2 - balaCanhao->tamX;
    balaCanhao->posY = balaCanhao->posY2 - balaCanhao->tamY;

    balaCanhao->imagem = al_load_bitmap("Sprites/balacanhao/bala1.png");

    return balaCanhao;
};
