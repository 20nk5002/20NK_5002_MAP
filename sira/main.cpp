#include "DxLib.h"
#include "game.h"
#include "title.h"

//�V�[���Ǘ�
enum {
    TITLE_INIT,TITLE_UPDATE,GAME_INIT,GAME_UPDATE
};

int WINAPI WinMain( HINSTANCE hInsrtance, HINSTANCE hPrevInstance, LPSTR lpcmdLine, int nCmdShow ) {
    ChangeWindowMode( 1 );//�E�B���h�E�\��
    SetGraphMode( 1280, 720, 32 );//��ʉ𑜓x

    SetMainWindowText( "Game" );

    SetWaitVSyncFlag( false );

    if( DxLib_Init() == -1 ) { //DX���C�u�����̏�����
        return 0;
    }
    SetDrawScreen( DX_SCREEN_BACK );//����ʂɕ`��

    Title title;
    Game game;
    if( game.init() == false ) {
        return 0;
    }


    int fps_counter = 0;
    LONGLONG fps_timer = 0;

    int work = TITLE_INIT;

    while( ProcessMessage() != -1 ) {

        LONGLONG now_time = GetNowHiPerformanceCount();
        ++fps_counter;
        if( now_time - fps_timer > 1000000 ) {
            char name[ _MAX_PATH ];
            sprintf( name, "Game:%d", fps_counter );
            SetMainWindowText( name );

            fps_counter = 0;
            fps_timer = now_time;
        }

        switch( work ) {
        case TITLE_INIT:
            if( title.init() == false ) {
                return 0;
            }
            work = TITLE_UPDATE;
            break;
        case TITLE_UPDATE:
            if( title.update() == false ) {
                title.destroy();
                work = GAME_INIT;
                continue;
            }
            break;
        case GAME_INIT:
            if( game.init() == false ) {
                return 0;
            }
            work = GAME_UPDATE;
        case GAME_UPDATE:
            if( game.update() == false ) {
                game.destroy();
                work = TITLE_INIT;
                continue;
            }
            break;
        }

        ClearDrawScreen(); //��ʂ̏�����

        switch( work ) {
        case TITLE_UPDATE:
            title.draw();
            break;
        case GAME_UPDATE:
            game.draw();
            break;
        }

        ScreenFlip(); //����ʂɕ`�悵�����e��\��

        WaitTimer( 16 );
    }

    game.destroy();

    DxLib_End(); //�j��

    return 0;
}