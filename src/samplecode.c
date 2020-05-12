/*static void handleInput()
{
    //variable donde se guarda la entrada del mando
    u16 value = JOY_readJoypad(JOY_1);
    //si pulsamos izquierda...
    if (value & BUTTON_LEFT)
        SPR_setPosition(mi_sprite, posx -= (1 * speed), posy);
    //si pulsamos derecha...
    if (value & BUTTON_RIGHT)
        SPR_setPosition(mi_sprite, posx += (1 * speed), posy);
    //si pulsamos arriba...
    if (value & BUTTON_UP)
        SPR_setPosition(mi_sprite, posx, posy -= (1 * speed));
    //si pulsamos abajo...
    if (value & BUTTON_DOWN)
        SPR_setPosition(mi_sprite, posx, posy += (1 * speed));

    //si pulsamos A...
    if ((value & BUTTON_A))
    {
        mi_sprite = ramp_sprite_2;
        SPR_setPosition(mi_sprite, posx, posy); //necesario para q actualice al momento la TV
    }
    //si pulsamos B...
    if ((value & BUTTON_B))
    {
        mi_sprite = ramp_sprite_1;
        SPR_setPosition(mi_sprite, posx, posy);
    }
}

//Funci�m pinta_posicion() : Escribe en pantalla la posici�n del sprite
static void pinta_posicion()
{
    //declaramos una cadena de caracteres
    //sprintf : pasa un valor numerico(posx / posy) a caracteres y los copia
    //en la cadena anterior. %4d alinea a la derecha, importante para al pasar
    //de numeros negativos a positivos todo salga correctamente

    char cadena1[32];
    sprintf(cadena1, "x:  %4d", posx);
    VDP_drawText(cadena1, 2, 23);

    char cadena2[32];
    sprintf(cadena2, "y:  %4d", posy);
    VDP_drawText(cadena2, 2, 24);
}
*/