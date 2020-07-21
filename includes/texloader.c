/* The source from where parts of this code come from
 * is unknown to me. Everybody uses it, but I could
 * not find the source no matter what. Therefore, for
 * the time being, this is not licensed.*/

#include "texloader.h"

GLuint texture_id[MAX_NO_TEXTURES];

char *filenameArray[MAX_NO_TEXTURES] = {
    "textures/rgb/red.bmp",
    "textures/rgb/green.bmp",
    "textures/rgb/blue.bmp",

    "textures/player/player_head_front.bmp",
    "textures/player/player_head_back.bmp",
    "textures/player/player_head_left.bmp",
    "textures/player/player_head_right.bmp",
    "textures/player/player_head_top.bmp",
    "textures/player/player_head_bottom.bmp",
    "textures/player/player_torso_front.bmp",
    "textures/player/player_torso_back.bmp",
    "textures/player/player_torso_side1.bmp",
    "textures/player/player_torso_side2.bmp",
    "textures/player/player_torso_bottom.bmp",
    "textures/player/player_arms_front.bmp",
    "textures/player/player_arms_back.bmp",
    "textures/player/player_arms_side1.bmp",
    "textures/player/player_arms_side2.bmp",
    "textures/player/player_arms_shoulders.bmp",
    "textures/player/player_arms_hands.bmp",
    "textures/player/player_legs_front.bmp",
    "textures/player/player_legs_back.bmp",
    "textures/player/player_legs_side1.bmp",
    "textures/player/player_legs_side2.bmp",
    "textures/player/player_legs_top.bmp",
    "textures/player/player_legs_feet.bmp",
    "textures/player/player_hatbase_top.bmp",
    "textures/player/player_hatbase_side.bmp",
    "textures/player/player_hatbase_bottom.bmp",
    "textures/player/player_hattop_front.bmp",
    "textures/player/player_hattop_back.bmp",
    "textures/player/player_hattop_left.bmp",
    "textures/player/player_hattop_right.bmp",
    "textures/player/player_hattop_top.bmp",
    "textures/player/player_hattop_bottom.bmp",
    "textures/player/player_gun_front.bmp",
    "textures/player/player_gun_back.bmp",
    "textures/player/player_gun_left.bmp",
    "textures/player/player_gun_right.bmp",
    "textures/player/player_gun_top.bmp",
    "textures/player/player_gun_bottom.bmp",
    "textures/player/player_gun_handle.bmp",

    "textures/mummy/mummy_head_front.bmp",
    "textures/mummy/mummy_head_back.bmp",
    "textures/mummy/mummy_head_left.bmp",
    "textures/mummy/mummy_head_right.bmp",
    "textures/mummy/mummy_head_top.bmp",
    "textures/mummy/mummy_head_bottom.bmp",
    "textures/mummy/mummy_torso_front.bmp",
    "textures/mummy/mummy_torso_back.bmp",
    "textures/mummy/mummy_torso_side1.bmp",
    "textures/mummy/mummy_torso_side2.bmp",
    "textures/mummy/mummy_torso_bottom.bmp",
    "textures/mummy/mummy_arms_front.bmp",
    "textures/mummy/mummy_arms_back.bmp",
    "textures/mummy/mummy_arms_side1.bmp",
    "textures/mummy/mummy_arms_side2.bmp",
    "textures/mummy/mummy_arms_shoulders.bmp",
    "textures/mummy/mummy_arms_hands.bmp",
    "textures/mummy/mummy_legs_front.bmp",
    "textures/mummy/mummy_legs_back.bmp",
    "textures/mummy/mummy_legs_side1.bmp",
    "textures/mummy/mummy_legs_side2.bmp",
    "textures/mummy/mummy_legs_top.bmp",
    "textures/mummy/mummy_legs_feet.bmp",
    "textures/mummy/mummy_falling_parts.bmp",

    "textures/scorpion/scorpion_head_front.bmp", //66
    "textures/scorpion/scorpion_head_back.bmp",
    "textures/scorpion/scorpion_head_left.bmp",
    "textures/scorpion/scorpion_head_right.bmp",
    "textures/scorpion/scorpion_head_top.bmp",
    "textures/scorpion/scorpion_head_bottom.bmp",
    "textures/scorpion/scorpion_bf_front.bmp",
    "textures/scorpion/scorpion_bf_back.bmp",
    "textures/scorpion/scorpion_bf_left.bmp",
    "textures/scorpion/scorpion_bf_right.bmp",
    "textures/scorpion/scorpion_bf_top.bmp",
    "textures/scorpion/scorpion_bf_bottom.bmp",
    "textures/scorpion/scorpion_bmf_front.bmp", //78
    "textures/scorpion/scorpion_bmf_back.bmp",
    "textures/scorpion/scorpion_bmf_left.bmp",
    "textures/scorpion/scorpion_bmf_right.bmp",
    "textures/scorpion/scorpion_bmf_top.bmp",
    "textures/scorpion/scorpion_bmf_bottom.bmp",
    "textures/scorpion/scorpion_bmb_front.bmp", //84
    "textures/scorpion/scorpion_bmb_back.bmp",
    "textures/scorpion/scorpion_bmb_left.bmp",
    "textures/scorpion/scorpion_bmb_right.bmp",
    "textures/scorpion/scorpion_bmb_top.bmp",
    "textures/scorpion/scorpion_bmb_bottom.bmp",
    "textures/scorpion/scorpion_bb_front.bmp", //90
    "textures/scorpion/scorpion_bb_back.bmp",
    "textures/scorpion/scorpion_bb_left.bmp",
    "textures/scorpion/scorpion_bb_right.bmp",
    "textures/scorpion/scorpion_bb_top.bmp",
    "textures/scorpion/scorpion_bb_bottom.bmp",
    "textures/scorpion/scorpion_legs_axis.bmp",//96
    "textures/scorpion/scorpion_legs_front.bmp",
    "textures/scorpion/scorpion_legs_back.bmp",
    "textures/scorpion/scorpion_legs_top.bmp",
    "textures/scorpion/scorpion_legs_bottom.bmp",
    "textures/scorpion/scorpion_legs_side1.bmp",
    "textures/scorpion/scorpion_legs_side2.bmp",
    "textures/scorpion/scorpion_metasoma_front.bmp", //103
    "textures/scorpion/scorpion_metasoma_back.bmp",
    "textures/scorpion/scorpion_metasoma_left.bmp",
    "textures/scorpion/scorpion_metasoma_right.bmp",
    "textures/scorpion/scorpion_metasoma_top.bmp",
    "textures/scorpion/scorpion_metasoma_bottom.bmp",
    "textures/scorpion/scorpion_telson_front.bmp", //109
    "textures/scorpion/scorpion_telson_back.bmp",
    "textures/scorpion/scorpion_telson_left.bmp",
    "textures/scorpion/scorpion_telson_right.bmp",
    "textures/scorpion/scorpion_telson_top.bmp",
    "textures/scorpion/scorpion_telson_bottom.bmp",
    "textures/scorpion/scorpion_arms_axis_small.bmp",
    "textures/scorpion/scorpion_arms_axis_large.bmp",
    "textures/scorpion/scorpion_arms_front.bmp", //117
    "textures/scorpion/scorpion_arms_back.bmp",
    "textures/scorpion/scorpion_arms_left.bmp",
    "textures/scorpion/scorpion_arms_right.bmp",
    "textures/scorpion/scorpion_arms_top.bmp",
    "textures/scorpion/scorpion_arms_bottom.bmp",
    "textures/scorpion/scorpion_claws_front.bmp", //123
    "textures/scorpion/scorpion_claws_back.bmp",
    "textures/scorpion/scorpion_claws_left.bmp",
    "textures/scorpion/scorpion_claws_right.bmp",
    "textures/scorpion/scorpion_claws_top.bmp",
    "textures/scorpion/scorpion_claws_bottom.bmp",

    "textures/snake/snake_body_front.bmp", //129
    "textures/snake/snake_body_back.bmp",
    "textures/snake/snake_body_left.bmp",
    "textures/snake/snake_body_right.bmp",
    "textures/snake/snake_body_top.bmp",
    "textures/snake/snake_body_bottom.bmp",
    "textures/snake/snake_rattle_front.bmp", //135
    "textures/snake/snake_rattle_back.bmp",
    "textures/snake/snake_rattle_left.bmp",
    "textures/snake/snake_rattle_right.bmp",
    "textures/snake/snake_rattle_top.bmp",
    "textures/snake/snake_rattle_bottom.bmp",
    "textures/snake/snake_large_front.bmp", //141
    "textures/snake/snake_large_back.bmp",
    "textures/snake/snake_large_left.bmp",
    "textures/snake/snake_large_right.bmp",
    "textures/snake/snake_large_top.bmp",
    "textures/snake/snake_large_bottom.bmp",
    "textures/snake/snake_head_front.bmp", //147
    "textures/snake/snake_head_back.bmp",
    "textures/snake/snake_head_left.bmp",
    "textures/snake/snake_head_right.bmp",
    "textures/snake/snake_head_top.bmp",
    "textures/snake/snake_head_bottom.bmp",
    "textures/snake/snake_tongue.bmp",

    "textures/cup/cup_bodycolor.bmp", //154
    "textures/cup/cup_stemstripes1.bmp",
    "textures/cup/cup_stemstripes2.bmp",
    "textures/cup/cup_top.bmp",

    "textures/teapot/teapot_bodycolor.bmp", //158
    "textures/teapot/teapot_top.bmp",

    "textures/candelabra/candelabra_bodycolor.bmp", //160
    "textures/candelabra/candelabra_holder.bmp",
    "textures/candelabra/candelabra_candle.bmp",

    "textures/key/key_bodycolor.bmp", //163
    "textures/key/key_base_left.bmp", //unused
    "textures/key/key_base_right.bmp", //unused
    "textures/key/key_stem_left.bmp",
    "textures/key/key_stem_right.bmp",
    "textures/key/key_thing_left.bmp",
    "textures/key/key_thing_right.bmp",

    "textures/wall/wall00_front.bmp", //170
    "textures/wall/wall00_back.bmp",
    "textures/wall/wall00_left.bmp",
    "textures/wall/wall00_right.bmp",
    "textures/wall/wall00_top.bmp",
    "textures/wall/wall00_bottom.bmp",
    "textures/floor/floor00.bmp", //176

    "textures/wall/wall01_front.bmp", //177
    "textures/wall/wall01_back.bmp",
    "textures/wall/wall01_left.bmp",
    "textures/wall/wall01_right.bmp",
    "textures/wall/wall01_top.bmp",
    "textures/wall/wall01_bottom.bmp",
    "textures/floor/floor01.bmp", //183

    "textures/wall/wall02_front.bmp", //184
    "textures/wall/wall02_back.bmp",
    "textures/wall/wall02_left.bmp",
    "textures/wall/wall02_right.bmp",
    "textures/wall/wall02_top.bmp",
    "textures/wall/wall02_bottom.bmp",
    "textures/floor/floor02.bmp", //190

    "textures/wall/wall03_front.bmp", //191
    "textures/wall/wall03_back.bmp",
    "textures/wall/wall03_left.bmp",
    "textures/wall/wall03_right.bmp",
    "textures/wall/wall03_top.bmp",
    "textures/wall/wall03_bottom.bmp",
    "textures/floor/floor03.bmp", //197

    "textures/wall/wall04_front.bmp", //198
    "textures/wall/wall04_back.bmp",
    "textures/wall/wall04_left.bmp",
    "textures/wall/wall04_right.bmp",
    "textures/wall/wall04_top.bmp",
    "textures/wall/wall04_bottom.bmp",
    "textures/floor/floor04.bmp", //204

    "textures/wall/wall05_front.bmp", //205
    "textures/wall/wall05_back.bmp",
    "textures/wall/wall05_left.bmp",
    "textures/wall/wall05_right.bmp",
    "textures/wall/wall05_top.bmp",
    "textures/wall/wall05_bottom.bmp",
    "textures/floor/floor05.bmp", //211

    "textures/wall/wall06_front.bmp", //212
    "textures/wall/wall06_back.bmp",
    "textures/wall/wall06_left.bmp",
    "textures/wall/wall06_right.bmp",
    "textures/wall/wall06_top.bmp",
    "textures/wall/wall06_bottom.bmp",
    "textures/floor/floor06.bmp", //218

    "textures/floor/floor_player_spawn.bmp", //219
    "textures/floor/floor_player_exit.bmp", //220
    "textures/floor/floor_mob_spawn.bmp", //221

    "textures/pedestal/pedestal_front.bmp", //222
    "textures/pedestal/pedestal_back.bmp",
    "textures/pedestal/pedestal_left.bmp",
    "textures/pedestal/pedestal_right.bmp",
    "textures/pedestal/pedestal_top.bmp",
    "textures/pedestal/pedestal_bodycolor.bmp",

    "textures/door/door00_front.bmp", //228
    "textures/door/door00_back.bmp",
    "textures/door/door00_left.bmp",
    "textures/door/door00_right.bmp",
    "textures/door/door00_top.bmp",
    "textures/door/door00_bottom.bmp",

    "textures/door/door01_front.bmp", //234
    "textures/door/door01_back.bmp",
    "textures/door/door01_left.bmp",
    "textures/door/door01_right.bmp",
    "textures/door/door01_top.bmp",
    "textures/door/door01_bottom.bmp",

    "textures/door/door02_front.bmp", //240
    "textures/door/door02_back.bmp",
    "textures/door/door02_left.bmp",
    "textures/door/door02_right.bmp",
    "textures/door/door02_top.bmp",
    "textures/door/door02_bottom.bmp",

    "textures/key/key_base_left_red.bmp", //246
    "textures/key/key_base_right_red.bmp",
    "textures/key/key_base_left_green.bmp",
    "textures/key/key_base_right_green.bmp",
    "textures/key/key_base_left_blue.bmp",
    "textures/key/key_base_right_blue.bmp",

    "textures/floor/floor_key_red.bmp", //252
    "textures/floor/floor_key_green.bmp",
    "textures/floor/floor_key_blue.bmp",

    "textures/water/water_01.bmp", //255
    "textures/water/water_02.bmp",
    "textures/water/water_03.bmp",
    "textures/water/water_04.bmp",
    "textures/water/water_05.bmp",
    "textures/water/water_06.bmp",
    "textures/water/water_07.bmp",
    "textures/water/water_08.bmp",
    "textures/water/water_09.bmp",
    "textures/water/water_10.bmp",
    "textures/water/water_11.bmp",
    "textures/water/water_12.bmp",
    "textures/water/water_13.bmp",
    "textures/water/water_14.bmp",
    "textures/water/water_15.bmp",
    "textures/water/water_16.bmp",
    "textures/water/water_17.bmp",
    "textures/water/water_18.bmp",
    "textures/water/water_19.bmp",
    "textures/water/water_20.bmp",
    "textures/water/water_21.bmp",
    "textures/water/water_22.bmp",
    "textures/water/water_23.bmp",
    "textures/water/water_24.bmp",
    "textures/water/water_25.bmp",

    "textures/overlay/ov_reload.bmp", //280
    "textures/overlay/ov_flashbang.bmp",
    "textures/overlay/ov_life.bmp",
    "textures/overlay/ov_flash.bmp",
    "textures/overlay/ov_watch.bmp",
    "textures/overlay/numbers/n0.bmp", //285
    "textures/overlay/numbers/n1.bmp",
    "textures/overlay/numbers/n2.bmp",
    "textures/overlay/numbers/n3.bmp",
    "textures/overlay/numbers/n4.bmp",
    "textures/overlay/numbers/n5.bmp",
    "textures/overlay/numbers/n6.bmp",
    "textures/overlay/numbers/n7.bmp",
    "textures/overlay/numbers/n8.bmp",
    "textures/overlay/numbers/n9.bmp",
    "textures/overlay/ov_black_strip.bmp",

    "textures/menu/menu_00.bmp", //296
    "textures/menu/menu_01.bmp",
    "textures/menu/menu_02.bmp",

    "textures/floor/floor_teleport_charged.bmp", //299
    "textures/floor/floor_teleport_cooldown.bmp",

    "textures/settings/settings_water_1.bmp", //301
    "textures/settings/settings_water_2.bmp",
    "textures/settings/settings_water_3.bmp",
    "textures/settings/settings_water_4.bmp",

    "textures/settings/settings_darkness_1.bmp", //305
    "textures/settings/settings_darkness_2.bmp",
    "textures/settings/settings_darkness_3.bmp",

    "textures/waterwall/water_wall_front.bmp", //308
    "textures/waterwall/water_wall_back_01.bmp",
    "textures/waterwall/water_wall_back_02.bmp",
    "textures/waterwall/water_wall_back_03.bmp",
    "textures/waterwall/water_wall_back_04.bmp",
    "textures/waterwall/water_wall_back_05.bmp",
    "textures/waterwall/water_wall_back_06.bmp",
    "textures/waterwall/water_wall_back_07.bmp",
    "textures/waterwall/water_wall_back_08.bmp",
    "textures/waterwall/water_wall_back_09.bmp",
    "textures/waterwall/water_wall_back_10.bmp",
    "textures/waterwall/water_wall_back_11.bmp",
    "textures/waterwall/water_wall_back_12.bmp",
    "textures/waterwall/water_wall_back_13.bmp",
    "textures/waterwall/water_wall_back_14.bmp",
    "textures/waterwall/water_wall_back_15.bmp",
    "textures/waterwall/water_wall_back_16.bmp",
    "textures/waterwall/water_wall_back_17.bmp",
    "textures/waterwall/water_wall_back_18.bmp",
    "textures/waterwall/water_wall_back_19.bmp",
    "textures/waterwall/water_wall_back_20.bmp",
    "textures/waterwall/water_wall_back_21.bmp",
    "textures/waterwall/water_wall_back_22.bmp",
    "textures/waterwall/water_wall_back_23.bmp",
    "textures/waterwall/water_wall_back_24.bmp",
    "textures/waterwall/water_wall_back_25.bmp",
    "textures/waterwall/water_wall_left.bmp", //334
    "textures/waterwall/water_wall_right.bmp",
    "textures/waterwall/water_wall_top.bmp",
    "textures/waterwall/water_wall_bottom.bmp",
};

void getBitmapImageData(char * pFileName, BMPImage * pImage)
{
    FILE * pFile = NULL;
    unsigned short nNumPlanes;
    unsigned short nNumBPP;
    int i;

    if ((pFile =fopen(pFileName, "rb")) == NULL)
        printf("ERROR: getBitmapImageData - %s notfound.\n", pFileName);

    // Seekforward to width and height info
   fseek(pFile, 18, SEEK_CUR);

    if ((i =fread( & pImage -> width, 4, 1, pFile)) != 1)
        printf("ERROR: getBitmapImageData - Couldn't read widthfrom %s.\n ", pFileName);

    if ((i =fread( & pImage -> height, 4, 1, pFile)) != 1)
        printf("ERROR: getBitmapImageData - Couldn't read heightfrom %s.\n ", pFileName);

    if ((fread( & nNumPlanes, 2, 1, pFile)) != 1)
        printf("ERROR: getBitmapImageData - Couldn't read plane countfrom %s.\n", pFileName);

    if (nNumPlanes != 1)
        printf("ERROR: getBitmapImageData - Plane countfrom %s.\n ", pFileName);

    if ((i =fread( & nNumBPP, 2, 1, pFile)) != 1)
        printf("ERROR: getBitmapImageData - Couldn't read BPPfrom %s.\n ", pFileName);

    if (nNumBPP != 24)
        printf("ERROR: getBitmapImageData - BPPfrom %s.\n ", pFileName);

    // Seekforward to image data
   fseek(pFile, 24, SEEK_CUR);

    // Calculate the image's total size in bytes. Note how we multiply the
    // result of (width * height) by 3. This is becuase a 24 bit color BMP
    //file will give you 3 bytes per pixel.
    int nTotalImagesize = (pImage -> width * pImage -> height) * 3;

    pImage -> data = (char * ) malloc(nTotalImagesize);

    if ((i =fread(pImage -> data, nTotalImagesize, 1, pFile)) != 1)
        printf("ERROR: getBitmapImageData - Couldn't read image datafrom %s.\n ", pFileName);

    // Finally, rearrange BGR to RGB
    char charTemp;
   for (i = 0; i < nTotalImagesize; i += 3) {
        charTemp = pImage -> data[i];
        pImage -> data[i] = pImage -> data[i + 2];
        pImage -> data[i + 2] = charTemp;
    }
}

void loadTextures()
{
    BMPImage textura;

    // set amount of textures and texture vector
    glGenTextures(MAX_NO_TEXTURES, texture_id);

    int i;
   for (i = 0; i < MAX_NO_TEXTURES; i++) {
        getBitmapImageData(filenameArray[i], & textura);
        glBindTexture(GL_TEXTURE_2D, texture_id[i]);
        glTexImage2D(GL_TEXTURE_2D, 0, 3, textura.width, textura.height, 0, GL_RGB, GL_UNSIGNED_BYTE, textura.data);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    }
}

void initTexture()
{
    glEnable(GL_RESCALE_NORMAL);
    glEnable(GL_NORMALIZE);
    glEnable(GL_TEXTURE_2D);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    loadTextures();
}
