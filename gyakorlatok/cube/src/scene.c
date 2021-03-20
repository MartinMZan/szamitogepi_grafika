#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

#include <math.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->cube), "cube.obj");
    scene->texture_id = load_texture("cube.png"); 
	
	load_model(&(scene->house), "house.obj");
    scene->texture_id = load_texture("house.png"); 
	
	scene->ambient_light[0] = 0.2f;
	scene->ambient_light[1] = 0.2f;
	scene->ambient_light[2] = 0.2f;
	scene->ambient_light[3] = 0.2f;
	
	scene->diffuse_light[0] = 0.0f;
	scene->diffuse_light[1] = 0.0f;
	scene->diffuse_light[2] = 0.0f;
	scene->diffuse_light[3] = 0.0f;
	
	scene->light_mult = 1;
	
    glBindTexture(GL_TEXTURE_2D, scene->texture_id);

    scene->material.ambient.red = 0.5;
    scene->material.ambient.green = 0.5;
    scene->material.ambient.blue = 0.5;

    scene->material.diffuse.red = 0.5;
    scene->material.diffuse.green = 0.5;
    scene->material.diffuse.blue = 0.5;

    scene->material.specular.red = 1.0;
    scene->material.specular.green = 1.0;
    scene->material.specular.blue = 1.0;

    scene->material.shininess = 30.0;
	
	scene->cube_rotation = 0;
	scene->house_rotation = 0;
}

void set_lighting(const Scene* scene)
{
    float specular_light[] = { 1.0f, 1.0f, 1.0f, 1.0f };
    float position[] = { 5.0f, 2.0f, 2.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, scene->ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, scene->diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}

void draw_scene(const Scene* scene)
{
	int i;
	
    set_material(&(scene->material));
    set_lighting(scene);
    draw_origin();
    
	for (i=0; i<10; ++i)
	{
		glPushMatrix();
		glTranslatef(2, 0, 0);
		glutSolidSphere(1, 30, 30);
	}
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(5.0f, 2.0f, 2.0f);
	glRotatef(scene->cube_rotation, 1, 0, 0);
	draw_model(&(scene->cube));
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(0.0f, -3.0f, 0.2f);
	glScalef(0.02f, 0.02f, 0.02f);
	glRotatef(90, 1.0f, 0.0f, 0.0f);
	glRotatef(scene->house_rotation, 0, 0, 1);
	draw_model(&(scene->house));
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

void update_scene(Scene* scene, double time)
{
	scene->cube_rotation += 10*time;
	scene->house_rotation += 20*time;
	
	if(scene->diffuse_light[0] > 1 || scene->diffuse_light[0] < 0) 
		scene->light_mult *= -1.0;
	scene->diffuse_light[0] += 0.1*time*scene->light_mult;
	scene->diffuse_light[1] += 0.2*time*scene->light_mult;
	scene->diffuse_light[2] += 0.3*time*scene->light_mult;
	scene->diffuse_light[3] += 0.4*time*scene->light_mult;
	
	
	glLightfv(GL_LIGHT0, GL_DIFFUSE, scene->diffuse_light);
}

void update_lightning(Scene* scene, float amount)
{
	if(amount > 0 && scene->ambient_light[0] < 1)
	{
		scene->ambient_light[0] += amount;
		scene->ambient_light[1] += amount;
		scene->ambient_light[2] += amount;
		scene->ambient_light[3] += amount;
	}
	
	if(amount < 0 && scene->ambient_light[0] > 0)
	{
		scene->ambient_light[0] += amount;
		scene->ambient_light[1] += amount;
		scene->ambient_light[2] += amount;
		scene->ambient_light[3] += amount;
	}
	
	glLightfv(GL_LIGHT0, GL_AMBIENT, scene->ambient_light);
}