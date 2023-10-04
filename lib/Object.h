#pragma once

#include <global.h>
#include "Shader.h"
#include "Model.h"
#include "Animation.h"
#include "Animator.h"
#include "Sound.h"


// deltaTime global varialibe is required to this part of project - this varialibe should contain time between current and earlier frame
extern float deltaTime;
// also camera object is needed
extern Camera cam;

class Object{
    private:
        void prepareRender(void);
        void UpdateAnimation(void);
    public:
        glm::vec3 position;

        bool isAnimated;    //default 0, set to 1 before Init to use shader for animation
        bool noSound;       //default 0, you can set it to 1 if you dont want to reate sound source at Init

        std::string ModelFile;
        std::string AnimationFile;
        std::string SoundFile;
        
        Shader* shader;
        Model* model;
        
        //if animated
        Animation* animation;
        Animator* animator; 

        Sound* sound;

        Object(void);

        void Init(void);
        void Render(void);
        void UpdateSoundPosition(void);
};