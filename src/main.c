#include <genesis.h>
#include <tiles.h>

int main()
{

    VDP_setScreenWidth320();
    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    //SPR_init(0, 0, 0);
    //floor_init();
    TILES_init();
    VDP_setTextPlan(PLAN_B);
    int speed = 1;
    int offset = 0;
    while (TRUE)
    {
        offset += speed;
        if (offset >= 512)
        {
            offset = 0;
        }

        //VDP_setHorizontalScroll(PLAN_A, -offset);
        VDP_showFPS(TRUE);
        //SPR_update();
        TILES_move();
        VDP_waitVSync();
    }

    return 0;
}
