/* This is Tutano's teapot model.
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

#include "m_teapot.h"

GLfloat tp_floating = 0.0f;
GLfloat tp_rotation = 0.0f;
int tp_isAnimating = 0;

void m_teapot_anim()
{
	int i;
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(0, 0.4 + sin(tp_floating) * 0.2, 0);
	glRotatef(tp_rotation, 0, 1, 0);
	glTranslatef(0, 1, 0);
	glRotatef((!tp_isAnimating) ? 0 : 15, 1, 0, 0);
	glTranslatef(0, -1, 0);

	// layers
	glPushMatrix();
		for (i = 0; i < 5; i++)
		{
			glTranslatef(0, (i == 0) ? 0 : 0.1, 0);
			glPushMatrix();
				glScalef(1+sqrt(i)*0.4, 0.1, 1+sqrt(i)*0.4);
				glColor4f(1.0, 0.1+i*0.05, 0.1+i*0.05, 0.0);
				tcube((int[]){158, 158, 158, 158, 158, 158});
			glPopMatrix();
		}

		glTranslatef(0, 0.1, 0);
		for (i = 0; i < 8; i++)
		{
			glTranslatef(0, (i == 0) ? 0 : 0.1, 0);
			glPushMatrix();
				glScalef(1.8-i*0.1, 0.1, 1.8-i*0.1);
				glColor4f(1.0, 0.35+i*0.05, 0.35+i*0.05, 0.0);
				if (i==7)
					tcube((int[]){158, 159, 158, 158, 158, 158});
				else
					tcube((int[]){158, 158, 158, 158, 158, 158});
			glPopMatrix();
		}

		glTranslatef(0, 0.15, 0);
		glPushMatrix();
			glScalef(0.2, 0.2, 0.2);
			glColor4f(1.0, 0.80, 0.80, 0.0);
			tcube((int[]){158, 158, 158, 158, 158, 158});
		glPopMatrix();

	glPopMatrix();

	// handle
	glPushMatrix();
		glTranslatef(0, 1.1, 0.7);
		for (i = 0; i < 7; i++)
		{
			glTranslatef(0, -0.09, (i == 0) ? 0 : 0.26);
			glRotatef((i == 0) ? -15 : 36.5, 1, 0, 0);
			glPushMatrix();
				glScalef(0.2, 0.1, 0.3);
				glColor4f(1.0, 0.60-i*0.07, 0.60-i*0.07, 0.0);
				tcube((int[]){158, 158, 158, 158, 158, 158});
			glPopMatrix();
		}
	glPopMatrix();

	// part that pours tea (but it won't, since it's solid)
	glPushMatrix();
		glTranslatef(0, 0.45, -0.9);
		glRotatef(20, 1, 0, 0);
		for (i = 0; i < 3; i++)
		{
			glTranslatef(0, (i == 0) ? 0 : 0.08, (i == 0) ? 0 : -0.215);
			glRotatef((i == 0) ? 0 : 35, 1, 0, 0);	
			glPushMatrix();
				glScalef(0.4-i*0.06, 0.2, 0.3);
				glColor4f(1.0, 0.35+i*0.07, 0.35+i*0.07, 0.0);
				tcube((int[]){158, 158, 158, 158, 158, 158});
			glPopMatrix();
		}

		glTranslatef(0, -0.065, -0.215);
		for (i = 0; i < 2; i++)
		{
			glTranslatef(0, (i == 0) ? 0 : -0.065, (i == 0) ? 0 : -0.215);
			glRotatef(-35, 1, 0, 0);
			glPushMatrix();
				glScalef(0.22-i*0.06, 0.2, 0.3);
				glColor4f(1.0, 0.65+i*0.07, 0.65+i*0.07, 0.0);
				tcube((int[]){158, 158, 158, 158, 158, 158});
			glPopMatrix();
		}
	glPopMatrix();

	glColor4f(1.0, 1.0, 1.0, 0.0);
}

void obj_teapot(int tp_animindex)
{
	switch(tp_animindex)
	{
		case 0: // idle
			tp_floating = 0.0;
			tp_rotation = 0.0;
			tp_isAnimating = 0;
			m_teapot_anim();
			break;
		case 1:
			tp_isAnimating = 1;
			tp_floating = (tp_floating <= 2 * M_PI) ? tp_floating + 0.05 : 0;
			tp_rotation = (tp_rotation < 360) ? tp_rotation + 1 : 0;
			m_teapot_anim();
		default:
			break;
	}
}
