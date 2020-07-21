/* This is Tutano's header for overlay system. 
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

#ifndef _OVERLAY_H_
#define _OVERLAY_H_

#include <GL/glut.h>
#include "primitives.h"
#include "../global.h"
#include "mapfunctions.h"
#include "numtoimg.h"
#include "../models/all_models.h"

void draw_ov_lives(GLfloat x, GLfloat y, GLfloat z, GLfloat lives_number);
void draw_ov_flashes(GLfloat x, GLfloat y, GLfloat z, GLfloat flashes_number);
void draw_ov_black_strip(GLfloat x, GLfloat y, GLfloat z);
void draw_ov_points(GLfloat x, GLfloat y, GLfloat z, GLint points);
void draw_ov_time(GLfloat x, GLfloat y, GLfloat z, GLint time);
void draw_ov_keys(GLfloat x, GLfloat y, GLfloat z, GLint keys[3]);
void draw_ov_reload(GLfloat x, GLfloat y, GLfloat z, GLfloat reload_time);
void draw_ov_flash(GLfloat x, GLfloat y, GLfloat z, GLint flash_time);
void draw_overlay(GLfloat x, GLfloat y, GLfloat z, GLfloat reload_time, GLint flash_time, GLint lives_number, GLint flashes_number, GLint points, GLint time, GLint keys[3]);
void draw_ov_ed_block (GLfloat x, GLfloat y, GLfloat z, GLint block);
void draw_editor_overlay(GLfloat x, GLfloat y, GLfloat z, GLint block, GLint help);

#endif
