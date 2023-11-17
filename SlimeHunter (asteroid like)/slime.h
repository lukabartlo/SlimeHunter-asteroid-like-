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

void Purpleslime_move(list_Slime, nb_Slime);
void Purpleslime_spawn(list_Slime, nb_Slime, size, posX, posY);
void PurpleSlimecol(list_Slime, player, arrow, nb_Slime, hp);