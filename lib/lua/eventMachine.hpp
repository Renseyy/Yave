#include <unordered_map>
#include <vector>
#include <iostream>

#include "../sol/sol.hpp"

using namespace std;
class Event{
    public: 
        string name = "___";
};
class InitEvent : public Event{
    public:
        string name = "init";  
        TextureManager textureManager;
        TextureManager getTextureManager(){
            return this->textureManager;
        }
};
class EventMachine{
    private: 
        sol::state* lua;
        unordered_map<string, vector<sol::function>> eventListeners;
    public:
        EventMachine(sol::state* lua){
            this->lua = lua;
        }
        sol::object addEventListener(string eventName, sol::function callback){
            if(eventListeners.count(eventName) == 0){
                eventListeners.insert(pair<string, vector<sol::function>> (eventName, {}));
            }
            eventListeners.at(eventName).push_back(callback);
            return sol::make_object(*this->lua, callback); 
        }
        bool dispatchEvent(string eventName, InitEvent* event){
            for(auto fun : this->eventListeners[eventName]){
                fun(event);
            }
            return true;
        }
};

void initLuaTypes(sol::state* lua){
    lua->new_usertype<TextureManager>("TextureManager",
	     sol::constructors<TextureManager()>(),
	     "addTexture",
	     &TextureManager::addTexture,
	     "bakeBuffer",
	     &TextureManager::bakeBuffer);
    lua->new_usertype<InitEvent>("InitEvent",
	     sol::constructors<InitEvent()>(),
	     "getTextureManager",
	     &InitEvent::getTextureManager);
}