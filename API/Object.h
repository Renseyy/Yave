#pragma once

#include <string>
#include <array>

class Shader;
class Model;
class Animation;
class Animator;
class Sound;
class Camera;

// deltaTime global varialibe is required to this part of project - this varialibe should contain time between current and earlier frame
extern float deltaTime;
// also camera object is needed
extern Camera cam;

class Object{
    private:
        Shader* shader;
        Model* model;
        
        //if animated
        Animation* animation;
        Animator* animator; 

        void prepareRender(void);
        void UpdateAnimation(void);

    public:
        std::array <float,3> position;
        std::array <float,4> color;

        bool isAnimated;    //default 0, set to 1 before Init to use shader for animation
        bool noSound;       //default 0, you can set it to 1 if you dont want to reate sound source at Init

        std::string ModelFile;
        std::string AnimationFile;
        std::string SoundFile;
        
        Sound* sound;

        Object(void);   // constructor

        void Init(void);
        void Render(void);
        void UpdateSoundPosition(void);
        void PlaySound(void);
};