#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SFML/Window.h>
#include <SFML/Graphics.h>
#include <SFML/System.h>
#include <math.h>
#include "player.h"
#include "slime.h"
#include "arrow.h"
#define nb_PurpleSlime 6

struct Player player = { .X = 500, .Y = 500, .speed = 0, .dirX = 0, .dirY = 0, .angle = -90 };
struct Arrow arrow = { .X = 1050, .Y = 1005, .speed = 10, .dirX = 0, .dirY = 0, .angle = 0, .lifespan = 0, .bullet = 1 };
struct Slime list_purpleSlime[nb_PurpleSlime];

int points = 0;

int delta = 0;

int hp = 3;

//bool player_dead = false;

sfClock* deltaClock;

sfFont* font1;
sfText* text_score;

sfRenderWindow* window;

sfCircleShape* shape;               //shape Bow
sfRectangleShape* shape2[6];        //shape PurpleSlime
sfRectangleShape* shape3;           //shape Arrow
/*sfRectangleShape* shape4;         //shape BlueSlime
sfRectangleShape* shape5;*/         //shape GreenSlime
sfRectangleShape* shape6[3];        //shape Heart

sfSprite* sprite;                   //Sprite Map
//sfSprite* sprite2;                  //Sprite GameOver

sfTexture* texture;                 //Texture Bow
sfTexture* texture2;                //Texture PurpleSlime
sfTexture* texture3;                //Texture Arrow
/*sfTexture* texture4;              //Texture BlueSlime
sfTexture* texture5;*/              //Texture GreenSlime
sfTexture* texture6;                //Texture Map
sfTexture* texture7;                //Texture Heart
//sfTexture* texture8;              //Texture GameOver

void create() {

    sfVideoMode mode = { 1000, 1000, 32 };
    window = sfRenderWindow_create(mode, "SlimeHunter", sfResize | sfClose, 0);
    sfRenderWindow_setFramerateLimit(window, 60);

    deltaClock = sfClock_create();

    text_score = sfText_create();

    shape = sfCircleShape_create();
    shape3 = sfRectangleShape_create();

    font1 = sfFont_createFromFile("pixeltext.ttf");

    sprite = sfSprite_create();

    texture = sfTexture_createFromFile("Arc.png", 0);
    texture2 = sfTexture_createFromFile("SlimeViolet.png", 0);
    texture3 = sfTexture_createFromFile("Arrow.png", 0);

    texture6 = sfTexture_createFromFile("MapSlimeHunter.png", 0);
    texture7 = sfTexture_createFromFile("Heart.png", 0);

    for (int i = 0; i < nb_PurpleSlime; i++) {
        shape2[i] = sfRectangleShape_create();
        sfRectangleShape_setSize(shape2[i], (sfVector2f) { 150, 100 });
        sfRectangleShape_setTexture(shape2[i], texture2, 0);
        sfRectangleShape_setOrigin(shape2[i], (sfVector2f) { 75, 50 });
    }

    for (int i = 0; i < hp; i++) {
        shape6[i] = sfRectangleShape_create();
        sfRectangleShape_setSize(shape6[i], (sfVector2f) { 42.5, 42.5 });
        sfRectangleShape_setTexture(shape6[i], texture7, NULL);
        sfRectangleShape_setPosition(shape6[i], (sfVector2f) { 4 + 50*i, 45 });
    }

    sfCircleShape_setRadius(shape, 25);
    sfRectangleShape_setSize(shape3, (sfVector2f) { 50, 17.5 });

    sfSprite_setTexture(sprite, texture6,0);

    sfCircleShape_setTexture(shape, texture, 0);
    sfRectangleShape_setTexture(shape3, texture3, 0);

    sfText_scale(text_score, (sfVector2f) { 0.75, 0.75 });
    sfText_setFont(text_score, font1);
}

void Delta() {

    sfTime dtime = sfClock_getElapsedTime(deltaClock);
    delta = sfTime_asMilliseconds(dtime);
    sfClock_restart(deltaClock);
}

void out_of_bounds(float* X, float* Y) {

    if (*X < -100) {
        *X += 1100;
    }

    if (*X > 1100) {
        *X -= 2250;
    }

    if (*Y < -100) {
        *Y += 1100;
    }

    if (*Y > 1100) {
        *Y -= 2250;
    }
}



void score() {
    char str_score[13];
    snprintf(str_score, 13, "Score: %d", points);
    sfText_setString(text_score, str_score);
}

int main() {

    srand(time(0));
    create();
    Purplespawn_Slime(&list_purpleSlime);

    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        if (!sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        score();
        Delta();
        player_move(&player);
        out_of_bounds(&player.X, &player.Y);
        for (int i = 0; i < nb_PurpleSlime; 0) {
            out_of_bounds(&list_purpleSlime[i].X, &list_purpleSlime[i].Y);
        }
        Purpleslime_move(list_purpleSlime, nb_PurpleSlime);
        shoot(&arrow, player);
        PurpleSlimecol();

        sfRenderWindow_clear(window, sfBlack);

        sfCircleShape_setRotation(shape, player.angle + 90);
        sfRectangleShape_setRotation(shape3, ArrowAngle);

        sfSprite_setPosition(sprite, (sfVector2f) { 0, 0 });

        sfCircleShape_setPosition(shape, (sfVector2f) { player.X, player.Y });
        sfRectangleShape_setPosition(shape3, (sfVector2f) { ArrowX, ArrowY });

        sfCircleShape_setOrigin(shape, (sfVector2f) { 25, 25 });

        sfRenderWindow_drawSprite(window, sprite, 0);

        sfRenderWindow_drawCircleShape(window, shape, 0);
        sfRenderWindow_drawRectangleShape(window, shape3, 0);

        sfText_setPosition(text_score, (sfVector2f) { 5, 12.5 });
        sfRenderWindow_drawText(window, text_score, 0);
       

        for (int i = 0; i < nb_PurpleSlime; i++) {
            sfRectangleShape_setPosition(shape2[i], (sfVector2f) { PurpleSlimeX[i], PurpleSlimeY[i] });
            sfRenderWindow_drawRectangleShape(window, shape2[i], 0);
        }

        for (int i = 0; i < hp; i++) {
            sfRenderWindow_drawRectangleShape(window, shape6[i], 0);
        }

        sfRenderWindow_display(window);
    }

    sfCircleShape_destroy(shape);

    for (int i = 0; i < nb_PurpleSlime; i++) {
        sfRectangleShape_destroy(shape2[i]);
    }

    sfRectangleShape_destroy(shape3);

    for (int i = 0; i < hp; i++) {
        sfRectangleShape_destroy(shape6[i]);
    }

    sfSprite_destroy(sprite);

    sfTexture_destroy(texture);
    sfTexture_destroy(texture2);
    sfTexture_destroy(texture3);

    sfTexture_destroy(texture6);
    sfTexture_destroy(texture7);

    sfClock_destroy(deltaClock);

    sfFont_destroy(font1);
    sfText_destroy(text_score);

    sfRenderWindow_destroy(window);

    return 0;
}