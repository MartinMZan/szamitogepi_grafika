#include "callbacks.h"

#define VIEWPORT_RATIO (4.0 / 3.0)
#define VIEWPORT_ASPECT 50.0

struct {
    int x;
    int y;
} mouse_position;

void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glPushMatrix();
    set_view(&camera);
    draw_scene(&scene);
    glPopMatrix();

    if (is_preview_visible) {
        show_texture_preview();
    }
	
	if (users_guide_visible) {
		show_users_guide();
	}

    glutSwapBuffers();
}

void reshape(GLsizei width, GLsizei height)
{
    int x, y, w, h;
    double ratio;

    ratio = (double)width / height;
    if (ratio > VIEWPORT_RATIO) {
        w = (int)((double)height * VIEWPORT_RATIO);
        h = height;
        x = (width - w) / 2;
        y = 0;
    }
    else {
        w = width;
        h = (int)((double)width / VIEWPORT_RATIO);
        x = 0;
        y = (height - h) / 2;
    }

    glViewport(x, y, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(VIEWPORT_ASPECT, VIEWPORT_RATIO, 0.01, 10000.0);
}

void mouse(int UNUSED(button), int UNUSED(state), int x, int y)
{
    mouse_position.x = x;
    mouse_position.y = y;
}

void motion(int x, int y)
{
    rotate_camera(&camera, 0.5*(mouse_position.x - x), 0.5*(mouse_position.y - y));
    mouse_position.x = x;
    mouse_position.y = y;
    glutPostRedisplay();
}

void keyboard(unsigned char key, int UNUSED(x), int UNUSED(y))
{
    switch (key) {
    case 'w':
        set_camera_speed(&camera, 1.5);
        break;
    case 's':
        set_camera_speed(&camera, -1.5);
        break;
    case 'a':
        set_camera_side_speed(&camera, 1.5);
        break;
    case 'd':
        set_camera_side_speed(&camera, -1.5);
        break;
    case 't':
        if (is_preview_visible) {
            is_preview_visible = FALSE;
        }
        else {
            is_preview_visible = TRUE;
        }
        break;
	case '+':
		change_lighting(&scene, 0.1);
		break;
	case '-':
		change_lighting(&scene, -0.1);
		break;
	case 'u':
		if  (users_guide_visible) {
			users_guide_visible = FALSE;
		}
		else {
			users_guide_visible = TRUE;
		}
		break;
	}
	
    glutPostRedisplay();
}

void keyboard_up(unsigned char key, int UNUSED(x), int UNUSED(y))
{
    switch (key) {
    case 'w':
    case 's':
        set_camera_speed(&camera, 0.0);
        break;
    case 'a':
    case 'd':
        set_camera_side_speed(&camera, 0.0);
        break;
    }

    glutPostRedisplay();
}

void idle()
{
    static int last_frame_time = 0;
    int current_time;
    double elapsed_time;
   
    current_time = glutGet(GLUT_ELAPSED_TIME);
    elapsed_time = (double)(current_time - last_frame_time) / 1000;
    last_frame_time = current_time;

    update_camera(&camera, elapsed_time);

    glutPostRedisplay();
}
