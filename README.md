# Tutano 1.0

![splashscreen](docs/screenshot1.png)
![in-game](docs/screenshot2.png)
![editor](docs/screenshot3.png)

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

Read [this](docs/INSTALL_WINDOWS.md) file to get the instructions for Windows.

## Launch the game from the terminal

It's important that Tutano is launched from within the terminal, especially if you plan to use the map editor.
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
D          | Flash (kill all mobs)  | 1          | Cycle floors
ESC        | Go to main menu        | 2          | Cycle walls
                                    | 3          | Cycle spawns/exit/tele
Map and point system informations   | 4          | Cycle item pillars
====================================| 5          | Cycle keys
                                    | 6          | Cycle doors
Each map must have at most 3 monster| 7          | Cycle water/water wall
spawners, 3 doors, 3 keys, 3 items. | 8          | Cycle water directions
Also, a player spawner and exit are | 9          | Cycle darkness levels
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

## Troubleshooting

### Framerate issues

Tutano has one major flaw: the framerate adjustment. Unfortunately, GLUT
doesn't provide a convenient way to cap the framerate at a certain value and
Tutano's physics depends on the framerate (my fault, but GLUT doesn't make it
any easier to remove this dependency).

So, if the game is running too fast, you can increase the first parameter of
both `glutTimerFunc()` inside **Tutano.c**.  If it's running too slow, decrease
them. Recompile the game and test it. A good reference for the game speed is
the in-game timer.

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

