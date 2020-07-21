/* This is Tutano's scorpion model.
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

#include "m_scorpion.h"

GLfloat sc_trot = 0;
GLfloat sc_tang = -M_PI/6;
GLfloat sc_tx = -M_PI/6;
GLfloat sc_ty = -M_PI/6;
GLfloat sc_hit_offset = 0;
GLfloat sc_legsAng = 0;
GLfloat sc_idle_pose = 0;
GLfloat sc_deathAng = 0.0f;
int sc_hit_up = 1;
int sc_hit_timer = 0;

void m_scorpion_legspair(GLfloat translate, GLfloat rotate)
{
	glPushMatrix();
		// main transform
		glTranslatef(translate, -0.1, 0);
		glRotatef(rotate, 0, 1, 0);

		// axis
		glPushMatrix();
			glScalef(0.1, 0.1, 2);
			tcube((int[]){96, 96, 96, 96, 96, 96});
		glPopMatrix();

		// right leg
		glPushMatrix();
			glTranslatef(0, -0.1, 1.1);
			glRotatef(-45, 1, 0, 0);
			glScalef(0.2, 0.4, 0.1);
			tcube((int[]){98, 99, 97, 99, 101, 102});
		glPopMatrix();

		// left leg
		glPushMatrix();
			glTranslatef(0, -0.1, -1.1);
			glRotatef(45, 1, 0, 0);
			glScalef(0.2, 0.4, 0.1);
			tcube((int[]){98, 100, 97, 100, 101, 102});
		glPopMatrix();
	glPopMatrix();
}

void m_scorpion_arms()
{
	glPushMatrix();
		glRotatef(cos(sc_legsAng)*15, 0, 1, 0);
			glPushMatrix();
				glTranslatef(0, 0.145, 0);
				glScalef(0.3, 0.1, 2);
				tcube((int[]){115, 116, 115, 116, 115, 115}); // arms axis
			glPopMatrix();

		//right
		glPushMatrix();
			glRotatef(-10, 0, 1, 0);
			glTranslatef(0.35, 0.2, 0.95);
			glPushMatrix();
				glScalef(1, 0.1, 0.3);
				tcube((int[]){118, 121, 117, 122, 120, 119}); // right arm
			glPopMatrix();
			// claws
			glPushMatrix();
				glTranslatef(0.5, 0, 0.25);
				glScalef(0.4, 0.15, 0.2);
				tcube((int[]){124, 127, 123, 128, 126, 125}); // right
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.5, 0, -0.25);
				glScalef(0.4, 0.15, 0.2);
				tcube((int[]){124, 127, 123, 128, 126, 125}); //left
			glPopMatrix();
		glPopMatrix();

		// left
		glPushMatrix();
			glRotatef(10, 0, 1, 0);
			glTranslatef(0.35, 0.2, -0.95);
			glPushMatrix();
				glScalef(1, 0.1, 0.3);
				tcube((int[]){118, 121, 117, 122, 120, 119}); // left arm
			glPopMatrix();
			// claws
			glPushMatrix();
				glTranslatef(0.5, 0, 0.25);
				glScalef(0.4, 0.15, 0.2);
				tcube((int[]){124, 127, 123, 128, 126, 125}); // right
			glPopMatrix();
			glPushMatrix();
				glTranslatef(0.5, 0, -0.25);
				glScalef(0.4, 0.15, 0.2);
				tcube((int[]){124, 127, 123, 128, 126, 125}); //left
			glPopMatrix();
		glPopMatrix();

	glPopMatrix();
}

void m_scorpion_anim()
{
	glTranslatef(1.2, 0.38, 0);
	glRotatef(sc_deathAng, 1, 0, 0);

	// body
	glPushMatrix();
		glTranslatef(0, -sin(sc_idle_pose)*0.015-sin(sc_trot)*0.22, 0);
		glRotatef(-sin(sc_trot)+sin(sc_idle_pose), 1, 0, 0);
		glRotatef(-sin(sc_trot)*7, 0, 0, 1);

		// head
		glPushMatrix();
			glTranslatef(0.4, 0, 0);
			glScalef(0.25, 0.25, 0.5);
			tcube((int[]){67, 70, 66, 71, 69, 68});
		glPopMatrix();

		// arms
		m_scorpion_arms();

		glPushMatrix();
			glScalef(0.6, 0.4, 1);
			tcube((int[]){73, 76, 72, 77, 75, 74}); // front
		glPopMatrix();

		glTranslatef(-0.6, 0.1, 0);

		glPushMatrix();
			glScalef(0.6, 0.6, 1);
			tcube((int[]){79, 82, 78, 83, 81, 80}); // middle-front
		glPopMatrix();

		glTranslatef(-0.6, 0.1, 0);

		glPushMatrix();
			glScalef(0.6, 0.8, 1);
			tcube((int[]){85, 88, 84, 89, 87, 86}); // middle-back
		glPopMatrix();

		glTranslatef(-0.6, 0.1, 0);

		glScalef(0.6, 1, 1);
		tcube((int[]){91, 94, 90, 95, 93, 92}); //back
	glPopMatrix();

	// legs
	m_scorpion_legspair(0, sin(sc_legsAng)*10);
	m_scorpion_legspair(-0.6, -sin(sc_legsAng)*10);
	m_scorpion_legspair(-1.2, cos(sc_legsAng)*10);
	m_scorpion_legspair(-1.8, -cos(sc_legsAng)*10);

	// metasoma and telson
	glPushMatrix();
		// metasomas
		glTranslatef(-2.35, 0.825-sin(sc_idle_pose)*0.02, 0);
		glRotatef(-15, 0, 0, 1);

		glTranslatef(0.3, 0, 0);
		glRotatef(-sin(sc_trot)*140, 0, 0, 1);
		glTranslatef(-0.3, 0, 0);

		glPushMatrix();
			glScalef(0.6, 0.1, 0.3);
			tcube((int[]){104, 107, 103, 108, 106, 105});
		glPopMatrix();

		for (int i = 0; i < 5; i++)
		{
			glTranslatef(-sin(sc_tx)*0.03-0.57, -sin(sc_ty)*0.1+0.18, 0);
			glRotatef(sin(sc_tang)*21-36, 0, 0, 1);

			glPushMatrix();
				glScalef(0.6, 0.1, 0.3);
				tcube((int[]){104, 107, 103, 108, 106, 105});
			glPopMatrix();
		}

		// telson
		glTranslatef(-0.6, 0.08, 0);
		glRotatef(-15, 0, 0, 1);

		glPushMatrix();
			glScalef(0.6, 0.1, 0.1);
			tcube((int[]){110, 113, 109, 114, 112, 111});
		glPopMatrix();

	glPopMatrix();
}

void sc_fast_default()
{
	sc_hit_up = 1;
	sc_hit_timer = 0;
	sc_hit_offset = (sc_hit_offset > -M_PI/6) ? sc_hit_offset - 0.1 : -M_PI/6;
	sc_trot = (sc_trot  > 0) ? sc_trot - 0.1 : 0;
	sc_tang = (sc_tang  > -M_PI/6) ? sc_tang - 0.1 : -M_PI/6;
	sc_tx = (sc_tx  > -M_PI/6) ? sc_tx - 0.1 : -M_PI/6;
	sc_ty = (sc_ty  > -M_PI/6) ? sc_ty - 0.1 : -M_PI/6;
}

void obj_scorpion(int sc_animindex)
{
	switch(sc_animindex)
	{
		case 0: // idle
			sc_idle_pose = (sc_idle_pose <= 2*M_PI) ? sc_idle_pose+0.05 : 0;
			sc_fast_default();
			m_scorpion_anim();
			break;

		case 1: // walk
			sc_fast_default();
			sc_idle_pose = (sc_idle_pose <= 2*M_PI) ? sc_idle_pose+0.1 : 0;
			sc_legsAng = (sc_legsAng <= 2*M_PI) ? sc_legsAng+0.1 : 0;
			m_scorpion_anim();
			break;

		case 2: //still hit
			sc_idle_pose = (sc_idle_pose <= 2*M_PI) ? sc_idle_pose+0.05 : 0;
			if (sc_hit_timer == 0)
				if (sc_hit_up)
					if (sc_hit_offset < M_PI/2)
						sc_hit_offset += 0.2;
					else
						sc_hit_up = !sc_hit_up;
				else
					if (sc_hit_offset > -M_PI/6)
						sc_hit_offset -= 0.1;
					else
					{
						sc_hit_up = !sc_hit_up;
						sc_hit_timer = 100;
					}
				else
					sc_hit_timer -= 1;

			sc_tang = sc_tx = sc_ty = sc_hit_offset;
			if (sc_hit_offset > 0) sc_trot = sc_hit_offset;
			else sc_trot = 0;

			m_scorpion_anim();
			break;

		case 3: // walk hit
			sc_legsAng = (sc_legsAng <= 2*M_PI) ? sc_legsAng+0.1 : 0;
			sc_idle_pose = (sc_idle_pose <= 2*M_PI) ? sc_idle_pose+0.1 : 0;
			if (sc_hit_timer == 0)
				if (sc_hit_up)
					if (sc_hit_offset < M_PI/2)
						sc_hit_offset += 0.2;
					else
						sc_hit_up = !sc_hit_up;
				else
					if (sc_hit_offset > -M_PI/6)
						sc_hit_offset -= 0.1;
					else
					{
						sc_hit_up = !sc_hit_up;
						sc_hit_timer = 100;
					}
				else
					sc_hit_timer -= 1;

			sc_tang = sc_tx = sc_ty = sc_hit_offset;
			if (sc_hit_offset > 0) sc_trot = sc_hit_offset;
			else sc_trot = 0;

			m_scorpion_anim();
			break;

		case 4: // death
			sc_fast_default();
			sc_deathAng = (sc_deathAng < 180) ? sc_deathAng + 20 : 180;
			sc_legsAng = (sc_legsAng <= 2*M_PI) ? sc_legsAng+0.5 : 0;
			m_scorpion_anim();
			break;

		case 5: // reverse death
			sc_deathAng = 0;
			m_scorpion_anim();
			break;

		default:
			break;
	}
}
