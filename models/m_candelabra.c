/* This is Tutano's candelabra model.
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

#include "m_candelabra.h"

GLfloat cb_floating = 0.0f;
GLfloat cb_rotation = 0.0f;
int cb_isAnimating = 0;

void cb_candle()
{
	glPushMatrix();
		// holder
		glPushMatrix();
			glScalef(0.3, 0.1, 0.3);
			tcube((int[]){161, 161, 161, 161, 161, 161});
		glPopMatrix();

		// candle
		glTranslatef(0, 0.2, 0);
		glPushMatrix();
			glScalef(0.15, 0.3, 0.15);
			tcube((int[]){162, 162, 162, 162, 162, 162});
		glPopMatrix();
	glPopMatrix();
}

void m_candelabra_anim()
{
	int i, j;
	glScalef(0.5, 0.5, 0.5);
	glTranslatef(0, 0.4 + sin(cb_floating) * 0.2, 0);
	glRotatef(cb_rotation, 0, 1, 0);
	glTranslatef(0, 1, 0);
	glRotatef((!cb_isAnimating) ? 0 : 15, 1, 0, 0);
	glTranslatef(0, -1, 0);

	// base
	glPushMatrix();
		for (i = 0; i < 3; i++)
		{
			glTranslatef(0, 0.1, 0);
			glPushMatrix();
				glScalef(1.25-i*0.25, 0.1, 1.25-i*0.25);
				tcube((int[]){160, 160, 160, 160, 160, 160});
			glPopMatrix();
		}
	glPopMatrix();

	// stem
	glPushMatrix();
		// stem's base
		glTranslatef(0, 1.5, 0);
		glPushMatrix();
			glScalef(0.2, 2.5, 0.2);
			tcube((int[]){160, 160, 160, 160, 160, 160});
		glPopMatrix();

		// candle and holder
		glTranslatef(0, 1.25, 0);
		cb_candle();
		
	glPopMatrix();

	// curves
	for (j = 0; j < 4; j++)
	{
		glPushMatrix();
			glTranslatef(0, 1.3, 0);
			glRotatef(j*90+45, 0, 1, 0);
			glRotatef(-49.5, 1, 0, 0);
			glTranslatef(0, 0.17, 0.495);
			glPushMatrix();
				glScalef(0.2, 0.4, 0.2);
				tcube((int[]){160, 160, 160, 160, 160, 160});
			glPopMatrix();
			for (i = 0; i < 4; i++)
			{
				glRotatef(-32.5, 1, 0, 0);
				glTranslatef(0, -0.375, -0.11);
				glPushMatrix();
					glScalef(0.2, 0.4, 0.2);
					tcube((int[]){160, 160, 160, 160, 160, 160});
				glPopMatrix();
				if (i == 3)
				{
					glTranslatef(0, -0.2, 0);
					glRotatef(180, 1, 0, 0);
					cb_candle();
				}
			}
		glPopMatrix();
	}

}

void obj_candelabra(int cb_animindex)
{
	switch(cb_animindex)
	{
		case 0: // idle
			cb_floating = 0.0;
			cb_rotation = 0.0;
			cb_isAnimating = 0;
			m_candelabra_anim();
			break;
		case 1:
			cb_isAnimating = 1;
			cb_floating = (cb_floating <= 2 * M_PI) ? cb_floating + 0.05 : 0;
			cb_rotation = (cb_rotation < 360) ? cb_rotation + 1 : 0;
			m_candelabra_anim();
		default:
			break;
	}
}
