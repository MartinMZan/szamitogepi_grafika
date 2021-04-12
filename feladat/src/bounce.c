#include "bounce.h"
#include "texture.h"

void init_ball(Ball* ball)
{
	ball->position = 6.0f;
	ball->direction = -1;
	ball->speed = 0.0f;
	ball->last_bounce_time = glutGet(GLUT_ELAPSED_TIME) / 1000;
	ball->simulation_end_time = 0;
}

float get_ball_position(Ball* ball)
{
	return ball->position;
}

int get_simulation_end_time(Ball* ball)
{
	return ball->simulation_end_time;
}

void update_bounce_ball(Ball* ball)
{
	static float floor = 0.5f;
	static float energy_loss_factor = 0.8f;
	float speed_constant = 0.07f;
	float elapsed_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0 - ball->last_bounce_time;
	
	if (ball->position > floor && ball->direction == -1)
	{
		ball->speed = elapsed_time * speed_constant;
		ball->position = ball->position - ball->speed;
	}
	else if (ball->position >= floor && ball->direction == 1)
	{
		if (ball->speed - elapsed_time * speed_constant / energy_loss_factor <= 0) {
			ball->direction *= -1;
			ball->last_bounce_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
		}
		else {
			ball->position = ball->position + ball->speed - elapsed_time * speed_constant;
		}
	}
	else if (ball->position <= floor)
	{
		if (ball->speed <= 0.0005) {
			ball->speed = 0;
		}
		
		ball->direction *= -1;
		ball->position = 0.5;
		ball->speed *= energy_loss_factor;
		ball->last_bounce_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	}
	
	if (ball->speed == 0)
	{
		ball->simulation_end_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	}
	
}