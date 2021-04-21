#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include <stdbool.h>
#include "utils.h"
#include "bounce.h"

typedef struct Cube_bounding_box
{
	float min_x;
	float min_y;
	float max_x;
	float max_y;
} Cube_bounding_box;

Cube_bounding_box cube_bounding_box;

float distance;

/**
 * Initialize the cube_bounding_box structure.
 */
void init_cube_bounding_box(Cube_bounding_box* cube_bounding_box);

/**
 * Give value to the cube_bounding_box structure.
 */
void make_cube_bounding_box(Cube_bounding_box* cube_bounding_box, vec3 center, float size);

/**
 * Which side of the bounding box hit by the camera along the X axis? Hit codes: 1 - front, 2 - back.
 */
int hit_bounding_box_x(Cube_bounding_box* cube_bounding_box, vec3 camera_position);

/**
 * Which side of the bounding box hit by the camera along the Y axis? Hit codes: 1 - right, 2 - left.
 */
int hit_bounding_box_y(Cube_bounding_box* cube_bounding_box, vec3 camera_position);

/**
 * Which wall of the map hit by the camera?
 */
int hit_map_by_player(vec3 position);

/**
 * Moves a ball when it collide with the edge of the map.
 */
void hit_map_by_ball(Balls* balls, int i);

/**
 * Moves two balls when they collide.
 */
void ball_collision(Balls* balls, int i, int j);

#endif /* BOUNDING_BOX.H */