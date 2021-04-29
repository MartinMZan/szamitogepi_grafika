#ifndef BALL_H
#define BALL_H

#include "bounding_box.h"

/**
 * Update the current values of bounce mechanism.
 */
void update_bounce_balls(Scene* scene, double elapsed_time);

/**
 * Detect the winning or losing conditions.
 */
void check_game_finished(Scene* scene, vec3 camera_position);

/**
 * Finishes the game by setting some variables to their initial value.
 */
void close_game(Scene* scene);

#endif /* BALL.H */