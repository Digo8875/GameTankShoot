#include "bibliotecas.h"
#include "funcoes.h"

//Jogo...
void game ()
{
    //Variáreis Allegro
    ALLEGRO_DISPLAY *janela = NULL;
    ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
    ALLEGRO_BITMAP *fundo = NULL;
    ALLEGRO_BITMAP *auxImagem = NULL;

    int finaliza = 0;   //Variável responsável pelo jogo rodar ou não
    int tecla;

    //Função para inicializar o Allegro. Se algo não inicializar, o jogo não roda...
    finaliza = inicializarAllegro(&janela, &fila_eventos, &fundo);

    //Variáveis do jogo...(player... itens...)
    tankDados *tank = new tankDados;
    tijoloDados *tijolo[QUANTIA_DE_TIJOLO];
    for(int i=0 ; i<QUANTIA_DE_TIJOLO ; i++)
        tijolo[i] = NULL;
    balaCanhaoDados *balaCanhao[QUANTIA_DE_TIROS];
    for (int i=0 ; i<QUANTIA_DE_TIROS ; i++)
        balaCanhao[i] = NULL;

    //Inicializar o tank...
    inicializarTank(tank);

    //While para o loop do game
    while(finaliza != 1)
    {
        //Desenha o fundo...
        al_draw_bitmap(fundo, 0, 0, 0);
        //Desenha o Tank
        al_draw_bitmap(tank->imagem, tank->posX, tank->posY, 0);
        //For para inicializar e desenhar os tijolos
        for(int i=0 ; i<QUANTIA_DE_TIJOLO ; i++)
        {
            if(tijolo[i] == NULL)
                tijolo[i] = inicializarTijolo();

            if(tijolo[i] != NULL);
                al_draw_bitmap(tijolo[i]->imagem, tijolo[i]->posX, tijolo[i]->posY, 0);
        };

        for(int i=0 ; i<QUANTIA_DE_TIROS ; i++)
            if(balaCanhao[i] != NULL)
                al_draw_bitmap(balaCanhao[i]->imagem, balaCanhao[i]->posX, balaCanhao[i]->posY, 0);

        //Atualiza a tela...
        al_flip_display();

        while(!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);

            //IF e estrutura para saber se houve algum evento...
            if (evento.type == ALLEGRO_EVENT_KEY_DOWN) //Evento de tecla pressionada
            {
                switch(evento.keyboard.keycode)
                {
                    case ALLEGRO_KEY_UP:
                        tecla = SETA_CIMA;
                    break;
                    case ALLEGRO_KEY_DOWN:
                        tecla = SETA_BAIXO;
                    break;
                    case ALLEGRO_KEY_LEFT:
                        tecla = SETA_ESQUERDA;
                    break;
                    case ALLEGRO_KEY_RIGHT:
                        tecla = SETA_DIREITA;
                    break;
                    case ALLEGRO_KEY_Z:
                        tecla = 20;
                    break;
                    case ALLEGRO_KEY_ESCAPE:
                        finaliza = 1;
                    break;
                };
            }
            else if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE) //Evento de tela fechada
            {
                finaliza = 1;
            };
        };

        //IF para ver se tecla foi pesionada pelo player e decidir a ação...
        if(tecla)
        {
            switch(tecla)
            {
                case SETA_CIMA:

                break;

                case SETA_BAIXO:

                break;

                case SETA_ESQUERDA:
                    if(tank->posX - 40 > 0)
                        tank->posX -= 40;
                    else
                        tank->posX = 0;

                    //Atualizar posição x2,y2 do TANK quando andar
                    tank->posX2 = tank->posX + tank->tamX;
                    tank->posY2 = tank->posY + tank->tamY;
                break;

                case SETA_DIREITA:
                    if(tank->posX2 + 40 < LARGURA_TELA)
                        tank->posX += 40;
                    else
                        tank->posX = LARGURA_TELA - tank->tamX;

                    //Atualizar posição x2,y2 do TANK quando andar
                    tank->posX2 = tank->posX + tank->tamX;
                    tank->posY2 = tank->posY + tank->tamY;
                break;

                //Se player apertar 'Z' , cria um tiro
                case TECLA_Z:
                    for(int i=0 ; i<QUANTIA_DE_TIROS ; i++)
                    {
                        if(balaCanhao[i] == NULL)
                        {
                            balaCanhao[i] = inicializarBalaCanhao(tank);
                            printf("\nPOS CANHAO > %d",i);
                            break;
                        };
                    };
                break;
            };
            tecla = 0; //Zerar a tecla para não ficar sempre entrando no IF()
        };

            //Filtrar para ver se não tem colisão de nada... (TIJOLO - TANK)
            for(int i=0 ; i<QUANTIA_DE_TIJOLO ; i++)
            {
                if(tijolo[i] != NULL)
                {
                    if(tijolo[i]->posY2 >= tank->posY) //Se Y do tijolo for igual ou menor que o Y do Tank
                    {
                        if(!((tijolo[i]->posX > tank->posX2) || (tijolo[i]->posX2 < tank->posX))) // Se os X's do tijolo baterem com os X's do Tank
                        {
                            delete tijolo[i];
                            tijolo[i] = NULL;
                            tank->vida --;
                        };
                    };
                };
            };

            //Filtrar para ver se não tem colisão de nada... (TIJOLO - TIRO)
            for(int i=0 ; i<QUANTIA_DE_TIJOLO ; i++)
            {
                    for(int j=0 ; j<QUANTIA_DE_TIROS ; j++)
                    {
                        if(tijolo[i] != NULL && balaCanhao[j] != NULL)
                        {
                            if((!(tijolo[i]->posY2 < balaCanhao[j]->posY) && !(tijolo[i]->posY > balaCanhao[j]->posY2))
                                && !(tijolo[i]->posX > balaCanhao[j]->posX2) && !(tijolo[i]->posX2 < balaCanhao[j]->posX)) // Se os X's do tijolo baterem com os X's do tiro
                            {
                                delete tijolo[i];
                                tijolo[i] = NULL;
                                delete balaCanhao[j];
                                balaCanhao[j] = NULL;
                            };
                        };
                    };
            };

            //Fazer tijolos se movimentarem
            for(int i=0 ; i<QUANTIA_DE_TIJOLO ; i++)
            {
                bool flagNaoDeletou = true;
                if(tijolo[i] != NULL)
                {
                    if(tijolo[i]->posY2 + MOVIMENTO_TIJOLO < 599)
                    {
                        tijolo[i]->posY += MOVIMENTO_TIJOLO;
                    }
                    else
                    {
                        delete tijolo[i];
                        tijolo[i] = NULL;
                        flagNaoDeletou = false;
                    };
                    //Atualizar posições x2,y2 do TIJOLO quando andar
                    if(flagNaoDeletou)
                    {
                        tijolo[i]->posX2 = tijolo[i]->posX + tijolo[i]->tamX;
                        tijolo[i]->posY2 = tijolo[i]->posY + tijolo[i]->tamY;
                    };
                };
            };

            //Fazer tiros se movimentarem
            for(int i=0 ; i<QUANTIA_DE_TIROS ; i++)
            {
                bool flagNaoDeletou = true;
                if(balaCanhao[i] != NULL)
                {
                    if(balaCanhao[i]->posY - MOVIMENTO_TIRO > 1)
                        balaCanhao[i]->posY -= MOVIMENTO_TIRO;
                    else
                    {
                        delete balaCanhao[i];
                        balaCanhao[i] = NULL;
                        flagNaoDeletou = false;
                    };
                    //Atualizar posições x2,y2 do TIRO quando andar
                    if(flagNaoDeletou)
                    {
                        balaCanhao[i]->posX2 = balaCanhao[i]->posX + balaCanhao[i]->tamX;
                        balaCanhao[i]->posY2 = balaCanhao[i]->posX + balaCanhao[i]->tamY;
                    };
                };
            };

        //Se Tank perder todas vidas, perde...
        if(tank->vida <= 0)
            finaliza = 1;

        //FPS... Pra não comer processador
        Sleep(100);
    };

    finalizarAllegro(&janela, &fila_eventos);
};
