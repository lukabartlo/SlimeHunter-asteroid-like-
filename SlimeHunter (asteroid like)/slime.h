#pragma once

struct Slime {
    float X;
    float Y;
    float speed;
    float dirX;
    float dirY;
    float angle;
    sfRectangleShape* shape;
};

void Purpleslime_move(list_PurpleSlime, nb_PurpleSlime);
void Purpleslime_spawn(list_PurpleSlime, nb_PurpleSlime);
void PurpleSlimecol();