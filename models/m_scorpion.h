/* This is Tutano's header for the scorpion model.
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

#ifndef _M_SCORPION_H
#define _M_SCORPION_H

#include <GL/glut.h>
#include <math.h>
#include "../includes/primitives.h"

void m_scorpion_legspair(GLfloat translate, GLfloat rotate);
void m_scorpion_arms();
void m_scorpion_anim();
void sc_fast_default();
void obj_scorpion(int sc_animindex);

#endif
