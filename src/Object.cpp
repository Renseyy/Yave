#include <Object.h>
#include <version_config.h>

Object::Object(){
    position={0,0,0};
    isAnimated=0;
    noSound=0;
}

void Object::Init(void){
    if(isAnimated){
        shader = new Shader(DIRECT_DIR("shaders/animations/anim_model.vs"), DIRECT_DIR("shaders/animations/anim_model.fs"));
    }else{
        shader = new Shader(DIRECT_DIR("shaders/base.vertex.glsl"),DIRECT_DIR("shaders/base.fragment.glsl"));
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
    }
}

void Object::UpdateSoundPosition(void){
    sound->setPosition(position[0],position[1],position[2]);
}

// Render - renders view and sound
void Object::Render(void){
    //renderView
    prepareRender();
    if(isAnimated){
        UpdateAnimation();
    }

    shader->setBool("Texturing", GL_TRUE);
    shader->setVec4("color", glm::vec4(0.0, 1.0 , 0.0 , 1.0));
	// render the loaded model
	glm::mat4 tmpmodel = glm::mat4(1.0f);
        
	tmpmodel = glm::translate(tmpmodel, position); // translate it down so it's at the center of the scene

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
    view  = cam.GetViewMatrix();
    projection = glm::perspective(glm::radians(45.0f), YAVE_ratio , 0.1f, 3000.0f);
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