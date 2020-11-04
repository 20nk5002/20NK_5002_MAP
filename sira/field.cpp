#include<cstdio>
#include "DxLib.h"
#include "field.h"

#define CHECK32 if(cnt==32){walkanimate=1;} 
#define CHECK64 cnt+=4; if(cnt>=64){cnt=0; walking=0; walkanimate=0;}

Chip::Chip() {
    x = y = 0;
    trim_x = trim_y = 0;
    id = 0;
}

Field::Field() {
    texture = 0;
    chips = NULL;
}

Field::~Field() {
    destroy();
}

bool Field::init() {

    if( (texture = LoadGraph( "mapchip0.png" )) == -1 ) {
        return false;
    }
    FILE* fp = fopen( "field.fmf", "rb" );
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

}

void Field::draw() {
    for( int i = 0; i < width * height; i++ ) {
        DrawRectGraph( chips[ i ].x, chips[ i ].y, chips[ i ].trim_x, chips[ i ].trim_y, 64, 64, texture, false );
        if( chips[ i ].solid == 1 ) {
            DrawFormatString( chips[ i ].x, chips[ i ].y, 0xFFFFFF, "¡");
        }
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

Player::Player() {
    walkanimate = aim = 0;

    x = y = 128;

    walking = 0;
}

Player::~Player() {
    destroy();
}

bool Player::init(){
    if( (texture = LoadGraph( "sira.png" )) == -1 ) {
        return false;
    }
    return true;
}

void Player::update() {

    if( walking == 1 ) {
        if( aim == 0 ) {
            y += 4;
            CHECK64
            CHECK32
        }
        else if( aim == 1 ) {
            x -= 4;
            CHECK64
            CHECK32
        }
        else if( aim == 2 ) {
            y -= 4;
            CHECK64
            CHECK32
        }
        else if( aim == 3 ) {
            x += 4;
            CHECK64
            CHECK32
            }
    }

    if( walking == 0 ) {
        if( CheckHitKey( KEY_INPUT_DOWN ) ) {
            walking = 1;
            aim = 0;
        }
        else if( CheckHitKey( KEY_INPUT_LEFT ) ) {
            walking = 1;
            aim = 1;
        }
        else if( CheckHitKey( KEY_INPUT_UP ) ) {
            walking = 1;
            aim = 2;
        }
        else if( CheckHitKey( KEY_INPUT_RIGHT ) ) {
            walking = 1;
            aim = 3;
        }
    }
}

void Player::draw() {
    DrawRectGraph( x, y, 64 * (walking + walkanimate), 96 * aim, 64, 96, texture, 1, 0, 0 );
}

void Player::destroy() {
    DeleteGraph( texture );
}