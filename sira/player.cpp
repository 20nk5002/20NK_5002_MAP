#include<cstdio>
#include"DxLib.h"
#include"player.h"


PChip::PChip() {
    x = y = 0;
    trim_x = trim_y = 0;
    id = 0;
    solid = 0;
}




Player::Player() {
    texture = 0;
    walkanimate = aim = 0;
    walkcount = 0;
    cnt = 0;
    x = y = 0;

    walking = 0;
    chips = NULL;
}

Player::~Player() {
    destroy();
}

bool Player::init() {
    if( (texture = LoadGraph( "sira.png" )) == -1 ) {
        return false;
    }

    FILE* fp = fopen( "alice.fmf", "rb" );
    if( fp == NULL ) {
        return false;
    }

    fseek( fp, 8L, SEEK_SET );
    fread( &stagewidth, sizeof( int ), 1, fp );
    fread( &stageheight, sizeof( int ), 1, fp );

    chips = new PChip[ stagewidth * stageheight ];
    if( chips == NULL ) {
        return false;
    }

    iswhere = 490;

    x = (iswhere % 20) * 64;
    y = ((iswhere / 20) - 1) * 64;

    fseek( fp, 20L, SEEK_SET );

    for( int i = 0; i < stagewidth * stageheight; i++ ) {
        fread( &chips[ i ].id, sizeof( char ), 1, fp );

        chips[ i ].trim_x = chips[ i ].id % 12 * 64;
        chips[ i ].trim_y = chips[ i ].id / 12 * 64;

        chips[ i ].x = 64 * (i % stagewidth);
        chips[ i ].y = 64 * (i / stagewidth);

        if( chips[ i ].id == 4 || chips[ i ].id == 5 || chips[ i ].id == 10 || chips[ i ].id == 11 ) {
            chips[ i ].solid = 0;
        }
        else {
            chips[ i ].solid = 1;
        }
    }


    return true;
}

void Player::update() {

    if( walking == 1 ) {
        if( aim == 0 ) {
            //y += 4;
        }
        else if( aim == 1 ) {
            //x -= 4;
        }
        else if( aim == 2 ) {
            //y -= 4;
        }
        else if( aim == 3 ) {
            //x += 4;
        }
        else if( aim == 4 ) {
            //x -= 4; y -= 4;
        }
        else if( aim == 5 ) {
            //x -= 4; y += 4;
        }
        else if( aim == 6 ) {
            //x += 4; y += 4;
        }
        else if( aim == 7 ) {
            //x += 4; y -= 4;
        }
        cnt += 4; 
        if( cnt >= 64 ) {
            cnt = 0; walking = 0;
        }

    }

    if( walking == 0 ) {
        if( CheckHitKey( KEY_INPUT_UP ) && CheckHitKey( KEY_INPUT_LEFT ) && iswhere % stagewidth != 0 ) {
            if( chips[ iswhere - (stagewidth + 1) ].solid == 0 ) {
                walking = 1;
                iswhere -= stagewidth + 1;
            }
            aim = 4;
        }
        else if( CheckHitKey( KEY_INPUT_DOWN ) && CheckHitKey( KEY_INPUT_LEFT ) && iswhere % stagewidth != 0 ) {
            if( chips[ iswhere + (stagewidth - 1) ].solid == 0 ) {
                walking = 1;
                iswhere += stagewidth - 1;
            }
            aim = 5;
        }
        else if( CheckHitKey( KEY_INPUT_DOWN ) && CheckHitKey( KEY_INPUT_RIGHT ) && iswhere % stagewidth != (stagewidth - 1) ) {
            if( chips[ iswhere + (stagewidth + 1) ].solid == 0 ) {
                walking = 1;
                iswhere += stagewidth + 1;
            }
            aim = 6;
        }
        else if( CheckHitKey( KEY_INPUT_UP ) && CheckHitKey( KEY_INPUT_RIGHT ) && iswhere % stagewidth != (stagewidth - 1) ) {
            if( chips[ iswhere - (stagewidth - 1) ].solid == 0 ) {
                walking = 1;
                iswhere -= stagewidth - 1;
            }
            aim = 7;
        }
        else if( CheckHitKey( KEY_INPUT_DOWN ) ) {
            if( chips[ iswhere + stagewidth ].solid == 0 ) {
                walking = 1;
                iswhere += stagewidth;
            }
            aim = 0;
        }
        else if( CheckHitKey( KEY_INPUT_LEFT ) && iswhere % stagewidth != 0 ) {
            if( chips[ iswhere - 1 ].solid == 0 ) {
                walking = 1;
                iswhere -= 1;
            }
            aim = 1;
        }
        else if( CheckHitKey( KEY_INPUT_UP ) ) {
            if( chips[ iswhere - stagewidth ].solid == 0 ) {
                walking = 1;
                iswhere -= stagewidth;
            }
            aim = 2;
        }
        else if( CheckHitKey( KEY_INPUT_RIGHT ) && iswhere % stagewidth != (stagewidth - 1) ) {
            if( chips[ iswhere + 1 ].solid == 0 ) {
                walking = 1;
                iswhere += 1;
            }
            aim = 3;
        }
    }

   walkcount++;
    if( walkcount == 20 ) {
        walkanimate = 1;
    }
    if( walkcount == 40 ) {
        walkanimate = 0;
    }
    if( walkcount == 60 ) {
        walkanimate = 2;
    }if( walkcount == 80 ) {
        walkanimate = 0;
        walkcount = 0;
    }

}

void Player::draw() {
    DrawRectGraph( 640, 320, 64 * (walkanimate)+(192 * (aim >= 4)), 96 * (aim % 4), 64, 96, texture, 1, 0, 0 );
    //DrawFormatString( (iswhere % stagewidth) * 64, (iswhere / stagewidth) * 64, 0x00FFFF, "Å°" );
}

void Player::destroy() {
    DeleteGraph( texture );
}