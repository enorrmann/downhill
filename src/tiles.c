#include <tiles.h>

#define TILE_WHITE 9
#define TILE_BLACK 0

#define NUM_TILES 41
#define ULTIMO_TILE 40

static void pinta_posicion();

u8 delay = 1;
u8 delay_count = 0;
s8 direccion = D_NULL;
u8 vuelta = 0;
s8 piso = 27;
u8 x;

u8 tiles_y[NUM_TILES];

void TILES_init()
{
     VDP_setBackgroundColor(55);
    for (int i = 0; i < NUM_TILES; i++)
    {
        tiles_y[i] = piso;
        VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_WHITE), i, tiles_y[i]);
    }
    x = NUM_TILES - 1;
    tiles_y[x] = piso;
}

void TILES_move_()
{

    if (delay_count >= delay)
    {

        delay_count = 0;
        vuelta++;
        x = NUM_TILES - vuelta - 1;
        tiles_y[x] = tiles_y[x + 1];
        VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_BLACK), x, tiles_y[x - 1]);
        VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_WHITE), x, tiles_y[x + 1]);

        if (x == 5)
        {
            vuelta = 0;
            tiles_y[NUM_TILES - 1]++;
        }
        if (tiles_y[x] == 20)
        {
            vuelta = 0;
            tiles_y[NUM_TILES - 1] = 2;
        }
    }
    else
    {
        delay_count++;
    }
    pinta_posicion();
}
void TILES_halt()
{
    direccion = D_NULL;
}
void TILES_up()
{
    //if (piso > 0) piso--;
    direccion = D_UP;
}
void TILES_down()
{
    //if (piso < 27) piso++;
    direccion = D_DOWN;
}
void TILES_right()
{
    //if (piso < 27) piso++;
    direccion = D_RIGHT;
}
void TILES_move()
{
    //if (direccion == D_NULL)        return;

    if (delay_count >= delay)
    {
        delay_count = 0;

        if (direccion == D_UP || direccion == D_DOWN)
        {
            piso += direccion;
        }
        tiles_y[ULTIMO_TILE] = piso;

        //VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_BLACK), ULTIMO_TILE, tiles_y[ULTIMO_TILE]);
        //tiles_y[ULTIMO_TILE] = piso;
        //VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_WHITE), ULTIMO_TILE, tiles_y[ULTIMO_TILE]);

        for (int i = 0; i < NUM_TILES - 1; i++)
        {
            if (tiles_y[i] != tiles_y[i + 1] && direccion != D_NULL)
            {
                if (tiles_y[i] < tiles_y[i + 1])
                {
                    VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_BLACK), i, tiles_y[i]);
                }
                tiles_y[i] = tiles_y[i + 1];
                VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_WHITE), i, tiles_y[i]);
            }
        }
    }
    else
    {
        delay_count++;
    }
    //pinta_posicion();
}
static void pinta_posicion()
{
    char cadena1[32];
    sprintf(cadena1, "x:  %4d", x);
    VDP_drawText(cadena1, 2, 23);

    char cadena2[32];
    sprintf(cadena2, "tiles_y[x]:  %4d", tiles_y[x]);
    VDP_drawText(cadena2, 2, 24);

    sprintf(cadena2, "piso:  %4d", piso);
    VDP_drawText(cadena2, 2, 25);
}