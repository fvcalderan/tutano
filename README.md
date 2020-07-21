# Tutano 1.0

![image](https://user-images.githubusercontent.com/24211835/88117113-a27c3680-cb90-11ea-8ae5-b43979d83573.png)

## What is it?

Tutano is a simple adventure game created using only C and OpenGL. 
It's based on an old game called Tutankham from Odyssey 2 game console.

## Who created it?

Felipe V. Calderan (Programming) and Natália V. Calderan (Art).

## Why was it created?

The game was made as a final project for my (Felipe) undergraduate Computer Graphics subject.
There was no intention to release the source code, but I realized it could help people trying to make similar projects.
Though, be warned: the code isn't pretty, nor optimized, but it works nonetheless. It is my first ever OpenGL project.

## Features

* 10 default levels to play
* A basic, but complete, level editor
* Easy to create custom campaigns
* High score is saved per campaign

## Dependencies

* C language and compiler
* OpenGL 3.2, GLU and freeglut

**NOTE:** Although it does work with glut, it may require some modifications in the code.

## How to build from source

### GNU/Linux

Having installed all the dependencies using your distribution's package manager, change directory to Tutano's root and type `make` in the terminal.

### mac OS X

OpenGL, GLU and glut are shipped with OS X, but Xcode developer CLI tools may be required. Other than that, it's the same procedure as in GNU/Linux.

### Windows

Install the dependencies and then use MinGW/Cygwin to compile Tutano or do whatever you need to do in Visual Studio. I personally built the binary in Windows manually using GCC from MinGW, linking the needed DLLs (OpenGL, GLU and glut). Although it's possible to compile it in Windows, modifications
in the code are typically required, e.g.: Defining `M_PI` yourself.

## Launch the game from the terminal

It's important that Tutano is launched from within the terminal, especially if you'll use the map editor. 
In GNU/Linux or MacOS, in Tutano's root folder, type `./Tutano`.
In Windows, using the CMD, just type `Tutano` in Tutano's root folder.

## Controls and basic informations

You can see the following information in the terminal everytime you launch the game, so there's no need to come back here to see the controls.

```
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
=========================================================================
```

## Software License (GPL v3.0)

Tutano v1.0  
Copyright (C) 2020 Felipe V. Calderan, <fvcalderan@gmail.com>  
Copyright (C) 2020 Natália V. Calderan, <nvcalderan@gmail.com>  
  
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

## Art License (CC BY 4.0)

Tutano Textures (c) by Natália V. Calderan and Felipe V. Calderan  

Tutano Textures is licensed under a
Creative Commons Attribution 4.0 International License.  
  
You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by/4.0/>.  

