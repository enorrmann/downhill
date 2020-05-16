#include <tiles.h>

#define TILE_WHITE 9
#define TILE_BLACK 0
//#define TILE_DIAG_UP 6
#define TILE_DIAG 6
#define TILE_DIAG_DOWN 7

#define NUM_TILES 6
#define ULTIMO_TILE NUM_TILES - 1

#define TECHO 10
#define PISO 28

s8 debug = 1;
char debug_string[32];

static void TILES_DEBUG();
static void avanzar();
static int wait();

const u32 tileDiag[8] =
    {
        0xF0000000,
        0xFF000000,
        0xFFF00000,
        0xFFFF0000,
        0xFFFFF000,
        0xFFFFFF00,
        0xFFFFFFF0,
        0xFFFFFFFF};

u8 delay = 6;
u8 delay_count = 0;
s8 direccion = D_NULL;
u8 vuelta = 0;
s8 piso = 25;
u8 rotate = 0;

u8 tiles_y[NUM_TILES];
s8 tiles_direction[NUM_TILES];
s8 tiles_shape[4];

void TILES_init()
{
    //VDP_setBackgroundColor(55);
    VDP_loadTileData((const u32 *)tileDiag, TILE_DIAG, 1, 0);
    //VDP_loadTileData((const u32 *)tileDiagDown, TILE_DIAG_DOWN, 1, 0);
    tiles_shape[0] = TILE_DIAG;  // up
    tiles_shape[1] = TILE_WHITE; // null
    tiles_shape[2] = TILE_DIAG;  // down
    tiles_shape[3] = TILE_WHITE; // right

    for (int i = 0; i < NUM_TILES; i++)
    {
        tiles_y[i] = piso;
        tiles_direction[i] = 0; //
        //VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_WHITE), i, tiles_y[i]);
    }

    tiles_y[ULTIMO_TILE] = piso;
    tiles_direction[ULTIMO_TILE] = 0;
}

void TILES_halt()
{
    direccion = D_NULL;
}
void TILES_up()
{
    direccion = D_UP;
}
void TILES_down()
{
    direccion = D_DOWN;
}
void TILES_right()
{
    if (direccion == D_SCROLL_UP)
    {
        piso++;
    }
    direccion = D_RIGHT;
}
void TILES_scroll_up()
{
    if (wait() == FALSE)
    {
        for (int i = 0; i <= ULTIMO_TILE; i++)
        {

            // pintar todo lo que este > piso, o sea mas abajo del piso
            if (tiles_y[i] >= piso && tiles_y[i] > TECHO)
            {
                tiles_direction[i] = D_SCROLL_UP;
                VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_WHITE), i, tiles_y[i]);
                tiles_y[i]--;
            }
        }
        piso = tiles_y[ULTIMO_TILE];
    }
    if (debug)
        TILES_DEBUG();
}

int wait()
{
    delay_count++;
    if (delay_count >= delay)
    {
        delay_count = 0;
        return FALSE;
    }
    return TRUE;
}
void TILES_move()
{
    if (direccion == D_NULL)
    {
        return;
    }

    if (wait() == FALSE)
    {
        if (direccion == D_UP && piso > TECHO)
        {
            piso--;
            tiles_direction[ULTIMO_TILE] = direccion; // el ultimo tile lleva la direccion actual
        }
        if (direccion == D_DOWN && piso < PISO)
        {
            piso++;
            tiles_direction[ULTIMO_TILE] = direccion; // el ultimo tile lleva la direccion actual
        }
        if (direccion == D_RIGHT)
        {
            tiles_direction[ULTIMO_TILE] = direccion; // el ultimo tile lleva la direccion actual
        }

        tiles_y[ULTIMO_TILE] = piso;

        //VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_BLACK), ULTIMO_TILE, tiles_y[ULTIMO_TILE]);
        //tiles_y[ULTIMO_TILE] = piso;
        //VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_WHITE), ULTIMO_TILE, tiles_y[ULTIMO_TILE]);
        avanzar();
        //avanzar();
    }
}
static void avanzar()
{
    // esto se ejecuta para todas los tiles de arriba
    for (int i = 0; i < ULTIMO_TILE; i++)
    {
        //if (tiles_y[i] != tiles_y[i + 1] && direccion != D_NULL)
        if (1) //if (direccion != D_NULL)
        {
            //if (tiles_y[i] < tiles_y[i + 1])            {
            // "borro" el tile de arriba
            VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_BLACK), i, tiles_y[i]);
            //}
            tiles_y[i] = tiles_y[i + 1];                 // rotata posiciones
            tiles_direction[i] = tiles_direction[i + 1]; // rotates direccion en ese momento
                                                         //VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_WHITE), i, tiles_y[i]);

            // esto se ejecuta para todas los tiles de arriba
            rotate = tiles_direction[i] == D_UP;
            VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, rotate, tiles_shape[tiles_direction[i] + 1]), i, tiles_y[i]);

            //VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, tiles_direction[i]), 5, 5);
            //VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, rotate, tiles_direction[i]), 6, 6);
        }
        if (debug)
            TILES_DEBUG();
    }
    // VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, tiles_direction[ULTIMO_TILE]), ULTIMO_TILE, tiles_y[ULTIMO_TILE]);
}
static void TILES_DEBUG()
{
    /*   char cadena1[32];
    sprintf(cadena1, "x:  %4d", x);
    VDP_drawText(cadena1, 2, 23);

    */
    VDP_drawText("x", 10, 10);

    sprintf(debug_string, "direccion %4d", direccion);
    VDP_drawText(debug_string, 20, 9);

    sprintf(debug_string, "piso %4d", piso);
    VDP_drawText(debug_string, 20, 10);

    for (int i = 0; i <= ULTIMO_TILE; i++)
    {
        sprintf(debug_string, "y,d,s %2d,%2d,%2d,%2d", i, tiles_y[i], tiles_direction[i], tiles_shape[tiles_direction[i] + 1]);
        VDP_drawText(debug_string, 20, 11 + i);
    }
}