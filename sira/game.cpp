#include"DxLib.h"
#include "Game.h"

bool Game::init() {
    if( field_.init() == false || player_.init()==false ) {
        return false;
    }

    return true;
}
bool Game::update() {
    field_.update();
    player_.update();
    if( CheckHitKey( KEY_INPUT_RETURN ) ) {
        return false;
    }
    return true;
}
void Game::draw() {
    field_.draw();
    player_.draw();
}
void Game::destroy() {
    field_.destroy();
    player_.destroy();
}