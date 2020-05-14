#include <genesis.h>
#define D_UP -1
#define D_DOWN 1

typedef struct _Bar
{
    u8 x;
    u8 y;

    u8 tile_y;
    u8 tile_y_travel;
    s8 tile_direction;

} Bar;

void TILES_init();
void TILES_move();
