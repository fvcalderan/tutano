/* This is Tutano's main file.
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

#include "Tutano.h"

#define SCRX 1024
#define SCRY 576

// scenes
int scene_value = 0;
int menu_position = 0;
int menu_cooldown = 0;

// camera
#define LOOKSPEED 0.002
#define WALKSPEED 0.1
float cam_lookX = 0, cam_lookY = 0, cam_lookZ = 0;
float cam_lookTheta = M_PI, cam_lookPhi = M_PI/2;
float cam_posX = 5, cam_posY = 5, cam_posZ = 5;
VECTOR3 cam_dir;
int actual_camera = 0;
int camchange_cooldown = 0;

// actors
PLAYER player;
SNAKE snake;
SCORPION scorpion;
MUMMY mummy;
CURSOR cursor;

// map
int map_matrix[MAPSIZE][MAPSIZE];
VECTOR2 exit_in_position;
VECTOR2 item_in_position[3];
VECTOR2 key_in_position[3];
VECTOR2 door_in_position[3];
VECTOR2 teleport_in_position[2];

// ai
VECTOR2 mob_spawn_pos_snake;
VECTOR2 mob_spawn_pos_scorpion;
VECTOR2 mob_spawn_pos_mummy;

// doors and keys
int door_open_tile_change_timer = 0;
// 0: red | 1: green | 2: blue
int doors_opened[3];
int keys_gotten[3];

// gameplay
#define PLAYER_LIVES_START 3
#define PLAYER_FLASHES_START 3
#define ARTIFACT_POINTS 40
#define TIMELIMIT 180
#define TELEPORT_COOLDOWN_CS 200
char selected_campaign[100];
int teleport_cooldown;
int player_actual_level;
int player_lives_number;
int player_flashes_number;
int player_score;
int player_time;
int player_time_cd;
int player_fire_init_fix = 15;
int player_high_score;

// editor
#define ED_BLOCK_CD 15
int ed_block;
int ed_block_time;
int ed_spawn_exit_placed[5];
int ed_key_placed[3];
int ed_artifact_placed;
int ed_door_placed[3];
int ed_place_init_fix;
int ed_teleports_placed;
int ed_water_settings_placed;
int ed_dark_settings_placed;

// other
#define WT_KEYFRAME_MAX 96
int wt_keyframe_main = 0;
float wt_rotation = 0.0f;
float lt_settings = 0.2f;
int window_mode;

void credits_and_controls()
{
	printf("=========================================================================\n"
		   "Tutano v1.0\n"
           "Copyright (C) 2020 Felipe V. Calderan <fvcalderan@gmail.com>\n"
           "Copyright (C) 2020 Natália V. Calderan <nvcalderan@gmail.com>\n\n"
           "This program is free software: you can redistribute it and/or modify\n"
           "it under the terms of the GNU General Public License as published by\n"
           "the Free Software Foundation, either version 3 of the License, or\n"
           "(at your option) any later version.\n\n"
           "This program is distributed in the hope that it will be useful,\n"
           "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
           "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
           "GNU General Public License for more details.\n\n"
           "You should have received a copy of the GNU General Public License\n"
           "along with this program.  If not, see <https://www.gnu.org/licenses/>.\n"
		   "=========================================================================\n"
		   "Game Controls                       | Editor Controls\n"
		   "=========================================================================\n"
		   "                                    |\n" 
		   "Arrows     | Turn and move          | Arrows     | Move cursor\n"
		   "A + Arrows | Turn without moving    | A + Arrows | Move cursor faster\n"
		   "Space      | Fire                   | D          | Eye dropper\n"
		   "D          | Flash (kill all mobs)  | 1          | Cycle floors\n"
		   "ESC        | Go to main menu        | 2          | Cycle walls\n"
		   "                                    | 3          | Cycle spawns/exit/tele\n"
		   "Map and point system informations   | 4          | Cycle item pillars\n"
		   "====================================| 5          | Cycle keys\n"
		   "                                    | 6          | Cycle doors\n"
		   "Each map must have at most 3 monster| 7          | Cycle water/water wall\n"
		   "spawners, 3 doors, 3 keys, 3 items. | 8          | Cycle water directions\n"
		   "Also, a player spawner and exit are | 9          | Cycle darkness levels\n"
		   "needed to save the map.             | 0          | Eraser (empty tile)\n"
		   "                                    | Space      | Place block\n"
		   "During the game, each item is worth | F1         | Save map (see console)\n"
		   "40 points and each second remaining | F2         | Load map (see console)\n"
		   "is worth 1 point. Campaign's high   | F3         | Clear map\n"
		   "score is shown in the main menu.    | ESC        | Go to main menu\n"
		   "=========================================================================\n"
		   "Commandline: ./Tutano [campaign_name] [0=window | 1=fullscreen]\n"
		   "=========================================================================\n");
}

void MousePassive(int x, int y){
    cam_lookTheta += (float)(x - SCRX/2) * LOOKSPEED;
    cam_lookPhi += (float)(y - SCRY/2) * LOOKSPEED;
    if (x != SCRX/2 || y != SCRY/2) glutWarpPointer(SCRX/2, SCRY/2);
}

void resetCamera()
{
    cam_lookX = cam_lookY = cam_lookZ = 0;
    cam_lookTheta = M_PI; cam_lookPhi = M_PI/2;
    cam_posX = 5; cam_posY = 5; cam_posZ = 5;
}

void refresh_camera()
{
    glLoadIdentity();

    if (scene_value == 0)
    {
    	gluLookAt(4, 0, 0,   // camera cam_position
                  0, 0, 0,   // camera look
                  0, 1, 0);  // view-up vector
    }
    else if (scene_value == 1)
    {
        gluLookAt(player.abs_pos.z-5, 7, player.abs_pos.x,   // camera cam_position
                  player.abs_pos.z, 0.5, player.abs_pos.x,   // camera look
                  0.0, 1.0, 0.0);                  			 // view-up vector
    }
    else
    {
    	gluLookAt(cursor.abs_pos.z-5, 7, cursor.abs_pos.x,   // camera cam_position
                  cursor.abs_pos.z, 0.5, cursor.abs_pos.x,   // camera look
                  0.0, 1.0, 0.0);                  			 // view-up vector
    }
    // }
}

void init_entities(int mode)
{
	// mode == 0 => fresh game
	// mode == 1 => respawn

	int i, j, k;

	if (!mode)
	{
		// items
		for (i = 0; i < 3; i ++)
		{
			item_in_position[i].x = MAPSIZE*2;
			item_in_position[i].y = MAPSIZE*2;
		}

		k = 0;
		for (i = 0; i < MAPSIZE; i++)
		{
			for (j = 0; j < MAPSIZE; j++)
			{
				if (map_ttype(map_matrix, i, j) == M_ITEM)
				{
					item_in_position[k].x = i;
					item_in_position[k].y = j;
					k++;
				}
			}
		}

		// keys
		for (i = 0; i < 3; i ++)
		{
			keys_gotten[i] = 0;
			key_in_position[i].x = MAPSIZE*2;
			key_in_position[i].y = MAPSIZE*2;
		}

		for (i = 0; i < MAPSIZE; i++)
		{
			for (j = 0; j < MAPSIZE; j++)
			{
				if (map_ttype(map_matrix, i, j) == M_KEY)
				{
					key_in_position[map_matrix[i][j]-26].x = i;
					key_in_position[map_matrix[i][j]-26].y = j;
				}
			}
		}

		// doors
		for (i = 0; i < 3; i ++)
		{
			doors_opened[i] = 0;
			door_in_position[i].x = MAPSIZE*2;
			door_in_position[i].y = MAPSIZE*2;
		}

		for (i = 0; i < MAPSIZE; i++)
		{
			for (j = 0; j < MAPSIZE; j++)
			{
				if (map_ttype(map_matrix, i, j) == M_DOOR_CLOSED)
				{
					door_in_position[map_matrix[i][j]-29].x = i;
					door_in_position[map_matrix[i][j]-29].y = j;
				}
			}
		}

		// exit
		exit_in_position.x = MAPSIZE*2;
		exit_in_position.y = MAPSIZE*2;
		for (i = 0; i < MAPSIZE; i++)
		{
			for (j = 0; j < MAPSIZE; j++)
			{
				if (map_ttype(map_matrix, i, j) == M_PLAYER_EXIT)
				{
					exit_in_position.x = i;
					exit_in_position.y = j;
				}
			}
		}

		// teleport
		k = 0;
		teleport_in_position[0].x = MAPSIZE*2;
		teleport_in_position[0].y = MAPSIZE*2;
		teleport_in_position[1].x = MAPSIZE*2;
		teleport_in_position[1].y = MAPSIZE*2;
		teleport_cooldown = 0;
		for (i = 0; i < MAPSIZE; i++)
		{
			for (j = 0; j < MAPSIZE; j++)
			{
				if (map_ttype(map_matrix, i, j) == M_TELEPORT)
				{
					teleport_in_position[k].x = i;
					teleport_in_position[k].y = j;
					k++;
				}
			}
		}

		// water_settings
		wt_rotation = 0.0f;
		for (i = 0; i < MAPSIZE; i++)
		{
			for (j = 0; j < MAPSIZE; j++)
			{
				if (map_ttype(map_matrix, i, j) == M_WATER_SETTINGS)
				{
					wt_rotation = ((float)map_matrix[i][j] - 35.0f) * 90.0f;
				}
			}
		}

		// dark_settings
		lt_settings = 0.2f;
		for (i = 0; i < MAPSIZE; i++)
		{
			for (j = 0; j < MAPSIZE; j++)
			{
				if (map_ttype(map_matrix, i, j) == M_DARK_SETTINGS)
				{
					if (map_matrix[i][j] == 39)
					{
						lt_settings = 0.0f;
					}
					else if (map_matrix[i][j] == 40)
					{
						lt_settings = 0.2f;
					}
					else if (map_matrix[i][j] == 41)
					{
						lt_settings = 0.6f;
					}
				}
			}
		}
	}

	// mob_spawn
	mob_spawn_pos_snake.x = mob_spawn_pos_scorpion.x = mob_spawn_pos_mummy.x = MAPSIZE*2;
	mob_spawn_pos_snake.y = mob_spawn_pos_scorpion.y = mob_spawn_pos_mummy.y = MAPSIZE*2;
	for (i = 0; i < MAPSIZE; i++)
	{
		for (j = 0; j < MAPSIZE; j++)
		{
			if (map_ttype(map_matrix, i, j) == M_MOB_SPAWN_SNAKE)
			{
				mob_spawn_pos_snake.x = i;
				mob_spawn_pos_snake.y = j;
			}
			else if (map_ttype(map_matrix, i, j) == M_MOB_SPAWN_SCORPION)
			{
				mob_spawn_pos_scorpion.x = i;
				mob_spawn_pos_scorpion.y = j;
			}
			else if (map_ttype(map_matrix, i, j) == M_MOB_SPAWN_MUMMY)
			{
				mob_spawn_pos_mummy.x = i;
				mob_spawn_pos_mummy.y = j;
			}
		}
	}

	if (!mode)
	{
		// player
		for (i = 0; i < MAPSIZE; i++)
		{
			for (j = 0; j < MAPSIZE; j++)
			{
				if (map_ttype(map_matrix, i, j) == M_PLAYER_SPAWN)
				{
					player.grid_pos.x = i;
					player.grid_pos.y = j;
				}
			}
		}
	}

	player.turn_speed = 15;
	player.move_speed = 0.05;
	player.abs_pos.x = (float)player.grid_pos.x;
	player.abs_pos.z = (float)player.grid_pos.y + 1.0f;
	player.grid_going.x = player.grid_pos.x;
	player.grid_going.y = player.grid_pos.y;
	player.abs_rot = 0;
	player.done_rotating = 1;
	player.can_move = 1;
	player.direction = 0;
	player.animation = 1;
	player.is_alive = 1;
	player.respawn_time = 100;
	player.respawn = 0;
	player.reload_time = 100;
	player.reload = 0;
	GLOBAL_pl_hit_timer_cd = player.reload_time;
	player.flash_time = 200;
	player.flash = 0;

	// snake
	snake.turn_speed = 15;
	snake.move_speed = 0.055;
	snake.abs_pos.x = MAPSIZE*2;
	snake.abs_pos.z = MAPSIZE*2+1;
	snake.grid_pos.x = MAPSIZE*2;
	snake.grid_pos.y = MAPSIZE*2;
	snake.grid_going.x = MAPSIZE*2;
	snake.grid_going.y = MAPSIZE*2;
	snake.abs_rot = 0;
	snake.can_move = 1;
	snake.is_attacking = 0;
	snake.direction = 0;
	snake.animation = 1;
	snake.BFS_size = 0;
	snake.is_alive = 0;
	snake.respawn_time = 300;
	snake.respawn = snake.respawn_time;
	snake.try_reach = 3.0f;
	snake.attack_reach = 1.2f;

	// scorpion
	scorpion.turn_speed = 15;
	scorpion.move_speed = 0.05;
	scorpion.abs_pos.x = MAPSIZE*2;
	scorpion.abs_pos.z = MAPSIZE*2+1;
	scorpion.grid_pos.x = MAPSIZE*2;
	scorpion.grid_pos.y = MAPSIZE*2;
	scorpion.grid_going.x = MAPSIZE*2;
	scorpion.grid_going.y = MAPSIZE*2;
	scorpion.abs_rot = 0;
	scorpion.can_move = 1;
	scorpion.is_attacking = 0;
	scorpion.direction = 0;
	scorpion.animation = 1;
	scorpion.BFS_size = 0;
	scorpion.is_alive = 0;
	scorpion.respawn_time = 200;
	scorpion.respawn = scorpion.respawn_time;
	scorpion.try_reach = 3.0f;
	scorpion.attack_reach = 1.3f;

	// mummy
	mummy.turn_speed = 15;
	mummy.move_speed = 0.04;
	mummy.abs_pos.x = MAPSIZE*2;
	mummy.abs_pos.z = MAPSIZE*2+1;
	mummy.grid_pos.x = MAPSIZE*2;
	mummy.grid_pos.y = MAPSIZE*2;
	mummy.grid_going.x = MAPSIZE*2;
	mummy.grid_going.y = MAPSIZE*2;
	mummy.abs_rot = 0;
	mummy.can_move = 1;
	mummy.is_attacking = 0;
	mummy.direction = 0;
	mummy.animation = 1;
	mummy.BFS_size = 0;
	mummy.is_alive = 0;
	mummy.respawn_time = 100;
	mummy.respawn = mummy.respawn_time;
	mummy.try_reach = 3.0f;
	mummy.attack_reach = 1.2f;
}

void init() 
{

	cursor.grid_pos.x = MAPSIZE*2;
	cursor.grid_pos.y = MAPSIZE*2;
	cursor.abs_pos.x = cursor.grid_pos.x;
	cursor.abs_pos.z = (float)cursor.grid_pos.y + 1.0f;

    load_map(map_matrix, selected_campaign, "map00");

    player_actual_level = 0;
    player_lives_number = PLAYER_LIVES_START;
    player_flashes_number = PLAYER_FLASHES_START;
    player_score = 0;
    player_time = TIMELIMIT;
    player_time_cd = 0;

    init_entities(0);
}

void pre_init()
{
	glEnable(GL_BLEND);
    glBlendFunc(GL_ONE_MINUS_SRC_ALPHA,GL_SRC_ALPHA);

    glEnable(GL_COLOR_MATERIAL);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glEnable(GL_DEPTH_TEST);

    glShadeModel(GL_SMOOTH);
    glEnable(GL_NORMALIZE);

    glMatrixMode(GL_MODELVIEW);
    refresh_camera();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, (float)SCRX/(float)SCRY, 0.1, 32);
    glViewport(0, 0, SCRX, SCRY);

}

void draw_map() 
{
    int i, j;
    int draw_after_enabled = 0;
    int draw_after[6] = {MAPSIZE, MAPSIZE, MAPSIZE, MAPSIZE, MAPSIZE, MAPSIZE};

    glBindTexture(GL_TEXTURE_2D, texture_id[1]);

    glPushMatrix();
        glTranslatef(0, 0.75, 0);
        for (i = 0; i < MAPSIZE; i++)
        {      
            for (j = 0; j < MAPSIZE; j++)
            {
                glTranslatef(1, 0, 0);
                if (map_ttype(map_matrix, i, j) == M_WALL || map_ttype(map_matrix, i, j) == M_WATER_WALL)
                {
                    if ((player.grid_pos.x == i && player.grid_pos.y == j+1) ||
                    	(cursor.grid_pos.x == i && cursor.grid_pos.y == j+1))
                    {
                        draw_after_enabled = 1;
                        draw_after[0] = i;
                        draw_after[1] = j;
                    }
                    else if ((player.grid_pos.x-1 == i && player.grid_pos.y == j+1) ||
                    	     (cursor.grid_pos.x-1 == i && cursor.grid_pos.y == j+1))
                    {
                        draw_after_enabled = 1;
                        draw_after[2] = i;
                        draw_after[3] = j;
                    }
                    else if ((player.grid_pos.x+1 == i && player.grid_pos.y == j+1) ||
                    	     (cursor.grid_pos.x+1 == i && cursor.grid_pos.y == j+1))
                    {
                        draw_after_enabled = 1;
                        draw_after[4] = i;
                        draw_after[5] = j;
                    }
                    else
                    {
                    	if (map_ttype(map_matrix, i, j) == M_WATER_WALL)
		                {
		                	if (map_matrix[i][j] == 42)
		                	{
		                		obj_water_wall(wt_keyframe_main, 0.0f);
		                	}
		                	else if (map_matrix[i][j] == 43)
		                	{
		                		obj_water_wall(wt_keyframe_main, 90.0f);
		                	}
		                	else if (map_matrix[i][j] == 44)
		                	{
		                		obj_water_wall(wt_keyframe_main, 180.0f);
		                	}
		                	else
		                	{
		                		obj_water_wall(wt_keyframe_main, 270.0f);
		                	} 
		                }
		                else
		                {
                        obj_wall(map_get_wall_skin(map_matrix, i, j)); 
                    	}
                    }
                }
                if (map_ttype(map_matrix, i, j) == M_FLOOR)
                {
                    obj_floor(map_get_floor_skin(map_matrix, i, j));
                }
                if (map_ttype(map_matrix, i, j) == M_PLAYER_SPAWN)
                {
                    obj_player_spawn();
                }
                if (map_ttype(map_matrix, i, j) == M_PLAYER_EXIT)
                {
                    obj_player_exit();
                }
                if (map_ttype(map_matrix, i, j) == M_MOB_SPAWN_SNAKE ||
                	map_ttype(map_matrix, i, j) == M_MOB_SPAWN_SCORPION ||
                	map_ttype(map_matrix, i, j) == M_MOB_SPAWN_MUMMY)
                {
                    obj_mob_spawn();
                }
                if (map_ttype(map_matrix, i, j) == M_ITEM)
                {
                    obj_pedestal(map_get_pedestal_skin(map_matrix, i, j));
                }
                if (map_ttype(map_matrix, i, j) == M_KEY)
                {
                    obj_key_spawn(map_get_key_floor_skin(map_matrix, i, j));
                }
                if (map_ttype(map_matrix, i, j) == M_DOOR_CLOSED)
                {
                    obj_door(doors_opened[map_matrix[i][j]-29], map_get_door_skin(map_matrix, i, j));
                }
                if (map_ttype(map_matrix, i, j) == M_DOOR_OPEN)
                {
                    obj_door_open();
                }
                if (map_ttype(map_matrix, i, j) == M_WATER)
                {
                    obj_water(wt_keyframe_main, wt_rotation);
                }
                if (map_ttype(map_matrix, i, j) == M_TELEPORT)
                {
                    obj_teleport(teleport_cooldown > 0);
                }
                if (map_ttype(map_matrix, i, j) == M_WATER_SETTINGS && scene_value == 2)
                {
                    obj_water_settings(map_get_water_settings_skin(map_matrix, i, j));
                }
                if (map_ttype(map_matrix, i, j) == M_DARK_SETTINGS && scene_value == 2)
                {
                    obj_dark_settings(map_get_dark_settings_skin(map_matrix, i, j));
                }
            }
            glTranslatef(-MAPSIZE, 0, 1);
        }
    glPopMatrix();

    if (draw_after_enabled)
    {
        glPushMatrix();
            if (draw_after[0] < MAPSIZE && draw_after[1] < MAPSIZE) {
                glTranslatef(draw_after[1]+1, 0.751, draw_after[0]);
                obj_wall_bottom(map_get_wall_skin(map_matrix, draw_after[0], draw_after[1]));
            }
        glPopMatrix();
        glPushMatrix();
            if (draw_after[2] < MAPSIZE && draw_after[3] < MAPSIZE) {
                glTranslatef(draw_after[3]+1, 0.751, draw_after[2]);
                obj_wall_bottom(map_get_wall_skin(map_matrix, draw_after[2], draw_after[3]));
            }
        glPopMatrix();
        glPushMatrix();
            if (draw_after[4] < MAPSIZE && draw_after[5] < MAPSIZE) {
                glTranslatef(draw_after[5]+1, 0.751, draw_after[4]);
                obj_wall_bottom(map_get_wall_skin(map_matrix, draw_after[4], draw_after[5]));
            }
        glPopMatrix();

        glPushMatrix();
            if (draw_after[0] < MAPSIZE && draw_after[1] < MAPSIZE) {
                glTranslatef(draw_after[1]+1, 0.75, draw_after[0]);
                obj_transparent_wall(map_get_wall_skin(map_matrix, draw_after[0], draw_after[1]), wt_keyframe_main);
            }
        glPopMatrix();
        
        if (map_walkable(map_matrix, draw_after[2], draw_after[3]+1))
        {
            glPushMatrix();
                if (draw_after[2] < MAPSIZE && draw_after[3] < MAPSIZE) {
                    glTranslatef(draw_after[3]+1, 0.75, draw_after[2]);
                    obj_transparent_wall(map_get_wall_skin(map_matrix, draw_after[2], draw_after[3]), wt_keyframe_main);
                }
            glPopMatrix();
        }
        else
        { 
            if (draw_after[2] < MAPSIZE && draw_after[3] < MAPSIZE) {
                if (map_matrix[draw_after[2]][draw_after[3]] >= 42)
                {
                    glPushMatrix();
                        glTranslatef(draw_after[3]+1, 0.75, draw_after[2]);
                        if (map_matrix[draw_after[2]][draw_after[3]] == 42)
                        {
                            obj_water_wall(wt_keyframe_main, 0.0f);
                        }
                        else if (map_matrix[draw_after[2]][draw_after[3]] == 43)
                        {
                            obj_water_wall(wt_keyframe_main, 90.0f);
                        }
                        else if (map_matrix[draw_after[2]][draw_after[3]] == 44)
                        {
                            obj_water_wall(wt_keyframe_main, 180.0f);
                        }
                        else
                        {
                            obj_water_wall(wt_keyframe_main, 270.0f);
                        } 
                    glPopMatrix();
                }
                else
                {
                    glPushMatrix();
                        glTranslatef(draw_after[3]+1, 0.75, draw_after[2]);
                        obj_wall(map_get_wall_skin(map_matrix, draw_after[2], draw_after[3]));
                    glPopMatrix();
                }
            }       
        }

        if (draw_after[4] < MAPSIZE && draw_after[5] < MAPSIZE) {
            if (map_walkable(map_matrix, draw_after[4], draw_after[5]+1))
            {
                glPushMatrix();
                    glTranslatef(draw_after[5]+1, 0.75, draw_after[4]);
                    obj_transparent_wall(map_get_wall_skin(map_matrix, draw_after[4], draw_after[5]), wt_keyframe_main);
                glPopMatrix();
            }
            else
            {
                if (map_matrix[draw_after[4]][draw_after[5]] >= 42)
                {
                    glPushMatrix();
                        glTranslatef(draw_after[5]+1, 0.75, draw_after[4]);
                        if (map_matrix[draw_after[4]][draw_after[5]] == 42)
                        {
                            obj_water_wall(wt_keyframe_main, 0.0f);
                        }
                        else if (map_matrix[draw_after[4]][draw_after[5]] == 43)
                        {
                            obj_water_wall(wt_keyframe_main, 90.0f);
                        }
                        else if (map_matrix[draw_after[4]][draw_after[5]] == 44)
                        {
                            obj_water_wall(wt_keyframe_main, 180.0f);
                        }
                        else
                        {
                            obj_water_wall(wt_keyframe_main, 270.0f);
                        } 
                    glPopMatrix();
                }
                else
                {
                    glPushMatrix();
                        glTranslatef(draw_after[5]+1, 0.75, draw_after[4]);
                        obj_wall(map_get_wall_skin(map_matrix, draw_after[4], draw_after[5]));
                    glPopMatrix();
                }
            }
        }
    }
}

void draw_player()
{
    glPushMatrix();
        glTranslatef(player.abs_pos.z, 0, player.abs_pos.x);
        glRotatef(player.abs_rot, 0, 1, 0);
        glScalef(0.5, 0.5, 0.5);
        obj_player(player.animation);
    glPopMatrix();
}

void draw_snake()
{
	glPushMatrix();
        glTranslatef(snake.abs_pos.z, 0, snake.abs_pos.x);
        glRotatef(snake.abs_rot, 0, 1, 0);
        glScalef(0.5, 0.5, 0.5);
        obj_snake(snake.animation);
    glPopMatrix();
}

void draw_scorpion()
{
	glPushMatrix();
        glTranslatef(scorpion.abs_pos.z, 0, scorpion.abs_pos.x);
        glRotatef(scorpion.abs_rot, 0, 1, 0);
        glScalef(0.3, 0.3, 0.3);
        obj_scorpion(scorpion.animation);
    glPopMatrix();
}

void draw_mummy()
{
	glPushMatrix();
        glTranslatef(mummy.abs_pos.z, 0, mummy.abs_pos.x);
        glRotatef(mummy.abs_rot, 0, 1, 0);
        glScalef(0.5, 0.5, 0.5);
        obj_mummy(mummy.animation);
    glPopMatrix();
}

void draw_item(int item)
{
	if (item == 0)
	{
		glPushMatrix();
	        glTranslatef(item_in_position[0].y+1, 0.75, item_in_position[0].x);
	        glScalef(0.5, 0.5, 0.5);
	        obj_cup(1);
	    glPopMatrix();
	}
	else if (item == 1)
	{
		glPushMatrix();
	        glTranslatef(item_in_position[1].y+1, 0.75, item_in_position[1].x);
	        glScalef(0.5, 0.5, 0.5);
	        obj_candelabra(1);
	    glPopMatrix();
	}
	else
	{
		glPushMatrix();
	        glTranslatef(item_in_position[2].y+1, 0.75, item_in_position[2].x);
	        glScalef(0.5, 0.5, 0.5);
	        obj_teapot(1);
	    glPopMatrix();
	}
}

void draw_key(int key)
{
	if (key == 0)
	{
		glPushMatrix();
	        glTranslatef(key_in_position[0].y+1, 0.25, key_in_position[0].x);
	        glScalef(0.4, 0.4, 0.4);
	        obj_key(1, 0);
	    glPopMatrix();
	}
	else if (key == 1)
	{
		glPushMatrix();
	        glTranslatef(key_in_position[1].y+1, 0.25, key_in_position[1].x);
	        glScalef(0.4, 0.4, 0.4);
	        obj_key(1, 1);
	    glPopMatrix();
	}
	else
	{
		glPushMatrix();
	        glTranslatef(key_in_position[2].y+1, 0.25, key_in_position[2].x);
	        glScalef(0.4, 0.4, 0.4);
	        obj_key(1, 2);
	    glPopMatrix();
	}
}

void init_map_editor()
{
	int i;

	teleport_cooldown = 0;

	for (i = 0; i < 3; i ++)
	{
		doors_opened[i] = 0;
		keys_gotten[i] = 0;
	}

	// player
	player.turn_speed = 15;
	player.move_speed = 0.05;
	player.grid_pos.x = MAPSIZE*2;
	player.grid_pos.y = MAPSIZE*2;
	player.abs_pos.x = (float)player.grid_pos.x;
	player.abs_pos.z = (float)player.grid_pos.y + 1.0f;
	player.grid_going.x = player.grid_pos.x;
	player.grid_going.y = player.grid_pos.y;
	player.abs_rot = 0;
	player.done_rotating = 1;
	player.can_move = 1;
	player.direction = 0;
	player.animation = 6;
	player.is_alive = 1;
	player.respawn_time = 100;
	player.respawn = 0;
	player.reload_time = 100;
	player.reload = 0;
	GLOBAL_pl_hit_timer_cd = player.reload_time;
	player.flash_time = 200;
	player.flash = 0;
	draw_player();

	// snake
	snake.turn_speed = 15;
	snake.move_speed = 0.055;
	snake.abs_pos.x = MAPSIZE*2;
	snake.abs_pos.z = MAPSIZE*2+1;
	snake.grid_pos.x = MAPSIZE*2;
	snake.grid_pos.y = MAPSIZE*2;
	snake.grid_going.x = MAPSIZE*2;
	snake.grid_going.y = MAPSIZE*2;
	snake.abs_rot = 0;
	snake.can_move = 1;
	snake.is_attacking = 0;
	snake.direction = 0;
	snake.animation = 5;
	snake.BFS_size = 0;
	snake.is_alive = 0;
	snake.respawn_time = 300;
	snake.respawn = snake.respawn_time;
	snake.try_reach = 3.0f;
	snake.attack_reach = 1.2f;
	draw_snake();

	// scorpion
	scorpion.turn_speed = 15;
	scorpion.move_speed = 0.05;
	scorpion.abs_pos.x = MAPSIZE*2;
	scorpion.abs_pos.z = MAPSIZE*2+1;
	scorpion.grid_pos.x = MAPSIZE*2;
	scorpion.grid_pos.y = MAPSIZE*2;
	scorpion.grid_going.x = MAPSIZE*2;
	scorpion.grid_going.y = MAPSIZE*2;
	scorpion.abs_rot = 0;
	scorpion.can_move = 1;
	scorpion.is_attacking = 0;
	scorpion.direction = 0;
	scorpion.animation = 5;
	scorpion.BFS_size = 0;
	scorpion.is_alive = 0;
	scorpion.respawn_time = 200;
	scorpion.respawn = scorpion.respawn_time;
	scorpion.try_reach = 3.0f;
	scorpion.attack_reach = 1.3f;
	draw_scorpion();

	// mummy
	mummy.turn_speed = 15;
	mummy.move_speed = 0.04;
	mummy.abs_pos.x = MAPSIZE*2;
	mummy.abs_pos.z = MAPSIZE*2+1;
	mummy.grid_pos.x = MAPSIZE*2;
	mummy.grid_pos.y = MAPSIZE*2;
	mummy.grid_going.x = MAPSIZE*2;
	mummy.grid_going.y = MAPSIZE*2;
	mummy.abs_rot = 0;
	mummy.can_move = 1;
	mummy.is_attacking = 0;
	mummy.direction = 0;
	mummy.animation = 6;
	mummy.BFS_size = 0;
	mummy.is_alive = 0;
	mummy.respawn_time = 100;
	mummy.respawn = mummy.respawn_time;
	mummy.try_reach = 3.0f;
	mummy.attack_reach = 1.2f;
	draw_mummy();

	cursor.grid_pos.x = 15;
	cursor.grid_pos.y = 15;
	cursor.abs_pos.x = cursor.grid_pos.x;
	cursor.abs_pos.z = (float)cursor.grid_pos.y + 1.0f;
	cursor.move_time = 0;
	cursor.move_cd = 10;

	ed_block = 1;
	ed_block_time = 0;
	for (i = 0; i < 3; i++)
	{
		ed_spawn_exit_placed[i] = 0;
		ed_key_placed[i] = 0;
		ed_door_placed[i] = 0;
	}
	ed_spawn_exit_placed[3] = 0; // player spawn
	ed_spawn_exit_placed[4] = 0; // player exit
	ed_artifact_placed = 0;
	ed_teleports_placed = 0;
	ed_water_settings_placed = 0;
	ed_place_init_fix = 15;
	

	generate_blank_map(map_matrix);
}

void fix_rotations()
{
    // player =====================================================
    if (player.direction == 0)
    {
        if (player.abs_rot < 0)
        {
        	player.abs_rot += player.turn_speed;
        	player.done_rotating = 0;
        }
        if (player.abs_rot > 0)
        {
        	player.abs_rot -= player.turn_speed;
        	player.done_rotating = 0;
        }
        if (player.abs_rot == 0)
        {
        	player.done_rotating = 1;
        }
    }
    if (player.direction == 1)
    {
        if (player.abs_rot < 0)
        {
        	player.abs_rot += 360;
        	player.done_rotating = 0;
        }
        if (player.abs_rot < 180)
        {
        	player.abs_rot += player.turn_speed;
        	player.done_rotating = 0;
        }
        if (player.abs_rot > 180)
        {
        	player.abs_rot -= player.turn_speed;
        	player.done_rotating = 0;
        }
        if (player.abs_rot == 180)
        {
        	player.done_rotating = 1;
        }
    }
    if (player.direction == 2)
    {
        if (player.abs_rot < 90)
        {
        	player.abs_rot += player.turn_speed;
        	player.done_rotating = 0;
        }
        if (player.abs_rot > 90)
        {
        	player.abs_rot -= player.turn_speed;
        	player.done_rotating = 0;
        }
        if (player.abs_rot == 90)
        {
        	player.done_rotating = 1;
        }
    }
    if (player.direction == 3)
    {
        if (player.abs_rot > 90)
        {
        	player.abs_rot -= 360;
        	player.done_rotating = 0;
        }
        if (player.abs_rot < -90)
        {
        	player.abs_rot += player.turn_speed;
        	player.done_rotating = 0;
        }
        if (player.abs_rot > -90)
        {
        	player.abs_rot -= player.turn_speed;
        	player.done_rotating = 0;
        }
        if (player.abs_rot == -90)
        {
        	player.done_rotating = 1;
        }
    }

    // snake =====================================================
	if (snake.direction == 0)
	{
	    if (snake.abs_rot < 0) snake.abs_rot += snake.turn_speed;
	    if (snake.abs_rot > 0) snake.abs_rot -= snake.turn_speed;
	}
	if (snake.direction == 1)
	{
	    if (snake.abs_rot < 0) snake.abs_rot += 360;
	    if (snake.abs_rot < 180) snake.abs_rot += snake.turn_speed;
	    if (snake.abs_rot > 180) snake.abs_rot -= snake.turn_speed;
	}
	if (snake.direction == 2)
	{
	    if (snake.abs_rot < 90) snake.abs_rot += snake.turn_speed;
	    if (snake.abs_rot > 90) snake.abs_rot -= snake.turn_speed;
	}
	if (snake.direction == 3)
	{
	    if (snake.abs_rot > 90) snake.abs_rot -= 360;
	    if (snake.abs_rot < -90) snake.abs_rot += snake.turn_speed;
	    if (snake.abs_rot > -90) snake.abs_rot -= snake.turn_speed;
	}

	// scorpion =====================================================
	if (scorpion.direction == 0)
	{
	    if (scorpion.abs_rot < 0) scorpion.abs_rot += scorpion.turn_speed;
	    if (scorpion.abs_rot > 0) scorpion.abs_rot -= scorpion.turn_speed;
	}
	if (scorpion.direction == 1)
	{
	    if (scorpion.abs_rot < 0) scorpion.abs_rot += 360;
	    if (scorpion.abs_rot < 180) scorpion.abs_rot += scorpion.turn_speed;
	    if (scorpion.abs_rot > 180) scorpion.abs_rot -= scorpion.turn_speed;
	}
	if (scorpion.direction == 2)
	{
	    if (scorpion.abs_rot < 90) scorpion.abs_rot += scorpion.turn_speed;
	    if (scorpion.abs_rot > 90) scorpion.abs_rot -= scorpion.turn_speed;
	}
	if (scorpion.direction == 3)
	{
	    if (scorpion.abs_rot > 90) scorpion.abs_rot -= 360;
	    if (scorpion.abs_rot < -90) scorpion.abs_rot += scorpion.turn_speed;
	    if (scorpion.abs_rot > -90) scorpion.abs_rot -= scorpion.turn_speed;
	}

    // mummy =====================================================
    if (mummy.direction == 0)
    {
        if (mummy.abs_rot < 0) mummy.abs_rot += mummy.turn_speed;
        if (mummy.abs_rot > 0) mummy.abs_rot -= mummy.turn_speed;
    }
    if (mummy.direction == 1)
    {
        if (mummy.abs_rot < 0) mummy.abs_rot += 360;
        if (mummy.abs_rot < 180) mummy.abs_rot += mummy.turn_speed;
        if (mummy.abs_rot > 180) mummy.abs_rot -= mummy.turn_speed;
    }
    if (mummy.direction == 2)
    {
        if (mummy.abs_rot < 90) mummy.abs_rot += mummy.turn_speed;
        if (mummy.abs_rot > 90) mummy.abs_rot -= mummy.turn_speed;
    }
    if (mummy.direction == 3)
    {
        if (mummy.abs_rot > 90) mummy.abs_rot -= 360;
        if (mummy.abs_rot < -90) mummy.abs_rot += mummy.turn_speed;
        if (mummy.abs_rot > -90) mummy.abs_rot -= mummy.turn_speed;
    }
}

void fix_positions()
{    
    int player_can_move_x = 1;
    int player_can_move_z = 1;
    int snake_can_move_x = 1;
    int snake_can_move_z = 1;
    int scorpion_can_move_x = 1;
    int scorpion_can_move_z = 1;
    int mummy_can_move_x = 1;
    int mummy_can_move_z = 1;

    // player =====================================================
    if (player.is_alive)
	{
	    if (player.abs_pos.z < player.grid_going.y - 0.1 + 1 && 
	        player.abs_pos.z < player.grid_going.y + 0.1 + 1)
	    {
	        player.abs_pos.z += player.move_speed;
	        player_can_move_x = 0;
	    }
	    else if (player.abs_pos.z > player.grid_going.y + 1)
	    {
	        player.abs_pos.z -= player.move_speed;
	        player_can_move_x = 0;
	    }
	    else
	    {
	        player.grid_pos.y = player.grid_going.y;
	        player_can_move_x = 1;
	    }

	    if (player.abs_pos.x < player.grid_going.x - 0.1 && 
	        player.abs_pos.x < player.grid_going.x + 0.1)
	    {
	        player.abs_pos.x += player.move_speed;
	        player_can_move_z = 0;
	    }
	    else if (player.abs_pos.x > player.grid_going.x)
	    {
	        player.abs_pos.x -= player.move_speed;
	        player_can_move_z = 0;
	    }
	    else
	    {
	        player.grid_pos.x = player.grid_going.x;
	        player_can_move_z = 1;
	    }

	    if (player_can_move_x && player_can_move_z) player.can_move = 1;
	}

	// snake =====================================================
    if (snake.is_alive)
    {
    	if (snake.abs_pos.z < snake.grid_going.y - 0.1 + 1 && 
        snake.abs_pos.z < snake.grid_going.y + 0.1 + 1)
    {
        snake.abs_pos.z += snake.move_speed;
        snake_can_move_x = 0;
    }
    else if (snake.abs_pos.z > snake.grid_going.y + 1)
    {
        snake.abs_pos.z -= snake.move_speed;
        snake_can_move_x = 0;
    }
    else
    {
        snake.grid_pos.y = snake.grid_going.y;
        snake_can_move_x = 1;
    }

    if (snake.abs_pos.x < snake.grid_going.x - 0.1 && 
        snake.abs_pos.x < snake.grid_going.x + 0.1)
    {
        snake.abs_pos.x += snake.move_speed;
        snake_can_move_z = 0;
    }
    else if (snake.abs_pos.x > snake.grid_going.x)
    {
        snake.abs_pos.x -= snake.move_speed;
        snake_can_move_z = 0;
    }
    else
    {
        snake.grid_pos.x = snake.grid_going.x;
        snake_can_move_z = 1;
    }

    if (snake_can_move_x && snake_can_move_z) snake.can_move = 1;
    }

    // scorpion =====================================================
    if (scorpion.is_alive)
    {
    	if (scorpion.abs_pos.z < scorpion.grid_going.y - 0.1 + 1 && 
        scorpion.abs_pos.z < scorpion.grid_going.y + 0.1 + 1)
    {
        scorpion.abs_pos.z += scorpion.move_speed;
        scorpion_can_move_x = 0;
    }
    else if (scorpion.abs_pos.z > scorpion.grid_going.y + 1)
    {
        scorpion.abs_pos.z -= scorpion.move_speed;
        scorpion_can_move_x = 0;
    }
    else
    {
        scorpion.grid_pos.y = scorpion.grid_going.y;
        scorpion_can_move_x = 1;
    }

    if (scorpion.abs_pos.x < scorpion.grid_going.x - 0.1 && 
        scorpion.abs_pos.x < scorpion.grid_going.x + 0.1)
    {
        scorpion.abs_pos.x += scorpion.move_speed;
        scorpion_can_move_z = 0;
    }
    else if (scorpion.abs_pos.x > scorpion.grid_going.x)
    {
        scorpion.abs_pos.x -= scorpion.move_speed;
        scorpion_can_move_z = 0;
    }
    else
    {
        scorpion.grid_pos.x = scorpion.grid_going.x;
        scorpion_can_move_z = 1;
    }

    if (scorpion_can_move_x && scorpion_can_move_z) scorpion.can_move = 1;
    }

    // mummy =====================================================
    if (mummy.is_alive)
    {
    	if (mummy.abs_pos.z < mummy.grid_going.y - 0.1 + 1 && 
        mummy.abs_pos.z < mummy.grid_going.y + 0.1 + 1)
    {
        mummy.abs_pos.z += mummy.move_speed;
        mummy_can_move_x = 0;
    }
    else if (mummy.abs_pos.z > mummy.grid_going.y + 1)
    {
        mummy.abs_pos.z -= mummy.move_speed;
        mummy_can_move_x = 0;
    }
    else
    {
        mummy.grid_pos.y = mummy.grid_going.y;
        mummy_can_move_x = 1;
    }

    if (mummy.abs_pos.x < mummy.grid_going.x - 0.1 && 
        mummy.abs_pos.x < mummy.grid_going.x + 0.1)
    {
        mummy.abs_pos.x += mummy.move_speed;
        mummy_can_move_z = 0;
    }
    else if (mummy.abs_pos.x > mummy.grid_going.x)
    {
        mummy.abs_pos.x -= mummy.move_speed;
        mummy_can_move_z = 0;
    }
    else
    {
        mummy.grid_pos.x = mummy.grid_going.x;
        mummy_can_move_z = 1;
    }

    if (mummy_can_move_x && mummy_can_move_z) mummy.can_move = 1;
    }
}

void fix_animations()
{
	// player =====================================================
	if (player.is_alive && player.reload == 0)
	{
	    if (player.can_move == 1) player.animation = 1;
	    else player.animation = 2;
	}
	else if (player.is_alive && player.reload > 0)
	{
		if (player.can_move == 1) player.animation = 3;
	    else player.animation = 4;
	}

	// snake =====================================================
    if (snake.is_alive && player.is_alive)
    {
    	if (snake.can_move == 1 && snake.is_attacking == 0)
	    {
	    	snake.animation = 0;
	    }
	    else if (snake.can_move == 0 && snake.is_attacking == 0)
	    {
	    	snake.animation = 1;
	    }
	    else if (snake.can_move == 1 && snake.is_attacking == 1)
	    {
	    	snake.animation = 2;
	    }
	    else
	    {
	    	snake.animation = 3;
	    }
    }
    else if (snake.is_alive && !player.is_alive)
    {
    	snake.animation = 0;
    }
    else
    {
    	snake.animation = 4;
    }

    // scorpion =====================================================
    if (scorpion.is_alive && player.is_alive)
    {
    	if (scorpion.can_move == 1 && scorpion.is_attacking == 0)
	    {
	    	scorpion.animation = 0;
	    }
	    else if (scorpion.can_move == 0 && scorpion.is_attacking == 0)
	    {
	    	scorpion.animation = 1;
	    }
	    else if (scorpion.can_move == 1 && scorpion.is_attacking == 1)
	    {
	    	scorpion.animation = 2;
	    }
	    else
	    {
	    	scorpion.animation = 3;
	    }
    }
    else if (scorpion.is_alive && !player.is_alive)
    {
    	scorpion.animation = 0;
    }
    else
    {
    	scorpion.animation = 4;
    }

    // mummy =====================================================
    if (mummy.is_alive && player.is_alive)
    {
    	if (mummy.can_move == 1 && mummy.is_attacking == 0)
	    {
	    	mummy.animation = 1;
	    }
	    else if (mummy.can_move == 0 && mummy.is_attacking == 0)
	    {
	    	mummy.animation = 2;
	    }
	    else if (mummy.can_move == 1 && mummy.is_attacking == 1)
	    {
	    	mummy.animation = 3;
	    }
	    else
	    {
	    	mummy.animation = 4;
	    }
    }
    else if (mummy.is_alive && !player.is_alive)
    {
    	mummy.animation = 0;
    }
    else
    {
    	mummy.animation = 5;
    }
    
}

// checks if position on map is avaliable
int position_available(int x, int y)
{
	// map limits
	if (x < 0 || x > MAPSIZE-1) return 0;
	if (y < 0 || y > MAPSIZE-1) return 0;

	// is the tile walkable?
    if (map_walkable(map_matrix, x, y))
        return 1;
    else
        return 0;
}

void draw_BFS_GPS()
{
	int i = 0;
	while (i < scorpion.BFS_size)
 	{
 		glPushMatrix();
 			glTranslatef((float)scorpion.movement_array[i].y+1, 0.5, (float)scorpion.movement_array[i].x);
 			glutSolidSphere(0.2, 5, 5);
 		glPopMatrix();
 		i++;
 	}
}

void respawn_player()
{
	player.animation = 6;
	draw_player();
	init_entities(1);
}

void restart_game()
{
	player.animation = 6;
	draw_player();
	init();
}

void goto_title_screen()
{
	player_fire_init_fix = 15;
	player.animation = 6;
	draw_player();
	scene_value = 0;
}

void next_level()
{
	char mapname[10];

	player.animation = 6;
	draw_player();

	player_actual_level ++;
	player_score += player_time;

	if (!map_exists(selected_campaign, player_actual_level))
    {
    	if (player_score > player_high_score)
		{
			save_score(&player_score, selected_campaign);
		}
    	goto_title_screen();
    	return;
    }

    if (player_actual_level < 10)
	{
		sprintf(mapname, "map0%d", player_actual_level);
	}
	else
	{
		sprintf(mapname, "map%d", player_actual_level);
	}

    load_map(map_matrix, selected_campaign, mapname);

    player_time = TIMELIMIT;
    player_time_cd = 0;

    init_entities(0);
}

void map_draw_temp_mobs()
{
	int i, j;

	for (i = 0; i < MAPSIZE; i++)
	{
		for (j = 0; j < MAPSIZE; j++)
		{
			if (map_matrix[i][j] == 16)
			{
				glPushMatrix();
			    	glTranslatef(j+1, 0, i);
			    	glRotatef(180, 0, 1, 0);
			    	glScalef(0.5, 0.5, 0.5);
			    	obj_snake(0);
			    glPopMatrix();
			}

			if (map_matrix[i][j] == 17)
			{
				glPushMatrix();
			    	glTranslatef(j+1, 0, i);
			    	glRotatef(180, 0, 1, 0);
			    	glScalef(0.3, 0.3, 0.3);
			    	obj_scorpion(0);
			    glPopMatrix();
			}

			if (map_matrix[i][j] == 18)
			{
				glPushMatrix();
			    	glTranslatef(j+1, 0, i);
			    	glRotatef(180, 0, 1, 0);
			    	glScalef(0.5, 0.5, 0.5);
			    	obj_mummy(0);
			    glPopMatrix();
			}
		}
	}
}

void map_draw_cursor()
{
	glPushMatrix();
		glTranslatef((float)cursor.grid_pos.y + 1.0, 1.0, cursor.grid_pos.x);
		glRotatef(45, 0, 1, 0);
		glScalef(0.2, 2.5, 0.2);
		tcube((int[]){1, 0, 1, 1, 1, 2});
	glPopMatrix();
}

void display_function() 
{
	int i;

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    refresh_camera();
    glColor4f(1.0f, 1.0f, 1.0f, 0.0); 
    if (scene_value == 0)
    {
    	load_score(&player_high_score, selected_campaign);
    	draw_menu_bg(menu_position, player_high_score);
    }
    else if (scene_value == 1)
    {
	    draw_player();
	    draw_snake();
	    draw_scorpion();
	    draw_mummy();
	    for (i = 0; i < 3; i++) draw_item(i);
	    for (i = 0; i < 3; i++) draw_key(i);
	    draw_map(); 

	    // draw HUD
	    draw_overlay(player.abs_pos.z-5, 7, player.abs_pos.x, player.reload, player.flash, player_lives_number,
	    	         player_flashes_number, player_score, player_time, keys_gotten);

	    if (player.respawn > 0)
	    {
	    	lighting(player.abs_pos.z, player.abs_pos.x, 0.05f, 
	    		     ((float)player.respawn-10)/((float)player.respawn_time-10)-(1.0f-lt_settings));
	    }
	    else if (player.flash > 100)
	    {
	    	lighting(player.abs_pos.z, player.abs_pos.x, 0.05f, 
	    		     ((float)player.flash-100)/((float)player.flash_time-100) + lt_settings);
	    }
	    else if (player.reload > 97)
	    {
	    	lighting(player.abs_pos.z, player.abs_pos.x, 0.01f, lt_settings);
	    }
	    else
	    {
			lighting(player.abs_pos.z, player.abs_pos.x, 0.05f, lt_settings);
	    }
    }
    else
    {	
    	map_draw_temp_mobs();
    	map_draw_cursor();
    	draw_map();
    	draw_editor_overlay(cursor.abs_pos.z-5, 7, cursor.abs_pos.x, ed_block, 0);
    	lighting(cursor.abs_pos.z, cursor.abs_pos.x, 0.001f, 1.0);
    }

    glutSwapBuffers();
}

void player_death_animation()
{
	if (player_lives_number > 0)
	{
		player_lives_number--;
	}
	player.is_alive = 0;
	player.can_move = 0;
	player.animation = 5;
	player.respawn = player.respawn_time;
}

void snake_death_animation()
{
	snake.is_alive = 0;
	snake.can_move = 0;
	snake.animation = 4;
	snake.respawn = snake.respawn_time;
}

void scorpion_death_animation()
{
	scorpion.is_alive = 0;
	scorpion.can_move = 0;
	scorpion.animation = 4;
	scorpion.respawn = scorpion.respawn_time;
}

void mummy_death_animation()
{
	mummy.is_alive = 0;
	mummy.can_move = 0;
	mummy.animation = 5;
	mummy.respawn = mummy.respawn_time;
}

void AI()
{
	// snake =====================================================
	if (snake.is_alive && snake.abs_pos.x < MAPSIZE+1 && snake.abs_pos.z < MAPSIZE+1) // follow and kill player
	{
		if (player.is_alive)
		{
			if (snake.can_move)
			{
				BFS(snake.grid_pos, player.grid_pos, map_matrix);
		 		snake.BFS_size = BFS_get_path_coords(snake.grid_pos, player.grid_pos, snake.movement_array);

			 	if (abs(snake.movement_array[0].x - snake.grid_pos.x) > 1 ||
			 		abs(snake.movement_array[0].y - snake.grid_pos.y) > 1)
			 	{
			 		goto snake_dont_move;
			 	}
			 	
			 	if (snake.movement_array[0].y == snake.grid_pos.y+1) snake.direction = 0;
			 	if (snake.movement_array[0].y == snake.grid_pos.y-1) snake.direction = 1;
			 	if (snake.movement_array[0].x == snake.grid_pos.x-1) snake.direction = 2;
			 	if (snake.movement_array[0].x == snake.grid_pos.x+1) snake.direction = 3;

			 	if (snake.grid_going.x != snake.movement_array[0].x ||
			 		snake.grid_going.y != snake.movement_array[0].y)
			 	{
			 		snake.grid_going.x = snake.movement_array[0].x;
				 	snake.grid_going.y = snake.movement_array[0].y;
					snake.can_move = 0;
				}
			}

			if (VECTOR2F_dist(player.abs_pos, snake.abs_pos) < snake.attack_reach)
			{
				player_death_animation();
			}
			else if (VECTOR2F_dist(player.abs_pos, snake.abs_pos) < snake.try_reach)
			{
				snake.is_attacking = 1;
			}
			else
			{
				snake.is_attacking = 0;
			}
		}
	}
	else if (snake.respawn == 0) // spawn or respawn
	{
		snake.animation = 5;
		draw_snake();
		snake.abs_pos.x = mob_spawn_pos_snake.x;
		snake.abs_pos.z = mob_spawn_pos_snake.y+1;
		snake.grid_pos.x = mob_spawn_pos_snake.x;
		snake.grid_pos.y = mob_spawn_pos_snake.y;
		snake.grid_going.x = mob_spawn_pos_snake.x;
		snake.grid_going.y = mob_spawn_pos_snake.y;
		snake.is_alive = 1;
	}
	else // reduce respawn
	{
		snake.respawn--;
	}

	snake_dont_move:

	// scorpion =====================================================
	if (scorpion.is_alive && scorpion.abs_pos.x < MAPSIZE+1 && scorpion.abs_pos.z < MAPSIZE+1) // follow and kill player
	{
		if (player.is_alive)
		{
			if (scorpion.can_move)
			{
				BFS(scorpion.grid_pos, player.grid_pos, map_matrix);
		 		scorpion.BFS_size = BFS_get_path_coords(scorpion.grid_pos, player.grid_pos, scorpion.movement_array);
			 	
			 	if (abs(scorpion.movement_array[0].x - scorpion.grid_pos.x) > 1 ||
			 		abs(scorpion.movement_array[0].y - scorpion.grid_pos.y) > 1)
			 	{
			 		goto scorpion_dont_move;
			 	}
			 	if (scorpion.movement_array[0].y == scorpion.grid_pos.y+1) scorpion.direction = 0;
			 	if (scorpion.movement_array[0].y == scorpion.grid_pos.y-1) scorpion.direction = 1;
			 	if (scorpion.movement_array[0].x == scorpion.grid_pos.x-1) scorpion.direction = 2;
			 	if (scorpion.movement_array[0].x == scorpion.grid_pos.x+1) scorpion.direction = 3;

			 	if (scorpion.grid_going.x != scorpion.movement_array[0].x ||
			 		scorpion.grid_going.y != scorpion.movement_array[0].y)
			 	{
			 		scorpion.grid_going.x = scorpion.movement_array[0].x;
				 	scorpion.grid_going.y = scorpion.movement_array[0].y;
					scorpion.can_move = 0;
				}
			}

			if (VECTOR2F_dist(player.abs_pos, scorpion.abs_pos) < scorpion.attack_reach)
			{
				player_death_animation();
			}
			else if (VECTOR2F_dist(player.abs_pos, scorpion.abs_pos) < scorpion.try_reach)
			{
				scorpion.is_attacking = 1;
			}
			else
			{
				scorpion.is_attacking = 0;
			}
		}
	}
	else if (scorpion.respawn == 0) // spawn or respawn
	{
		scorpion.animation = 5;
		draw_scorpion();
		scorpion.abs_pos.x = mob_spawn_pos_scorpion.x;
		scorpion.abs_pos.z = mob_spawn_pos_scorpion.y+1;
		scorpion.grid_pos.x = mob_spawn_pos_scorpion.x;
		scorpion.grid_pos.y = mob_spawn_pos_scorpion.y;
		scorpion.grid_going.x = mob_spawn_pos_scorpion.x;
		scorpion.grid_going.y = mob_spawn_pos_scorpion.y;
		scorpion.is_alive = 1;
	}
	else // reduce respawn
	{
		scorpion.respawn--;
	}

	scorpion_dont_move:

	// mummy =====================================================
	if (mummy.is_alive && mummy.abs_pos.x < MAPSIZE+1 && mummy.abs_pos.z < MAPSIZE+1) // follow and kill player
	{
		if (player.is_alive)
		{
			if (mummy.can_move)
			{
				BFS(mummy.grid_pos, player.grid_pos, map_matrix);
		 		mummy.BFS_size = BFS_get_path_coords(mummy.grid_pos, player.grid_pos, mummy.movement_array);

			 	if (abs(mummy.movement_array[0].x - mummy.grid_pos.x) > 1 ||
			 		abs(mummy.movement_array[0].y - mummy.grid_pos.y) > 1)
			 	{
			 		goto mummy_dont_move;
			 	}
			 	
			 	if (mummy.movement_array[0].y == mummy.grid_pos.y+1) mummy.direction = 0;
			 	if (mummy.movement_array[0].y == mummy.grid_pos.y-1) mummy.direction = 1;
			 	if (mummy.movement_array[0].x == mummy.grid_pos.x-1) mummy.direction = 2;
			 	if (mummy.movement_array[0].x == mummy.grid_pos.x+1) mummy.direction = 3;

			 	if (mummy.grid_going.x != mummy.movement_array[0].x ||
			 		mummy.grid_going.y != mummy.movement_array[0].y)
			 	{
			 		mummy.grid_going.x = mummy.movement_array[0].x;
				 	mummy.grid_going.y = mummy.movement_array[0].y;
					mummy.can_move = 0;
				}
			}

			if (VECTOR2F_dist(player.abs_pos, mummy.abs_pos) < mummy.attack_reach)
			{
				player_death_animation();
			}
			else if (VECTOR2F_dist(player.abs_pos, mummy.abs_pos) < mummy.try_reach)
			{
				mummy.is_attacking = 1;
			}
			else
			{
				mummy.is_attacking = 0;
			}
		}
	}
	else if (mummy.respawn == 0) // spawn or respawn
	{
		mummy.animation = 6;
		draw_mummy();
		mummy.abs_pos.x = mob_spawn_pos_mummy.x;
		mummy.abs_pos.z = mob_spawn_pos_mummy.y+1;
		mummy.grid_pos.x = mob_spawn_pos_mummy.x;
		mummy.grid_pos.y = mob_spawn_pos_mummy.y;
		mummy.grid_going.x = mob_spawn_pos_mummy.x;
		mummy.grid_going.y = mob_spawn_pos_mummy.y;
		mummy.is_alive = 1;
	}
	else // reduce respawn
	{
		mummy.respawn--;
	}

	mummy_dont_move:
	return;
}

void check_if_player_has_exit()
{
	if (player.grid_pos.x == exit_in_position.x && player.grid_pos.y == exit_in_position.y)
	{
		next_level();
	}
}

void check_if_player_has_teleported()
{
	if (teleport_cooldown > 0)
	{
		teleport_cooldown --;
		return;
	}
	if (player.grid_pos.x == teleport_in_position[0].x && player.grid_pos.y == teleport_in_position[0].y)
	{
		player.grid_pos.x = teleport_in_position[1].x;
		player.grid_pos.y = teleport_in_position[1].y;
		player.grid_going.x = player.grid_pos.x;
		player.grid_going.y = player.grid_pos.y;
		player.abs_pos.x = (float)player.grid_pos.x;
		player.abs_pos.z = (float)player.grid_pos.y + 1.0f;
		teleport_cooldown = TELEPORT_COOLDOWN_CS;
		return;
	}
	else if (player.grid_pos.x == teleport_in_position[1].x && player.grid_pos.y == teleport_in_position[1].y)
	{
		player.grid_pos.x = teleport_in_position[0].x;
		player.grid_pos.y = teleport_in_position[0].y;
		player.grid_going.x = player.grid_pos.x;
		player.grid_going.y = player.grid_pos.y;
		player.abs_pos.x = (float)player.grid_pos.x;
		player.abs_pos.z = (float)player.grid_pos.y + 1.0f;
		teleport_cooldown = TELEPORT_COOLDOWN_CS;
		return;
	}
}

void check_if_player_is_dead()
{
	if (!player.is_alive)
	{
		player.respawn--;

		if (player.respawn == 0)
		{
			if (player_lives_number == 0)
			{
				if (player_score > player_high_score)
				{
					save_score(&player_score, selected_campaign);
				}
				goto_title_screen();
			}
			else
			{
				respawn_player();
			}
		}
	}
}

void check_if_player_is_reloading()
{
	if (player.reload > 0)
	{
		player.reload --;
	}
}

void check_if_player_is_reflashing()
{
	if (player.flash > 0)
	{
		player.flash --;
	}
}

void player_fire()
{
	int firerot = player.direction;

	VECTOR2 firepos;
	firepos.x = player.grid_pos.x;
	firepos.y = player.grid_pos.y;

	if (player.reload == 0 && player.done_rotating)
	{
		player.reload = player.reload_time;
		while (map_walkable(map_matrix, firepos.x, firepos.y))
		{
			if (mummy.grid_pos.x == firepos.x && mummy.grid_pos.y == firepos.y && mummy.is_alive)
			{
				mummy_death_animation();
				break;
			}
			else if (snake.grid_pos.x == firepos.x && snake.grid_pos.y == firepos.y && snake.is_alive)
			{
				snake_death_animation();
				break;
			}
			else if (scorpion.grid_pos.x == firepos.x && scorpion.grid_pos.y == firepos.y && scorpion.is_alive)
			{
				scorpion_death_animation();
				break;
			}
			else
			{
				switch (firerot)
				{
					case 0:
						firepos.y += 1;
						break;
					case 1:
						firepos.y -= 1;
						break;
					case 2:
						firepos.x -= 1;
						break;
					case 3:
						firepos.x += 1;
						break;
				}
			}
		}
	}
}

void player_flash()
{
	if (player_flashes_number > 0)
	{
		player_flashes_number --;
		player.flash = player.flash_time;
		snake_death_animation();
		scorpion_death_animation();
		mummy_death_animation();
	}
}

void check_if_player_picked_up_item()
{
	for (int i = 0; i < 3; i++)
	{
		if (abs(player.grid_pos.x - item_in_position[i].x) + 
			abs(player.grid_pos.y - item_in_position[i].y) <= 1)
		{
			player_score += ARTIFACT_POINTS;
			item_in_position[i].x = MAPSIZE*2;
			item_in_position[i].y = MAPSIZE*2;
		}
	}
}

void check_if_player_picked_up_key()
{
	for (int i = 0; i < 3; i++)
	{
		if (player.grid_pos.x == key_in_position[i].x &&
			player.grid_pos.y == key_in_position[i].y)
		{
			key_in_position[i].x = MAPSIZE*2;
			key_in_position[i].y = MAPSIZE*2;
			keys_gotten[i] = 1;
		}
	}
}

void check_if_player_is_by_a_door()
{
	for (int i = 0; i < 3; i++)
	{
		if (abs(player.grid_pos.x - door_in_position[i].x) + 
			abs(player.grid_pos.y - door_in_position[i].y) <= 1)
		{
			// if the player has the correct key, open the door
			if (keys_gotten[i] && !doors_opened[i])
			{
				doors_opened[i] = 1;
				door_open_tile_change_timer = 10;
			}
		}
	}
}

void check_if_door_has_been_opened()
{
	if (door_open_tile_change_timer == 0)
	{
		for (int i = 0; i < 3; i++)
		{
			if (doors_opened[i])
			{
				map_matrix[door_in_position[i].x][door_in_position[i].y] = 32;
			}
		}
	}
	else
	{
		door_open_tile_change_timer --;
	}
}

void map_check_specials()
{
	int i, j;

	for (i = 0; i < 5; i++) ed_spawn_exit_placed[i] = 0;
	ed_artifact_placed = 0;
	ed_teleports_placed = 0;
	ed_water_settings_placed = 0;
	wt_rotation = 0.0f;
	ed_dark_settings_placed = 0;
	for (i = 0; i < 3; i++) ed_key_placed[i] = 0;
	for (i = 0; i < 3; i++) ed_door_placed[i] = 0;

	for (i = 0; i < MAPSIZE; i++)
	{
		for (j= 0; j < MAPSIZE; j++)
		{
			if (map_matrix[i][j] >= 14 && map_matrix[i][j] <= 18)
			{
				ed_spawn_exit_placed[map_matrix[i][j]-14] ++;
			}
			else if (map_matrix[i][j] >= 20 && map_matrix[i][j] <= 25)
			{
				ed_artifact_placed ++;
			}
			else if (map_matrix[i][j] >= 26 && map_matrix[i][j] <= 28)
			{
				ed_key_placed[map_matrix[i][j]-26] ++;
			}
			else if (map_matrix[i][j] >= 29 && map_matrix[i][j] <= 31)
			{
				ed_door_placed[map_matrix[i][j]-29] ++;
			}
			else if (map_matrix[i][j] == 34)
			{
				ed_teleports_placed ++;
			}
			else if (map_matrix[i][j] >= 35 && map_matrix[i][j] <= 38)
			{
				ed_water_settings_placed ++;
				wt_rotation = ((float)map_matrix[i][j] - 35.0f) * 90.0f;
			}
			else if (map_matrix[i][j] >= 39 && map_matrix[i][j] <= 41)
			{
				ed_dark_settings_placed ++;
			}
		}
	}
}

void map_convert_unused_tiles(int mode)
{
	// 0: save | 1: load
	int i, j;

	if (mode)
	{
		for (i = 0; i < MAPSIZE; i++)
		{
			for (j = 0; j < MAPSIZE; j++)
			{
				if (map_matrix[i][j] == -1)
				{
					map_matrix[i][j] = 0;
				}
			}
		}
	}
	else
	{
		for (i = 0; i < MAPSIZE; i++)
		{
			for (j = 0; j < MAPSIZE; j++)
			{
				if (map_matrix[i][j] == 0)
				{
					map_matrix[i][j] = -1;
				}
			}
		}
	}
}

void time_tick()
{
	if (player_time_cd == 100)
	{
		player_time = (player_time > 0) ? player_time - 1 : 0;
		player_time_cd = 0;
	}
	else
	{
		player_time_cd ++;
	}
}

void loop_function(int value)
{	
	if (scene_value == 0)
	{
		if (skey_buffer[GLUT_KEY_UP] && menu_cooldown == 0)
		{
			menu_position = (menu_position > 0) ? menu_position - 1 : 2;
			menu_cooldown = 15;
		}
	    if (skey_buffer[GLUT_KEY_DOWN] && menu_cooldown == 0)
	    {
	    	menu_position = (menu_position < 2) ? menu_position + 1 : 0;
	    	menu_cooldown = 15;
	    }
	    if (key_buffer[' '])
	    {
	    	if (menu_position == 0)
	    	{
	    		scene_value = 1;
	    		init();
	    	}
	    	else if (menu_position == 1)
	    	{
	    		scene_value = 2;
	    		init_map_editor();
	    	}
	    	else
	    	{
	    		exit(0);
	    	}
	    }

	    menu_cooldown = (menu_cooldown > 0) ? menu_cooldown - 1 : 0;
	}
	else if (scene_value == 1)
	{
		AI();
		check_if_player_has_exit();
		check_if_player_is_dead();
		check_if_player_is_reloading();
		check_if_player_is_reflashing();
		check_if_player_picked_up_item();
		check_if_player_picked_up_key();
		check_if_player_is_by_a_door();
		check_if_door_has_been_opened();
		check_if_player_has_teleported();

	    if (key_buffer[27])
	    {
	    	if (player_score > player_high_score)
			{
				save_score(&player_score, selected_campaign);
			}
			goto_title_screen();
	    }
	    
	    camchange_cooldown = (camchange_cooldown > 0) ? camchange_cooldown - 1 : 0;

	    // player controls =============================================================

	    if (player.can_move && player.is_alive)
	    {
	    	if (key_buffer['a'] || key_buffer['A'])
	    	{
	    		if (skey_buffer[GLUT_KEY_UP]) player.direction = 0;
	    		if (skey_buffer[GLUT_KEY_DOWN]) player.direction = 1;
	    		if (skey_buffer[GLUT_KEY_LEFT]) player.direction = 2;
	    		if (skey_buffer[GLUT_KEY_RIGHT]) player.direction = 3;
	    	}
	    	else
	    	{
	    		if (skey_buffer[GLUT_KEY_UP])
		        {
		            if (position_available(player.grid_going.x, player.grid_going.y+1))
		            {
		                player.grid_going.y = player.grid_pos.y+1;
		                player.can_move = 0;
		            }
		            player.direction = 0;
		        }
		        else if (skey_buffer[GLUT_KEY_DOWN])
		        {
		            if (position_available(player.grid_going.x, player.grid_going.y-1))
		            {
		                player.grid_going.y = player.grid_pos.y-1;
		                player.can_move = 0;
		            }
		            player.direction = 1;
		            
		        }
		        else if (skey_buffer[GLUT_KEY_LEFT])
		        {
		            if (position_available(player.grid_going.x-1, player.grid_going.y))
		            {
		                player.grid_going.x = player.grid_pos.x-1;
		                player.can_move = 0;
		            }
		            player.direction = 2;
		        }
		        else if (skey_buffer[GLUT_KEY_RIGHT])
		        {
		            if (position_available(player.grid_going.x+1, player.grid_going.y))
		            {
		                player.grid_going.x = player.grid_pos.x+1;
		                player.can_move = 0;
		            }
		            player.direction = 3;
		        }
	    	}
	    }
	    if (player.is_alive)
	    {
	    	if (key_buffer[' '] && GLOBAL_pl_hit_timer == 0 && player_fire_init_fix == 0)
	        {
	        	player_fire();
	        }
	        if ((key_buffer['d'] || key_buffer['D']) && player.flash == 0)
	        {
	        	player_flash();
	        }
	    }

	    player_fire_init_fix = (player_fire_init_fix > 0) ? player_fire_init_fix - 1 : 0;

	    // fix everything
	    fix_animations();
	    fix_positions();
	    fix_rotations();

	    time_tick();
	}
	else
	{
		if (skey_buffer[GLUT_KEY_UP] && cursor.grid_pos.y < MAPSIZE-1 && cursor.move_time == 0)
		{
			cursor.grid_pos.y ++;
			cursor.abs_pos.z = (float)cursor.grid_pos.y + 1.0;
			cursor.move_time = cursor.move_cd;
		}
		else if (skey_buffer[GLUT_KEY_DOWN] && cursor.grid_pos.y > 0 && cursor.move_time == 0)
		{
			cursor.grid_pos.y --;
			cursor.abs_pos.z = (float)cursor.grid_pos.y + 1.0;
			cursor.move_time = cursor.move_cd;
		}
		if (skey_buffer[GLUT_KEY_LEFT] && cursor.grid_pos.x > 0 && cursor.move_time == 0)
		{
			cursor.grid_pos.x --;
			cursor.abs_pos.x = cursor.grid_pos.x;
			cursor.move_time = cursor.move_cd;
		}
		else if (skey_buffer[GLUT_KEY_RIGHT] && cursor.grid_pos.x < MAPSIZE-1 && cursor.move_time == 0)
		{
			cursor.grid_pos.x ++;
			cursor.abs_pos.x = cursor.grid_pos.x;
			cursor.move_time = cursor.move_cd;
		}

		cursor.move_time = (cursor.move_time > 0) ? cursor.move_time - 1 : 0;

		if (key_buffer['a'] || key_buffer['A'])
		{
			cursor.move_cd = 0;
		}
		else
		{
			cursor.move_cd = 10;
		}

		if (key_buffer['d'] || key_buffer['D'])
		{
			ed_block = map_matrix[cursor.grid_pos.x][cursor.grid_pos.y];
		}

		if (key_buffer[' '] && ed_place_init_fix == 0)
		{
			if (ed_block <= 13 || ed_block == 33)
			{
				map_matrix[cursor.grid_pos.x][cursor.grid_pos.y] = ed_block;
			}
			else
			{
				if (ed_block >= 14 && ed_block <= 18 && !ed_spawn_exit_placed[ed_block-14])
				{
					map_matrix[cursor.grid_pos.x][cursor.grid_pos.y] = ed_block;
				}

				else if (ed_block >= 20 && ed_block <= 25 && ed_artifact_placed < 3)
				{
					map_matrix[cursor.grid_pos.x][cursor.grid_pos.y] = ed_block;
				}

				else if (ed_block >= 26 && ed_block <= 28 && !ed_key_placed[ed_block-26])
				{
					map_matrix[cursor.grid_pos.x][cursor.grid_pos.y] = ed_block;
				}
				else if (ed_block >= 29 && ed_block <= 31 && !ed_door_placed[ed_block-29])
				{
					map_matrix[cursor.grid_pos.x][cursor.grid_pos.y] = ed_block;
				}
				else if (ed_block == 34 && ed_teleports_placed < 2)
				{
					map_matrix[cursor.grid_pos.x][cursor.grid_pos.y] = ed_block;
				}
				else if (ed_block >= 35 && ed_block <= 38 && ed_water_settings_placed == 0)
				{
					map_matrix[cursor.grid_pos.x][cursor.grid_pos.y] = ed_block;
				}
				else if (ed_block >= 39 && ed_block <= 41 && ed_dark_settings_placed == 0)
				{
					map_matrix[cursor.grid_pos.x][cursor.grid_pos.y] = ed_block;
				}
				else if (ed_block >= 42 && ed_block <= 45)
				{
					map_matrix[cursor.grid_pos.x][cursor.grid_pos.y] = ed_block;
				}
			}
			map_check_specials();
		}

		ed_place_init_fix = (ed_place_init_fix > 0) ? ed_place_init_fix - 1 : 0;

		if (key_buffer['1'] && ed_block_time == 0)
		{
			if (ed_block >= 1 && ed_block < 6)
			{
				ed_block++;
				ed_block_time = ED_BLOCK_CD;
			}
			else
			{
				ed_block = 1;
				ed_block_time = ED_BLOCK_CD;
			}
		}
		if (key_buffer['2'] && ed_block_time == 0)
		{
			if (ed_block >= 8 && ed_block < 13)
			{
				ed_block++;
				ed_block_time = ED_BLOCK_CD;
			}
			else
			{
				ed_block = 8;
				ed_block_time = ED_BLOCK_CD;
			}
		}
		if (key_buffer['3'] && ed_block_time == 0)
		{
			if (ed_block == 18)
			{
				ed_block = 34;
				ed_block_time = ED_BLOCK_CD;
			}
			else if (ed_block >= 14 && ed_block < 18)
			{
				ed_block++;
				ed_block_time = ED_BLOCK_CD;
			}
			else
			{
				ed_block = 14;
				ed_block_time = ED_BLOCK_CD;
			}
		}
		if (key_buffer['4'] && ed_block_time == 0)
		{
			if (ed_block >= 20 && ed_block < 25)
			{
				ed_block++;
				ed_block_time = ED_BLOCK_CD;
			}
			else
			{
				ed_block = 20;
				ed_block_time = ED_BLOCK_CD;
			}
		}
		if (key_buffer['5'] && ed_block_time == 0)
		{
			if (ed_block >= 26 && ed_block < 28)
			{
				ed_block++;
				ed_block_time = ED_BLOCK_CD;
			}
			else
			{
				ed_block = 26;
				ed_block_time = ED_BLOCK_CD;
			}
		}
		if (key_buffer['6'] && ed_block_time == 0)
		{
			if (ed_block >= 29 && ed_block < 31)
			{
				ed_block++;
				ed_block_time = ED_BLOCK_CD;
			}
			else
			{
				ed_block = 29;
				ed_block_time = ED_BLOCK_CD;
			}
		}
		if (key_buffer['7'] && ed_block_time == 0)
		{
			if (ed_block == 33)
			{
				ed_block = 42;
				ed_block_time = ED_BLOCK_CD;
			}
			else if (ed_block == 43)
			{
				ed_block = 45;
				ed_block_time = ED_BLOCK_CD;
			}
			else if (ed_block >= 42 && ed_block < 44)
			{
				ed_block++;
				ed_block_time = ED_BLOCK_CD;
			}
			else
			{
				ed_block = 33;
				ed_block_time = ED_BLOCK_CD;
			}
		}
		if (key_buffer['8'] && ed_block_time == 0)
		{
			if (ed_block >= 35 && ed_block < 38)
			{
				ed_block++;
				ed_block_time = ED_BLOCK_CD;
			}
			else
			{
				ed_block = 35;
				ed_block_time = ED_BLOCK_CD;
			}
		}
		if (key_buffer['9'] && ed_block_time == 0)
		{
			if (ed_block >= 39 && ed_block < 41)
			{
				ed_block++;
				ed_block_time = ED_BLOCK_CD;
			}
			else
			{
				ed_block = 39;
				ed_block_time = ED_BLOCK_CD;
			}
		}
		if (key_buffer['0'] && ed_block_time == 0)
		{
			ed_block = 0;
		}

		if (skey_buffer[GLUT_KEY_F1] && ed_block_time == 0)
		{
			char campaign_name_s[100];
			char map_name_s[100];
			printf("\n\t========== SAVE MAP ==========\n\n");
			if (ed_spawn_exit_placed[0] == 1 && ed_spawn_exit_placed[1] == 1)
			{
				printf("\n\tType the name of the Campaign: ");
				scanf("%s", campaign_name_s);
				printf("\n\tType the name of the Map: ");
				scanf("%s", map_name_s);
				printf("\n\tDone!\n\n");
				map_convert_unused_tiles(0);
				save_map(map_matrix, campaign_name_s, map_name_s);
				map_convert_unused_tiles(1);
			}
			else
			{
				printf("\n\tMap needs at least a start and an exit to be saved!\n\n");
			}
			
			ed_block_time = ED_BLOCK_CD;
		}

		if (skey_buffer[GLUT_KEY_F2] && ed_block_time == 0)
		{
			char campaign_name_l[100];
			char map_name_l[100];
			printf("\n\t========== LOAD MAP ==========\n\n");
			printf("\n\tType the name of the Campaign: ");
			scanf("%s", campaign_name_l);
			printf("\n\tType the name of the Map: ");
			scanf("%s", map_name_l);
			printf("\n\tDone!\n\n");
			load_map(map_matrix, campaign_name_l, map_name_l);
			map_convert_unused_tiles(1);
			map_check_specials();
			ed_block_time = ED_BLOCK_CD;
		}

		if (skey_buffer[GLUT_KEY_F3] && ed_block_time == 0)
		{
			generate_blank_map(map_matrix);
		}

		if (key_buffer[27])
	    {
			goto_title_screen();
	    }

		ed_block_time = (ed_block_time > 0) ? ed_block_time - 1 : 0;
	}

	wt_keyframe_main = (wt_keyframe_main < WT_KEYFRAME_MAX) ? wt_keyframe_main + 1 : 0;
    glutPostRedisplay();
    glutTimerFunc(10,loop_function, 1);
}

int main(int argc, char * argv[]) 
{
	credits_and_controls();
	if (argc == 1)
	{
		sprintf(selected_campaign, "default");
		window_mode = 0;
	}
	else if (argc == 2)
	{
		sprintf(selected_campaign, "%s", argv[1]);
		window_mode = 0;
		
	}
	else
	{
		sprintf(selected_campaign, "%s", argv[1]);
		window_mode = atoi(argv[2]);
	}

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    glutInitWindowPosition(50, 50);
    glutInitWindowSize(SCRX, SCRY);
    glutCreateWindow("Tutano");

    if (window_mode == 1)
    {
    	glutFullScreen();
    }
    
    clear_key_buffer();
    glutSpecialFunc(KeyboardSpecial);
    glutSpecialUpFunc(KeyboardUpSpecial);
    glutKeyboardFunc(Keyboard);
    glutKeyboardUpFunc(KeyboardUp);

    glutSetCursor(GLUT_CURSOR_NONE);
    glutPassiveMotionFunc(MousePassive);
    glutMouseFunc(Mouse);

    pre_init();

    glutDisplayFunc(display_function);
    glutTimerFunc(60, loop_function, 1);
    
    initTexture();
    glutMainLoop();
    return 0;
}
