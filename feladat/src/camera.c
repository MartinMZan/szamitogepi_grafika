#include "camera.h"

#include <GL/glut.h>

#include <math.h>

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
	win_game			= FALSE;
	lose_game			= FALSE;
}

void update_camera(Camera* camera, double time)
{
    double angle;
    double side_angle;
	int hitmap = hit_map_by_player(camera->position);
	
    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);
	
	if (hitmap) {
		switch (hitmap) {
			case 1: camera->position.x = 5-0.03; break;
			case 2: camera->position.x = -5+0.03; break;
			case 3: camera->position.y = 5-0.03; break;
			case 4: camera->position.y = -5+0.03; break;
		}
	}
	else {
		camera->position.x += cos(angle) * camera->speed.y * time;
		camera->position.x += cos(side_angle) * camera->speed.x * time;
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
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

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

void show_texture(int code)
{
	GLuint texture = 0;
	if (code == 0) {
		texture = load_texture("data/textures/users_guide.png"); 
	}
	else if (code == 1) {
		texture = load_texture("data/textures/win.png"); 
	}
	
	else if (code == 2) {
		texture = load_texture("data/textures/lose.png"); 
	}
	
    glBindTexture(GL_TEXTURE_2D, texture);
	
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

int hit_map_by_player(vec3 position)
{
	float map_size = 5-0.03;
	
	if (position.x > map_size) {
		return 1;
	}
	else if (position.x < (-1) * map_size) {
		return 2;
	}
	else if (position.y > map_size) {
		return 3;
	}
	else if (position.y < (-1) * map_size) {
		return 4;
	}
	else {
		return 0;
	}
}