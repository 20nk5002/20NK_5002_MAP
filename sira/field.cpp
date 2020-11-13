#include<cstdio>
#include "DxLib.h"
#include "field.h"

Chip::Chip() {
    x_ = y_ = 0;
    trim_x_ = trim_y_ = 0;
    id_ = 0;
    solid_ = 0;
}

Field::Field() {
    texture_ = 0;
    chips_ = NULL;

    x_ = y_ = 0;
    walking_= aim_ = 0;
    cnt_ = 0;
}

Field::~Field() {
    destroy();
}

bool Field::init() {

    iswhere_ = 490;

    if( (texture_ = LoadGraph( "mapchip0.png" )) == -1 ) {
        return false;
    }
    FILE* fp = fopen( "alice.fmf", "rb" );
    if( fp == NULL ) {
        return false;
    }

    fseek( fp, 8L, SEEK_SET );
    fread( &width_, sizeof( int ), 1, fp );
    fread( &height_, sizeof( int ), 1, fp );

    chips_ = new Chip[ width_ * height_ ];
    if( chips_ == NULL ) {
        return false;
    }

    fseek( fp, 20L, SEEK_SET );

    for( int i = 0; i < width_ * height_; i++ ) {
        fread( &chips_[ i ].id_, sizeof( char ), 1, fp );

        chips_[ i ].trim_x_ = chips_[ i ].id_ % 12 * 64;
        chips_[ i ].trim_y_ = chips_[ i ].id_ / 12 * 64;

        chips_[ i ].x_ = 64 * (i % width_);
        chips_[ i ].y_ = 64 * (i / width_);

        if( chips_[ i ].id_ == 4 || chips_[ i ].id_ == 5 || chips_[ i ].id_ == 10 || chips_[ i ].id_ == 11 ) {
            chips_[ i ].solid_ = 0;
        }
        else {
            chips_[ i ].solid_ = 1;
        }
    }

    return true;
}

void Field::update() {

    if( walking_ == 1 ) {
        if( aim_ == 0 ) {
            y_ += 4;
        }
        else if( aim_ == 1 ) {
            x_ -= 4;
        }
        else if( aim_ == 2 ) {
            y_ -= 4;
        }
        else if( aim_ == 3 ) {
            x_ += 4;
        }
        else if( aim_ == 4 ) {
            x_ -= 4; y_ -= 4;
        }
        else if( aim_ == 5 ) {
            x_ -= 4; y_ += 4;
        }
        else if( aim_ == 6 ) {
            x_ += 4; y_ += 4;
        }
        else if( aim_ == 7 ) {
            x_ += 4; y_ -= 4;
        }
        cnt_ += 4;
        if( cnt_ >= 64 ) {
            cnt_ = 0; walking_ = 0;
        }

    }

    if( walking_ == 0 ) {
        if( CheckHitKey( KEY_INPUT_UP ) && CheckHitKey( KEY_INPUT_LEFT ) && iswhere_ % width_ != 0 ) {
            if( chips_[ iswhere_ - (width_ + 1) ].solid_ == 0 ) {
                walking_ = 1;
                iswhere_ -= width_ + 1;
            }
            aim_ = 4;
        }
        else if( CheckHitKey( KEY_INPUT_DOWN ) && CheckHitKey( KEY_INPUT_LEFT ) && iswhere_ % width_ != 0 ) {
            if( chips_[ iswhere_ + (width_ - 1) ].solid_ == 0 ) {
                walking_ = 1;
                iswhere_ += width_ - 1;
            }
            aim_ = 5;
        }
        else if( CheckHitKey( KEY_INPUT_DOWN ) && CheckHitKey( KEY_INPUT_RIGHT ) && iswhere_ % width_ != (width_ - 1) ) {
            if( chips_[ iswhere_ + (width_ + 1) ].solid_ == 0 ) {
                walking_ = 1;
                iswhere_ += width_ + 1;
            }
            aim_ = 6;
        }
        else if( CheckHitKey( KEY_INPUT_UP ) && CheckHitKey( KEY_INPUT_RIGHT ) && iswhere_ % width_ != (width_ - 1) ) {
            if( chips_[ iswhere_ - (width_ - 1) ].solid_ == 0 ) {
                walking_ = 1;
                iswhere_ -= width_ - 1;
            }
            aim_ = 7;
        }
        else if( CheckHitKey( KEY_INPUT_DOWN ) ) {
            if( chips_[ iswhere_ + width_ ].solid_ == 0 ) {
                walking_ = 1;
                iswhere_ += width_;
            }
            aim_ = 0;
        }
        else if( CheckHitKey( KEY_INPUT_LEFT ) && iswhere_ % width_ != 0 ) {
            if( chips_[ iswhere_ - 1 ].solid_ == 0 ) {
                walking_ = 1;
                iswhere_ -= 1;
            }
            aim_ = 1;
        }
        else if( CheckHitKey( KEY_INPUT_UP ) ) {
            if( chips_[ iswhere_ - width_ ].solid_ == 0 ) {
                walking_ = 1;
                iswhere_ -= width_;
            }
            aim_ = 2;
        }
        else if( CheckHitKey( KEY_INPUT_RIGHT ) && iswhere_ % width_ != (width_ - 1) ) {
            if( chips_[ iswhere_ + 1 ].solid_ == 0 ) {
                walking_ = 1;
                iswhere_ += 1;
            }
            aim_ = 3;
        }
    }
}

void Field::draw() {
    for( int i = 0; i < width_ * height_; i++ ) {
        DrawRectGraph( chips_[ i ].x_ - x_, chips_[ i ].y_ - y_, chips_[ i ].trim_x_, chips_[ i ].trim_y_, 64, 64, texture_, false );
       //DrawFormatString( chips_[ i ].x_, chips_[ i ].y_, chips_[ i ].solid_ ? 0x_FFFF00 : 0x_FFFFFF, "%d", i );
    }
}

void Field::destroy(){
    if( texture_ != 0 ) {
        DeleteGraph( texture_ );
        texture_ = 0;
    }
    delete[] chips_;
    chips_ = NULL;
}