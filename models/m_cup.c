/* This is Tutano's cup model.
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

#include "m_cup.h"

GLfloat cp_floating = 0.0f;
GLfloat cp_rotation = 0.0f;
int cp_isAnimating = 0;

void m_cup_anim()
{
	int i;
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(0, 0.4 + sin(cp_floating) * 0.2, 0);
	glRotatef(cp_rotation, 0, 1, 0);
	glTranslatef(0, 1, 0);
	glRotatef((!cp_isAnimating) ? 0 : 15, 1, 0, 0);
	glTranslatef(0, -1, 0);

	// base
	glPushMatrix();
		glScalef(0.75, 0.1, 0.75);
		tcube((int[]){154, 154, 154, 154, 154, 154});
	glPopMatrix();

	// stem
	glPushMatrix();
		glTranslatef(0, 0.5, 0);
		glScalef(0.2, 1, 0.2);
		tcube((int[]){155, 155, 155, 155, 156, 156});
	glPopMatrix();

	// layers
	glPushMatrix();
		glTranslatef(0, 1, 0);
		for (i = 0; i < 5; i++)
		{
			glTranslatef(0, (i == 0) ? 0 : 0.2, 0);
			glPushMatrix();
				glScalef(0.4+sqrt(i)*0.3, 0.2, 0.4+sqrt(i)*0.3);
				if (i == 4) tcube((int[]){154, 157, 154, 154, 154, 154});
				else tcube((int[]){154, 154, 154, 154, 154, 154});
			glPopMatrix();
		}
	glPopMatrix();
}

void obj_cup(int cp_animindex)
{
	switch(cp_animindex)
	{
		case 0: // idle
			cp_floating = 0.0;
			cp_rotation = 0.0;
			cp_isAnimating = 0;
			m_cup_anim();
			break;
		case 1:
			cp_isAnimating = 1;
			cp_floating = (cp_floating <= 2 * M_PI) ? cp_floating + 0.05 : 0;
			cp_rotation = (cp_rotation < 360) ? cp_rotation + 1 : 0;
			m_cup_anim();
		default:
			break;
	}
}
