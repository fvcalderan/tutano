/* This is Tutano's 3D primitives file. 
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

#include "primitives.h"

void cube()
{
    float size = 1.0;

    GLfloat n[6][3] =
    {
        {-1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0},
        {0.0, 0.0, -1.0}
    };

    GLint faces[6][4] =
    {
        {0, 1, 2, 3},
        {3, 2, 6, 7},
        {7, 6, 5, 4},
        {4, 5, 1, 0},
        {5, 6, 2, 1},
        {7, 4, 0, 3}
    };

    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size * 0.5;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size * 0.5;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size * 0.5;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size * 0.5;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size * 0.5;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size * 0.5;

    for (i = 5; i >= 0; i--) 
    {
        glBegin(GL_QUADS);
            glNormal3fv(&n[i][0]);
            glTexCoord2f(0.0f,0.0f);
            glVertex3fv(&v[faces[i][0]][0]);
            glTexCoord2f(1.0f,0.0f);
            glVertex3fv(&v[faces[i][1]][0]);
            glTexCoord2f(1.0f,1.0f);
            glVertex3fv(&v[faces[i][2]][0]);
            glTexCoord2f(0.0f,1.0f);
            glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}

void tcube(int tex_arr[6])
{
    float size = 1.0;

    GLfloat n[6][3] =
    {
        {-1.0, 0.0, 0.0},
        {0.0, 1.0, 0.0},
        {1.0, 0.0, 0.0},
        {0.0, -1.0, 0.0},
        {0.0, 0.0, 1.0},
        {0.0, 0.0, -1.0}
    };

    GLint faces[6][4] =
    {
        {0, 1, 2, 3},
        {3, 2, 6, 7},
        {7, 6, 5, 4},
        {4, 5, 1, 0},
        {5, 6, 2, 1},
        {7, 4, 0, 3}
    };

    GLfloat v[8][3];
    GLint i;

    v[0][0] = v[1][0] = v[2][0] = v[3][0] = -size * 0.5;
    v[4][0] = v[5][0] = v[6][0] = v[7][0] = size * 0.5;
    v[0][1] = v[1][1] = v[4][1] = v[5][1] = -size * 0.5;
    v[2][1] = v[3][1] = v[6][1] = v[7][1] = size * 0.5;
    v[0][2] = v[3][2] = v[4][2] = v[7][2] = -size * 0.5;
    v[1][2] = v[2][2] = v[5][2] = v[6][2] = size * 0.5;

    for (i = 5; i >= 0; i--) 
    {
        glBindTexture(GL_TEXTURE_2D, texture_id[tex_arr[i]]);
        glBegin(GL_QUADS);
            glNormal3fv(&n[i][0]);
            glTexCoord2f(0.0f,0.0f);
            glVertex3fv(&v[faces[i][0]][0]);
            glTexCoord2f(1.0f,0.0f);
            glVertex3fv(&v[faces[i][1]][0]);
            glTexCoord2f(1.0f,1.0f);
            glVertex3fv(&v[faces[i][2]][0]);
            glTexCoord2f(0.0f,1.0f);
            glVertex3fv(&v[faces[i][3]][0]);
        glEnd();
    }
}

void tquad (int tex)
{
    GLfloat v[4][3] = 
    {
        {0, -0.5, -0.5},
        {0, -0.5, 0.5},
        {0, 0.5, 0.5},
        {0, 0.5, -0.5}
    };

    glBindTexture(GL_TEXTURE_2D, texture_id[tex]);
    glBegin(GL_QUADS);
        glNormal3fv((float[]){1.0, 0.0, 0.0});
        glTexCoord2f(0.0f,0.0f);
        glVertex3fv(&v[0][0]);
        glTexCoord2f(1.0f,0.0f);
        glVertex3fv(&v[1][0]);
        glTexCoord2f(1.0f,1.0f);
        glVertex3fv(&v[2][0]);
        glTexCoord2f(0.0f,1.0f);
        glVertex3fv(&v[3][0]);
    glEnd();
}

void tfaces (int tex)
{
    GLfloat v1[4][3] = 
    {
        {0.0001, -0.5, -0.5},
        {0.0001, -0.5, 0.5},
        {0.0001, 0.5, 0.5},
        {0.0001, 0.5, -0.5}
    };

    glBindTexture(GL_TEXTURE_2D, texture_id[tex]);
    glBegin(GL_QUADS);
        glNormal3fv((float[]){1.0, 0.0, 0.0});
        glTexCoord2f(0.0f,0.0f);
        glVertex3fv(&v1[0][0]);
        glTexCoord2f(1.0f,0.0f);
        glVertex3fv(&v1[1][0]);
        glTexCoord2f(1.0f,1.0f);
        glVertex3fv(&v1[2][0]);
        glTexCoord2f(0.0f,1.0f);
        glVertex3fv(&v1[3][0]);
    glEnd();

    GLfloat v2[4][3] = 
    {
        {-0.0001, -0.5, -0.5},
        {-0.0001, -0.5, 0.5},
        {-0.0001, 0.5, 0.5},
        {-0.0001, 0.5, -0.5}
    };

    glBindTexture(GL_TEXTURE_2D, texture_id[tex]);
    glBegin(GL_QUADS);
        glNormal3fv((float[]){-1.0, 0.0, 0.0});
        glTexCoord2f(0.0f,0.0f);
        glVertex3fv(&v2[0][0]);
        glTexCoord2f(1.0f,0.0f);
        glVertex3fv(&v2[1][0]);
        glTexCoord2f(1.0f,1.0f);
        glVertex3fv(&v2[2][0]);
        glTexCoord2f(0.0f,1.0f);
        glVertex3fv(&v2[3][0]);
    glEnd();
}
