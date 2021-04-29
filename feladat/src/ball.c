#include "ball.h"

void update_bounce_balls(Scene* scene, double elapsed_time)
{
	float speed_constant = 1.2f;
	int last_ball_index = get_last_ball_index(scene);
	int i;
	int j;
	
	for (i=0; i<=last_ball_index; i++) {
		hit_map_by_ball(scene, i);
		
		scene->ball[i].position.x = scene->ball[i].position.x + (scene->ball[i].speed.x * speed_constant * elapsed_time);
		scene->ball[i].position.y = scene->ball[i].position.y + (scene->ball[i].speed.y * speed_constant * elapsed_time);
		scene->ball[i].position.z = scene->ball[i].position.z + (scene->ball[i].speed.z * speed_constant * elapsed_time);
			
	}
	
	for (i=0; i<=last_ball_index-1; i++) {
		for (j=i+1; j<=last_ball_index; j++) {
			ball_collision(scene, i, j);
		}
	}
}

void check_game_finished(Scene* scene, vec3 camera_position)
{
	int i;
	
	float xvalue;
	float yvalue;
	float zvalue;
	float distance;
	int win_time = 10;
	
	for (i=0; i<=get_last_ball_index(scene); i++) {
		xvalue = pow(camera_position.x - scene->ball[i].position.x , 2);
		yvalue = pow(camera_position.y - scene->ball[i].position.y , 2);
		zvalue = pow(camera_position.z - scene->ball[i].position.z , 2);
		distance = sqrt( xvalue + yvalue + zvalue );
		
		if (distance < ball_size && lose_game == FALSE) {
			close_game(scene);
			lose_game = TRUE;
		}
	}
	
	if (ball_simulation &&  scene->game_start_time + win_time <= glutGet(GLUT_ELAPSED_TIME) / 1000) {
		close_game(scene);
		win_game = TRUE;
	}		
}

void close_game(Scene* scene)
{
	int i;
	
	ball_simulation = FALSE;
	
	for (i=0; i<get_last_ball_index(scene); i++) {
		scene->ball[i].position.x = 0.0f;
		scene->ball[i].position.y = 0.0f;
		scene->ball[i].position.z = 10.0f;
	}
	
	set_last_ball_index(scene, -1);
}