#include <tiles.h>

#define TILE_WHITE 15
#define TILE_BLACK 1
#define D_UP -1
#define D_DOWN 1
#define NUM_BARS 20
#define BAR_SPACING 2


static void pinta_posicion(Bar *aBar);
static void TILE_move(Bar *aBar);

u8 delay = 8;
u8 delay_count = 0;

Bar bars[NUM_BARS];

void TILES_init()
{
    int initial_x = 0;
    int initial_travel = 4;

    for (int i = 0; i < NUM_BARS; i++)
    {
        if (initial_travel > 9)
        {
            initial_travel = 5;
        }
        bars[i].tile_direction = D_DOWN;
        bars[i].x = (initial_x++) * BAR_SPACING;
        bars[i].y = 20;
        bars[i].tile_y = 10;
        bars[i].tile_y_travel = initial_travel++;
    }
}
void TILES_move()
{
    if (delay_count == delay)
    {
        delay_count = 0;
        for (int i = 0; i < NUM_BARS; i++)
        {
            TILE_move(&bars[i]);
        }
    }
    else
    {
        delay_count++;
    }
}
static void TILE_move(Bar *aBar)
{
    if (aBar->tile_direction == D_DOWN)
    {
        if (aBar->tile_y < aBar->y)
        {
            VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_BLACK), aBar->x, aBar->tile_y);
            aBar->tile_y++;
        }
        else
        {
            aBar->tile_y--;
            aBar->tile_direction = D_UP;
        }
    }
    else // going UP
    {
        if (aBar->tile_y >= (aBar->y - aBar->tile_y_travel))
        {
            aBar->tile_y--;
        }
        else
        {
            VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, TILE_BLACK), aBar->x, aBar->tile_y);
            aBar->tile_y++;
            aBar->tile_direction = D_DOWN;
        }
    }

    VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL1, 1, 0, 0, TILE_WHITE), aBar->x, aBar->tile_y);

    // pinta_posicion(aBar);
}
static void pinta_posicion(Bar *aBar)
{
    //declaramos una cadena de caracteres
    //sprintf : pasa un valor numerico(posx / posy) a caracteres y los copia
    //en la cadena anterior. %4d alinea a la derecha, importante para al pasar
    //de numeros negativos a positivos todo salga correctamente

    char cadena1[32];
    sprintf(cadena1, "y:  %4d", aBar->tile_y);
    VDP_drawText(cadena1, 2, 23);

    char cadena2[32];
    sprintf(cadena2, "direccion:  %4d", aBar->tile_direction);
    VDP_drawText(cadena2, 2, 24);
}