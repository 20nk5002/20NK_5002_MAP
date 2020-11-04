#include "DxLib.h"
#include "field.h"

int WINAPI WinMain( HINSTANCE hInsrtance, HINSTANCE hPrevInstance, LPSTR lpcmdLine, int nCmdShow ) {
    ChangeWindowMode( 1 );//ウィンドウ表示
    SetGraphMode( 1280, 720, 32 );//画面解像度

    if( DxLib_Init() == -1 ) { //DXライブラリの初期化
        return 0;
    }
    SetDrawScreen( DX_SCREEN_BACK );//裏画面に描画

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

        ClearDrawScreen(); //画面の初期化

        field.draw();
        sira.draw();

        ScreenFlip(); //裏画面に描画した内容を表示
    }

    field.destroy();
    sira.destroy();

    DxLib_End(); //破棄

    return 0;
}