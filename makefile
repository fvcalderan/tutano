# This is Tutano's main file.
# Copyright (C) 2020 Felipe V. Calderan <fvcalderan@gmail.com>
# Copyright (C) 2020 Natália V. Calderan <nvcalderan@gmail.com>
# 
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
#
CC 			= gcc
CFLAGS 		= -Wall
LDFLAGS 	= -lm -lGL -lGLU -lglut
OBJFILES 	= models/m_cup.o models/m_key.o models/m_map.o models/m_door.o models/m_mummy.o \
			  models/m_snake.o models/m_player.o models/m_teapot.o models/m_scorpion.o models/m_candelabra.o \
			  includes/controls.o includes/numtoimg.o includes/texloader.o includes/primitives.o \
			  includes/lighting.o includes/customtypes.o includes/overlay.o \
			  includes/mapfunctions.o includes/mainmenu.o includes/queue.o includes/BFS.o \
			  Tutano.o
TARGET = Tutano

all: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJFILES) $(LDFLAGS)
	rm -f $(OBJFILES) *~

clean:
	rm -f $(TARGET) *~
