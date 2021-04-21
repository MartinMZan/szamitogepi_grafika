#ifndef BOUNCE_H
#define BOUNCE_H

#include <obj/model.h>
#include "utils.h"
#include <math.h>

typedef struct Ball
{
	vec3 position;
	vec3 speed;
	float init_time;
} Ball;

typedef struct Balls
{
	Ball ball[10];
} Balls;

Balls balls;
float ball_size;

/**
 * Initialize the required balls.
 */
void init_balls(Balls* balls, int index);

/**
 * Initialize the init_time value for every ball.
 */
void init_ball_times(Balls* balls);

/**
 * Getter functions.
 */
vec3 get_ball_position(Balls* balls, int index);
int get_last_ball_index(Balls* balls);
float get_last_ball_init_time(Balls* balls);

/**
 * Update the current values of bounce mechanism.
 */
void update_bounce_balls(Balls* balls);

/**
 * Detect the winning or losing conditions.
 */
void game_end_result(Balls* balls, vec3 camera_position);

#endif /* BOUNCE.H */