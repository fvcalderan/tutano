/* This is Tutano's overlay system. 
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

#include "overlay.h"

void draw_ov_lives(GLfloat x, GLfloat y, GLfloat z, GLfloat lives_number)
{
	int i;
	for (i = 0; i < lives_number; i++)
	{
		glPushMatrix();
	        glTranslatef(x+2.5, y-9.2, z-6+i*0.6);
	        glRotatef(-52.50, 0, 0, 1);	
	        glScalef(0.5, 0.5, 0.5);
	        tfaces(282);
	    glPopMatrix();
	}
}

void draw_ov_flashes(GLfloat x, GLfloat y, GLfloat z, GLfloat flashes_number)
{
	int i;
	for (i = 0; i < flashes_number; i++)
	{
		glPushMatrix();
	        glTranslatef(x+2.5, y-9.2, z+6-i*0.6);
	        glRotatef(-52.50, 0, 0, 1);	
	        glScalef(0.5, 0.5, 0.5);
	        tfaces(283);
	    glPopMatrix();
	}
}

void draw_ov_black_strip(GLfloat x, GLfloat y, GLfloat z)
{
	glPushMatrix();
        glTranslatef(x+2.6, y-9.5, z);
        glRotatef(-59, 0, 0, 1);	
        glScalef(1, 1, 20);
        tfaces(295);
    glPopMatrix();
}

void draw_ov_points(GLfloat x, GLfloat y, GLfloat z, GLint points)
{
	int i;

	for (i = 0; i < 6; i++)
	{
		glPushMatrix();
	        glTranslatef(x+2.5, y-9.2, z-i*0.34+0.85);
	        glRotatef(-59, 0, 0, 1);	
	        glScalef(1, 0.5, 0.34);
	        tfaces(num_to_img(points, i));
	    glPopMatrix();
	}
}

void draw_ov_time(GLfloat x, GLfloat y, GLfloat z, GLint time)
{
	int i;

	glPushMatrix();
        glTranslatef(x+2.5, y-9.2, z+2.6);
        glRotatef(-52.50, 0, 0, 1);	
        glScalef(0.5, 0.5, 0.5);
        tfaces(284);
    glPopMatrix();

	for (i = 0; i < 3; i++)
	{
		glPushMatrix();
	        glTranslatef(x+2.5, y-9.2, z+3-i*0.34+0.85);
	        glRotatef(-59, 0, 0, 1);	
	        glScalef(1, 0.5, 0.34);
	        tfaces(num_to_img(time, i));
	    glPopMatrix();
	}
}

void draw_ov_keys(GLfloat x, GLfloat y, GLfloat z, GLint keys[3])
{
	int i;
	for (i = 0; i < 3; i++)
	{
		if (keys[i])
		{
			glPushMatrix();
		        glTranslatef(x+2.5, y-9.2, z-3.7+i*0.6);
		        glRotatef(-52.50, 0, 0, 1);	
		        glRotatef(180, 1, 0, 0);
		        glScalef(0.5, 0.5, 0.5);
		        tfaces(252+i);
		    glPopMatrix();
		}
	}
}

void draw_ov_reload(GLfloat x, GLfloat y, GLfloat z, GLfloat reload_time)
{
	glPushMatrix();
        glTranslatef(x+2.5, y-5, z);
        glRotatef(-37.569, 0, 0, 1);	
        glScalef(1, 0.1, reload_time/100);
        tfaces(280);
    glPopMatrix();
}

void draw_ov_flash(GLfloat x, GLfloat y, GLfloat z, GLint flash_time)
{
	glEnable(GL_LIGHTING);
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f-(float)flash_time/100.0+1);
	glPushMatrix();
        glTranslatef(x+2.6, y-5, z);
        glRotatef(-37.569, 0, 0, 1);	
        glScalef(1, 10, 10);
        tfaces(281);
    glPopMatrix();
    glDisable(GL_LIGHTING);
}

void draw_overlay(GLfloat x, GLfloat y, GLfloat z, GLfloat reload_time, GLint flash_time, GLint lives_number,
				  GLint flashes_number, GLint points, GLint time, GLint keys[3])
{
    glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    	draw_ov_black_strip(x, y, z);
    	draw_ov_lives(x, y, z, lives_number);
    	draw_ov_flashes(x, y, z, flashes_number);
    	draw_ov_points(x, y, z, points);
    	draw_ov_time(x, y, z, time);
    	draw_ov_keys(x, y, z, keys);
    	draw_ov_reload(x, y, z, reload_time);
    	draw_ov_flash(x, y, z, flash_time);
    glEnable(GL_LIGHTING);
}

void draw_ov_ed_block (GLfloat x, GLfloat y, GLfloat z, GLint block)
{
	glPushMatrix();
        glTranslatef(x+3, y-9, z+6);
	       glRotatef(-40, 0, 0, 1);	
        //glScalef(0.5, 0.5, 0.5);
		if (map_ed_ttype(block) == M_WALL)
		{
		    obj_wall(map_ed_get_wall_skin(block)); 
		}
		if (map_ed_ttype(block) == M_FLOOR)
		{
		    obj_floor(map_ed_get_floor_skin(block));
		}
		if (map_ed_ttype(block) == M_PLAYER_SPAWN)
		{
		    obj_player_spawn();
		}
		if (map_ed_ttype(block) == M_PLAYER_EXIT)
		{
		    obj_player_exit();
		}
		if (map_ed_ttype(block) == M_MOB_SPAWN_SNAKE)
		{
		    obj_mob_spawn();
		    glPushMatrix();
		    	glTranslatef(0, -0.75, 0);
		    	glRotatef(180, 0, 1, 0);
		    	glScalef(0.5, 0.5, 0.5);
		    	obj_snake(0);
		    glPopMatrix();
		}
		if (map_ed_ttype(block) == M_MOB_SPAWN_SCORPION)
		{
		    obj_mob_spawn();
		    glPushMatrix();
		    	glTranslatef(0, -0.75, 0);
		    	glRotatef(180, 0, 1, 0);
		    	glScalef(0.3, 0.3, 0.3);
		    	obj_scorpion(0);
		    glPopMatrix();
		}
		if (map_ed_ttype(block) == M_MOB_SPAWN_MUMMY)
		{
		    obj_mob_spawn();
		    glPushMatrix();
		    	glTranslatef(0, -0.75, 0);
		    	glRotatef(180, 0, 1, 0);
		    	glScalef(0.5, 0.5, 0.5);
		    	obj_mummy(0);
		    glPopMatrix();
		}
		if (map_ed_ttype(block) == M_ITEM)
		{
		    obj_pedestal(map_ed_get_pedestal_skin(block));
		}
		if (map_ed_ttype(block) == M_KEY)
		{
		    obj_key_spawn(map_ed_get_key_floor_skin(block));
		}
		if (map_ed_ttype(block) == M_DOOR_CLOSED)
		{
		    obj_door(0, map_ed_get_door_skin(block));
		}
		if (map_ed_ttype(block) == M_DOOR_OPEN)
		{
		    obj_door_open();
		}
		if (map_ed_ttype(block) == M_WATER)
		{
		    obj_water(0, 0.0f);
		}
		if (map_ed_ttype(block) == M_TELEPORT)
		{
		    obj_teleport(0);
		}
		if (map_ed_ttype(block) == M_WATER_SETTINGS)
		{
		    obj_water_settings(map_ed_get_water_settings_skin(block));
		}
		if (map_ed_ttype(block) == M_DARK_SETTINGS)
		{
		    obj_dark_settings(map_ed_get_dark_settings_skin(block));
		}
		if (map_ed_ttype(block) == M_WATER_WALL)
		{
		    if (block == 42)
        	{
        		obj_water_wall(0, 0.0f);
        	}
        	else if (block == 43)
        	{
        		obj_water_wall(0, 90.0f);
        	}
        	else if (block == 44)
        	{
        		obj_water_wall(0, 180.0f);
        	}
        	else
        	{
        		obj_water_wall(0, 270.0f);
        	} 
		}
	glPopMatrix();
}

void draw_editor_overlay(GLfloat x, GLfloat y, GLfloat z, GLint block, GLint help)
{
	glClear(GL_DEPTH_BUFFER_BIT);
    glDisable(GL_LIGHTING);
    	draw_ov_ed_block(x, y, z, block);
    glEnable(GL_LIGHTING);
}
