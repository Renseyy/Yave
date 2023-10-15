/*
HEADER containing API for user

created 10.10.2023
*/

#pragma once

#include "Object.h"     // provide object functions
#include "Camera.h"     // and camera functions
#include "Listener.h"   // lets add audio - Listener
#include "render.h"     // and render functions

extern Camera cam;  // also the global camera object

extern void Yave_Init(void);
extern void Yave_End(void);

extern void Sound_CreateListener(void);
extern void Sound_DeleteListener(void);

//enums
enum YAVE_MODES{
    YAVE_MODE_NORMAL = 0, //tryb normalny, bez menu
    YAVE_MODE_MOUSE, //brak możliwości poruszania, widoczna myszka
    YAVE_MODE_BACKPACK //"plecak" widoczna myszka, możesz się poruszać
};
