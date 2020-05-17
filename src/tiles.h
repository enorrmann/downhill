#include <genesis.h>
#define D_UP -1
#define D_NULL 0
#define D_DOWN 1
#define D_RIGHT 2
#define D_SCROLL_UP 3

typedef struct _Bar
{
    u8 x;
    u8 y;

    u8 tile_y;
    u8 tile_y_travel;
    s8 tile_direction;

} Bar;

void TILES_init();
int TILES_move();
void TILES_up();
void TILES_down();
void TILES_halt();
void TILES_right();
void TILES_scroll_up();