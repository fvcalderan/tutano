/* This is Tutano's main menu system. 
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

#include "mainmenu.h"

void draw_menu_bg(GLint menu_val, GLint highscore)
{
	int i;

	glDisable(GL_LIGHTING);
	glPushMatrix();
        glTranslatef(0, 0, 0);
        glRotatef(180, 0, 1, 0);	
        glScalef(1, 3.7294, 6.63);
        tfaces(296+menu_val);
    glPopMatrix();

	for (i = 0; i < 6; i++)
	{
		glPushMatrix();
	        glTranslatef(0.1, -1.48, i*0.2+1.73);
	        glRotatef(180, 0, 1, 0);
	        glScalef(1, 0.3, 0.204);
	        tfaces(num_to_img(highscore, i));
	    glPopMatrix();
	}
    glEnable(GL_LIGHTING);
}
