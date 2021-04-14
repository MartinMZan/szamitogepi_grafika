#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"
#include "bounding_box.h"
#include "bounce.h"

#include <obj/model.h>

typedef struct Scene
{
    Model models[3];
    Material material;
    GLuint texture_id[5];
	float ambient_light;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

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
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

/**
 * Draw more models from the same type which is used for draw the wall.
 */
void draw_wall(Model model, int startpoint, int endpoint, int centerx, int centery);

/**
 * Other type of wall.
 */
void draw_wall2(Model model, int startpoint, int endpoint, int centerx, int centery);
 
/**
 * Draw the map in the following order: bottom, up, left, right, front, back.
 */
void draw_map(const Scene* scene);
 
/**
 * Draw a model to demonstrate the bounding box implementation on it.
 */
void draw_bounding_box_example(const Scene* scene);

/**
 * Draw a trampoline.
 */
void draw_trampoline(const Scene* scene);

/**
 * Draw ball to demonstrate the bounce physics implementation.
 */
void draw_bounce_example(const Scene* scene);

/**
 * Draw an example of models with transparent textures.
 */
void draw_transparent_texture_example(const Scene* scene);
#endif /* SCENE_H */
