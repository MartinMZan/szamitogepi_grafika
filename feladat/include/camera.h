#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"
#include <stdbool.h>
#include "texture.h"

/**
 * Camera, as a moving point with direction
 */
typedef struct Camera
{
    vec3 position;
    vec3 rotation;
    vec3 speed;
} Camera;

/**
 * Is the user's guide visible?
 */
bool users_guide_visible;

/**
 * Is the ball simulation running?
 */
bool ball_simulation;

/**
 * Is the player win/lose the game?
 */
bool win_game;
bool lose_game;
 
/**
 * Initialize the camera to the start position.
 */
void init_camera(Camera* camera);

/**
 * Update the position of the camera.
 */
void update_camera(Camera* camera, double time);

/**
 * Apply the camera settings to the view transformation.
 */
void set_view(const Camera* camera);

/**
 * Set the horizontal and vertical rotation of the view angle.
 */
void rotate_camera(Camera* camera, double horizontal, double vertical);

/**
 * Set the speed of forward and backward motion.
 */
void set_camera_speed(Camera* camera, double speed);

/**
 * Set the speed of left and right side steps.
 */
void set_camera_side_speed(Camera* camera, double speed);

/**
 * Show you a preview of the first texture.
 */
void show_texture_preview();

/**
 * Used to show the user's guide/winning screen/losing screen.
 */
void show_texture(int code);

/**
 * Which wall of the map hit by the camera?
 */
int hit_map_by_player(vec3 position);

#endif /* CAMERA_H */
