#include <stdlib.h>

#include <math.h>

#include "bounce.h"
#include "texture.h"
#include "bounding_box.h"
#include "camera.h"

void init_balls(Balls* balls, int index)
{
	int norm;
	int i;
	
	for (i=0; i<get_last_ball_index(balls); i++) {
		if ( 2 * ball_size > sqrt( pow(2.0 - balls->ball[i].position.x, 2) + pow(0.0 - balls->ball[i].position.y, 2) + pow(2.0 - balls->ball[i].position.z, 2) ) ) {
			return;
		}
	}

	balls->ball[index].position.x = 2.0f;
	balls->ball[index].position.y = 0.0f;
	balls->ball[index].position.z = 2.0f;
	
	do {
		balls->ball[index].speed.x = rand()%201 / 100 - 1;
		balls->ball[index].speed.y = rand()%201 / 100 - 1;
		balls->ball[index].speed.z = rand()%201 / 100 - 1;
	} while (balls->ball[index].speed.z >= -0.3 && balls->ball[index].speed.z <= 0.3);
	
	norm = fabs(balls->ball[index].speed.x + balls->ball[index].speed.y + balls->ball[index].speed.z);
	balls->ball[index].speed.x /= norm;
	balls->ball[index].speed.y /= norm;
	balls->ball[index].speed.z /= norm;
	
	balls->ball[index].init_time = glutGet(GLUT_ELAPSED_TIME) / 1000 + 0.001;
	ball_size = 0.2;
}

void init_ball_times(Balls* balls)
{
	int i;
	
	for (i = 0; i < 10; i++) {
		balls->ball[i].init_time = 0.0f;
	}
}

vec3 get_ball_position(Balls* balls, int index)
{
	return balls->ball[index].position;
}

int get_last_ball_index(Balls* balls)
{
	int i;
	
	for (i=0; i<10; i++) {
		if(balls->ball[i].init_time == 0.0) {
			break;
		}
	}
	
	return i-1;
}
float get_last_ball_init_time(Balls* balls)
{
	int last_ball_index = get_last_ball_index(balls);
	if (last_ball_index == -1) {
		return 0;
	}
	return balls->ball[last_ball_index].init_time;
}

void update_bounce_balls(Balls* balls)
{
	float speed_constant = 0.01f;
	int last_ball_index = get_last_ball_index(balls);
	int i;
	int j;
	
	for (i=0; i<=last_ball_index; i++) {
		hit_map_by_ball(balls, i);
		
		balls->ball[i].position.x = balls->ball[i].position.x + (balls->ball[i].speed.x * speed_constant);
		balls->ball[i].position.y = balls->ball[i].position.y + (balls->ball[i].speed.y * speed_constant);
		balls->ball[i].position.z = balls->ball[i].position.z + (balls->ball[i].speed.z * speed_constant);
			
	}
	
	for (i=0; i<=last_ball_index-1; i++) {
		for (j=i+1; j<=last_ball_index; j++) {
			ball_collision(balls, i, j);
		}
	}
}

void game_end_result(Balls* balls, vec3 camera_position)
{
	int i;
	
	float xvalue;
	float yvalue;
	float zvalue;
	float distance;
	int win_time = 60;
	
	for (i=0; i<=get_last_ball_index(balls); i++) {
		xvalue = pow(camera_position.x - balls->ball[i].position.x , 2);
		yvalue = pow(camera_position.y - balls->ball[i].position.y , 2);
		zvalue = pow(camera_position.z - balls->ball[i].position.z , 2);
		distance = sqrt( xvalue + yvalue + zvalue );
		
		if (distance < ball_size && lose_game == FALSE) {
			ball_simulation = FALSE;
			for (i=0; i<get_last_ball_index(balls); i++) {
				balls->ball[i].position.x = 0.0f;
				balls->ball[i].position.y = 0.0f;
				balls->ball[i].position.z = 10.0f;
			}
			lose_game = TRUE;
			init_ball_times(balls);
		}
	}
	
	if (ball_simulation &&  balls->ball[0].init_time + win_time < glutGet(GLUT_ELAPSED_TIME) / 1000) {
		ball_simulation = FALSE;
			for (i=0; i<get_last_ball_index(balls); i++) {
				balls->ball[i].position.x = 0.0f;
				balls->ball[i].position.y = 0.0f;
				balls->ball[i].position.z = 10.0f;
			}
		win_game = TRUE;
		init_ball_times(balls);
	}		
}