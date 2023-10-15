#pragma once

class Animator;
class Shader;
class Model;

void YAVE_adjustFPS(float);
void YAVE_renderImgui(void);
void YAVE_renderBackground(void);
void YAVE_prepareRender(void);
void YAVE_execAnimation(Animator *,Shader *);
void YAVE_renderModel(Shader *,Model *);
void YAVE_executeEvents(void);
bool YAVE_activeWindow(void);