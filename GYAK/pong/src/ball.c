#include "ball.h"

void move_ball(Ball* ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
}

void start_ball(Ball* ball, float x, float y)
{
    ball->radius = 50;
    move_ball(ball, x, y);
    ball->speed_x = 150;
    ball->speed_y = 150;
	ball->angle = 0.00;
}

void update_ball(Ball* ball, double time)
{
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;
	
	if (ball->speed_x > 0)
		ball->angle += 0.01;
	else
		ball->angle -= 0.01;
}

void rescale_ball(Ball* ball, int amount)
{
	if (amount > 0)
	{
		if (ball->radius <= 60)
			ball->radius += amount;
	}
	else
	{
		if (ball->radius >= 40)
			ball->radius += amount;
	}
}