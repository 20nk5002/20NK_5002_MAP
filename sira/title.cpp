#include "DxLib.h"
#include "title.h"
#include"error.h"

Title::Title() {
    texture_ = 0;
}
Title::~Title() {
    destroy();
}

bool Title::init() {
    if( !(texture_ = LoadGraph( "messon.png" )) ) {
        Error::showDialog( "\"messon.png\" is not found." );
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
    DrawGraph( 0, 0, texture_, 0 );
}

void Title::destroy() {
    DeleteGraph( texture_ );
    texture_ = 0;
}