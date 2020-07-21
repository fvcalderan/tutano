/* This is Tutano's header for the map models.
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

#ifndef _M_MAP_H_
#define _M_MAP_H_

#include <GL/glut.h>
#include <math.h>
#include "../includes/primitives.h"
#include "../global.h"

void obj_wall(int texture);
void obj_floor(int texture);
void obj_player_spawn();
void obj_player_exit();
void obj_wall_bottom(int texture);
void obj_mob_spawn();
void obj_door_open();
void obj_key_spawn(int texture);
void obj_water_settings(int mode);
void obj_dark_settings(int mode);
void obj_water(GLint wt_keyframe, GLfloat rot);
void obj_water_wall(GLint wt_keyframe, GLfloat rot);
void obj_teleport(int mode);
void obj_transparent_wall(int texture, int wt_keyframe);
void obj_pedestal(int texture);

#endif
