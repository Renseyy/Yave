#include <Listener.h>
#include <Camera.h>
#include <Sound.h>

extern Camera cam;      //global varialibe

void UpdateListener(void){
    float x=cam.Position[0];
        float y=cam.Position[1];
        float z=cam.Position[2];

        float * orientation;
        orientation=new float[6];

        for(int v=0;v<3;v++){
            orientation[v]=cam.Up[v];
            orientation[v+3]=-cam.Front[v];
        }
        
    float o_y=cam.Position[1];
    float o_z=cam.Position[2];
    Sound_SetListenerPosition(x,y,z);
    Sound_SetListenerOrientation(orientation);
}