/* This is Tutano's header for AI Pathfinding system.
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

#ifndef _BFS_H_
#define _BFS_H_

#include <stdio.h>
#include "../global.h"
#include "queue.h"
#include "customtypes.h"
#include "mapfunctions.h"

typedef struct {
	int level;
	VECTOR2 parent;
	char mark;
} BFS_ELEMENT;


void BFS_initialize_elements();
void BFS_mark(VECTOR2 pos);
void BFS_level(VECTOR2 pos, int l);
void BFS_parent(VECTOR2 c, VECTOR2 p);
void BFS (VECTOR2 start_pos, VECTOR2 end_pos, int testmap[MAPSIZE][MAPSIZE]);
void BFS_get_path_coords_dbg(VECTOR2 start_pos, VECTOR2 end_pos);
int BFS_get_path_coords(VECTOR2 start_pos, VECTOR2 end_pos, VECTOR2 pos_vet[MAPSIZE*MAPSIZE]);

#endif
