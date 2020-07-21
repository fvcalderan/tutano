/* This is Tutano's player model.
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

#include "m_player.h"

GLfloat pl_legsAng = 0.0f;
GLfloat pl_armsAngH = 0.0f;
GLfloat pl_armsAngV = 0.0f;
GLfloat pl_armsAngvOffset = 0.0f;
GLfloat pl_hit_offset = 0.0f;
GLfloat pl_deathAng = 0.0;
int pl_hit_up = 1;

int GLOBAL_pl_hit_timer;
int GLOBAL_pl_hit_timer_cd;

void m_player()
{
	glScalef(0.5, 0.5, 0.5);

	// hat top
	glPushMatrix();
		glTranslatef(0, 1.5, 0);
		glScalef(0.7, 0.7, 0.7);
		tcube((int[]){30, 33, 29, 34, 32, 31});
	glPopMatrix();

	// hat base
	glPushMatrix();
		glTranslatef(0, 1.8, 0);
		glScalef(1.4, 0.2, 1.4);
		tcube((int[]){27, 26, 27, 28, 27, 27});
	glPopMatrix();

	// head
	glPushMatrix();
		glTranslatef(0, 1.3, 0);
		tcube((int[]){4, 7, 3, 8, 6, 5});
	glPopMatrix();

	// torso
	glPushMatrix();
		glScalef(0.5, 1.6, 1);
		tcube((int[]){10, 13, 9, 13, 12, 11});
	glPopMatrix();

	// right arm
	glPushMatrix();
		glTranslatef(0, 0, 0.75);
		glScalef(0.5, 1.6, 0.5);
		tcube((int[]){15, 18, 14, 19, 17, 16});
	glPopMatrix();

	// gun
	glPushMatrix();
		glTranslatef(0, 0, 0.75);
		glTranslatef(0.5, -0.9, 0);
		glScalef(0.35, 0.8, 0.35);
		tcube((int[]){36, 39, 35, 40, 38, 37});
		glScalef(2.85714285714, 1.25, 2.85714285714);
		glTranslatef(-0.35, 0.30, 0);
		glScalef(0.35, 0.20, 0.35);
		tcube((int[]){41, 41, 41, 41, 41, 41});
	glPopMatrix();

	// left arm
	glPushMatrix();
		glTranslatef(0, 0, -0.75);
		glScalef(0.5, 1.6, 0.5);
		tcube((int[]){15, 18, 14, 19, 17, 16});
	glPopMatrix();

	// right leg
	glPushMatrix();
		glTranslatef(0, -1.8, 0.25);
		glScalef(0.5, 2, 0.5);
		tcube((int[]){21, 24, 20, 25, 23, 22});
	glPopMatrix();

	// left leg
	glPushMatrix();
		glTranslatef(0, -1.8, -0.25);
		glScalef(0.5, 2, 0.5);
		tcube((int[]){21, 24, 20, 25, 23, 22});
	glPopMatrix();
}

void m_player_anim()
{
	glTranslatef(0, 1.4, 0);
	glScalef(0.5, 0.5, 0.5);

	glTranslatef(0, -2, 0);
	glRotatef(pl_deathAng/(M_PI/2)*90, 0, 0, 1);
	glTranslatef(0, 2, 0);

	// hat top
	glPushMatrix();
		glTranslatef(0, 1.9, 0);
		glScalef(0.7, 0.7, 0.7);
		tcube((int[]){30, 33, 29, 34, 32, 31});
	glPopMatrix();

	// hat base
	glPushMatrix();
		glTranslatef(0, 1.8, 0);
		glScalef(1.4, 0.2, 1.4);
		tcube((int[]){27, 26, 27, 28, 27, 27});
	glPopMatrix();

	// head
	glPushMatrix();
		glTranslatef(0, 1.3, 0);
		tcube((int[]){4, 7, 3, 8, 6, 5});
	glPopMatrix();

	// torso
	glPushMatrix();
		glScalef(0.5, 1.6, 1);
		tcube((int[]){10, 13, 9, 13, 12, 11});
	glPopMatrix();

	// right arm
	glPushMatrix();
		glTranslatef(0, 0, 0.75);
		glTranslatef(0, 0.55, 0);
		glPushMatrix();
			glRotatef(sin(pl_armsAngV)*5+pl_armsAngvOffset+sin(pl_hit_offset)*25, 0, 0, 1);
			glRotatef(pl_armsAngH, 1, 0, 0);
			glTranslatef(0, -0.55, 0);
			glScalef(0.5, 1.6, 0.5);
			tcube((int[]){15, 18, 14, 19, 17, 16});
		glPopMatrix();

		// gun
		glPushMatrix();
			glRotatef(sin(pl_armsAngV)*5+pl_armsAngvOffset+sin(pl_hit_offset)*25, 0, 0, 1);
			glTranslatef(0, -0.55, 0);
			glTranslatef(0.5-pl_deathAng*0.4, -0.9, -pl_armsAngH*0.0375);
			glRotatef(sin(pl_deathAng)*90, 0, -1, 0);
			glScalef(0.35, 0.8, 0.35);
			tcube((int[]){36, 39, 35, 40, 38, 37});
			glScalef(2.85714285714, 1.25, 2.85714285714);
			glTranslatef(-0.35, 0.30, 0);
			glScalef(0.35, 0.20, 0.35);
			tcube((int[]){41, 41, 41, 41, 41, 41});
		glPopMatrix();
	glPopMatrix();

	// left arm
	glPushMatrix();
		glTranslatef(0, 0, -0.75);
		glTranslatef(0, 0.55, 0);
		glRotatef(sin(pl_armsAngV)*5+pl_armsAngvOffset+sin(pl_hit_offset)*25, 0, 0, 1);
		glRotatef(-pl_armsAngH, 1, 0, 0);
		glTranslatef(0, -0.55, 0);
		glScalef(0.5, 1.6, 0.5);
		tcube((int[]){15, 18, 14, 19, 17, 16});
	glPopMatrix();

	// right leg
	glPushMatrix();
		glTranslatef(0, -1.8, 0.25);
		glTranslatef(0, 1, 0);
		glRotatef(sin(pl_legsAng)*45, 0, 0, 1);
		glRotatef(sin(pl_deathAng)*15, -1, 0, 0);
		glTranslatef(0, -1, 0);
		glScalef(0.5, 2, 0.5);
		tcube((int[]){21, 24, 20, 25, 23, 22});
	glPopMatrix();

	// left leg
	glPushMatrix();
		glTranslatef(0, -1.8, -0.25);
		glTranslatef(0, 1, 0);
		glRotatef(-sin(pl_legsAng)*45, 0, 0, 1);
		glRotatef(sin(pl_deathAng)*15, 1, 0, 0);
		glTranslatef(0, -1, 0);
		glScalef(0.5, 2, 0.5);
		tcube((int[]){21, 24, 20, 25, 23, 22});
	glPopMatrix();
}

void pl_fast_default()
{
	pl_hit_up = 1;
	GLOBAL_pl_hit_timer = 0;
	pl_hit_offset = 0;
}

void pl_fast_leg_fix()
{
	if (pl_legsAng > M_PI-0.2 && pl_legsAng < M_PI+0.2) pl_legsAng = 0;
	if (pl_legsAng > M_PI) pl_legsAng -= 0.2;
	if (pl_legsAng < M_PI && pl_legsAng != 0) pl_legsAng += 0.2;
}
void obj_player(int pl_animindex)
{
	switch(pl_animindex)
	{
		case 0: // idle
			pl_fast_default();
			pl_fast_leg_fix();
			pl_armsAngH = (pl_armsAngH > 0) ? pl_armsAngH-2 : 0;
			pl_armsAngvOffset = (pl_armsAngvOffset > 0) ? pl_armsAngvOffset-10 : 0;
			pl_armsAngV = (pl_armsAngV <= 2*M_PI) ? pl_armsAngV+0.02 : 0;
			m_player_anim();
			break;

		case 1: // aim
			pl_fast_default();
			pl_fast_leg_fix();
			pl_armsAngH = (pl_armsAngH < 20) ? pl_armsAngH+2 : 20;
			pl_armsAngvOffset = (pl_armsAngvOffset < 90) ? pl_armsAngvOffset+10 : 90;
			pl_armsAngV = (pl_armsAngV <= 2*M_PI) ? pl_armsAngV+0.02 : 0;
			m_player_anim();
			break;

		case 2: // walk aim
			pl_fast_default();
			pl_legsAng = (pl_legsAng <= 2*M_PI) ? pl_legsAng+0.1 : 0;
			pl_armsAngH = (pl_armsAngH < 20) ? pl_armsAngH+2 : 20;
			pl_armsAngvOffset = (pl_armsAngvOffset < 90) ? pl_armsAngvOffset+10 : 90;
			pl_armsAngV = (pl_armsAngV <= 2*M_PI) ? pl_armsAngV+0.1 : 0;
			m_player_anim();
			break;

		case 3: // fire aim
			pl_fast_leg_fix();
			pl_armsAngH = (pl_armsAngH < 20) ? pl_armsAngH+2 : 20;
			pl_armsAngvOffset = (pl_armsAngvOffset < 90) ? pl_armsAngvOffset+10 : 90;
			if (GLOBAL_pl_hit_timer == 0)
				if (pl_hit_up)
					if (pl_hit_offset < M_PI/2)
						pl_hit_offset += 0.6;
					else
						pl_hit_up = !pl_hit_up;
				else
					if (pl_hit_offset > 0)
						pl_hit_offset -= 0.1;
					else
					{
						pl_hit_up = !pl_hit_up;
						GLOBAL_pl_hit_timer = GLOBAL_pl_hit_timer_cd;
					}
			else
				GLOBAL_pl_hit_timer -= 1;

			pl_armsAngV = (pl_armsAngV <= 2*M_PI) ? pl_armsAngV+0.02 : 0;
			m_player_anim();
			break;

		case 4: // fire walk aim
			pl_legsAng = (pl_legsAng <= 2*M_PI) ? pl_legsAng+0.1 : 0;
			pl_armsAngvOffset = (pl_armsAngvOffset < 90) ? pl_armsAngvOffset+10 : 90;
			pl_armsAngH = (pl_armsAngH < 20) ? pl_armsAngH+2 : 20;
			if (GLOBAL_pl_hit_timer == 0)
				if (pl_hit_up)
					if (pl_hit_offset < M_PI/2)
						pl_hit_offset += 0.6;
					else
						pl_hit_up = !pl_hit_up;
				else
					if (pl_hit_offset > 0)
						pl_hit_offset -= 0.1;
					else
					{
						pl_hit_up = !pl_hit_up;
						GLOBAL_pl_hit_timer = GLOBAL_pl_hit_timer_cd;
					}
			else
				GLOBAL_pl_hit_timer -= 1;

			pl_armsAngV = (pl_armsAngV <= 2*M_PI) ? pl_armsAngV+0.1 : 0;
			m_player_anim();
			break;

		case 5: // death
			pl_hit_up = 1;
			GLOBAL_pl_hit_timer = 0;
			pl_hit_offset = 0;
			if (pl_legsAng > M_PI-0.2 && pl_legsAng < M_PI+0.2) pl_legsAng = 0;
			if (pl_legsAng > M_PI) pl_legsAng -= 0.2;
			if (pl_legsAng < M_PI && pl_legsAng != 0) pl_legsAng += 0.2;
			pl_armsAngvOffset = (pl_armsAngvOffset > 0) ? pl_armsAngvOffset-10 : 0;
			pl_armsAngV = (pl_armsAngV > 0) ? pl_armsAngV-0.1 : 0;

			pl_deathAng = (pl_deathAng < M_PI/2) ? pl_deathAng + 0.125 : M_PI/2;
			pl_armsAngH = (pl_armsAngH > -45) ? pl_armsAngH - 5 : -45;

			m_player_anim();
			break;

		case 6: // reverse death
			//pl_deathAng = (pl_deathAng > 0) ? pl_deathAng - 0.1 : 0;
			//pl_armsAngH = (pl_armsAngH < 0) ? pl_armsAngH + 5 : 0;
			pl_deathAng = 0;
			pl_armsAngH = 0;
			m_player_anim();
			break;

		default:
			break;
	}
}
