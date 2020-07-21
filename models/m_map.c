/* This is Tutano's map models.
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

#include "m_map.h"

void obj_wall(int texture)
{
	glPushMatrix();
		glScalef(1, 1.5, 1);
        tcube((int[]){171+texture*7, 174+texture*7, 170+texture*7, 175+texture*7, 173+texture*7, 172+texture*7});
	glPopMatrix();
}

void obj_floor(int texture)
{
	glPushMatrix();
		glTranslatef(0, -0.75, 0);
        glRotatef(90, 0, 0, 1);
        tquad(176+texture*7);
	glPopMatrix();
}

void obj_player_spawn()
{
	glPushMatrix();
		glTranslatef(0, -0.75, 0);
        glRotatef(90, 0, 0, 1);
        tquad(219);
	glPopMatrix();
}

void obj_player_exit()
{
	glPushMatrix();
		glTranslatef(0, -0.75, 0);
        glRotatef(90, 0, 0, 1);
        tquad(220);
	glPopMatrix();
}

void obj_wall_bottom(int texture)
{
	if (texture < 42)
	{
		glPushMatrix();
			glTranslatef(0, -0.75, 0);
	        glRotatef(90, 0, 0, 1);
	        tquad(175+texture*7);
		glPopMatrix();
	}
	else
	{
		glPushMatrix();
			glTranslatef(0, -0.75, 0);
	        glRotatef(90, 0, 0, 1);
	        tquad(336);
		glPopMatrix();
	}
}

void obj_mob_spawn()
{
	glPushMatrix();
		glTranslatef(0, -0.75, 0);
        glRotatef(90, 0, 0, 1);
        tquad(221);
	glPopMatrix();
}

void obj_door_open()
{
	glPushMatrix();
		glTranslatef(0, -0.75, 0);
        glRotatef(90, 0, 0, 1);
        tquad(232);
	glPopMatrix();
}

void obj_key_spawn(int texture)
{
	glPushMatrix();
		glTranslatef(0, -0.75, 0);
        glRotatef(90, 0, 0, 1);
        tquad(252+texture);
	glPopMatrix();
}

void obj_water_settings(int mode)
{
	glPushMatrix();
		glTranslatef(0, -0.75, 0);
        glRotatef(90, 0, 0, 1);
        tquad(301+mode);
	glPopMatrix();
}

void obj_dark_settings(int mode)
{
	glPushMatrix();
		glTranslatef(0, -0.75, 0);
        glRotatef(90, 0, 0, 1);
        tquad(305+mode);
	glPopMatrix();
}

void obj_water(GLint wt_keyframe, GLfloat rot)
{
	glPushMatrix();
		glTranslatef(0, -0.75, 0);
        glRotatef(90, 0, 0, 1);
        glRotatef(rot, 1, 0, 0);
        tquad(255 + wt_keyframe/4);
	glPopMatrix();
}

void obj_water_wall(GLint wt_keyframe, GLfloat rot)
{
	glPushMatrix();
	glRotatef(rot, 0, 1, 0);
		glScalef(1, 1.5, 1);
        tcube((int[]){309+wt_keyframe/4, 336, 308, 337, 335, 334});
	glPopMatrix();
}

void obj_teleport(int mode)
{
	glPushMatrix();
		glTranslatef(0, -0.75, 0);
        glRotatef(90, 0, 0, 1);
        tquad(299+mode);
	glPopMatrix();
}

void obj_transparent_wall(int texture, int wt_keyframe)
{
	glColor4f(1.0f, 1.0f, 1.0f, CAM_BLOCK_TRANSPARENCY); 

	if (texture < 42)
	{
	glPushMatrix();
		glTranslatef(0, 0.75, 0);
		glRotatef(270, 0, 0, 1);
		tquad(174+texture*7);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-0.5, 0, 0);
		glRotatef(180, 0, 1, 0);
		glScalef(1, 1.5, 1);
		tquad(171+texture*7);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.5, 0, 0);
		glRotatef(180, 0, 1, 0);
		glScalef(1, 1.5, 1);
		tquad(171+texture*7);
	glPopMatrix(); 

	glPushMatrix();
		glTranslatef(0, 0, -0.5);
		glRotatef(90, 0, 1, 0);
		glScalef(1, 1.5, 1);
		tquad(171+texture*7);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 0, 0.495);
		glRotatef(90, 0, 1, 0);
		glScalef(1, 1.5, 1);
		tquad(171+texture*7);
	glPopMatrix();
	}
	else
	{
		glPushMatrix();

			glRotatef(((float)texture - 42.0f)*90.0f, 0, 1, 0);

			glPushMatrix();
				glTranslatef(0, 0.75, 0);
				glRotatef(270, 0, 0, 1);
				tquad(336);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(-0.5, 0, 0);
				glRotatef(180, 0, 1, 0);
				glScalef(1, 1.5, 1);
				tquad(309+wt_keyframe/4);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0.5, 0, 0);
				glRotatef(180, 0, 1, 0);
				glScalef(1, 1.5, 1);
				tquad(185);
			glPopMatrix(); 

			glPushMatrix();
				glTranslatef(0, 0, -0.5);
				glRotatef(90, 0, 1, 0);
				glScalef(1, 1.5, 1);
				tquad(185);
			glPopMatrix();

			glPushMatrix();
				glTranslatef(0, 0, 0.495);
				glRotatef(90, 0, 1, 0);
				glScalef(1, 1.5, 1);
				tquad(185);
			glPopMatrix();

		glPopMatrix();
	}

	glColor4f(1.0f, 1.0f, 1.0f, 0.0); 
}

void obj_pedestal(int texture)
{
	int i;

	// floor
	glPushMatrix();
		glTranslatef(0, -0.75, 0);
        glRotatef(90, 0, 0, 1);
        tquad(176+texture*7);
	glPopMatrix();

	// base
	glPushMatrix();
		glScalef(0.5, 0.75, 0.5);
		glTranslatef(0, -0.95, 0);
		for (i = 0; i < 2; i++)
		{
			if (i>0) glTranslatef(0, 0.1, 0);
			glPushMatrix();
				glScalef(1-i*0.25, 0.1, 1-i*0.25);
				tcube((int[]){227, 227, 227, 227, 227, 227});
			glPopMatrix();
		}

		glPushMatrix();
			glTranslatef(0, 0.3, 0);
			glScalef(0.5, 0.6, 0.5);
			tcube((int[]){223, 227, 222, 227, 225, 224});
		glPopMatrix();

		glTranslatef(0, 0.65, 0);
		for (i = 0; i < 2; i++)
		{
			if (i>0) glTranslatef(0, 0.1, 0);
			glPushMatrix();
				glScalef(0.75+i*0.25, 0.1, 0.75+i*0.25);
				tcube((int[]){227, 226, 227, 227, 227, 227});
			glPopMatrix();
		}
	glPopMatrix();
}
