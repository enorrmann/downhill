#include <genesis.h>
#include <tiles.h>
#include <test.h>

static void handleInput();

int main()
{

    VDP_setScreenWidth320();
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    //SPR_init(0, 0, 0);
    //floor_init();

    TILES_init();
    //VDP_setTextPlan(PLAN_B);
    while (TRUE)
    {

        //VDP_setHorizontalScroll(PLAN_A, -offset);
        //VDP_showFPS(TRUE);
        VDP_showCPULoad();
        //SPR_update();
        handleInput();
        TILES_move();
        //TEST_main();
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