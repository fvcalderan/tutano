/* This is Tutano's main header file.
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

// default includes
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include <string.h>
#include "global.h"

// custom types and algorithms
#include "includes/customtypes.h"
#include "includes/mapfunctions.h"
#include "includes/queue.h"
#include "includes/BFS.h"
#include "includes/entitystructs.h"

// opengl-related includes and defines
#include "includes/texloader.h"
#include "includes/lighting.h"
#include "includes/controls.h"
#include "includes/primitives.h"
#include "includes/numtoimg.h"
#include "includes/mainmenu.h"

// model-related includes and defines
//#include "models/m_player.c"
//#include "models/m_mummy.c"
//#include "models/m_scorpion.c"
//#include "models/m_snake.c"
//#include "models/m_cup.c"
//#include "models/m_teapot.c"
//#include "models/m_candelabra.c"
//#include "models/m_key.c"
//#include "models/m_map.c"
//#include "models/m_door.c"

// these includes must be included after everything
#include "includes/overlay.h"
