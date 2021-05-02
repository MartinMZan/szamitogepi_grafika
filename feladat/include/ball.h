#ifndef BALL_H
#define BALL_H

#include "utils.h"

#include <stdbool.h>
#include <math.h>
#include <GL/glut.h>

typedef struct Ball
{
	vec3 position;
	vec3 speed;
} Ball;

/**
 * Moves a ball when it collide with the edge of the map.
 */
void hit_map_by_ball(Ball ball[], int i);

/**
 * Moves two balls when they collide.
 */
void ball_collision(Ball ball[], int i, int j);

/**
 * Update the current values of bounce mechanism.
 */
void update_bounce_balls(Ball ball[], double elapsed_time, int last_ball_index);

/**
 * Detect the winning or losing conditions.
 */
bool check_game_finished(Ball ball[], vec3 player_position, float game_start_time, float win_time, int last_ball_index);

/**
 * Finish the game by setting some variables to their initial value.
 */
void close_game(Ball ball[], int last_ball_index);

#endif /* BALL.H */