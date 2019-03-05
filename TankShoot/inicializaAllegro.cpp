#include "bibliotecas.h"
#include "funcoes.h"

///+--------------------------INICIALIZAR O ALLEGRO-----------------------------------+
int inicializarAllegro(ALLEGRO_DISPLAY **janela, ALLEGRO_EVENT_QUEUE **fila_eventos, ALLEGRO_BITMAP **fundo)
{
    if (!al_init())
    {
        fprintf(stderr, "Falha ao inicializar a Allegro.\n");
        return  1;
    }

    if (!al_init_image_addon())
    {
        fprintf(stderr, "Falha ao inicializar add-on allegro_image.\n");
        return  1;
    }

    if (!al_install_keyboard())
    {
        fprintf(stderr, "Falha ao inicializar o teclado.\n");
        return  1;
    }

    *janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!*janela)
    {
        fprintf(stderr, "Falha ao criar janela.\n");
        return  1;
    }

    al_set_window_title(*janela, "Tank Shoot");

    *fila_eventos = al_create_event_queue();
    if (!*fila_eventos)
    {
        fprintf(stderr, "Falha ao criar fila de eventos.\n");
        al_destroy_display(*janela);
        return  1;
    }

    *fundo = al_load_bitmap("Sprites/horizonte.jpg");
    if (!*fundo)
    {
        fprintf(stderr, "Falha ao carregar imagem de fundo.\n");
        al_destroy_display(*janela);
        al_destroy_event_queue(*fila_eventos);
        return  1;
    }

    al_register_event_source(*fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(*fila_eventos, al_get_display_event_source(*janela));
};
///+----------------------------------------------------------------------------------+


///+--------------------------FINALIZAR O ALLEGRO-----------------------------------+
void finalizarAllegro(ALLEGRO_DISPLAY **janela, ALLEGRO_EVENT_QUEUE **fila_eventos)
{
    al_destroy_display(*janela);
    al_destroy_event_queue(*fila_eventos);
};
///+----------------------------------------------------------------------------------+
