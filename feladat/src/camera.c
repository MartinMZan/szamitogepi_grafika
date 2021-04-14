#include "camera.h"

#include <GL/glut.h>

#include <stdio.h>
#include <math.h>
#include "texture.h"

void init_camera(Camera* camera)
{
    camera->position.x = 0.0;
    camera->position.y = 0.0;
    camera->position.z = 1.0;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;

    is_preview_visible 	= FALSE;
	users_guide_visible = FALSE;
	ball_simulation 	= FALSE;
}

void update_camera(Camera* camera, double time)
{
    double angle;
    double side_angle;
	int hitx = hit_bounding_box_x(&all_bounding_box, camera->position);
	int hity = hit_bounding_box_y(&all_bounding_box, camera->position);
	
    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);
	
	if (hitx)
	{
		camera->position.x = camera->position.x + 0.0001 * pow(-1, (double)hitx);
	}
	else
	{
		camera->position.x += cos(angle) * camera->speed.y * time;
		camera->position.x += cos(side_angle) * camera->speed.x * time;
	}
	
	
	if (hity)
	{
		camera->position.y = camera->position.y + 0.0001 * pow(-1, (double)hity);
	}
	else
	{
		camera->position.y += sin(angle) * camera->speed.y * time;
		camera->position.y += sin(side_angle) * camera->speed.x * time;
	}
	
    
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z -= horizontal;
    camera->rotation.x -= vertical;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
	camera->speed.y = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}

void show_texture_preview()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

	glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
}

void show_users_guide()
{
	GLuint users_guide = load_texture("data/textures/users_guide.png"); 
    glBindTexture(GL_TEXTURE_2D, users_guide);

	glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

	glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
	glDisable(GL_COLOR_MATERIAL);
}