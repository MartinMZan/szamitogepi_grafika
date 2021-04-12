#include "bounce.h"
#include "texture.h"

void init_ball(Ball* ball)
{
	ball->position = 5.5f;
	ball->direction = -1;
	ball->speed = 0.0f;
	ball->last_bounce_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	
	load_model(&(ball->model), "data/ball.obj");
	ball->texture_id = load_texture("data/ball.jpg");
}

void update_bounce_ball(Ball* ball)
{
	static float floor = 0.5f;
	static float energy_loss_factor = 0.8f;
	float speed_constant = 0.05f;
	float elapsed_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0 - ball->last_bounce_time;
	
	if (ball->position >= floor && ball->direction == -1)
	{
		ball->speed = elapsed_time * speed_constant;
		ball->position = ball->position - ball->speed;
	}
	else if (ball->position >= floor && ball->direction == 1)
	{
		if (ball->speed - elapsed_time * speed_constant / energy_loss_factor <= 0)
		{
			ball->direction *= -1;
			ball->last_bounce_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
		}
		ball->position = ball->position + ball->speed - elapsed_time * speed_constant / energy_loss_factor;
	}
	else if (ball->position < floor)
	{
		ball->direction *= -1;
		ball->position = 0.5;
		
		ball->last_bounce_time = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	}
	
}

void draw_bounce_example(const Ball* ball)
{
	glBindTexture(GL_TEXTURE_2D, ball->texture_id);
	glPushMatrix();
	glTranslatef(-3.25, 3.5, ball->position);
	glScalef(2,2,2);
	draw_model(&ball->model);
	glPopMatrix();
 }