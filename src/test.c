#include <genesis.h>

#define MI_TILE 1
#define MI_TILE_2 2

const u32 tile[8] =
    {
        0x44444421,
        0x44442211,
        0x44422110,
        0x44221100,
        0x42211000,
        0x42110000,
        0x21100000,
        0x11000000};

const u32 tile2[8] =
    {
        0x44444421,
        0xFFFFFFFF,
        0x44422110,
        0xFFFFFFFF,
        0x42211000,
        0xFFFFFFFF,
        0x21100000,
        0x11000000};

u8 tiles_array[5];
static int wait();
static void init();
u8 counter = 0;
int vuelta_test = 0;

static int wait()
{
    if (counter == 0)
    {
        init();
    }
    counter++;
    if (counter == 60)
    {
        counter = 1;
        return FALSE;
    }
    return TRUE;
}

void init()
{
    tiles_array[0] = MI_TILE;
    tiles_array[1] = MI_TILE_2;
    VDP_loadTileData((const u32 *)tile, MI_TILE, 1, 0);
    VDP_loadTileData((const u32 *)tile2, MI_TILE_2, 1, 0);
}
void TEST_main()
{

    if (wait())
    {
        return;
    }

    VDP_setTileMapXY(PLAN_A, tiles_array[vuelta_test], 1, 5);

    //Dibuja el tile usando TILE_ATTR_FULL()
    //primer parámetro: paleta. PAL2 = paleta de verdes
    //segund parámetro: prioridad. 0 = baja prioridad
    //tercer parámetro: volteo vertical. 1 = vflip
    //cuarto parámetro: volteo horizon. 0 = no hflip
    //quinto parámetro: tile referenciado.
    VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL2, 0, 0, 0, tiles_array[vuelta_test]), 3, 5);

    //Dibuja 2 veces el tile, la primera vez en el plano B con pal 0 (grises)
    //la segunda en el plano A con pal1 (rojos),
    VDP_setTileMapXY(PLAN_B, TILE_ATTR_FULL(PAL0, 0, 0, 0, tiles_array[vuelta_test]), 5, 5);
    VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, tiles_array[vuelta_test]), 5, 5);

    //Dibuja 2 veces el tile, igual que antes pero el tile del plano B con alta prioridad
    VDP_setTileMapXY(PLAN_B, TILE_ATTR_FULL(PAL0, 1, 0, 0, tiles_array[vuelta_test-1]), 7, 5);
    VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL1, 0, 0, 0, tiles_array[vuelta_test]), 7, 5);

    //dibuja la tile volteada horizontalmente, verticalmente y luego ambas a la vez
    VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 0, 1, tiles_array[vuelta_test]), 3, 8);
    VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 1, 0, tiles_array[vuelta_test-1]), 5, 8);
    VDP_setTileMapXY(PLAN_A, TILE_ATTR_FULL(PAL0, 1, 1, 1, tiles_array[vuelta_test]), 7, 8);

    vuelta_test++;
    if (vuelta_test > 2)
    {
        vuelta_test = 0;
    }

    
}