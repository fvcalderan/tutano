/* This is Tutano's header for entities' structures. 
 * Copyright (C) 2020 Felipe V. Calderan <fvcalderan@gmail.com>
 * Copyright (C) 2020 Natália V. Calderan <nvcalderan@gmail.com>
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.*/

#ifndef _ENTITYSTRUCTS_H_
#define _ENTITYSTRUCTS_H_

#include "../global.h"
#include "customtypes.h"

// player
typedef struct 
{
	float turn_speed;
	float move_speed;
	VECTOR2F abs_pos;
	float abs_rot;
	int done_rotating;
	int can_move;
	VECTOR2 grid_pos;
	VECTOR2 grid_going;
	int direction;
	int animation;
	int is_alive;
	int respawn_time;	// time needed to respawn
	int respawn;
	int reload_time;	// time needed to reload
	int reload;
	int flash_time;		// time needed to flash
	int flash;
} PLAYER;

// snake
typedef struct  {
	float turn_speed;
	float move_speed;
	VECTOR2F abs_pos;
	float abs_rot;
	int can_move;
	int is_attacking;
	VECTOR2 grid_pos;
	VECTOR2 grid_going;
	int direction;
	int animation;
	VECTOR2 movement_array[MAPSIZE*10];
	int BFS_size;
	int is_alive;
	int respawn_time;	// time needed to respawn
	int respawn;
	float try_reach;
	float attack_reach;
} SNAKE;

// scorpion
typedef struct  {
	float turn_speed;
	float move_speed;
	VECTOR2F abs_pos;
	float abs_rot;
	int can_move;
	int is_attacking;
	VECTOR2 grid_pos;
	VECTOR2 grid_going;
	int direction;
	int animation;
	VECTOR2 movement_array[MAPSIZE*10];
	int BFS_size;
	int is_alive;
	int respawn_time;	// time needed to respawn
	int respawn;
	float try_reach;
	float attack_reach;
} SCORPION;

// mummy
typedef struct  {
	float turn_speed;
	float move_speed;
	VECTOR2F abs_pos;
	float abs_rot;
	int can_move;
	int is_attacking;
	VECTOR2 grid_pos;
	VECTOR2 grid_going;
	int direction;
	int animation;
	VECTOR2 movement_array[MAPSIZE*10];
	int BFS_size;
	int is_alive;
	int respawn_time;	// time needed to respawn
	int respawn;
	float try_reach;
	float attack_reach;
} MUMMY;

// cursor
typedef struct 
{
	VECTOR2F abs_pos;
	VECTOR2 grid_pos;
	int move_time;
	int move_cd;
} CURSOR;

#endif
