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
        DrawFormatString( chips[ i ].x, chips[ i ].y, chips[ i ].solid ? 0xFFFF00 : 0xFFFFFF, "%d", i );
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