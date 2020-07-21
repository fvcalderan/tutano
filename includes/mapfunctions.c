/* This is Tutano's map functions. 
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

#include "mapfunctions.h"

int map_exists(char *campaign, int num)
{
	FILE * mapfile;

	char path[100];
	char filename[10];

	if (num < 10)
	{
		sprintf(filename, "map0%d", num);
	}
	else
	{
		sprintf(filename, "map%d", num);
	}
	
	strcpy(path, "campaigns/");
	strcat(path, campaign);
	strcat(path, "/");
	strcat(path, filename);

	mapfile = fopen(path, "rb");

	if (mapfile) {
	   fclose(mapfile);
	   return 1;
	}
	else
	{
	   return 0;
	}
}

void save_map(int map[MAPSIZE][MAPSIZE], char *campaign, char *filename)
{
	FILE *mapfile;

	char path[100];
	strcpy(path, "campaigns/");
	strcat(path, campaign);
	strcat(path, "/");
	strcat(path, filename);

	if((mapfile = fopen(path, "wb")) == NULL) 
	{
		printf("\n\tCritical Error: Map could not be saved!\n\n");
		exit(0);
	}

	if(fwrite(map, sizeof(int), MAPSIZE*MAPSIZE, mapfile) != MAPSIZE*MAPSIZE)
	{
		printf("\n\tCritical Error: Failed to write map to file\n\n");
		exit(0);
	}

	fclose(mapfile);
}

void save_ed_map(int map[MAPSIZE][MAPSIZE], char *filename)
{
	FILE *mapfile;

	if((mapfile = fopen(filename, "wb")) == NULL) 
	{
		printf("\n\tCritical Error: Map could not be saved!\n\n");
		exit(0);
	}

	if(fwrite(map, sizeof(int), MAPSIZE*MAPSIZE, mapfile) != MAPSIZE*MAPSIZE)
	{
		printf("\n\tCritical Error: Failed to write map to file\n\n");
		exit(0);
	}

	fclose(mapfile);
}

void load_map(int map[MAPSIZE][MAPSIZE], char *campaign, char *filename)
{
	FILE *mapfile;

	char path[100];
	strcpy(path, "campaigns/");
	strcat(path, campaign);
	strcat(path, "/");
	strcat(path, filename);

	if((mapfile = fopen(path, "rb")) == NULL) 
	{
		printf("\n\tCritical Error: Map could not be opened or Campaign doesn't exist!\n\n");
		exit(0);
	}

	if(fread(map, sizeof(int), MAPSIZE*MAPSIZE, mapfile) != MAPSIZE*MAPSIZE)
	{
		if(feof(mapfile))
		{
		    printf("\n\tCritical Error: Premature end of score file!\n\n");
		    exit(0);
		}
		else
		{
		    printf("\n\tCritical Error: Map could not be read!\n\n");
		    exit(0);
		}
	}

	fclose(mapfile);
}

void load_ed_map(int map[MAPSIZE][MAPSIZE], char *filename)
{
	FILE *mapfile;

	if((mapfile = fopen(filename, "rb")) == NULL) 
	{
		printf("\n\tCritical Error: Map could not be opened or Campaign doesn't exist!\n\n");
		exit(0);
	}

	if(fread(map, sizeof(int), MAPSIZE*MAPSIZE, mapfile) != MAPSIZE*MAPSIZE)
	{
		if(feof(mapfile))
		{
		    printf("\n\tCritical Error: Premature end of score file!\n\n");
		    exit(0);
		}
		else
		{
		    printf("\n\tCritical Error: Map could not be read!\n\n");
		    exit(0);
		}
	}

	fclose(mapfile);
}

void save_score(int *score, char *campaign)
{
	FILE *scorefile;

	char path[100];
	strcpy(path, "campaigns/");
	strcat(path, campaign);
	strcat(path, "/score");

	if((scorefile = fopen(path, "wb")) == NULL) 
	{
		printf("\n\tCritical Error: Score could not be saved!\n\n");
		exit(0);
	}

	if(fwrite(score, sizeof(int), 1, scorefile) != 1)
	{
		printf("\n\tCritical Error: Failed to write score to file\n\n");
		exit(0);
	}

	fclose(scorefile);
}

void load_score(int *score, char *campaign)
{
	FILE *scorefile;

	char path[100];
	strcpy(path, "campaigns/");
	strcat(path, campaign);
	strcat(path, "/score");

	if((scorefile = fopen(path, "rb")) == NULL) 
	{
		save_score((int[]){0}, campaign);
		printf("\n\tScore file created for this campaign.\n\tPlease restart the game.\n\n");
		exit(0);
	}

	if(fread(score, sizeof(int), 1, scorefile) != 1)
	{
		if(feof(scorefile))
		{
		    printf("\n\tCritical Error: Premature end of score file!\n\n");
		    exit(0);
		}
		else
		{
		    printf("\n\tCritical Error: Score could not be read!\n\n");
		    exit(0);
		}
	}

	fclose(scorefile);
}

void generate_blank_map(int map[MAPSIZE][MAPSIZE])
{
	int i, j;

	for (i = 0; i < MAPSIZE; i++)
	{
		for (j = 0; j < MAPSIZE; j++)
		{
			map[i][j] = 0;
		}
	}
}

// return type of the selected tile
int map_ttype(int map[MAPSIZE][MAPSIZE], int x, int y)
{
    if (x > MAPSIZE || y > MAPSIZE)
    {
        return 0;
    }
	if (map[x][y] >= 0 && map[x][y] <= 6) return M_FLOOR;				  // floor
	else if (map[x][y] >= 7 && map[x][y] <= 13) return M_WALL;			  // wall
	else if (map[x][y] == 14) return M_PLAYER_SPAWN;					  // player_spawn
	else if (map[x][y] == 15) return M_PLAYER_EXIT;						  // player_exit
	else if (map[x][y] == 16) return M_MOB_SPAWN_SNAKE;					  // snake
	else if (map[x][y] == 17) return M_MOB_SPAWN_SCORPION;				  // scorpion
	else if (map[x][y] == 18) return M_MOB_SPAWN_MUMMY;					  // mummy
	else if (map[x][y] >= 19 && map[x][y] <= 25) return M_ITEM;			  // item
	else if (map[x][y] >= 26 && map[x][y] <= 28) return M_KEY;			  // key
	else if (map[x][y] >= 29 && map[x][y] <= 31) return M_DOOR_CLOSED;	  // door closed
	else if (map[x][y] == 32) return M_DOOR_OPEN;						  // door open
	else if (map[x][y] == 33) return M_WATER;							  // water
	else if (map[x][y] == 34) return M_TELEPORT;						  // teleport
	else if (map[x][y] >= 35 && map[x][y] <= 38) return M_WATER_SETTINGS; // water_settings 
	else if (map[x][y] >= 39 && map[x][y] <= 41) return M_DARK_SETTINGS;  // dark settings
	else if (map[x][y] >= 42 && map[x][y] <= 45) return M_WATER_WALL;     // water wall
    return -1;
}

// return if tile is walkable
int map_walkable(int map[MAPSIZE][MAPSIZE], int x, int y)
{
    if (x > MAPSIZE || y > MAPSIZE)
    {
        return 0;
    }
	if (map_ttype(map, x, y) == M_FLOOR) return 1;
	else if (map_ttype(map, x, y) == M_PLAYER_SPAWN) return 1;
	else if (map_ttype(map, x, y) == M_PLAYER_EXIT) return 1;
	else if (map_ttype(map, x, y) == M_MOB_SPAWN_SNAKE) return 1;
	else if (map_ttype(map, x, y) == M_MOB_SPAWN_SCORPION) return 1;
	else if (map_ttype(map, x, y) == M_MOB_SPAWN_MUMMY) return 1;
	else if (map_ttype(map, x, y) == M_KEY) return 1;
	else if (map_ttype(map, x, y) == M_DOOR_OPEN) return 1;
	else if (map_ttype(map, x, y) == M_WATER) return 1;
	else if (map_ttype(map, x, y) == M_TELEPORT) return 1;
	return 0;
}

// find correct value for texturing the floor tiles
int map_get_floor_skin(int map[MAPSIZE][MAPSIZE], int x, int y)
{
    if (x > MAPSIZE || y > MAPSIZE)
    {
        return 0;
    }
	return map[x][y];
}

// find correct value for texturing the walls
int map_get_wall_skin(int map[MAPSIZE][MAPSIZE], int x, int y)
{
    if (x > MAPSIZE || y > MAPSIZE)
    {
        return 0;
    }
	if (map[x][y] >= 42)
	{
		return map[x][y];
	}
	return map[x][y] - 7;
}

// find correct value for texturing pedestal tile's floor
int map_get_pedestal_skin(int map[MAPSIZE][MAPSIZE], int x, int y)
{
    if (x > MAPSIZE || y > MAPSIZE)
    {
        return 0;
    }
	return map[x][y] - 19;
}

// get correct gem color for key floor
int map_get_key_floor_skin(int map[MAPSIZE][MAPSIZE], int x, int y)
{
    if (x > MAPSIZE || y > MAPSIZE)
    {
        return 0;
    }
	return map[x][y] - 26;
}

// get correct gems color for door
int map_get_door_skin(int map[MAPSIZE][MAPSIZE], int x, int y)
{
    if (x > MAPSIZE || y > MAPSIZE)
    {
        return 0;
    }
	return map[x][y] - 29;
}

// get correct water settings skin
int map_get_water_settings_skin(int map[MAPSIZE][MAPSIZE], int x, int y)
{
    if (x > MAPSIZE || y > MAPSIZE)
    {
        return 0;
    }
	return map[x][y] - 35;
}

// get correct dark settings skin
int map_get_dark_settings_skin(int map[MAPSIZE][MAPSIZE], int x, int y)
{
    if (x > MAPSIZE || y > MAPSIZE)
    {
        return 0;
    }
	return map[x][y] - 39;
}


// the following functions are editor only

// return type of the selected tile
int map_ed_ttype(int block_val)
{
	if (block_val >= 0 && block_val <= 6) return M_FLOOR;				  // floor
	else if (block_val >= 7 && block_val <= 13) return M_WALL;			  // wall
	else if (block_val == 14) return M_PLAYER_SPAWN;					  // player_spawn
	else if (block_val == 15) return M_PLAYER_EXIT;						  // player_exit
	else if (block_val == 16) return M_MOB_SPAWN_SNAKE;					  // snake
	else if (block_val == 17) return M_MOB_SPAWN_SCORPION;				  // scorpion
	else if (block_val == 18) return M_MOB_SPAWN_MUMMY;					  // mummy
	else if (block_val >= 19 && block_val <= 25) return M_ITEM;			  // item
	else if (block_val >= 26 && block_val <= 28) return M_KEY;			  // key
	else if (block_val >= 29 && block_val <= 31) return M_DOOR_CLOSED;	  // door closed
	else if (block_val == 32) return M_DOOR_OPEN;						  // door open
	else if (block_val == 33) return M_WATER;							  // water
	else if (block_val == 34) return M_TELEPORT;						  // teleport
	else if (block_val >= 35 && block_val <= 38) return M_WATER_SETTINGS; // water_settings
	else if (block_val >= 39 && block_val <= 41) return M_DARK_SETTINGS;  // dark settings
	else if (block_val >= 42 && block_val <= 45) return M_WATER_WALL;     // water wall
    return 0;
}

// find correct value for texturing the floor tiles
int map_ed_get_floor_skin(int block_val)
{
	return block_val;
}

// find correct value for texturing the walls
int map_ed_get_wall_skin(int block_val)
{
	if (block_val >= 42)
	{
		return block_val;
	}
	return block_val - 7;
}

// find correct value for texturing pedestal tile's floor
int map_ed_get_pedestal_skin(int block_val)
{
	return block_val - 19;
}

// get correct gem color for key floor
int map_ed_get_key_floor_skin(int block_val)
{
	return block_val - 26;
}

// get correct gems color for door
int map_ed_get_door_skin(int block_val)
{
	return block_val - 29;
}

// get correct water settings skin
int map_ed_get_water_settings_skin(int block_val)
{
	return block_val - 35;
}

// get correct dark settings skin
int map_ed_get_dark_settings_skin(int block_val)
{
	return block_val - 39;
}
