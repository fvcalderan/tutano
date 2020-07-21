/* This is Tutano's lighting system. 
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

#include "lighting.h"

void lighting(GLfloat x, GLfloat z, GLfloat attenuation, GLfloat ambient_intensity)
{
	GLfloat light_ambient[3] = {ambient_intensity, ambient_intensity, ambient_intensity};
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, light_ambient);


    GLfloat light0_pos[] = {x, 3.0f, z, 1.0f};
    GLfloat light_color_orange[] = {1.0f, 0.55f, 0.1f, 1.0f};
    GLfloat light_color_black[] = {0.0f, 0.0f, 0.0f, 1.0f};
    GLfloat light_attenuation[1] = {attenuation};

    glLightfv(GL_LIGHT0, GL_POSITION, light0_pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_color_black);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color_orange);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color_orange);
    glLightfv(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, light_attenuation);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}
