/* This is Tutano's snake model.
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

#include "m_snake.h"

GLfloat sn_curveRot = 0.0f;
GLfloat sn_hit_offset = 0.0f;
GLfloat sn_deathAng = 0.0f;
GLfloat sn_idleAng = 0.0f;
int sn_hit_up = 1;
int sn_hit_timer = 0;

void m_snake()
{
	int i = 0;

	glTranslatef(0, 0.1, 0);
	glScalef(0.6, 0.6, 0.6);
	glRotatef(sn_deathAng, 1, 0, 0);

	// body
	glPushMatrix();
		// ascending part
		glPushMatrix();
			for (i = 0; i < 3; i++)
			{
				glTranslatef(0.53, 0.13, 0);
				glRotatef(30-sin(sn_hit_offset)*25+sin(sn_deathAng/90)*25+sin(sn_idleAng), 0, 0, 1);
				glRotatef(sin(sn_curveRot)*5, 0, 1, 0);
				glPushMatrix();
					glScalef(0.5, 0.25, 0.25);
					tcube((int[]){130, 133, 129, 134, 132, 131});
				glPopMatrix();
			}
			// large part
			glTranslatef(0.5, 0, 0);
			glPushMatrix();
				glScalef(0.5, 0.25, 0.6);
				tcube((int[]){142, 145, 141, 146, 144, 143});
			glPopMatrix();

			// head
			glPushMatrix();
				glTranslatef(0.35, -0.07, 0);
				glPushMatrix();
					glScalef(0.2, 0.4, 0.35);
					tcube((int[]){148, 151, 147, 152, 150, 149});
				glPopMatrix();

				// tongue
				glTranslatef(-0.05, -0.25, 0);
				glPushMatrix();
					glScalef(0.025, 0.2, 0.1);
					tcube((int[]){153, 153, 153, 153, 153, 153});
				glPopMatrix();
			glPopMatrix();
		glPopMatrix();

		//desnending part
		glPushMatrix();

			// first tail curve
			for (i = 0; i < 3; i++)
			{
				glTranslatef((i == 0 ? 0 : 1) * -0.5, 0, 0);
				glRotatef(sin(sn_curveRot)*15, 0, 1, 0);
				glRotatef(-sin(sn_hit_offset)*15, 0, 0, 1);
				glPushMatrix();
					glScalef(0.5, 0.25, 0.25);
					tcube((int[]){130, 133, 129, 134, 132, 131});
				glPopMatrix();
			}

			// second tail curve
			for (i = 0; i < 3; i++)
			{
				glTranslatef(-0.5, 0, 0);
				glRotatef(-sin(sn_curveRot)*15, 0, 1, 0);
				glRotatef(sin(sn_hit_offset)*30, 0, 0, 1);
				glPushMatrix();
					glScalef(0.5, 0.25, 0.25);
					tcube((int[]){130, 133, 129, 134, 132, 131});
				glPopMatrix();
			}

			// rattle
			glPushMatrix();
				glTranslatef(-0.3, 0, 0);
				glRotatef(-sin(sn_curveRot)*15, 0, 1, 0);
				glPushMatrix();
					glScalef(0.3, 0.15, 0.15);
					tcube((int[]){136, 139, 135, 140, 138, 137});
				glPopMatrix();
			glPopMatrix();

		glPopMatrix();
	glPopMatrix();
}

void sn_fast_default()
{
	sn_hit_up = 1;
	sn_hit_timer = 0;
	sn_hit_offset = (sn_hit_offset > 0) ? sn_hit_offset - 0.2 : 0;
}

void obj_snake(int sn_animindex)
{
	switch(sn_animindex)
	{
		case 0: // idle
			sn_fast_default();
			sn_idleAng = (sn_idleAng < 2 * M_PI) ? sn_idleAng + 0.02 : 0;
			if ((sn_curveRot <= M_PI+0.15 && sn_curveRot >= M_PI-0.15) || sn_curveRot <= 0.0) 
				sn_curveRot = 0;
			if (sn_curveRot > M_PI) sn_curveRot -= 0.1;
			if (sn_curveRot < M_PI && sn_curveRot > 0) sn_curveRot -= 0.1;
			m_snake();
			break;

		case 1: // walk
			sn_fast_default();
			sn_curveRot = (sn_curveRot < 2 * M_PI) ? sn_curveRot + 0.1 : 0;
			m_snake();
			break;

		case 2: // still hit
			sn_idleAng = (sn_idleAng < 2 * M_PI) ? sn_idleAng + 0.02 : 0;
			if (sn_curveRot != 0)
			{
				if ((sn_curveRot <= M_PI+0.25 && sn_curveRot >= M_PI-0.25) || sn_curveRot <= 0.0) 
					sn_curveRot = 0;
				if (sn_curveRot > M_PI) sn_curveRot -= 0.2;
				if (sn_curveRot < M_PI && sn_curveRot > 0) sn_curveRot -= 0.2;
			}
			else
			{
				if (sn_hit_timer == 0)
					if (sn_hit_up)
						if (sn_hit_offset < M_PI/2)
							sn_hit_offset += 0.3;
						else
							sn_hit_up = !sn_hit_up;
					else
						if (sn_hit_offset > 0)
							sn_hit_offset -= 0.1;
						else
						{
							sn_hit_up = !sn_hit_up;
							sn_hit_timer = 100;
						}
					else
						sn_hit_timer -= 1;
			}
			m_snake();
			break;

		case 3: // walk hit
			sn_curveRot = (sn_curveRot < 2 * M_PI) ? sn_curveRot + 0.1 : 0;
			if (sn_hit_timer == 0)
				if (sn_hit_up)
					if (sn_hit_offset < M_PI/2)
						sn_hit_offset += 0.3;
					else
						sn_hit_up = !sn_hit_up;
				else
					if (sn_hit_offset > 0)
						sn_hit_offset -= 0.1;
					else
					{
						sn_hit_up = !sn_hit_up;
						sn_hit_timer = 100;
					}
				else
					sn_hit_timer -= 1;
			m_snake();
			break;

		case 4: // death
			sn_fast_default();
			if ((sn_curveRot <= M_PI+0.25 && sn_curveRot >= M_PI-0.25) || sn_curveRot <= 0.0) 
				sn_curveRot = 0;
			if (sn_curveRot > M_PI) sn_curveRot -= 0.2;
			if (sn_curveRot < M_PI && sn_curveRot > 0) sn_curveRot -= 0.2;
			sn_deathAng = (sn_deathAng < 90) ? sn_deathAng + 7 : 90;
			m_snake();
			break;

		case 5: // reverse death
			sn_fast_default();
			// if (sn_curveRot <= M_PI+0.25 && sn_curveRot >= M_PI-0.25 || sn_curveRot <= 0.0) 
			// 	sn_curveRot = 0;
			// if (sn_curveRot > M_PI) sn_curveRot -= 0.2;
			// if (sn_curveRot < M_PI && sn_curveRot > 0) sn_curveRot -= 0.2;
			// sn_deathAng = (sn_deathAng > 0) ? sn_deathAng - 7 : 0;
			sn_curveRot = 0;
			sn_deathAng = 0;
			m_snake();
			break;

		default:
			break;
	}
}
