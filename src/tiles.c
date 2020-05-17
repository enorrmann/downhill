#include <tiles.h>

#define TILE_WHITE 9
#define TILE_BLACK 0
#define TILE_DIAG 7
#define TILE_DIAG_2 7
#define TILE_DIAG_3 8

#define NUM_TILES 15
#define ULTIMO_TILE NUM_TILES - 1
#define DELAY 3
#define FACTOR 2

#define TECHO 10
#define PISO 28

s8 debug = 0;
char debug_string[32];

static void TILES_DEBUG();
static void avanzar();
static int wait();
static void ajustar_piso();
static void TILES_do_scroll_up();

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

const u32 tileDiag2[8] =
    {
        0xFF000000,
        0xFFFF0000,
        0xFFFFFF00,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF,
        0xFFFFFFFF};

const u32 tileDiag3[8] =
    {
        0x00000000,
        0x00000000,
        0x00000000,
        0x00000000,
        0xFF000000,
        0xFFFF0000,
        0xFFFFFF00,
        0xFFFFFFFF};

u8 delay_count = 0;
s8 direccion = D_NULL;
s8 last_direccion = D_NULL;
u8 vuelta = 0;
s8 piso = PISO;
u8 rotate = 0;
u8 tiles_offset = 0;

u8 tiles_y[NUM_TILES];
s8 tiles_direction[NUM_TILES];
s8 tiles_shape[4];
s8 tiles_next_shape[4];

void TILES_init()
{
    //VDP_setBackgroundColor(55);
    VDP_loadTileData((const u32 *)tileDiag, TILE_DIAG, 1, 0);
    VDP_loadTileData((const u32 *)tileDiag2, TILE_DIAG_2, 1, 0);
    VDP_loadTileData((const u32 *)tileDiag3, TILE_DIAG_3, 1, 0);
    //VDP_loadTileData((const u32 *)tileDiagDown, TILE_DIAG_DOWN, 1, 0);
    tiles_shape[0] = TILE_DIAG;  // up
    tiles_shape[1] = TILE_WHITE; // null
    tiles_shape[2] = TILE_DIAG;  // down
    tiles_shape[3] = TILE_WHITE; // right
    tiles_shape[4] = TILE_WHITE; // SCROLL_UP

    tiles_next_shape[0] = TILE_DIAG_3; // up
    tiles_next_shape[1] = TILE_WHITE;  // null
    tiles_next_shape[2] = TILE_DIAG_3; // down

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
    direccion = D_RIGHT;
}

void TILES_scroll_up()
{
    direccion = D_SCROLL_UP;
}
static void TILES_do_scroll_up()
{
    last_direccion = D_SCROLL_UP;

    for (int i = 0; i <= ULTIMO_TILE; i++)
    {
        // pintar todo lo que este > piso, o sea mas abajo del piso
        if (tiles_y[i] >= piso && tiles_y[i] >= TECHO)
        {
            // LA DIRECCION DETERMINA EL SHAPE
            tiles_direction[i] = D_SCROLL_UP;
            VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_WHITE), i, tiles_y[i]);
            tiles_y[i]--;
        }
    }
    piso = tiles_y[ULTIMO_TILE];

    if (debug)
        TILES_DEBUG();
}

int wait()
{
    delay_count++;
    if (delay_count >= DELAY)
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

        if (direccion == D_SCROLL_UP)
        {
            TILES_do_scroll_up();
            return;
        }

        ajustar_piso();
        avanzar();
    }
}

// se ejecuta cada frames / delay veces
static void avanzar()
{
    tiles_offset++;
    if (tiles_offset > 1)
    {
        tiles_offset = 0;
    }
    // esto se ejecuta para todas los tiles de arriba
    for (int i = 0; i < ULTIMO_TILE; i++)
    {
        // aca puedor ir variando el punto x de inicio, una vuelta x, una vuetla x+1
        int x = i * FACTOR + tiles_offset;

        //if (tiles_y[i] != tiles_y[i + 1] && direccion != D_NULL)
        //        if (1) //if (direccion != D_NULL)
        //      {

        // "borro" el tile de arriba si va para abajo, sino, blanco abajo
        if (tiles_y[i] < tiles_y[i + 1])
        {
            VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_BLACK), x, tiles_y[i]);
            VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_BLACK), x, tiles_y[i]-1);
            //VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_BLACK), x, tiles_y[i]+1);
        }
        else
        {
            VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_WHITE), x, tiles_y[i]);
        }
        tiles_y[i] = tiles_y[i + 1];                 // rotata posiciones
        tiles_direction[i] = tiles_direction[i + 1]; // rotates direccion en ese momento
                                                     //VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 0, TILE_WHITE), i, tiles_y[i]);

        // ESTE ES EL QUE DIBUJA EL KEY TILE, O SEA EL TILE QUE MANDA
        // esto se ejecuta para todas los tiles de arriba
        rotate = tiles_direction[i] == D_UP;
        //rotate = 0 ;
        VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, rotate, tiles_shape[tiles_direction[i] + 1]), x, tiles_y[i]);

        //int inter_x = x + 1 * direccion;
        // tile de interpolado
        //VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, rotate, tiles_next_shape[tiles_direction[i] + 1]), x+1, tiles_y[i] + 1*direccion);
        //  }
        if (debug)
            TILES_DEBUG();
    }
}

static void ajustar_piso()
{

    if (direccion == D_UP && piso > TECHO)
    {
        piso--;
    }

    if (direccion == D_DOWN && last_direccion != D_RIGHT && piso < PISO)
    {
        piso++;
    }

    // si la direccion anterior era scroll, acomodar el piso
    if (last_direccion == D_SCROLL_UP)
    {
        piso++;
        if (piso < TECHO)
            piso = TECHO;
    }
    if (direccion == D_RIGHT && last_direccion == D_DOWN)
    {
        piso++;
    }

    last_direccion = direccion;
    tiles_y[ULTIMO_TILE] = piso;
    tiles_direction[ULTIMO_TILE] = direccion; // el ultimo tile lleva la direccion actual
}
static void TILES_DEBUG()
{
    /*   char cadena1[32];
    sprintf(cadena1, "x:  %4d", x);
    VDP_drawText(cadena1, 2, 23);

    */
    VDP_drawText("x", 10, 10);

    sprintf(debug_string, "last_direccion %4d", last_direccion);
    VDP_drawText(debug_string, 20, 9);

    sprintf(debug_string, "direccion %4d", direccion);
    VDP_drawText(debug_string, 20, 10);

    for (int i = 0; i <= ULTIMO_TILE; i++)
    {
        sprintf(debug_string, "y,d,s %2d,%2d,%2d,%2d", i, tiles_y[i], tiles_direction[i], tiles_shape[tiles_direction[i] + 1]);
        VDP_drawText(debug_string, 20, 11 + i);
    }
}