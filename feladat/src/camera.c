#include "camera.h"

#include <GL/glut.h>

#include <stdio.h>
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

    is_preview_visible = FALSE;
	users_guide_visible = FALSE;
}

void update_camera(Camera* camera, double time)
{
    double angle;
    double side_angle;

    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);

    camera->position.x += cos(angle) * camera->speed.y * time;
    camera->position.y += sin(angle) * camera->speed.y * time;
    camera->position.x += cos(side_angle) * camera->speed.x * time;
    camera->position.y += sin(side_angle) * camera->speed.x * time;
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

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}

void Perspective() {
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (double) 1024 / 768, 0.01, 20000.0);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void Ortho() {
    glPushMatrix();
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 1024, 0, 768, -100, 100);
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void szovegKirajzolas(float x, float y, char* s) {
	unsigned int i;
    glDisable(GL_LIGHTING);
    Ortho();
    glPushMatrix();
    glLoadIdentity();
    glColor3f(1.0f, 1.0f, 1.0f);
    glColor3f(128, 128, 128);
    glDisable(GL_DEPTH_TEST);
    glRasterPos2f(x, y);
    for (i = 0; i < strlen(s); i++) {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
    }
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
    Perspective();
    glEnable(GL_LIGHTING);
}

void show_users_guide()
{
	char segedSting[200];
	sprintf(segedSting, "Segedmenu bezarasa: U");
    szovegKirajzolas(0, 640, segedSting);

    sprintf(segedSting, "Mozgas: W, A, S, D");
    szovegKirajzolas(0, 620, segedSting);

    sprintf(segedSting, "Kamera forgatas: egergomb le, majd egermozgassal");
    szovegKirajzolas(0, 600, segedSting);

    sprintf(segedSting, "Fenyero allitasa: +, -");
    szovegKirajzolas(0, 580, segedSting);

}