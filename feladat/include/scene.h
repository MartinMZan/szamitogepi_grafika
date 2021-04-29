#ifndef SCENE_H
#define SCENE_H

#include "camera.h"

#include <math.h>
#include <obj/model.h>

#define BALL_COUNT 10

typedef struct Ball
{
	vec3 position;
	vec3 speed;
} Ball;

typedef struct Scene
{
    Model models[2];
    Material material;
    GLuint texture_id[5];
	float ambient_light;
	float diffuse_light;
	Ball ball[BALL_COUNT];
	float game_start_time;
	float last_ball_spawn_time;
	int last_ball_index;
} Scene;

float ball_size;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Initialize the required balls.
 */
void init_balls(Scene* scene, int index);

/**
 * Getter functions.
 */
vec3 get_ball_position(const Scene* scene, int index);
float get_last_ball_spawn_time(const Scene* scene);
int get_last_ball_index(const Scene* scene);

/**
 * Setter functions.
 */
void set_game_start_time(Scene* scene, float time);
void set_last_ball_index(Scene* scene, int index);

/**
 * Set the lighting of the scene.
 */
void set_lighting(const Scene* scenes);

/**
 * Change the ambient light value.
 */
void change_lighting(Scene* scene, float amount);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Draw the scene objects.
 */
void draw_scene(const Scene* scene);

/**
 * Draw more models from the same type which is used for draw the wall.
 */
void draw_wall(Model model, int startpoint, int endpoint, int centerx, int centery);

/**
 * Draw an other type of wall.
 */
void draw_wall2(Model model, int startpoint, int endpoint, int centerx, int centery);
 
/**
 * Draw the map in the following order: bottom, up, left, right, front, back.
 */
void draw_map(const Scene* scene);

/**
 * Draw ball to demonstrate the bounce physics implementation.
 */
void draw_ball(const Scene* scene);

/**
 * Draw an example of models with transparent textures.
 */
void draw_transparent_texture_example(const Scene* scene);

#endif /* SCENE_H */
