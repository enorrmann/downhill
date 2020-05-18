#include <genesis.h>
#include <tiles.h>
#include <sprites.h>

#define PAL_BG_A PAL0
#define PAL_PLAYER PAL1
#define DEBUG 0

static void MAIN_DEBUG();
static void handleInput();
static void movePlayer(int yInTiles);
int offset = 0;
int scroll = 0;

int player_x = 0;

//cuenta de tiles en VRAM
u16 ind;

Sprite *player;
Sprite *moon;

int main()
{

    VDP_setScreenWidth320();
    SPR_init(0, 0, 0);

    //backgrounds
    ind = TILE_USERINDEX;
    VDP_setPalette(PAL_BG_A, bga_image.palette->data);
    // el segundo parametro es PRIO TRUE
    VDP_drawImageEx(PLAN_B, &bga_image, TILE_ATTR_FULL(PAL_BG_A, TRUE, FALSE, FALSE, ind), 0, 0, FALSE, TRUE);
    ind += bga_image.tileset->numTile;

    //while (TRUE){};

    VDP_setScrollingMode(HSCROLL_PLANE, VSCROLL_PLANE);

    VDP_setPalette(PAL_PLAYER, klonoa.palette->data);
    player = SPR_addSprite(&klonoa, 100, 100, TILE_ATTR(PAL_PLAYER, 0, FALSE, FALSE));
    SPR_setPriorityAttribut(player, TRUE);

    moon = SPR_addSprite(&moon_image, 100, 100, TILE_ATTR(PAL_BG_A, 0, FALSE, FALSE));
    SPR_setPriorityAttribut(moon, FALSE);

    SPR_setPosition(moon, 200, 20);

    TILES_init();
    //VDP_setTextPlan(PLAN_B);
    while (TRUE)
    {
        offset++;

        if (offset == 512 || scroll == 512)
        {
            offset = 0;
        }

        if (scroll == 512)
        {

            scroll = 0;
        }

        // muevo cada 10
        if (offset % 5 == 0)
        {
            scroll++;
        }
        VDP_setHorizontalScroll(PLAN_B, -scroll);
        SPR_setPosition(moon, 230, 150 - (scroll / 6));
        //VDP_setVerticalScroll(PLAN_B, scroll);
        //VDP_showFPS(TRUE);
        handleInput();
        player_x = TILES_move();
        movePlayer(player_x);
        SPR_update();
        //TEST_main();
        if (DEBUG)
        {

            MAIN_DEBUG();
        }

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
    VDP_showCPULoad();

    char debug_string[32];
    sprintf(debug_string, "player_x %4d", player_x);
    VDP_drawText(debug_string, 20, 9);
}

static void movePlayer(int yInTiles)
{
    SPR_setAnim(player, 0);
    SPR_setPosition(player, 60, yInTiles * 8 - 30);
}