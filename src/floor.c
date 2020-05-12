#include <floor.h>

int speed = 1;
FloorBlock block;
FloorBlock block_plain;

static void block_plain_init();

void floor_init()
{

    VDP_setPalette(PAL1, ramp.palette->data);

    block_plain_init();

    block.x = 0;
    block.y = 0;
    block.offset_x = 8;
    block.offset_y = 8;

    //Crea sprites
    block.sprite_1 = SPR_addSprite(&ramp, 0, 0, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
    block.sprite_2 = SPR_addSprite(&ramp, 0, 0, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));

    move_block(&block_plain);
    move_block(&block);
}

void move_block(FloorBlock *fb)
{

    //block.x++;
    if (fb->x == 512)
    {
        fb->x = 0;
    }
    //block.y++;
    SPR_setPosition(fb->sprite_1, fb->x, fb->y);
    SPR_setPosition(fb->sprite_2, fb->x + fb->offset_x, fb->y + fb->offset_y);
    //pinta_posicion();
}

/*void pinta_posicion()
{
    char cadena1[32];
    sprintf(cadena1, "x:  %4d", block.x);
    VDP_drawText(cadena1, 2, 23);

    char cadena2[32];
    sprintf(cadena2, "y:  %4d", block.y);
    VDP_drawText(cadena2, 2, 24);
}*/

static void block_plain_init()
{
    block_plain.x = 150;
    block_plain.y = 150;
    block_plain.offset_x = 16;
    block_plain.offset_y = 16;

    block_plain.sprite_1 = SPR_addSprite(&plain, 0, 0, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
    block_plain.sprite_2 = SPR_addSprite(&plain, 0, 0, TILE_ATTR(PAL1, TRUE, FALSE, FALSE));
}