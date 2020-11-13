#include "DxLib.h"
#include "title.h"

Title::Title() {
    texture = 0;
}
Title::~Title() {
    destroy();
}

bool Title::init() {
    if( !(texture = LoadGraph( "messon.png" )) ) {
        return false;
    }
    return true;
}
bool Title::update() {
    if( CheckHitKey( KEY_INPUT_SPACE ) ) {
        return false;
    }
    return true;
}
void Title::draw() {
    DrawGraph( 0, 0, texture, 0 );
}

void Title::destroy() {
    DeleteGraph( texture );
    texture = 0;
}