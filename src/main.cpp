#include <filesystem>

#include "libtcod.hpp"
#include "actor.hpp"
#include "map.hpp"
#include "engine.hpp"


Engine engine;

int main() {
    while ( !TCODConsole::isWindowClosed() ) {
    	engine.update();
    	engine.render();
    	TCODConsole::flush();
    }
    return 0;
}
