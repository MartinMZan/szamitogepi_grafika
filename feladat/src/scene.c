#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->models[0]), "data/cube.obj");
	load_model(&(scene->models[1]), "data/trampoline.obj");
    scene->texture_id[0] = load_texture("data/cube.jpg"); 
	scene->texture_id[1] = load_texture("data/trampoline.png"); 
	
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
	
	position[0] = -4.5f;
	position[1] = -4.5f;
	position[2] = 7.0f;
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
	draw_bounding_box_example(scene);
	
	//glDisable(GL_CULL_FACE);
	glBindTexture(GL_TEXTURE_2D, scene->texture_id[1]);
	glPushMatrix();
	glTranslatef(-3, 2, 0);
	glRotatef(90, 1, 0, 0);
	glScalef(0.1, 0.01, 0.01);
	draw_model(&scene->models[1]);
	glPopMatrix();
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

void draw_more(Model model, int startpoint, int endpoint, int centerx, int centery)
{
	int i, j;

	for (i=startpoint; i <= endpoint; i++)
	{
		for (j=startpoint; j <= endpoint; j++)
		{
			glPushMatrix();
			glTranslatef(centerx+i, centery+j, -0.5);
			draw_model(&model);
			glPopMatrix();
		}
	}
}

void draw_map(const Scene* scene)
{
	glBindTexture(GL_TEXTURE_2D, scene->texture_id[0]);
	draw_more(scene->models[0], -5, 5, 0, 0);
	
	glPushMatrix();
	glTranslatef(0, 0, 10);
	draw_more(scene->models[0], -5, 5, 0, 0);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 4.5, -5);
	draw_more(scene->models[0], -5, 5, 0, 0);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 4.5, 6);
	draw_more(scene->models[0], -5, 5, 0, 0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-5, 0, 4.5);
	glRotatef(90, 0, 1, 0);
	draw_more(scene->models[0], -5, 5, 0, 0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(6, 0, 4.5);
	glRotatef(90, 0, 1, 0);
	draw_more(scene->models[0], -5, 5, 0, 0);
	glPopMatrix();
}

void draw_bounding_box_example(const Scene* scene)
{
	vec3 t = {3, 3, 0.5};
	
	glPushMatrix();
	glTranslatef(3, 3, 0.5);
	draw_model(&scene->models[0]);
	glPopMatrix();
	
	make_cube_bounding_box(&all_bounding_box, t, 1);
}