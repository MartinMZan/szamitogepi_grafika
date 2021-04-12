#ifndef BOUNCE_H
#define BOUNCE_H

#include <obj/model.h>

#include "scene.h"

typedef struct Ball
{
	float position;
	int direction;
	float speed;
	float last_bounce_time;
	Model model;
	GLuint texture_id;
} Ball;

Ball ball;

/**
 * Initialize the ball.
 */
void init_ball(Ball* ball);

/**
 * Update the current values of bounce mechanism.
 */
void update_bounce_ball(Ball* ball);

/**
 * Draw ball to demonstrate the bounce physics implementation.
 */
void draw_bounce_example(const Ball* ball);

#endif /* BOUNCE.H */