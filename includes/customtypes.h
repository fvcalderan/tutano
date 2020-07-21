/* This is Tutano's header for custom types and related functions. 
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

#ifndef _CUSTOM_TYPES_H_
#define _CUSTOM_TYPES_H_

#include <math.h>
#include "../global.h"

// used for tiles only
typedef struct {
	int x;
	int y;
} VECTOR2;

// used to deal with XZ coordinates
typedef struct {
	float x;
	float z;
} VECTOR2F;

// used to deal with 3d space
typedef struct
{
	float x;
	float y;
	float z;
} VECTOR3;


float VECTOR3_norm(VECTOR3 vec);
float VECTOR3_xz_norm(VECTOR3 vec);
VECTOR3 VECTOR3_set(float x, float y, float z);
float VECTOR2F_dist(VECTOR2F a, VECTOR2F b);

#endif
