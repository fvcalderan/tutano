/* This is Tutano's AI Pathfinding system (using Breadth-First Search).
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

#include "BFS.h"

QUEUE BFS_queue;

// each place on the map can be analyzed by BFS
BFS_ELEMENT BFS_elements[MAPSIZE][MAPSIZE];

void BFS_initialize_elements()
{
	int i, j;

	for (i = 0; i < MAPSIZE; i++)
	{
		for (j = 0; j < MAPSIZE; j++)
		{
			BFS_elements[i][j].level = -1;
			BFS_elements[i][j].parent.x = -1;
			BFS_elements[i][j].parent.y = -1;
			BFS_elements[i][j].mark = 0;
		}
	}
}

// mark as visited
void BFS_mark(VECTOR2 pos)
{
	BFS_elements[pos.x][pos.y].mark = 1;
}

// how far is it from the start
void BFS_level(VECTOR2 pos, int l)
{
	BFS_elements[pos.x][pos.y].level = l;
}

// used for backtracking
void BFS_parent(VECTOR2 c, VECTOR2 p)
{
	BFS_elements[c.x][c.y].parent.x = p.x;;
	BFS_elements[c.x][c.y].parent.y = p.y;
}

// main algorithm based on Professor Reginaldo M. Kuroshu's slides
void BFS (VECTOR2 start_pos, VECTOR2 end_pos, int testmap[MAPSIZE][MAPSIZE])
{
	VECTOR2 actual, aux;

	BFS_initialize_elements();

	BFS_mark(start_pos);
	q_initialize(&BFS_queue);
	q_push(&BFS_queue, start_pos);
	BFS_level(start_pos, 0);

	while (!q_isempty(&BFS_queue))
	{
		// target unreachable
		if (q_isfull(&BFS_queue))
		{
			return;
		}

		actual = q_pop(&BFS_queue);

		// target unreachable
		if (actual.x < 0 || actual.y < 0)
		{
			return;
		}

		if (BFS_elements[actual.x+1][actual.y].mark == 0 && 
			map_walkable(testmap, actual.x+1, actual.y))
		{
			aux.x = actual.x+1; aux.y = actual.y;
			BFS_mark(aux);
			q_push(&BFS_queue, aux);
			BFS_level(aux, BFS_elements[actual.x][actual.y].level+1);
			BFS_parent(aux, actual);
			if (aux.x == end_pos.x && aux.y == end_pos.y)
			{
				return;
			}
		}

		if (BFS_elements[actual.x-1][actual.y].mark == 0 && 
			map_walkable(testmap, actual.x-1, actual.y))
		{
			aux.x = actual.x-1; aux.y = actual.y;
			BFS_mark(aux);
			q_push(&BFS_queue, aux);
			BFS_level(aux, BFS_elements[actual.x][actual.y].level+1);
			BFS_parent(aux, actual);
			if (aux.x == end_pos.x && aux.y == end_pos.y)
			{
				return;
			}
		}

		if (BFS_elements[actual.x][actual.y+1].mark == 0 && 
			map_walkable(testmap, actual.x, actual.y+1))
		{
			aux.x = actual.x; aux.y = actual.y+1;
			BFS_mark(aux);
			q_push(&BFS_queue, aux);
			BFS_level(aux, BFS_elements[actual.x][actual.y].level+1);
			BFS_parent(aux, actual);
			if (aux.x == end_pos.x && aux.y == end_pos.y)
			{
				return;
			}
		}

		
		if (BFS_elements[actual.x][actual.y-1].mark == 0 && 
			map_walkable(testmap, actual.x, actual.y-1))
		{	
			aux.x = actual.x; aux.y = actual.y-1;
			BFS_mark(aux);
			q_push(&BFS_queue, aux);
			BFS_level(aux, BFS_elements[actual.x][actual.y].level+1);
			BFS_parent(aux, actual);
			if (aux.x == end_pos.x && aux.y == end_pos.y)
			{
				return;
			}
		}
	}
}

// debugging only
void BFS_get_path_coords_dbg(VECTOR2 start_pos, VECTOR2 end_pos)
{
	VECTOR2 actual;
	actual = end_pos;

	while (BFS_elements[actual.x][actual.y].level > 0)
	{
		printf("(%d, %d)\n", actual.x, actual.y);
		actual = BFS_elements[actual.x][actual.y].parent;
	}
	printf("(%d, %d)\n", start_pos.x, start_pos.y);
}

// this is the function used in the main code
int BFS_get_path_coords(VECTOR2 start_pos, VECTOR2 end_pos, VECTOR2 pos_vet[MAPSIZE*MAPSIZE])
{
	int i = 0, j = 0, size = 0;

	VECTOR2 positions[MAPSIZE*MAPSIZE];
	positions[0] = end_pos;

	while (BFS_elements[positions[i].x][positions[i].y].level > 0)
	{
		positions[i+1] = BFS_elements[positions[i].x][positions[i].y].parent;
		i++;
	}
	i--;
	size = i;
	while (i > 0)
	{
		pos_vet[j].x = positions[i].x;
		pos_vet[j].y = positions[i].y;
		i--;
		j++;
	}
	return size;
}
