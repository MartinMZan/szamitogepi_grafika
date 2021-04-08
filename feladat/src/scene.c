#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->cube), "cube.obj");
    scene->texture_id = load_texture("cube.jpg"); 

    glBindTexture(GL_TEXTURE_2D, scene->texture_id);

    scene->material.ambient.red = 0.2;
    scene->material.ambient.green = 0.2;
    scene->material.ambient.blue = 0.2;

    scene->material.diffuse.red = 0.8;
    scene->material.diffuse.green = 0.8;
    scene->material.diffuse.blue = 0.8;

    scene->material.specular.red = 0.8;
    scene->material.specular.green = 0.8;
    scene->material.specular.blue = 0.8;

    scene->material.shininess = 0.0;
	
	scene->ambient_light = 0.2f;
}

void set_lighting(const Scene* scene)
{
	float ambient_light[4];
    float diffuse_light[4];
    float specular_light[4];
    float position[4];
	
	ambient_light[0] = scene->ambient_light;
	ambient_light[1] = scene->ambient_light;
	ambient_light[2] = scene->ambient_light;
	ambient_light[3] = 1.0f;
	
	diffuse_light[0] = 0.8f;
	diffuse_light[1] = 0.8f;
	diffuse_light[2] = 0.8f;
	diffuse_light[3] = 1.0f;
	
	specular_light[0] = 0.8f;
	specular_light[1] = 0.8f;
	specular_light[2] = 0.8f;
	specular_light[3] = 1.0f;
	
	position[0] = 0.0f;
	position[1] = 0.0f;
	position[2] = 10.0f;
	position[3] = 1.0f;

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void change_lighting(Scene* scene, float amount)
{
	if (amount > 0 && scene->ambient_light < 1)
	{
		scene->ambient_light += amount;
	}
	else if (amount < 0 && scene->ambient_light > 0)
	{
		scene->ambient_light += amount;
	}
}

void set_material(const Material* material)
{
    float ambient_material_color[3];
	float diffuse_material_color[3];
	float specular_material_color[3];
	
	ambient_material_color[0] = material->ambient.red;
	ambient_material_color[1] = material->ambient.green;
	ambient_material_color[2] = material->ambient.blue;

    diffuse_material_color[0] = material->diffuse.red;
    diffuse_material_color[1] = material->diffuse.green;
    diffuse_material_color[2] = material->diffuse.blue;
    
    specular_material_color[0] = material->specular.red;
    specular_material_color[1] = material->specular.green;
    specular_material_color[2] = material->specular.blue;
    
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void draw_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting(scene);
    
	draw_map(scene);
    
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}

void draw_map(const Scene* scene)
{
	int i, j;
	int startpoint = -5;
	int endpoint = 5;
	
	for (i=startpoint; i <= endpoint; i++)
	{
		for (j=startpoint; j <= endpoint; j++)
		{
			glPushMatrix();
			glTranslatef(i, j, -0.5);
			draw_model(&(scene->cube));
			glPopMatrix();
		}
	}
}