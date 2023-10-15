#pragma once

/*

    This is the general configuration file

*/

// *** CONFIGURATION of engine ***

#define YAVE_AMODEL_VS DIRECT_DIR("shaders/amodel.vs")
#define YAVE_AMODEL_FS DIRECT_DIR("shaders/amodel.fs")
#define YAVE_MODEL_VS DIRECT_DIR("shaders/model.vs")
#define YAVE_MODEL_FS DIRECT_DIR("shaders/model.fs")

const unsigned int WIDTH = 800;
const unsigned int HEIGHT = 600;

#define YAVE_x_speed 2.5f //velocity of camera in x axis
#define YAVE_y_speed 2.5f //velocity of camera in y axis
#define YAVE_z_speed 2.5f //velocity of camera in z axis
#define YAVE_rotx_speed 2.5f //velocity of rotation camera in x axis
#define YAVE_roty_speed 2.5f //velocity of rotation camera in y axis
