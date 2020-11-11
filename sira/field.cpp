#include<cstdio>
#include "DxLib.h"
#include "field.h"

Chip::Chip() {
    x = y = 0;
    trim_x = trim_y = 0;
    id = 0;
    solid = 0;
}

Field::Field() {
    texture = 0;
    chips = NULL;

    x = y = 0;
    walking = aim = 0;
    cnt = 0;
}

Field::~Field() {
    destroy();
}

bool Field::init() {

    iswhere = 490;

    if( (texture = LoadGraph( "mapchip0.png" )) == -1 ) {
        return false;
    }
    FILE* fp = fopen( "alice.fmf", "rb" );
    if( fp == NULL ) {
        return false;
    }

    fseek( fp, 8L, SEEK_SET );
    fread( &width, sizeof( int ), 1, fp );
    fread( &height, sizeof( int ), 1, fp );

    chips = new Chip[ width * height ];
    if( chips == NULL ) {
        return false;
    }

    fseek( fp, 20L, SEEK_SET );

    for( int i = 0; i < width * height; i++ ) {
        fread( &chips[ i ].id, sizeof( char ), 1, fp );

        chips[ i ].trim_x = chips[ i ].id % 12 * 64;
        chips[ i ].trim_y = chips[ i ].id / 12 * 64;

        chips[ i ].x = 64 * (i % width);
        chips[ i ].y = 64 * (i / width);

        if( chips[ i ].id == 4 || chips[ i ].id == 5 || chips[ i ].id == 10 || chips[ i ].id == 11 ) {
            chips[ i ].solid = 0;
        }
        else {
            chips[ i ].solid = 1;
        }
    }

    return true;
}

void Field::update() {

    if( walking == 1 ) {
        if( aim == 0 ) {
            y += 4;
        }
        else if( aim == 1 ) {
            x -= 4;
        }
        else if( aim == 2 ) {
            y -= 4;
        }
        else if( aim == 3 ) {
            x += 4;
        }
        else if( aim == 4 ) {
            x -= 4; y -= 4;
        }
        else if( aim == 5 ) {
            x -= 4; y += 4;
        }
        else if( aim == 6 ) {
            x += 4; y += 4;
        }
        else if( aim == 7 ) {
            x += 4; y -= 4;
        }
        cnt += 4;
        if( cnt >= 64 ) {
            cnt = 0; walking = 0;
        }

    }

    if( walking == 0 ) {
        if( CheckHitKey( KEY_INPUT_UP ) && CheckHitKey( KEY_INPUT_LEFT ) && iswhere % width != 0 ) {
            if( chips[ iswhere - (width + 1) ].solid == 0 ) {
                walking = 1;
                iswhere -= width + 1;
            }
            aim = 4;
        }
        else if( CheckHitKey( KEY_INPUT_DOWN ) && CheckHitKey( KEY_INPUT_LEFT ) && iswhere % width != 0 ) {
            if( chips[ iswhere + (width - 1) ].solid == 0 ) {
                walking = 1;
                iswhere += width - 1;
            }
            aim = 5;
        }
        else if( CheckHitKey( KEY_INPUT_DOWN ) && CheckHitKey( KEY_INPUT_RIGHT ) && iswhere % width != (width - 1) ) {
            if( chips[ iswhere + (width + 1) ].solid == 0 ) {
                walking = 1;
                iswhere += width + 1;
            }
            aim = 6;
        }
        else if( CheckHitKey( KEY_INPUT_UP ) && CheckHitKey( KEY_INPUT_RIGHT ) && iswhere % width != (width - 1) ) {
            if( chips[ iswhere - (width - 1) ].solid == 0 ) {
                walking = 1;
                iswhere -= width - 1;
            }
            aim = 7;
        }
        else if( CheckHitKey( KEY_INPUT_DOWN ) ) {
            if( chips[ iswhere + width ].solid == 0 ) {
                walking = 1;
                iswhere += width;
            }
            aim = 0;
        }
        else if( CheckHitKey( KEY_INPUT_LEFT ) && iswhere % width != 0 ) {
            if( chips[ iswhere - 1 ].solid == 0 ) {
                walking = 1;
                iswhere -= 1;
            }
            aim = 1;
        }
        else if( CheckHitKey( KEY_INPUT_UP ) ) {
            if( chips[ iswhere - width ].solid == 0 ) {
                walking = 1;
                iswhere -= width;
            }
            aim = 2;
        }
        else if( CheckHitKey( KEY_INPUT_RIGHT ) && iswhere % width != (width - 1) ) {
            if( chips[ iswhere + 1 ].solid == 0 ) {
                walking = 1;
                iswhere += 1;
            }
            aim = 3;
        }
    }
}

void Field::draw() {
    for( int i = 0; i < width * height; i++ ) {
        DrawRectGraph( chips[ i ].x - x, chips[ i ].y - y, chips[ i ].trim_x, chips[ i ].trim_y, 64, 64, texture, false );
       //DrawFormatString( chips[ i ].x, chips[ i ].y, chips[ i ].solid ? 0xFFFF00 : 0xFFFFFF, "%d", i );
    }
}

void Field::destroy(){
    if( texture != 0 ) {
        DeleteGraph( texture );
        texture = 0;
    }
    delete[] chips;
    chips = NULL;
}