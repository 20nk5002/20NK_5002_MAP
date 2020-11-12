#include "Game.h"

bool Game::init() {
    if( field.init() == false || player.init()==false ) {
        return false;
    }

    return true;
}
bool Game::update() {
    field.update();
    player.update();
    return true;
}
void Game::draw() {
    field.draw();
    player.draw();
}
void Game::destroy() {
    field.destroy();
    player.destroy();
}