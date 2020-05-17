#include <genesis.h>
#include <tiles.h>
#include <sprites.h>

static void MAIN_DEBUG();
static void handleInput();
static void movePlayer(int yInTiles);
int offset = 0;
int player_x = 0;
Sprite *player;

int main()
{

    VDP_setScreenWidth320();
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    SPR_init(0, 0, 0);
    player = SPR_addSprite(&klonoa, 100, 100, TILE_ATTR(PAL1, 0, FALSE, FALSE));
    VDP_setPalette(PAL1, klonoa.palette->data);

    TILES_init();
    //VDP_setTextPlan(PLAN_B);
    while (TRUE)
    {
        /*offset++;

        if (offset == 512)
        {
            offset = 0;
        }*/
        //VDP_setHorizontalScroll(PLAN_A, -offset);
        //VDP_showFPS(TRUE);
        VDP_showCPULoad();
        handleInput();
        player_x = TILES_move();
        movePlayer(player_x);
        SPR_update();
        //TEST_main();
        MAIN_DEBUG();
        VDP_waitVSync();
    }

    return 0;
}

static void handleInput()
{
    //variable donde se guarda la entrada del mando
    u16 value = JOY_readJoypad(JOY_1);

    TILES_halt();
    if (value & BUTTON_UP)
    {
        TILES_up();
    }
    if (value & BUTTON_DOWN)
    {
        TILES_down();
    }
    if (value & BUTTON_RIGHT)
    {
        TILES_right();
    }
    if (value & BUTTON_A)
    {
        TILES_scroll_up();
    }
}

static void MAIN_DEBUG()
{
    char debug_string[32];
    sprintf(debug_string, "player_x %4d", player_x);
    VDP_drawText(debug_string, 20, 9);
}

static void movePlayer(int yInTiles)
{
    SPR_setPosition(player, 60, yInTiles * 8 - 30 );
}