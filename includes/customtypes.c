/* This is Tutano's custom types and related functions. 
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

#include "customtypes.h"

float VECTOR3_norm(VECTOR3 vec)
{
    return sqrt(vec.x*vec.x + vec.y*vec.y + vec.z*vec.z);
}

float VECTOR3_xz_norm(VECTOR3 vec)
{
    return sqrt(vec.x*vec.x + vec.z*vec.z);
}

VECTOR3 VECTOR3_set(float x, float y, float z)
{
    VECTOR3 vec;
    vec.x = x;
    vec.y = y;
    vec.z = z;
    return vec;
}

float VECTOR2F_dist(VECTOR2F a, VECTOR2F b)
{
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.z - b.z) * (a.z - b.z));
}
