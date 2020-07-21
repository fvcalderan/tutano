/* This is Tutano's door model.
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
#include "m_door.h"

GLfloat dr_pos[3] = {0.0f, 0.0f, 0.0f};

void m_door_anim_red()
{
	glPushMatrix();
		glTranslatef(0, -sin(dr_pos[0])*1.5, 0);
		glScalef(1, 1.5, 1);
        tcube((int[]){229, 232, 228, 233, 231, 230});
	glPopMatrix();
}

void m_door_anim_green()
{
	glPushMatrix();
		glTranslatef(0, -sin(dr_pos[1])*1.5, 0);
		glScalef(1, 1.5, 1);
        tcube((int[]){235, 238, 234, 239, 237, 236});
	glPopMatrix();
}

void m_door_anim_blue()
{
	glPushMatrix();
		glTranslatef(0, -sin(dr_pos[2])*1.5, 0);
		glScalef(1, 1.5, 1);
        tcube((int[]){241, 244, 240, 245, 243, 242});
	glPopMatrix();
}

void obj_door(int dr_animindex, int color)
{
	if (color == 0) // red
	{
		switch(dr_animindex)
		{
			case 0: // closed
				dr_pos[0] = (dr_pos[0] > 0) ? dr_pos[0] - 0.1 : 0;
				m_door_anim_red();
				break;
			case 1: // open
				dr_pos[0] = (dr_pos[0] < M_PI/2) ? dr_pos[0] + 0.1 : M_PI/2;
				m_door_anim_red();
			default:
				break;
		}
	}
	else if (color == 1) // green
	{
		switch(dr_animindex)
		{
			case 0: // closed
				dr_pos[1] = (dr_pos[1] > 0) ? dr_pos[1] - 0.1 : 0;
				m_door_anim_green();
				break;
			case 1: // open
				dr_pos[1] = (dr_pos[1] < M_PI/2) ? dr_pos[1] + 0.1 : M_PI/2;
				m_door_anim_green();
			default:
				break;
		}
	}
	else // blue
	{
		switch(dr_animindex)
		{
			case 0: // closed
				dr_pos[2] = (dr_pos[2] > 0) ? dr_pos[2] - 0.1 : 0;
				m_door_anim_blue();
				break;
			case 1: // open
				dr_pos[2] = (dr_pos[2] < M_PI/2) ? dr_pos[2] + 0.1 : M_PI/2;
				m_door_anim_blue();
			default:
				break;
		}
	}
}
