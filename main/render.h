#pragma once

#include "../global.h"

void YAVE_adjustFPS(float);
void YAVE_renderImgui(void);
void YAVE_renderBackground(void);
void YAVE_prepareRender(Shader *);
void YAVE_execAnimation(Animator *,Shader *);
void YAVE_renderModel(Shader *,Model *);
void YAVE_executeEvents(void);