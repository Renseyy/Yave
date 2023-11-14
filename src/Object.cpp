#include <Object.h>

//dependencies
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp> //for casting

//config
#include <yave_config.h>
#include <version_config.h>

//classes
#include <Shader.h>
#include <Model.h>
#include <Camera.h>
#include <Animation.h>
#include <Animator.h>
#include <Sound.h>

#include <yave.h> //API configurable things

extern float YAVE_ratio; //global varialibe saying about ratio between width and height

glm::mat4 float4x4_to_mat4(std::array <std::array <float,4>,4> matrix){
    glm::mat4 tmptab;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            tmptab[i][j]=matrix[i][j];
        }
    }
    return tmptab;
}

Object::Object(){
    position={0,0,0};
    color={0,0,0,1.0f};
    isAnimated=0;
    noSound=0;
}

void Object::Init(void){
    if(isAnimated){
        shader = new Shader(YAVE_AMODEL_VS, YAVE_AMODEL_FS);
    }else{
        shader = new Shader(YAVE_MODEL_VS, YAVE_MODEL_FS);
    }
    model = new Model(ModelFile);

    if(isAnimated){
	    animation = new Animation(AnimationFile,model);
        animator = new Animator(animation);
    }

    if(!noSound){
        sound = new Sound();
        sound->Open(SoundFile.c_str());
        sound->CreateSource();
        UpdateSoundPosition();
    }
}

void Object::UpdateSoundPosition(void){
    sound->setPosition(position[0],position[1],position[2]);
}

void Object::PlaySound(void){
    sound->Play();
}

// Render - renders view and sound
void Object::Render(void){
    //renderView
    prepareRender();
    if(isAnimated){
        UpdateAnimation();
    }

    shader->setBool("Texturing", GL_FALSE);         // texturing TBD i believe **KK
    shader->setVec4("color",  glm::make_vec4(&color[0]) );
	// render the loaded model
	glm::mat4 tmpmodel = glm::mat4(1.0f);
        
	tmpmodel = glm::translate(tmpmodel, glm::make_vec3(&position[0])); // translate it down so it's at the center of the scene

	//model = glm::scale(model, glm::vec3(.5f, .5f, .5f));	// it's a bit too big for our scene, so scale it down
	shader->setMat4("model", tmpmodel);
	model->Draw(*shader);

    //render Sound
    if(!noSound){
    UpdateSoundPosition();
    sound->Update();
    }
}


void Object::prepareRender(void){
    shader->use();
    glm::mat4 view  = float4x4_to_mat4(cam.GetViewMatrix());
    glm::mat4 projection = glm::perspective(glm::radians(45.0f), YAVE_ratio , 0.1f, 3000.0f);
    unsigned int viewLoc = glGetUniformLocation(shader->ID,"view");
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
    shader->setMat4("projection", projection);
    shader->setMat4("view", view);
}

void Object::UpdateAnimation(void){
    animator->UpdateAnimation(deltaTime);
    std::vector<glm::mat4> transforms = animator->GetFinalBoneMatrices();
	for (int i = 0; i < transforms.size(); ++i)
	shader->setMat4("finalBonesMatrices[" + std::to_string(i) + "]", transforms[i]);
}