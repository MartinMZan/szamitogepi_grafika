#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "utils.h"

typedef struct Cube_bounding_box
{
	vec3 left_bottom_front;
	vec3 left_upper_front;
	vec3 right_upper_front;
	vec3 right_bottom_front;
	vec3 left_bottom_back;
	vec3 left_upper_back;
	vec3 right_upper_back;
	vec3 right_bottom_back;
} Cube_bounding_box;

typedef struct All_bounding_box
{
	Cube_bounding_box cube_bounding_box[1];
	float distance;
} All_bounding_box;

All_bounding_box all_bounding_box;

/**
 * Initialize the all_bounding_box structure.
 */
void init_all_bounding_box(All_bounding_box* all_bounding_box);
/**
 * Add a new bounding box to the all_bounding_boxes variable.
 */
void make_cube_bounding_box(All_bounding_box* all_bounding_box, vec3 center, float size);

/**
 * Is the camera go into a bounding box along the X axis? Hit codes: 1 - front, 2 - back.
 */
int hit_bounding_box_x(All_bounding_box* all_bounding_box, vec3 camera_position);

/**
 * Is the camera go into a bounding box along the Y axis? Hit codes: 1 - right, 2 - left
 */
int hit_bounding_box_y(All_bounding_box* all_bounding_box, vec3 camera_position);

#endif /* BOUNDING_BOX.H */