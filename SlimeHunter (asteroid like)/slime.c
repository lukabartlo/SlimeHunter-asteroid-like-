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

void Purpleslime_move(struct Slime list_Slime[], int nb_Slime) {
    for (int i = 0; i < nb_Slime; i++) {
        if (list_Slime[i].size != 0) {
            list_Slime[i].dirX = cosf(list_Slime[i].angle * 3.1415f / 180.0f);
            list_Slime[i].dirY = sinf(list_Slime[i].angle * 3.1415f / 180.0f);
            if (list_Slime[i].size == 3) {
                list_Slime[i].speed = (rand() % 3 + 2);
            }
            else if (list_Slime[i].size == 2) {
                list_Slime[i].speed = (rand() % 3 + 3);
            }
            else if (list_Slime[i].size == 1) {
                list_Slime[i].speed = (rand() % 3 + 4);
            }
            list_Slime[i].X += list_Slime[i].dirX * list_Slime[i].speed;
            list_Slime[i].Y += list_Slime[i].dirY * list_Slime[i].speed;
        }
    }
}

void Purpleslime_spawn(struct Slime list_Slime[], int nb_Slime, int size, int posX, int posY) {
    for (int i = 0; i < nb_Slime ; i++) {
        if (list_Slime[i].size == 0) {
            if (posX == 0 && posY == 0) {
                list_Slime[i].X = rand() % 1000;
                list_Slime[i].Y = rand() % 1000;
            }
            else {
                list_Slime[i].X = posX;
                list_Slime[i].Y = posY;
            }
            list_Slime[i].angle = rand() % 360;
            list_Slime[i].size = size;
            return;
        }
    }
}

void PurpleSlimecol(struct Slime list_Slime[], struct Player* player, struct Arrow* arrow, int nb_Slime, int* hp, int* points) {
    for (int i = 0; i < nb_Slime; i++) {
        if (list_Slime[i].size != 0) {
            if (list_Slime[i].size == 3) {
                if (abs(player->X - list_Slime[i].X) < 75 && abs(player -> Y - list_Slime[i].Y) < 50) {
                    player -> X = 500;
                    player -> Y = 500;
                    *hp -= 1;
                }
                if (abs(arrow->X - list_Slime[i].X) < 100 && abs(arrow -> Y - list_Slime[i].Y) < 75) {
                    arrow -> lifespan = 50;
                    Purpleslime_spawn(list_Slime, nb_Slime, list_Slime[i].size - 1, list_Slime[i].X, list_Slime[i].Y);
                    Purpleslime_spawn(list_Slime, nb_Slime, list_Slime[i].size - 1, list_Slime[i].X, list_Slime[i].Y);
                    list_Slime[i].size = 0;
                    *points += 25;

                }
            }
            else if (list_Slime[i].size == 2) {
                if (abs(player -> X - list_Slime[i].X) < 34.5f && abs(player -> Y - list_Slime[i].Y) < 25) {
                    player -> X = 500;
                    player -> Y = 500;
                    *hp -= 1;
                }
                if (abs(arrow -> X - list_Slime[i].X) < 50 && abs(arrow -> Y - list_Slime[i].Y) < 34.5f) {
                    arrow -> lifespan = 50;
                    Purpleslime_spawn(list_Slime, nb_Slime, list_Slime[i].size - 1, list_Slime[i].X, list_Slime[i].Y);
                    Purpleslime_spawn(list_Slime, nb_Slime, list_Slime[i].size - 1, list_Slime[i].X, list_Slime[i].Y);
                    list_Slime[i].size = 0;
                    *points += 50;
                }
            }
            else if (list_Slime[i].size == 1) {
                if (abs(player -> X - list_Slime[i].X) < 17.25f && abs(player -> Y - list_Slime[i].Y) < 25) {
                    player -> X = 500;
                    player -> Y = 500;
                    *hp -= 1;
                }
                if (abs(arrow->X - list_Slime[i].X) < 25 && abs(arrow -> Y - list_Slime[i].Y) < 17.25f) {
                    arrow -> lifespan = 50;
                    list_Slime[i].size = 0;
                    *points += 100;
                }
            }
        }
    }
}