#include "bounding_box.h"

void hit_map_by_ball(Scene* scene, int i)
{
	float map_size = 5-0.02;
	
	if (scene->ball[i].position.x + ball_size >= map_size) {
		scene->ball[i].speed.x *= -1; scene->ball[i].position.x = map_size - ball_size;
	}
	else if (scene->ball[i].position.x - ball_size <= (-1) * map_size) {
		scene->ball[i].speed.x *= -1; scene->ball[i].position.x = (-1) * map_size + ball_size;
	}
	else if (scene->ball[i].position.y + ball_size >= map_size) {
		scene->ball[i].speed.y *= -1; scene->ball[i].position.y = map_size - ball_size;
	}
	else if (scene->ball[i].position.y - ball_size <= (-1) * map_size) {
		scene->ball[i].speed.y *= -1; scene->ball[i].position.y = (-1) * map_size + + ball_size;
	}
	else if (scene->ball[i].position.z + ball_size >= map_size * 2 - 1) {
		scene->ball[i].speed.z *= -1; scene->ball[i].position.z = map_size * 2 - 1 - ball_size;
	}
	else if (scene->ball[i].position.z - ball_size <= 0) {
		scene->ball[i].speed.z *= -1; scene->ball[i].position.z = 0 + ball_size;
	}
}

void ball_collision(Scene* scene, int i, int j)
{
	vec3 direction_vector;
	float ball_distance;
	float norm;
	
	direction_vector.x = scene->ball[j].position.x - scene->ball[i].position.x;
	direction_vector.y = scene->ball[j].position.y - scene->ball[i].position.y;
	direction_vector.z = scene->ball[j].position.z - scene->ball[i].position.z;
	ball_distance = sqrt( pow(direction_vector.x, 2) + pow(direction_vector.y, 2) + pow(direction_vector.z, 2) );
	
	if (2*ball_size > ball_distance) {
		
		norm = fabs(direction_vector.x + direction_vector.y + direction_vector.z);
		scene->ball[i].speed.x = direction_vector.x / norm * (-1);
		scene->ball[i].speed.y = direction_vector.y / norm * (-1);
		scene->ball[i].speed.z = direction_vector.z / norm * (-1);
	
		scene->ball[j].speed.x = direction_vector.x / norm;
		scene->ball[j].speed.y = direction_vector.y / norm;
		scene->ball[j].speed.z = direction_vector.z / norm;
	}
}