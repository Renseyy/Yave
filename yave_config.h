#pragma once

/*

    This is the general configuration file

*/

// *** CONFIGURATION of engine ***
/*
YAVE_EXTERNAL_SHADER
if set then shaders must be provided in files atached to output project
you should set paths to this files below

if cleared it compiles internal shaders in YAVE
names of these shaders are provided below
*/
#define YAVE_EXTERNAL_SHADERS 0

#if YAVE_EXTERNAL_SHADERS
    #define YAVE_AMODEL_VS DIRECT_DIR("shaders/amodel.vs")
    #define YAVE_AMODEL_FS DIRECT_DIR("shaders/amodel.fs")
    #define YAVE_MODEL_VS DIRECT_DIR("shaders/model.vs")
    #define YAVE_MODEL_FS DIRECT_DIR("shaders/model.fs")
#else
    #define YAVE_AMODEL_VS YAVE_VS_ANIM
    #define YAVE_AMODEL_FS YAVE_FS_ANIM
    #define YAVE_MODEL_VS YAVE_VS
    #define YAVE_MODEL_FS YAVE_FS

    extern const char * YAVE_VS_ANIM;
    extern const char * YAVE_FS_ANIM;
    extern const char * YAVE_VS;
    extern const char * YAVE_FS;
#endif
const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

#define YAVE_x_speed 2.5f //velocity of camera in x axis
#define YAVE_y_speed 2.5f //velocity of camera in y axis
#define YAVE_z_speed 2.5f //velocity of camera in z axis
#define YAVE_rotx_speed 2.5f //velocity of rotation camera in x axis
#define YAVE_roty_speed 2.5f //velocity of rotation camera in y axis
