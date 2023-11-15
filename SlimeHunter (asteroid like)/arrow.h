#pragma once

struct Arrow {
	float X;
	float Y;
	float speed;
	float dirX;
	float dirY;
	float angle;
	int lifespan;
	int bullet;
};

void shoot(arrow, player);
