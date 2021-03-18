#include "scene.h"

#include <GL/glut.h>

#include <math.h>

void init_scene(Scene* scene)
{
	scene->teapot_rotation = 0.0;
	scene->sphere_radius = 0.0;
	scene->ball_rotation = 0.0;
}

void update_scene(Scene* scene, double time)
{
	scene->teapot_rotation += 15 * time;
	scene->sphere_radius += 0.01 * time;
	scene->ball_rotation += 10 * time;
}

void draw_scene(const Scene* scene)
{
	int i;
	int n_slices;
	
    draw_origin();
	
	glPushMatrix();
	for (i = 0; i < 10; ++i) {
		
		glTranslatef(1.5, 0, 0);
		
		glColor3f(1 - (float)i / 10, 0.8, (float)i / 10.0);
		glPushMatrix();
		
		glRotatef(scene->teapot_rotation, 0, 0, 1);
		glRotatef(90, 1, 0, 0);
		glTranslatef(0, 2, 0);
		
		glutWireTeapot(1);
		glPopMatrix();
	}
	glPopMatrix();
	
	/*
	n_slices = scene->sphere_radius * 50;
	if (n_slices < 3) {
		n_slices = 3;
	}
	glutWireSphere(scene->sphere_radius, n_slices, 20);
	*/
	
	draw_triangle();
	
	draw_ball(scene);
	
	draw_chess_board();
	
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

void draw_triangle()
{
	glBegin(GL_TRIANGLES);
	glColor3f(1, 1, 0);
	glVertex3f(0, 0, 0);
	glColor3f(0, 1, 1);
	glVertex3f(1, 0, 0);
	glColor3f(1, 0, 1);
	glVertex3f(0, 1, 1);
	glEnd();
}

void draw_ball(const Scene* scene)
{
	glPushMatrix();
	glRotatef(scene->ball_rotation, 0, 1, 0);
	glTranslatef(0.5, -0.5, 0.5);
	glColor3f(0.5, 0.5, 0.5);
	glutWireSphere(0.5, 10, 10);
	glPopMatrix();
}

void draw_chess_board()
{
	int i, j;
	double size = 0.05;
	
	for (i = 0 ; i<=7 ; i++) {
		for (j = 0 ; j<=7 ; j++) {
			glPushMatrix();
			glTranslatef(i*size, j*size, 0);
			
			glBegin(GL_QUADS);
			glColor3f((i+j)%2, (i+j)%2, (i+j)%2);
			glVertex3f(0, 0, 0);
			glVertex3f(0, size, 0);
			glVertex3f(size, size, 0);
			glVertex3f(size, 0, 0);
			glEnd();
			
			glPopMatrix();
		}
	}
	
}