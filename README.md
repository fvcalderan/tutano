```=========================================================================
Tutano v1.0
Copyright (C) 2020 Felipe V. Calderan <fvcalderan@gmail.com>
Copyright (C) 2020 Natália V. Calderan <nvcalderan@gmail.com>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <https://www.gnu.org/licenses/>.
=========================================================================
Game Controls                       | Editor Controls
=========================================================================
                                    | 
Arrows     | Turn and move          | Arrows     | Move cursor
A + Arrows | Turn without moving    | A + Arrows | Move cursor faster
Space      | Fire                   | D          | Eye dropper
D          | Flash (kill all mobs)  | 1          | Cicle floors
ESC        | Go to main menu        | 2          | Cicle walls
                                    | 3          | Cicle spawns/exit/tele
Map and point system informations   | 4          | Cicle item pillars
====================================| 5          | Cicle keys
                                    | 6          | Cicle doors
Each map must have at most 3 monster| 7          | Cicle water/water wall
spawners, 3 doors, 3 keys, 3 items. | 8          | Cicle water directions
Also, a player spawner and exit are | 9          | Cicle darkness levels
needed to save the map.             | 0          | Eraser (empty tile)
                                    | Space      | Place block
During the game, each item is worth | F1         | Save map (see console)
40 points and each second remaining | F2         | Load map (see console)
is worth 1 point. Campaign's high   | F3         | Clear map
score is shown in the main menu.    | ESC        | Go to main menu
=========================================================================
Commandline: ./Tutano [campaign_name] [0=window | 1=fullscreen]
=========================================================================```
