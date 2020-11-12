#include "DxLib.h"
#include "title.h"

bool Title::init() {
    if( !(texture = LoadGraph( "messon.png" )) ) {
        return false;
    }
    return true;
}
bool Title::update() {
    return true;
}
void Title::draw() {
    DrawGraph( 0, 0, texture, 0 );
}

void Title::destroy() {
    DeleteGraph( texture );
}