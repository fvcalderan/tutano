/* This is Tutano's header for map functions. 
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

#ifndef _MAPFUNCTIONS_H_
#define _MAPFUNCTIONS_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../global.h"

int map_exists(char *campaign, int num);
void save_map(int map[MAPSIZE][MAPSIZE], char *campaign, char *filename);
void save_ed_map(int map[MAPSIZE][MAPSIZE], char *filename);
void load_map(int map[MAPSIZE][MAPSIZE], char *campaign, char *filename);
void load_ed_map(int map[MAPSIZE][MAPSIZE], char *filename);
void save_score(int *score, char *campaign);
void load_score(int *score, char *campaign);
void generate_blank_map(int map[MAPSIZE][MAPSIZE]);
int map_ttype(int map[MAPSIZE][MAPSIZE], int x, int y);
int map_walkable(int map[MAPSIZE][MAPSIZE], int x, int y);
int map_get_floor_skin(int map[MAPSIZE][MAPSIZE], int x, int y);
int map_get_wall_skin(int map[MAPSIZE][MAPSIZE], int x, int y);
int map_get_pedestal_skin(int map[MAPSIZE][MAPSIZE], int x, int y);
int map_get_key_floor_skin(int map[MAPSIZE][MAPSIZE], int x, int y);
int map_get_door_skin(int map[MAPSIZE][MAPSIZE], int x, int y);
int map_get_water_settings_skin(int map[MAPSIZE][MAPSIZE], int x, int y);
int map_get_dark_settings_skin(int map[MAPSIZE][MAPSIZE], int x, int y);
int map_ed_ttype(int block_val);
int map_ed_get_floor_skin(int block_val);
int map_ed_get_wall_skin(int block_val);
int map_ed_get_pedestal_skin(int block_val);
int map_ed_get_key_floor_skin(int block_val);
int map_ed_get_door_skin(int block_val);
int map_ed_get_water_settings_skin(int block_val);
int map_ed_get_dark_settings_skin(int block_val);

#endif
