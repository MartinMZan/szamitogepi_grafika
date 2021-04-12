#ifndef BOUNCE_H
#define BOUNCE_H

#include <obj/model.h>

typedef struct Ball
{
	float position;
	int direction;
	float speed;
	float last_bounce_time;
	int simulation_end_time;
} Ball;

Ball ball;

/**
 * Initialize the ball.
 */
void init_ball(Ball* ball);

/**
 * Getter functions.
 */
float get_ball_position(Ball* ball);
int get_simulation_end_time(Ball* ball);

/**
 * Update the current values of bounce mechanism.
 */
void update_bounce_ball(Ball* ball);

#endif /* BOUNCE.H */