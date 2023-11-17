#pragma once

struct Slime {
    float X;
    float Y;
    float speed;
    float dirX;
    float dirY;
    float angle;
    int size;
};

void Purpleslime_move(list_PurpleSlime, nb_PurpleSlime);
void Purpleslime_spawn(list_PurpleSlime, nb_PurpleSlime, size, posX, posY);
void PurpleSlimecol(list_PurpleSlime, player, arrow, nb_PurpleSlime, hp);