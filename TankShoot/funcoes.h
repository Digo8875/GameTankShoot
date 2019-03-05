//Structs
struct tankDados
{
    int posX, posY, posX2, posY2, tamX, tamY;
    int vida;
    ALLEGRO_BITMAP *imagem;
};

struct tijoloDados
{
    int posX, posY, posX2, posY2, tamX, tamY;
    int vida;
    ALLEGRO_BITMAP *imagem;
};

struct balaCanhaoDados
{
    int posX, posY, posX2, posY2, tamX, tamY;
    ALLEGRO_BITMAP *imagem;
};



///-------------------------------------------------------------------------------------------
//Funções
void game ();
int inicializarAllegro(ALLEGRO_DISPLAY **janela, ALLEGRO_EVENT_QUEUE **fila_eventos, ALLEGRO_BITMAP **fundo);
void finalizarAllegro(ALLEGRO_DISPLAY **janela, ALLEGRO_EVENT_QUEUE **fila_eventos);
void inicializarTank(tankDados *tank);
tijoloDados *inicializarTijolo();
balaCanhaoDados *inicializarBalaCanhao(tankDados *tank);
void atualizarPosicoesX2(tankDados *tank, tijoloDados **tijolo, balaCanhaoDados **balaCanhao);
