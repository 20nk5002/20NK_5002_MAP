#include"DxLib.h"
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
    if( CheckHitKey( KEY_INPUT_RETURN ) ) {
        return false;
    }
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