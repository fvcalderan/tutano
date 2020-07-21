/* This is Tutano's key model.
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

#include "m_key.h"

GLfloat km_floating = 0.0f;
GLfloat km_rotation = 0.0f;
int km_isAnimating = 0;

void m_key_anim(int texture)
{
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(0, 0.4 + sin(km_floating) * 0.2, 0);
	glRotatef(km_rotation, 0, 1, 0);
	glTranslatef(0, 1, 0);
	glRotatef((!km_isAnimating) ? 0 : 30, 1, 0, 0);
	glTranslatef(0, -1, 0);

	// stem
	glPushMatrix();
		glTranslatef(0, 1, 0);
		glScalef(0.2, 2.3, 0.3);
		tcube((int[]){166, 163, 167, 163, 163, 163});
	glPopMatrix();

	// little thing that opens the door
	glPushMatrix();
		glTranslatef(0, 0.4, 0.4);
		glScalef(0.2, 0.4, 0.5);
		tcube((int[]){168, 163, 169, 163, 163, 163});
	glPopMatrix();

	// base
	glPushMatrix();
		glTranslatef(0, 2.65, 0);
		glScalef(0.2, 1, 1);
		tcube((int[]){246+texture*2, 163, 247+texture*2, 163, 163, 163});
	glPopMatrix();
}

void obj_key(int km_animindex, int texture)
{
	switch(km_animindex)
	{
		case 0: // idle
			km_floating = 0.0;
			km_rotation = 0.0;
			km_isAnimating = 0;
			m_key_anim(texture);
			break;
		case 1:
			km_isAnimating = 1;
			km_floating = (km_floating <= 2 * M_PI) ? km_floating + 0.05 : 0;
			km_rotation = (km_rotation < 360) ? km_rotation + 1 : 0;
			m_key_anim(texture);
		default:
			break;
	}
}
