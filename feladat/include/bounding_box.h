#ifndef BOUNDING_BOX_H
#define BOUNDING_BOX_H

#include "utils.h"
#include "scene.h"

/**
 * Moves a ball when it collide with the edge of the map.
 */
void hit_map_by_ball(Scene* scene, int i);

/**
 * Moves two balls when they collide.
 */
void ball_collision(Scene* scene, int i, int j);

#endif /* BOUNDING_BOX.H */