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
#define nb_Slime 24

struct Player player = { .X = 500, .Y = 500, .speed = 0, .dirX = 0, .dirY = 0, .angle = -90 };
struct Arrow arrow = { .X = 0, .Y = 0, .speed = 10, .dirX = 0, .dirY = 0, .angle = 0, .lifespan = 0};
struct Slime list_Slime[nb_Slime];

int points = 0;

int timer = 0;

int hp = 3;

sfClock* TimerClock;

sfFont* font1;
sfText* text_score;
sfText* text_timer;
sfText* text_restart;
sfText* text_quit;

sfRenderWindow* window;

sfRectangleShape* shape;                         //shape Bow
sfRectangleShape* shape2[nb_Slime];              //shape PurpleSlime
sfRectangleShape* shape3;                        //shape Arrow
sfRectangleShape* shape4[nb_Slime];              //shape BlueSlime
sfRectangleShape* shape5[nb_Slime];              //shape GreenSlime
sfRectangleShape* shape6[3];                     //shape Heart

sfSprite* sprite;                                //Sprite Map
sfSprite* sprite2;                               //Sprite GameOver

sfTexture* texture;                              //Texture Bow
sfTexture* texture2;                             //Texture PurpleSlime
sfTexture* texture3;                             //Texture Arrow
sfTexture* texture4;                             //Texture BlueSlime
sfTexture* texture5;                             //Texture GreenSlime
sfTexture* texture6;                             //Texture Map
sfTexture* texture7;                             //Texture Heart
sfTexture* texture8;                             //Texture GameOver

void create() {

    sfVideoMode mode = { 1000, 1000, 32 };
    window = sfRenderWindow_create(mode, "SlimeHunter", sfResize | sfClose, 0);
    sfRenderWindow_setFramerateLimit(window, 60);

    TimerClock = sfClock_create();

    

    text_score = sfText_create();
    text_timer = sfText_create();
    text_restart = sfText_create();
    text_quit = sfText_create();

    shape = sfRectangleShape_create();
    shape3 = sfRectangleShape_create();

    font1 = sfFont_createFromFile("pixeltext.ttf");

    sprite = sfSprite_create();
    sprite2 = sfSprite_create();

    texture = sfTexture_createFromFile("Arc.png", 0);
    texture2 = sfTexture_createFromFile("SlimeViolet.png", 0);
    texture3 = sfTexture_createFromFile("Arrow.png", 0);
    texture4 = sfTexture_createFromFile("SlimeBleu.png", 0);
    texture5 = sfTexture_createFromFile("SlimeVert.png", 0);
    texture6 = sfTexture_createFromFile("MapSlimeHunter.png", 0);
    texture7 = sfTexture_createFromFile("Heart.png", 0);
    texture8 = sfTexture_createFromFile("gameover.png", 0);

    for (int i = 0; i < nb_Slime; i++) {
        list_Slime[i].size = 0;
        shape2[i] = sfRectangleShape_create();
        sfRectangleShape_setSize(shape2[i], (sfVector2f) { 150, 100 });
        sfRectangleShape_setTexture(shape2[i], texture2, 0);
        sfRectangleShape_setOrigin(shape2[i], (sfVector2f) { 75, 50 });
    }

    for (int i = 0; i < nb_Slime; i++) {
        list_Slime[i].size = 0;
        shape4[i] = sfRectangleShape_create();
        sfRectangleShape_setSize(shape4[i], (sfVector2f) { 75, 50 });
        sfRectangleShape_setTexture(shape4[i], texture4, 0);
        sfRectangleShape_setOrigin(shape4[i], (sfVector2f) { 34.5f, 25 });
    }

    for (int i = 0; i < nb_Slime; i++) {
        list_Slime[i].size = 0;
        shape5[i] = sfRectangleShape_create();
        sfRectangleShape_setSize(shape5[i], (sfVector2f) { 34.5f, 25 });
        sfRectangleShape_setTexture(shape5[i], texture5, 0);
        sfRectangleShape_setOrigin(shape5[i], (sfVector2f) { 17.25f, 12.5f });
    }

    for (int i = 0; i < hp; i++) {
        shape6[i] = sfRectangleShape_create();
        sfRectangleShape_setSize(shape6[i], (sfVector2f) { 42.5f, 42.5f});
        sfRectangleShape_setTexture(shape6[i], texture7, NULL);
        sfRectangleShape_setPosition(shape6[i], (sfVector2f) { 4 + 50*i, 45 });
    }

    sfRectangleShape_setSize(shape, (sfVector2f) { 62, 54 });
    sfRectangleShape_setSize(shape3, (sfVector2f) { 62, 22 });

    sfSprite_setTexture(sprite, texture6, 0);
    sfSprite_setTexture(sprite2, texture8, 0);

    sfSprite_setScale(sprite2, (sfVector2f) { 10, 10 });

    sfRectangleShape_setTexture(shape, texture, 0);
    sfRectangleShape_setTexture(shape3, texture3, 0);

    sfText_scale(text_score, (sfVector2f) { 0.75f, 0.75f });
    sfText_scale(text_timer, (sfVector2f) { 0.75f, 0.75f });
    sfText_scale(text_restart, (sfVector2f) { 1.5f, 1.5f });
    sfText_scale(text_quit, (sfVector2f) { 1.5f, 1.5f });

    sfText_setFont(text_score, font1);
    sfText_setFont(text_timer, font1);
    sfText_setFont(text_restart, font1);
    sfText_setFont(text_quit, font1);
}

void Timer() {
    sfTime dtime = sfClock_getElapsedTime(TimerClock);
    timer = sfTime_asSeconds(dtime);
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

void Timer_text() {
    char str_timer[13];
    snprintf(str_timer, 13, "Timer: %d", timer);
    sfText_setString(text_timer, str_timer);
}

void restart_botton() {
    sfText_setString(text_restart, "Restart");
}

void quit_button() {
    sfText_setString(text_quit, "Quit");
}

int main() {

    srand(time(0));
    create();
    for (int i = 0; i < 6; i++) {
        Purpleslime_spawn(&list_Slime, nb_Slime, 3, 0, 0);
    }

    while (sfRenderWindow_isOpen(window)) {
        sfEvent event;
        if (!sfRenderWindow_pollEvent(window, &event)) {
            if (event.type == sfEvtClosed)
                sfRenderWindow_close(window);
        }

        if (hp > 0) {
            Timer();
            player_move(&player);
            Purpleslime_move(&list_Slime, nb_Slime);
            for (int i = 0; i < nb_Slime; i++) {
                out_of_bounds(&list_Slime[i].X, &list_Slime[i].Y);
            }
            out_of_bounds(&player.X, &player.Y);
            shoot(&arrow, &player);
            Slimecol(&list_Slime, &player, &arrow, nb_Slime, &hp, &points);
        }

        Timer_text();
        score();
        restart_botton();
        quit_button();

        sfRenderWindow_clear(window, sfBlack);

        sfRectangleShape_setRotation(shape, player.angle);
        sfRectangleShape_setRotation(shape3, arrow.angle);

        sfSprite_setPosition(sprite, (sfVector2f) { 0, 0 });

        sfRectangleShape_setPosition(shape, (sfVector2f) { player.X, player.Y });
        sfRectangleShape_setPosition(shape3, (sfVector2f) { arrow.X, arrow.Y });

        sfRectangleShape_setOrigin(shape, (sfVector2f) { 31, 27 });
        sfRectangleShape_setOrigin(shape3, (sfVector2f) { 31, 11 });

        sfRenderWindow_drawSprite(window, sprite, 0);

        sfRenderWindow_drawCircleShape(window, shape, 0);
        if (arrow.lifespan > 0) {
            sfRenderWindow_drawRectangleShape(window, shape3, 0);
        }

        for (int i = 0; i < nb_Slime; i++) {
            if (list_Slime[i].size == 3) {
                sfRectangleShape_setPosition(shape2[i], (sfVector2f) { list_Slime[i].X, list_Slime[i].Y });
                sfRenderWindow_drawRectangleShape(window, shape2[i], 0);
            }
            else if (list_Slime[i].size == 2) {
                sfRectangleShape_setPosition(shape4[i], (sfVector2f) { list_Slime[i].X, list_Slime[i].Y });
                sfRenderWindow_drawRectangleShape(window, shape4[i], 0);
            }
            else if (list_Slime[i].size == 1) {
                sfRectangleShape_setPosition(shape5[i], (sfVector2f) { list_Slime[i].X, list_Slime[i].Y });
                sfRenderWindow_drawRectangleShape(window, shape5[i], 0);
            }
        }

        sfText_setPosition(text_score, (sfVector2f) { 5, 12.5f });
        sfText_setPosition(text_timer, (sfVector2f) { 5, 100 });

        sfRenderWindow_drawText(window, text_score, 0);
        sfRenderWindow_drawText(window, text_timer, 0);

        for (int i = 0; i < hp; i++) {
            sfRenderWindow_drawRectangleShape(window, shape6[i], 0);
        }

        if (hp <= 0) {
            sfSprite_setPosition(sprite2, (sfVector2f) { 0, 0 });
            sfRenderWindow_drawSprite(window, sprite2, NULL);

            sfText_setPosition(text_score, (sfVector2f) { 250, 500 });
            sfText_setPosition(text_timer, (sfVector2f) { 600, 500 });
            sfText_setPosition(text_restart, (sfVector2f) { 200, 750 });
            sfText_setPosition(text_quit, (sfVector2f) { 650, 750 });
            
            sfFloatRect mouserect = (sfFloatRect){ sfMouse_getPosition(window).x, sfMouse_getPosition(window).y, 1, 1 };
            sfFloatRect quitrect = sfText_getGlobalBounds(text_quit);
            sfFloatRect restartrect = sfText_getGlobalBounds(text_restart);
            if (sfFloatRect_intersects(&mouserect, &quitrect, NULL) && sfMouse_isButtonPressed(sfMouseLeft)) {
                sfRenderWindow_close(window);
            }
            if (sfFloatRect_intersects(&mouserect, &restartrect, NULL) && sfMouse_isButtonPressed(sfMouseLeft)) {
                hp = 3;
                points = 0;
                timer = 0;
                sfClock_restart(TimerClock);
                player.X = 500;
                player.Y = 500;
                player.dirX = 0;
                player.dirY = 0;
            }

            sfRenderWindow_drawText(window, text_score, NULL);
            sfRenderWindow_drawText(window, text_timer, NULL);
            sfRenderWindow_drawText(window, text_restart, NULL);
            sfRenderWindow_drawText(window, text_quit, NULL);
        }

        sfRenderWindow_display(window);
    }

    sfRectangleShape_destroy(shape);

    for (int i = 0; i < nb_Slime; i++) {
        sfRectangleShape_destroy(shape2[i]);
        sfRectangleShape_destroy(shape4[i]);
        sfRectangleShape_destroy(shape5[i]);
    }

    sfRectangleShape_destroy(shape3);

    for (int i = 0; i < hp; i++) {
        sfRectangleShape_destroy(shape6[i]);
    }

    sfSprite_destroy(sprite);
    sfSprite_destroy(sprite2);

    sfTexture_destroy(texture);
    sfTexture_destroy(texture2);
    sfTexture_destroy(texture3);
    sfTexture_destroy(texture4);
    sfTexture_destroy(texture5);
    sfTexture_destroy(texture6);
    sfTexture_destroy(texture7);
    sfTexture_destroy(texture8);

    sfClock_destroy(TimerClock);

    sfFont_destroy(font1);

    sfText_destroy(text_score);
    sfText_destroy(text_timer);
    sfText_destroy(text_restart);
    sfText_destroy(text_quit);

    sfRenderWindow_destroy(window);

    return 0;
}