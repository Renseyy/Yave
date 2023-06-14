#define SOL_ALL_SAFETIES_ON 1
#include "./sol/sol.hpp"

namespace Lone{
    sol::state luaState;
}

#include "./eventMachine.hpp"

namespace Lone{
    void initLone(){
        luaState.open_libraries(sol::lib::base, sol::lib::package);
        //? Create new core
        EventMachine machine;
        luaState.set_function("on", &EventMachine::addEventListener, &machine);
        //? Run main.lua
        luaState.script_file("lua/main.lua");
    }
    
}
