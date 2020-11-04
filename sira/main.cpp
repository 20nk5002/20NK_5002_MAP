#include "DxLib.h"
#include "field.h"

int WINAPI WinMain( HINSTANCE hInsrtance, HINSTANCE hPrevInstance, LPSTR lpcmdLine, int nCmdShow ) {
    ChangeWindowMode( 1 );//�E�B���h�E�\��
    SetGraphMode( 1280, 720, 32 );//��ʉ𑜓x

    if( DxLib_Init() == -1 ) { //DX���C�u�����̏�����
        return 0;
    }
    SetDrawScreen( DX_SCREEN_BACK );//����ʂɕ`��

    Field field;
    if( field.init() == false ) {
        return 0;
    }
    Player sira;
    if( sira.init() == false ) {
        return 0;
    }

    while( ProcessMessage() != -1 ) {

        sira.update();

        ClearDrawScreen(); //��ʂ̏�����

        field.draw();
        sira.draw();

        ScreenFlip(); //����ʂɕ`�悵�����e��\��
    }

    field.destroy();
    sira.destroy();

    DxLib_End(); //�j��

    return 0;
}