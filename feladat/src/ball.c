#include "ball.h"

void hit_map_by_ball(Ball ball[], int i)
{
	float map_size = 5-0.05;
	static float ball_size = 0.2f;
	
	if (ball[i].position.x + ball_size >= map_size) {
		ball[i].speed.x *= -1; ball[i].position.x = map_size - ball_size;
	}
	else if (ball[i].position.x - ball_size <= (-1) * map_size) {
		ball[i].speed.x *= -1; ball[i].position.x = (-1) * map_size + ball_size;
	}
	else if (ball[i].position.y + ball_size >= map_size) {
		ball[i].speed.y *= -1; ball[i].position.y = map_size - ball_size;
	}
	else if (ball[i].position.y - ball_size <= (-1) * map_size) {
		ball[i].speed.y *= -1; ball[i].position.y = (-1) * map_size + + ball_size;
	}
	else if (ball[i].position.z + ball_size >= map_size * 2 - 1) {
		ball[i].speed.z *= -1; ball[i].position.z = map_size * 2 - 1 - ball_size;
	}
	else if (ball[i].position.z - ball_size <= 0) {
		ball[i].speed.z *= -1; ball[i].position.z = 0 + ball_size;
	}
}

void ball_collision(Ball ball[], int i, int j)
{
	vec3 direction_vector;
	float ball_distance;
	float norm;
	static float ball_size = 0.2f;
	
	direction_vector.x = ball[j].position.x - ball[i].position.x;
	direction_vector.y = ball[j].position.y - ball[i].position.y;
	direction_vector.z = ball[j].position.z - ball[i].position.z;
	ball_distance = sqrt( pow(direction_vector.x, 2) + pow(direction_vector.y, 2) + pow(direction_vector.z, 2) );
	
	if (2*ball_size > ball_distance) {
		
		norm = fabs(direction_vector.x + direction_vector.y + direction_vector.z);
		ball[i].speed.x = direction_vector.x / norm * (-1);
		ball[i].speed.y = direction_vector.y / norm * (-1);
		ball[i].speed.z = direction_vector.z / norm * (-1);
	
		ball[j].speed.x = direction_vector.x / norm;
		ball[j].speed.y = direction_vector.y / norm;
		ball[j].speed.z = direction_vector.z / norm;
	}
}

void update_bounce_balls(Ball ball[], double elapsed_time, int last_ball_index)
{
	float speed_constant = 1.2f;
	int i;
	int j;
	
	for (i=0; i<=last_ball_index; i++) {
		hit_map_by_ball(ball, i);
		
		ball[i].position.x = ball[i].position.x + (ball[i].speed.x * speed_constant * elapsed_time);
		ball[i].position.y = ball[i].position.y + (ball[i].speed.y * speed_constant * elapsed_time);
		ball[i].position.z = ball[i].position.z + (ball[i].speed.z * speed_constant * elapsed_time);
			
	}
	
	for (i=0; i<=last_ball_index-1; i++) {
		for (j=i+1; j<=last_ball_index; j++) {
			ball_collision(ball, i, j);
		}
	}
}

bool check_game_finished(Ball ball[], vec3 player_position, float game_start_time, float win_time, int last_ball_index)
{
	int i;
	
	float xvalue;
	float yvalue;
	float zvalue;
	float distance;
	static float ball_size = 0.2f;
	
	for (i=0; i<=last_ball_index; i++) {
		xvalue = pow(player_position.x - ball[i].position.x , 2);
		yvalue = pow(player_position.y - ball[i].position.y , 2);
		zvalue = pow(player_position.z - ball[i].position.z , 2);
		distance = sqrt( xvalue + yvalue + zvalue );
		
		if (distance < ball_size) {
			close_game(ball, last_ball_index);
			return true;
		}
	}
	
	if (game_start_time + win_time <= glutGet(GLUT_ELAPSED_TIME) / 1000) {
		close_game(ball, last_ball_index);
		return true;
	}

	return false;
}

void close_game(Ball ball[], int last_ball_index)
{
	int i;
	
	for (i=0; i<last_ball_index; i++) {
		ball[i].position.x = 0.0f;
		ball[i].position.y = 0.0f;
		ball[i].position.z = 10.0f;
	}
}