#include "bounding_box.h"

#include <math.h>

void init_cube_bounding_box(Cube_bounding_box* cube_bounding_box)
{	
	cube_bounding_box->min_x = 0.0f;
	cube_bounding_box->min_y = 0.0f;
	cube_bounding_box->max_x = 0.0f;
	cube_bounding_box->max_y = 0.0f;
	
	distance = 0.05;
}

void make_cube_bounding_box(Cube_bounding_box* cube_bounding_box, vec3 center, float size)
{
	cube_bounding_box->min_x = center.x - size/2;
	cube_bounding_box->min_y = center.y - size/2;
	cube_bounding_box->max_x = center.x + size/2;
	cube_bounding_box->max_y = center.x + size/2;
}

int hit_bounding_box_x(Cube_bounding_box* cube_bounding_box, vec3 camera_position)
{
	if ( cube_bounding_box->min_y <= camera_position.y &&
		cube_bounding_box->max_y >= camera_position.y &&
		cube_bounding_box->min_x - camera_position.x > 0 &&
		cube_bounding_box->min_x - camera_position.x < distance ) {
		return 2;
	}
	else if ( cube_bounding_box->min_y <= camera_position.y &&
		cube_bounding_box->max_y >= camera_position.y &&
		cube_bounding_box->max_x - camera_position.x < 0 &&
		cube_bounding_box->max_x - camera_position.x > (-1) * distance ) {
		return 1;
	}
	else {
		return 0;
	}
}

int hit_bounding_box_y(Cube_bounding_box* cube_bounding_box, vec3 camera_position)
{
	if ( cube_bounding_box->min_x <= camera_position.x &&
		cube_bounding_box->max_x >= camera_position.x &&
		cube_bounding_box->min_y - camera_position.y > 0 &&
		cube_bounding_box->min_y - camera_position.y < distance ) {
		return 1;	
	}
	else if (cube_bounding_box->min_x <= camera_position.x &&
		cube_bounding_box->max_x >= camera_position.x &&
		cube_bounding_box->max_y - camera_position.y < 0 &&
		cube_bounding_box->max_y - camera_position.y > (-1) * distance ){
		return 2;
	}
	else {
		return 0;
	}
}

int hit_map_by_player(vec3 position)
{
	float map_size = 5 - distance;
	
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

void hit_map_by_ball(Balls* balls, int i)
{
	float map_size = 5 - distance;
	static float replacevalue = 0.1;
	
	if (balls->ball[i].position.x + ball_size >= map_size) {
		balls->ball[i].speed.x *= -1; balls->ball[i].position.x -= replacevalue;
	}
	else if (balls->ball[i].position.x - ball_size <= (-1) * map_size) {
		balls->ball[i].speed.x *= -1; balls->ball[i].position.x += replacevalue;
	}
	else if (balls->ball[i].position.y + ball_size >= map_size) {
		balls->ball[i].speed.y *= -1; balls->ball[i].position.y -= replacevalue;
	}
	else if (balls->ball[i].position.y - ball_size <= (-1) * map_size) {
		balls->ball[i].speed.y *= -1; balls->ball[i].position.y += replacevalue;
	}
	else if (balls->ball[i].position.z + ball_size >= map_size * 2 - 1) {
		balls->ball[i].speed.z *= -1; balls->ball[i].position.z -= replacevalue;
	}
	else if (balls->ball[i].position.z - ball_size <= 0) {
		balls->ball[i].speed.z *= -1; balls->ball[i].position.z += replacevalue;
	}
}

void ball_collision(Balls* balls, int i, int j)
{
	vec3 direction_vector;
	float ball_distance;
	float norm;
	
	direction_vector.x = balls->ball[j].position.x - balls->ball[i].position.x;
	direction_vector.y = balls->ball[j].position.y - balls->ball[i].position.y;
	direction_vector.z = balls->ball[j].position.z - balls->ball[i].position.z;
	ball_distance = sqrt( pow(direction_vector.x, 2) + pow(direction_vector.y, 2) + pow(direction_vector.z, 2) );
	
	if (2*ball_size > ball_distance) {
		
		norm = fabs(direction_vector.x + direction_vector.y + direction_vector.z);
		balls->ball[i].speed.x = direction_vector.x / norm * (-1);
		balls->ball[i].speed.y = direction_vector.y / norm * (-1);
		balls->ball[i].speed.z = direction_vector.z / norm * (-1);
	
		balls->ball[j].speed.x = direction_vector.x / norm;
		balls->ball[j].speed.y = direction_vector.y / norm;
		balls->ball[j].speed.z = direction_vector.z / norm;
	}
}