#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <math.h>
#include "player.h"

void player_move(struct Player* player) {

    if (sfKeyboard_isKeyPressed(sfKeyUp) || sfKeyboard_isKeyPressed(sfKeyZ)) {
        if (player -> speed < 8) {
            player -> speed += 0.25;
        }
        player -> dirX = cosf(player -> angle * 3.1415f / 180.0f);
        player -> dirY = sinf(player -> angle * 3.1415f / 180.0f);
        player -> Y += player -> speed * player -> dirY;
        player -> X += player -> speed * player -> dirX;
    }

    else if (player -> speed != 0) {
        player -> speed *= 0.98;
        player -> Y += player -> speed * player -> dirY;
        player -> X += player -> speed * player -> dirX;
    }

    if (sfKeyboard_isKeyPressed(sfKeyRight) || sfKeyboard_isKeyPressed(sfKeyD)) {
        player -> angle += 5;
    }

    if (sfKeyboard_isKeyPressed(sfKeyLeft) || sfKeyboard_isKeyPressed(sfKeyQ)) {
        player -> angle -= 5;
    }
}