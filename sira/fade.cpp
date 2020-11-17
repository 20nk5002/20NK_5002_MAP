#include"DxLib.h"
#include"fade.h"

Fade::Fade() {
    fade_ = 0;
}

Fade::~Fade() {

}

bool Fade::fadeplus() {
    fade_ += 4;
    if( fade_ >= 256 ) {
        return true;
    }
    return false;
}

bool Fade::fademinus() {
    fade_ -= 4;
    if( fade_ <= 0 ) {
        return true;
    }
    return false;
}

void Fade::draw() {
    SetDrawBlendMode( DX_BLENDMODE_ALPHA, fade_ );
    DrawBox( 0, 0, 1280, 720, 0xFFFFFF, 1 );
    SetDrawBlendMode( DX_BLENDMODE_NOBLEND, 0 );
}