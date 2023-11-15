#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <math.h>
#include "slime.h"
#include "player.h"
#include "arrow.h"

void Purpleslime_move(struct Slime list_PurpleSlime[], int nb_PurpleSlime) {
    for (int i = 0; i < nb_PurpleSlime; i++) {
        list_PurpleSlime[i].dirX = cosf(list_PurpleSlime[i].angle * 3.1415f / 180.0f);
        list_PurpleSlime[i].dirY = sinf(list_PurpleSlime[i].angle * 3.1415f / 180.0f);
        list_PurpleSlime[i].speed = (rand() % 1 + 3);
        list_PurpleSlime[i].X += list_PurpleSlime[i].dirX * list_PurpleSlime[i].speed;
        list_PurpleSlime[i].Y += list_PurpleSlime[i].dirY * list_PurpleSlime[i].speed;
    }
}

void Purpleslime_spawn(struct Slime list_PurpleSlime[], int nb_PurpleSlime) {
    for (int i = 0; i < nb_PurpleSlime; i++) {
        list_PurpleSlime[i].X = rand() % 1000;
        list_PurpleSlime[i].Y = rand() % 1000;
        list_PurpleSlime[i].angle = rand() % 360;
    }
}

void PurpleSlimecol(struct Slime list_PurpleSlime[], struct Player player, struct Arrow* arrow, int nb_PurpleSlime, int* hp) {
    for (int i = 0; i < nb_PurpleSlime; 0) {
        if (abs(player.X - list_PurpleSlime[i].X) < 75 && abs(player.Y - list_PurpleSlime[i].Y) < 50) {
            player.X = 500;
            player.Y = 500;
            hp -= 1;
        }
        if (abs(arrow -> X - list_PurpleSlime[i].X) < 100 && abs(arrow -> Y - list_PurpleSlime[i].Y) < 75) {
            arrow -> lifespan = 50;
        }
    }
}