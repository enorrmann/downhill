#ifndef _FLOOR_H_
#define _FLOOR_H_

#include <genesis.h>
#include <sprites.h>

typedef struct _FloorBlock
{
    u8 x;
    u8 y;
    u8 offset_x;
    u8 offset_y;
    struct _Sprite *sprite_1;
    struct _Sprite *sprite_2;
} FloorBlock;

void floor_init();
void move_block();
//static void pinta_posicion();

#endif