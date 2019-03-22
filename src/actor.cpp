#include "libtcod.hpp"
#include "actor.hpp"

Actor::Actor(int x, int y, int ch, const TCODColor &col, bool is_player) :
    x(x),y(y),ch(ch),col(col), is_player (is_player) {
    // Temp

}

void Actor::render() const {

    TCODConsole::root->setChar(x + offsetx, y + offsety , ch);
    TCODConsole::root->setCharForeground(x + offsetx, y + offsety, col);
}
