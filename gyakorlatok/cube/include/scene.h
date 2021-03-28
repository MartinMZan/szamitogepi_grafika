#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    Model cube;
	float cube_rotation;
	Model house;
	float house_rotation;
    Material material;
    GLuint texture_id;
	GLuint texture_id2;
	float ambient_light[4];
	float diffuse_light[4];
	float light_mult;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

/**
 * Set the lighting of the scene.
 */
void set_lighting(const Scene* scene);

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Draw the scene objects.
 */
void draw_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

/**
 * Update the scene.
 */
void update_scene(Scene* scene, double time);

/**
 * Change the ambient lightning of the scene if button pressed.
 */
 void update_lightning(Scene* scene, float amount);

#endif /* SCENE_H */
