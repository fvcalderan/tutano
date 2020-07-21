/* This is Tutano's keyboard control system.
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

#include "controls.h"

char key_buffer[256];
char skey_buffer[256];

void clear_key_buffer()
{
    for (int i = 0; i < 256; i++)
    {
        key_buffer[i] = 0;
        skey_buffer[i] = 0;
    }
}

void Keyboard(unsigned char key, int x, int y)
{
	key_buffer[key] = 1;
}
void KeyboardUp(unsigned char key, int x, int y)
{
	key_buffer[key] = 0;
}
void KeyboardSpecial(int key, int x, int y)
{
	skey_buffer[key] = 1;
}
void KeyboardUpSpecial(int key, int x, int y)
{
	skey_buffer[key] = 0;
}

void Mouse (int button, int state, int x, int y){}
