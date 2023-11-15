#pragma once

struct Player {
    float X;
    float Y;
    float speed;
    float dirX;
    float dirY;
    float angle;
};

void player_move(player);