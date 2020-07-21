/* This is Tutano's mummy model.
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

#include "m_mummy.h"

GLfloat mm_legsAng = 0.0f;
GLfloat mm_armsAngV = 0.0f;
GLfloat mm_armsAngvOffset = 0.0f;
GLfloat mm_hit_offset = 0.0f;
GLfloat mm_deathAng = 0.0f;
GLfloat mm_deathPieces = 0.0f;
int mm_hit_up = 1;
int mm_hit_timer = 0;

void m_mummy()
{
	glScalef(0.6, 0.6, 0.6);

	// head
	glPushMatrix();
		glTranslatef(0, 1.3, 0);
		tcube((int[]){43, 46, 42, 47, 45, 44});
	glPopMatrix();

	// torso
	glPushMatrix();
		glScalef(0.5, 1.6, 1);
		tcube((int[]){49, 52, 48, 52, 51, 50});
	glPopMatrix();

	// right arm
	glPushMatrix();
		glTranslatef(0, -0.2, 0.75);
		glScalef(0.5, 2, 0.5);
		tcube((int[]){54, 57, 53, 58, 56, 55});
	glPopMatrix();

	// left arm
	glPushMatrix();
		glTranslatef(0, -0.2, -0.75);
		glScalef(0.5, 2, 0.5);
		tcube((int[]){54, 57, 53, 58, 56, 55});
	glPopMatrix();

	// right leg
	glPushMatrix();
		glTranslatef(0, -1.8, 0.25);
		glScalef(0.5, 2, 0.5);
		tcube((int[]){60, 63, 59, 64, 62, 61});
	glPopMatrix();

	// left leg
	glPushMatrix();
		glTranslatef(0, -1.8, -0.25);
		glScalef(0.5, 2, 0.5);
		tcube((int[]){60, 63, 59, 64, 62, 61});
	glPopMatrix();
}

void m_mummy_anim()
{
	glTranslatef(0, 1.68, 0);
	glScalef(0.6, 0.6, 0.6);

	glTranslatef(0, -2, 0);
	glRotatef(mm_deathAng, 0, 0, 1);
	glTranslatef(0, 2, 0);

	// head
	glPushMatrix();
		glTranslatef(0, 1.3+sin(mm_deathPieces)*0.4, 0);
		glRotatef(sin(mm_deathPieces)*15, 1, 0, 0);
		tcube((int[]){43, 46, 42, 47, 45, 44});

		//eyes
		glDisable(GL_LIGHTING);
		glTranslatef(0.5002, 0.06, 0.25);
		glPushMatrix();
			glScalef(1, 0.12, 0.28);
			tquad(0);
		glPopMatrix();
		glTranslatef(0, 0, -0.5);
		glPushMatrix();
			glScalef(1, 0.12, 0.28);
			tquad(0);
		glPopMatrix();
		glEnable(GL_LIGHTING);
	glPopMatrix();

	// torso
	glPushMatrix();
		glScalef(0.5, 1.6, 1);
		tcube((int[]){49, 52, 48, 52, 51, 50});
	glPopMatrix();

	// right arm
	glPushMatrix();
		glTranslatef(0, -0.2, 0.75);
		glTranslatef(0, 0.75+sin(mm_deathPieces)*0.4, 0+sin(mm_deathPieces)*0.4);
		glRotatef(sin(mm_deathPieces)*12, 1, 0, 0);
		glRotatef(sin(mm_armsAngV)*5+mm_armsAngvOffset+sin(mm_hit_offset)*50, 0, 0, 1);
		glTranslatef(0, -0.75, 0);

		// falling part
		glPushMatrix();
			glTranslatef((sin(mm_armsAngvOffset)+sin(mm_hit_offset))*0.1-0.005*mm_armsAngvOffset, 
				          -(cos(mm_armsAngvOffset)+cos(mm_hit_offset))*0.25-0.4, 
				          0.26);
			glRotatef(sin(mm_armsAngV)*5+mm_armsAngvOffset+sin(mm_hit_offset)*50, 0, 0, -1);
			glRotatef(90, 0, 1, 0);
			glScalef(1, 1, 0.5);
			tfaces(65);
		glPopMatrix();

		glScalef(0.5, 2, 0.5);
		tcube((int[]){54, 57, 53, 58, 56, 55});
	glPopMatrix();

	// left arm
	glPushMatrix();
		glTranslatef(0, -0.2+sin(mm_deathPieces)*0.4, -0.75-sin(mm_deathPieces)*0.4);
		glTranslatef(0, 0.75, 0);
		glRotatef(sin(-mm_deathPieces)*10, 1, 0, 0);
		glRotatef(sin(mm_armsAngV)*5+mm_armsAngvOffset+sin(mm_hit_offset)*50, 0, 0, 1);
		glTranslatef(0, -0.75, 0);

		// falling part
		glPushMatrix();
			glTranslatef((sin(mm_armsAngvOffset)+sin(mm_hit_offset))*0.1-0.005*mm_armsAngvOffset, 
				          -(cos(mm_armsAngvOffset)+cos(mm_hit_offset))*0.25-0.4, 
				          -0.26);
			glRotatef(sin(mm_armsAngV)*5+mm_armsAngvOffset+sin(mm_hit_offset)*50, 0, 0, -1);
			glRotatef(90, 0, 1, 0);
			glScalef(1, 1, 0.5);
			tfaces(65);
		glPopMatrix();

		glScalef(0.5, 2, 0.5);
		tcube((int[]){54, 57, 53, 58, 56, 55});
	glPopMatrix();

	// right leg
	glPushMatrix();
		glTranslatef(0, -1.8, 0.25);
		glTranslatef(0, 1-sin(mm_deathPieces)*0.4, 0+sin(mm_deathPieces)*0.4);
		glRotatef(-sin(mm_deathPieces)*15, 1, 0, 0);
		glRotatef(sin(mm_legsAng)*35, 0, 0, 1);
		glTranslatef(0, -1, 0);
		glScalef(0.5, 2, 0.5);
		tcube((int[]){60, 63, 59, 64, 62, 61});
	glPopMatrix();

	// left leg
	glPushMatrix();
		glTranslatef(0, -1.8, -0.25);
		glTranslatef(0, 1-sin(mm_deathPieces)*0.4, 0-sin(mm_deathPieces)*0.4);
		glRotatef(sin(mm_deathPieces)*25, 1, 0, 0);
		glRotatef(-sin(mm_legsAng)*35, 0, 0, 1);
		glTranslatef(0, -1, 0);
		glScalef(0.5, 2, 0.5);
		tcube((int[]){60, 63, 59, 64, 62, 61});
	glPopMatrix();
}

void obj_mummy(int mm_animindex)
{
	switch(mm_animindex)
	{
		case 0: // idle
			mm_hit_up = 1;
			mm_hit_timer = 0;
			mm_hit_offset = 0;
			if (mm_legsAng > M_PI-0.2 && mm_legsAng < M_PI+0.2) mm_legsAng = 0;
			if (mm_legsAng > M_PI) mm_legsAng -= 0.2;
			if (mm_legsAng < M_PI && mm_legsAng != 0) mm_legsAng += 0.2;
			if (mm_hit_offset < 0) mm_hit_offset += 0.05;
			mm_armsAngvOffset = (mm_armsAngvOffset > 0) ? mm_armsAngvOffset-10 : 0;
			mm_armsAngV = (mm_armsAngV <= 2*M_PI) ? mm_armsAngV+0.02 : 0;
			m_mummy_anim();
			break;

		case 1: // ready
			mm_hit_up = 1;
			mm_hit_timer = 0;
			mm_hit_offset = 0;
			if (mm_legsAng > M_PI-0.2 && mm_legsAng < M_PI+0.2) mm_legsAng = 0;
			if (mm_legsAng > M_PI) mm_legsAng -= 0.2;
			if (mm_legsAng < M_PI && mm_legsAng != 0) mm_legsAng += 0.2;
			if (mm_hit_offset < 0) mm_hit_offset += 0.05;
			mm_armsAngvOffset = (mm_armsAngvOffset < 90) ? mm_armsAngvOffset+10 : 90;
			mm_armsAngV = (mm_armsAngV <= 2*M_PI) ? mm_armsAngV+0.02 : 0;
			m_mummy_anim();
			break;

		case 2: // walk
			mm_hit_up = 1;
			mm_hit_timer = 0;
			mm_hit_offset = 0;
			if (mm_hit_offset < 0) mm_hit_offset += 0.05;
			mm_legsAng = (mm_legsAng <= 2*M_PI) ? mm_legsAng+0.07 : 0;
			mm_armsAngvOffset = (mm_armsAngvOffset < 90) ? mm_armsAngvOffset+10 : 90;
			mm_armsAngV = (mm_armsAngV <= 2*M_PI) ? mm_armsAngV+0.07 : 0;
			m_mummy_anim();
			break;

		case 3: // ready hit
			if (mm_legsAng > M_PI-0.2 && mm_legsAng < M_PI+0.2) mm_legsAng = 0;
			if (mm_legsAng > M_PI) mm_legsAng -= 0.2;
			if (mm_legsAng < M_PI && mm_legsAng != 0) mm_legsAng += 0.2;
			mm_armsAngvOffset = (mm_armsAngvOffset < 90) ? mm_armsAngvOffset+10 : 90;
			if (mm_hit_offset < 0) mm_hit_offset += 0.05;
			if (mm_hit_timer == 0)
				if (mm_hit_up)
					if (mm_hit_offset < M_PI/2)
						mm_hit_offset += 0.1;
					else
						mm_hit_up = !mm_hit_up;
				else
					if (mm_hit_offset > -M_PI/6)
						mm_hit_offset -= 0.3;
					else
					{
						mm_hit_up = !mm_hit_up;
						mm_hit_timer = 100;
					}
				else
					mm_hit_timer -= 1;
			
			mm_armsAngV = (mm_armsAngV <= 2*M_PI) ? mm_armsAngV+0.02 : 0;
			m_mummy_anim();
			break;

		case 4: // walk hit
			mm_legsAng = (mm_legsAng <= 2*M_PI) ? mm_legsAng+0.07 : 0;
			mm_armsAngvOffset = (mm_armsAngvOffset < 90) ? mm_armsAngvOffset+10 : 90;
			if (mm_hit_offset < 0) mm_hit_offset += 0.05;
			if (mm_hit_timer == 0)
				if (mm_hit_up)
					if (mm_hit_offset < M_PI/2)
						mm_hit_offset += 0.1;
					else
						mm_hit_up = !mm_hit_up;
				else
					if (mm_hit_offset > -M_PI/6)
						mm_hit_offset -= 0.3;
					else
					{
						mm_hit_up = !mm_hit_up;
						mm_hit_timer = 100;
					}
				else
					mm_hit_timer -= 1;
			
			mm_armsAngV = (mm_armsAngV <= 2*M_PI) ? mm_armsAngV+0.07 : 0;
			m_mummy_anim();
			break;

		case 5: // death
			if (mm_legsAng > M_PI-0.2 && mm_legsAng < M_PI+0.2) mm_legsAng = 0;
			if (mm_legsAng > M_PI) mm_legsAng -= 0.2;
			if (mm_legsAng < M_PI && mm_legsAng != 0) mm_legsAng += 0.2;
			if (mm_hit_offset < 0) mm_hit_offset += 0.05;
			mm_hit_offset = (mm_hit_offset > 0) ? mm_hit_offset-10 : 0;
			mm_armsAngvOffset = (mm_armsAngvOffset > 0) ? mm_armsAngvOffset-10 : 0;
			mm_armsAngV = 0;
			mm_deathAng = (mm_deathAng < 90) ? mm_deathAng + 10 : 90;
			if (mm_deathAng >= 88)
			{
				mm_deathPieces = (mm_deathPieces < M_PI/2) ? mm_deathPieces + 0.5 : M_PI/2;
			}
			m_mummy_anim();
			break;

		case 6: // reverse death
			mm_deathAng = 0;
			mm_deathPieces = 0;
			m_mummy_anim();
			break;

		default:
			break;
	}
}
