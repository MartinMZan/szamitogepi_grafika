#include "scene.h"

#include <GL/glut.h>

#include <obj/load.h>
#include <obj/draw.h>

void init_scene(Scene* scene)
{
    load_model(&(scene->models[0]), "data/models/cube.obj");
	load_model(&(scene->models[1]), "data/models/ball.obj");
	
    scene->texture_id[0] = load_texture("data/textures/cube.jpg"); 
	scene->texture_id[1] = load_texture("data/textures/ball.jpg");
	scene->texture_id[2] = load_texture("data/textures/transparent.png");
	scene->texture_id[3] = load_texture("data/textures/paint.jpg");
	scene->texture_id[4] = load_texture("data/textures/progress_bar.jpg");
	
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
	scene->diffuse_light = 0.7f;
	
	scene->last_ball_index = -1;
	
	ball_size = 0.2;
}

void init_balls(Scene* scene, int index)
{
	float norm;
	int i;
	
	for (i=0; i<get_last_ball_index(scene); i++) {
		if ( 2 * ball_size > sqrt( pow(2.0 - scene->ball[i].position.x, 2) + pow(0.0 - scene->ball[i].position.y, 2) + pow(2.0 - scene->ball[i].position.z, 2) ) ) {
			return;
		}
	}

	scene->ball[index].position.x = 2.0f;
	scene->ball[index].position.y = 0.0f;
	scene->ball[index].position.z = 2.0f;
	
	do {
		scene->ball[index].speed.x = rand()%201 / 100 - 1;
		scene->ball[index].speed.y = rand()%201 / 100 - 1;
		scene->ball[index].speed.z = rand()%201 / 100 - 1;
	} while (scene->ball[index].speed.z >= -0.3 && scene->ball[index].speed.z <= 0.3);
	
	norm = fabs(scene->ball[index].speed.x + scene->ball[index].speed.y + scene->ball[index].speed.z);
	scene->ball[index].speed.x /= norm;
	scene->ball[index].speed.y /= norm;
	scene->ball[index].speed.z /= norm;
	
	scene->last_ball_spawn_time = glutGet(GLUT_ELAPSED_TIME)/1000;
	scene->last_ball_index = index;
}

vec3 get_ball_position(const Scene* scene, int index)
{
	return scene->ball[index].position;
}

float get_last_ball_spawn_time(const Scene* scene)
{
	return scene->last_ball_spawn_time;
}

int get_last_ball_index(const Scene* scene)
{
	return scene->last_ball_index;
}

void set_game_start_time(Scene* scene, float time)
{
	scene->game_start_time = time;
}

void set_last_ball_index(Scene* scene, int index)
{
	scene->last_ball_index = index;
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
	
	diffuse_light[0] = scene->diffuse_light;
	diffuse_light[1] = scene->diffuse_light;
	diffuse_light[2] = scene->diffuse_light;
	diffuse_light[3] = 1.0f;
	
	specular_light[0] = 0.7f;
	specular_light[1] = 0.7f;
	specular_light[2] = 0.7f;
	specular_light[3] = 1.0f;
	
	position[0] = 0.0f;
	position[1] = 0.0f;
	position[2] = 7.0f;
	position[3] = 1.0f;

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void change_lighting(Scene* scene, float amount)
{
	if (amount > 0)
	{
		if (scene->diffuse_light < 1) {
			scene->diffuse_light += amount;
		}
		else if (scene->ambient_light < 1) {
			scene->ambient_light += amount;
		}
	}
	else if (amount < 0)
	{
		if (scene->diffuse_light > 0) {
			scene->diffuse_light += amount;
		}
		else if (scene->ambient_light > 0) {
			scene->ambient_light += amount;
		}
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
	
	draw_ball(scene);
	draw_transparent_texture_example(scene);
	draw_progress_bar(scene);
}

void draw_wall(Model model, int startpoint, int endpoint, int centerx, int centery)
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

void draw_wall2(Model model, int startpoint, int endpoint, int centerx, int centery)
{
	int i, j;

	for (i=startpoint; i <= endpoint; i++)
	{
		for (j=startpoint; j <= endpoint; j++)
		{
			if (i == -j) {
				continue;
			}
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
	draw_wall(scene->models[0], -5, 5, 0, 0);
	
	glPushMatrix();
	glTranslatef(0, 0, 10);
	draw_wall(scene->models[0], -5, 5, 0, 0);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 4.5, -5);
	draw_wall(scene->models[0], -5, 5, 0, 0);
	glPopMatrix();
	
	glPushMatrix();
	glRotatef(90, 1, 0, 0);
	glTranslatef(0, 4.5, 6);
	draw_wall(scene->models[0], -5, 5, 0, 0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-5, 0, 4.5);
	glRotatef(90, 0, 1, 0);
	draw_wall(scene->models[0], -5, 5, 0, 0);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(6, 0, 4.5);
	glRotatef(90, 0, 1, 0);
	draw_wall2(scene->models[0], -5, 5, 0, 0);
	glPopMatrix();
}

void draw_ball(const Scene* scene)
{
	int i;
	float scalevalue = 2.0;
	
	glBindTexture(GL_TEXTURE_2D, scene->texture_id[1]);
	
	if(get_last_ball_index(scene) == -1) {
		glPushMatrix();
		glTranslatef(2.0f, 0.0f, 2.0f);
		glScalef(scalevalue, scalevalue, scalevalue);
		draw_model(&scene->models[1]);
		glPopMatrix();
	}
	else {
		for (i=0; i<=get_last_ball_index(scene); i++) {
		vec3 ball = get_ball_position(scene, i);
		
		glPushMatrix();
		glTranslatef(ball.x, ball.y, ball.z);
		glScalef(scalevalue, scalevalue, scalevalue);
		draw_model(&scene->models[1]);
		glPopMatrix();
		}
	}
 }

void draw_transparent_texture_example(const Scene* scene)
 {
	int i=-5;
	int j=5;
	
	glBindTexture(GL_TEXTURE_2D, scene->texture_id[3]);
	glPushMatrix();
	glTranslatef(20, 0, 4.5);
	glScalef(1, 20, 20);
	glRotatef(90, 0, 1, 0);
	draw_model(&scene->models[0]);
	glPopMatrix();
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
	glBindTexture(GL_TEXTURE_2D, scene->texture_id[2]);
	glPushMatrix();
	glTranslatef(6, 0, 4.5);
	glRotatef(90, 0, 1, 0);
	for (i=-5; i <= 5; i++)
	{
		for (j=-5; j <= 5; j++)
		{
			if (i != -j) {
				continue;
			}
			glPushMatrix();
			glTranslatef(0+i, 0+j, -0.5);
			draw_model(&scene->models[0]);
			glPopMatrix();
		}
	}
	glPopMatrix();
	glDisable(GL_BLEND);
 }
 
 void draw_progress_bar(Scene* scene)
 {
	int x = 30;
	int y = 30;
	int width = 300;
	int height = 200;
	
	glBindTexture(GL_TEXTURE_2D, scene->texture_id[4]);
	
	glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	glColor3f(1, 1, 1);
	
	/*
    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1.3, -3);
    glTexCoord2f(600/640, 0);
    glVertex3f(1, 1.3, -3);
    glTexCoord2f(600/640, 100/480);
    glVertex3f(1, 1.1, -3);
    glTexCoord2f(0, 100/480);
    glVertex3f(-1, 1.1, -3);
    glEnd();
	*/
	
	
    glBegin(GL_QUADS);
	glColor3f(0, 0, 0);
    glVertex3f(-1.8, 1.3, -3);
    glVertex3f(1, 1.3, -3);
    glVertex3f(1, 1.1, -3);
    glVertex3f(-1, 1.1, -3);
    glEnd();
	


	glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
 }