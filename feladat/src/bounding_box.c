#include "bounding_box.h"

void init_all_bounding_box(All_bounding_box* all_bounding_box)
{
	int i;
	all_bounding_box->distance = 0.05f;
	
	for (i=0; i<sizeof(all_bounding_box)/sizeof(all_bounding_box[0]); i++)
	{
		all_bounding_box->cube_bounding_box[i].left_bottom_front.x = 0;
		all_bounding_box->cube_bounding_box[i].left_bottom_front.y = 0;
		all_bounding_box->cube_bounding_box[i].left_bottom_front.z = 0;
		
		all_bounding_box->cube_bounding_box[i].left_upper_front.x = 0;
		all_bounding_box->cube_bounding_box[i].left_upper_front.y = 0;
		all_bounding_box->cube_bounding_box[i].left_upper_front.z = 0;
		
		all_bounding_box->cube_bounding_box[i].right_upper_front.x = 0;
		all_bounding_box->cube_bounding_box[i].right_upper_front.y = 0;
		all_bounding_box->cube_bounding_box[i].right_upper_front.z = 0;
		
		all_bounding_box->cube_bounding_box[i].right_bottom_front.x = 0;
		all_bounding_box->cube_bounding_box[i].right_bottom_front.y = 0;
		all_bounding_box->cube_bounding_box[i].right_bottom_front.z = 0;
		
		all_bounding_box->cube_bounding_box[i].left_bottom_back.x = 0;
		all_bounding_box->cube_bounding_box[i].left_bottom_back.y = 0;
		all_bounding_box->cube_bounding_box[i].left_bottom_back.z = 0;
		
		all_bounding_box->cube_bounding_box[i].left_upper_back.x = 0;
		all_bounding_box->cube_bounding_box[i].left_upper_back.y = 0;
		all_bounding_box->cube_bounding_box[i].left_upper_back.z = 0;
		
		all_bounding_box->cube_bounding_box[i].right_upper_back.x = 0;
		all_bounding_box->cube_bounding_box[i].right_upper_back.y = 0;
		all_bounding_box->cube_bounding_box[i].right_upper_back.z = 0;
		
		all_bounding_box->cube_bounding_box[i].right_bottom_back.x = 0;
		all_bounding_box->cube_bounding_box[i].right_bottom_back.y = 0;
		all_bounding_box->cube_bounding_box[i].right_bottom_back.z = 0;
	}
}

void make_cube_bounding_box(All_bounding_box* all_bounding_box, vec3 center, float size)
{
	int i;
	
	for (i=0; i<sizeof(all_bounding_box)/sizeof(all_bounding_box[0]); i++)
	{
		if(all_bounding_box->cube_bounding_box[i].left_bottom_front.x == 0.0f)
		{
			break;
		}
	}
	
	all_bounding_box->cube_bounding_box[i].left_bottom_front.x = center.x - size/2;
	all_bounding_box->cube_bounding_box[i].left_bottom_front.y = center.y + size/2;
	all_bounding_box->cube_bounding_box[i].left_bottom_front.z = center.z - size/2;
	
	all_bounding_box->cube_bounding_box[i].left_upper_front.x = center.x - size/2;
	all_bounding_box->cube_bounding_box[i].left_upper_front.y = center.y + size/2;
	all_bounding_box->cube_bounding_box[i].left_upper_front.z = center.z + size/2;
	
	all_bounding_box->cube_bounding_box[i].right_upper_front.x = center.x - size/2;
	all_bounding_box->cube_bounding_box[i].right_upper_front.y = center.y - size/2;
	all_bounding_box->cube_bounding_box[i].right_upper_front.z = center.z + size/2;
	
	all_bounding_box->cube_bounding_box[i].right_bottom_front.x = center.x - size/2;
	all_bounding_box->cube_bounding_box[i].right_bottom_front.y = center.y - size/2;
	all_bounding_box->cube_bounding_box[i].right_bottom_front.z = center.z - size/2;
	
	all_bounding_box->cube_bounding_box[i].left_bottom_back.x = center.x + size/2;
	all_bounding_box->cube_bounding_box[i].left_bottom_back.y = center.y + size/2;
	all_bounding_box->cube_bounding_box[i].left_bottom_back.z = center.z - size/2;
	
	all_bounding_box->cube_bounding_box[i].left_upper_back.x = center.x + size/2;
	all_bounding_box->cube_bounding_box[i].left_upper_back.y = center.y + size/2;
	all_bounding_box->cube_bounding_box[i].left_upper_back.z = center.z + size/2;
	
	all_bounding_box->cube_bounding_box[i].right_upper_back.x = center.x + size/2;
	all_bounding_box->cube_bounding_box[i].right_upper_back.y = center.y - size/2;
	all_bounding_box->cube_bounding_box[i].right_upper_back.z = center.z + size/2;
	
	all_bounding_box->cube_bounding_box[i].right_bottom_back.x = center.x + size/2;
	all_bounding_box->cube_bounding_box[i].right_bottom_back.y = center.y - size/2;
	all_bounding_box->cube_bounding_box[i].right_bottom_back.z = center.z - size/2;
}

int hit_bounding_box_x(All_bounding_box* all_bounding_box, vec3 camera_position)
{
	int hit = FALSE;
	int i;
	
	for (i=0; i<sizeof(all_bounding_box->cube_bounding_box)/sizeof(all_bounding_box->cube_bounding_box[0]); i++)
	{
		if (all_bounding_box->cube_bounding_box[i].left_bottom_front.x - camera_position.x < all_bounding_box->distance &&
		all_bounding_box->cube_bounding_box[i].left_bottom_front.x - camera_position.x > 0 &&
		all_bounding_box->cube_bounding_box[i].left_bottom_front.y >= camera_position.y &&
		all_bounding_box->cube_bounding_box[i].right_bottom_front.y <= camera_position.y)
		{
			hit = 1;
		}
		if (all_bounding_box->cube_bounding_box[i].left_bottom_back.x - camera_position.x > all_bounding_box->distance * -1 &&
		all_bounding_box->cube_bounding_box[i].left_bottom_back.x - camera_position.x < 0 &&
		all_bounding_box->cube_bounding_box[i].left_bottom_front.y >= camera_position.y &&
		all_bounding_box->cube_bounding_box[i].right_bottom_front.y <= camera_position.y)
		{
			hit = 2;
		}
	}
	
	return hit;
}

int hit_bounding_box_y(All_bounding_box* all_bounding_box, vec3 camera_position)
{
	int hit = FALSE;
	int i;
	
	for (i=0; i<sizeof(all_bounding_box->cube_bounding_box)/sizeof(all_bounding_box->cube_bounding_box[0]); i++)
	{
		if (all_bounding_box->cube_bounding_box[i].left_bottom_front.x <= camera_position.x &&
		all_bounding_box->cube_bounding_box[i].left_bottom_back.x >= camera_position.x &&
		all_bounding_box->cube_bounding_box[i].right_bottom_front.y - camera_position.y < all_bounding_box->distance &&
		all_bounding_box->cube_bounding_box[i].right_bottom_front.y - camera_position.y > 0)
		{
			hit = 1;
		}
		if (all_bounding_box->cube_bounding_box[i].left_bottom_front.x <= camera_position.x &&
		all_bounding_box->cube_bounding_box[i].left_bottom_back.x >= camera_position.x &&
		all_bounding_box->cube_bounding_box[i].left_bottom_front.y - camera_position.y > all_bounding_box->distance * -1 &&
		all_bounding_box->cube_bounding_box[i].left_bottom_front.y - camera_position.y < 0)
		{
			hit = 2;
		}
	}
	
	return hit;
}
