#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <math.h>
#include "arrow.h"
#include "player.h"

void shoot(struct Arrow* arrow, struct Player* player) {

    if (sfKeyboard_isKeyPressed(sfKeySpace) && arrow -> lifespan == 0) {
        arrow -> X = player -> X;
        arrow -> Y = player -> Y;
        arrow -> dirX = cosf(player -> angle * 3.1415f / 180.0f);
        arrow -> dirY = sinf(player -> angle * 3.1415f / 180.0f);
        arrow -> angle = player -> angle;
        arrow -> lifespan = 1;
    }

    if (arrow -> lifespan > 0) {
        arrow -> X += arrow -> dirX * arrow -> speed ;
        arrow -> Y += arrow -> dirY * arrow -> speed ;
        arrow -> lifespan += 1;
    }

    if (arrow -> lifespan >= 50) {
        arrow -> lifespan = 0;
        arrow -> X = 0;
        arrow -> Y = 0;
    }
}