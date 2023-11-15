#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <math.h>
#include "arrow.h"
#include "player.h"

void shoot(struct Arrow* arrow, struct Player player) {

    if (sfKeyboard_isKeyPressed(sfKeySpace) && arrow -> bullet == 1) {
        arrow -> X = player.X;
        arrow -> Y = player.Y;
        arrow -> dirX = cosf(player.angle * 3.1415f / 180.0f);
        arrow -> dirY = sinf(player.angle * 3.1415f / 180.0f);
        arrow -> angle = player.angle;
        arrow -> lifespan = 0;
        arrow -> bullet = 1;
    }

    if (arrow -> lifespan > 0) {
        arrow -> X += arrow -> speed * arrow -> dirX;
        arrow -> Y += arrow -> speed * arrow -> dirY;
        arrow -> lifespan += 1;
    }

    if (arrow -> lifespan >= 50) {
        arrow -> bullet = 1;
        arrow -> lifespan = 0;
        arrow -> X = 1050;
        arrow -> X = 1050;
    }
}