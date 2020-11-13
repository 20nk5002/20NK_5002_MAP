#include<cstdio>
#include"DxLib.h"
#include"player.h"


PChip::PChip() {
    x_ = y_ = 0;
    trim_x_ = trim_y_ = 0;
    id_ = 0;
    solid_ = 0;
}




Player::Player() {
    texture_ = 0;
    walk_animate_ = aim_ = 0;
    walk_count_ = 0;
    cnt_ = 0;
    x_ = y_ = 0;

    walking_ = 0;
    chips_ = NULL;
}

Player::~Player() {
    destroy();
}

bool Player::init() {
    if( (texture_ = LoadGraph( "sira.png" )) == -1 ) {
        return false;
    }

    FILE* fp = fopen( "alice.fmf", "rb" );
    if( fp == NULL ) {
        return false;
    }

    fseek( fp, 8L, SEEK_SET );
    fread( &stage_width_, sizeof( int ), 1, fp );
    fread( &stage_height_, sizeof( int ), 1, fp );

    chips_ = new PChip[ stage_width_ * stage_height_ ];
    if( chips_ == NULL ) {
        return false;
    }

    iswhere_ = 490;

    x_ = (iswhere_ % 20) * 64;
    y_ = ((iswhere_ / 20) - 1) * 64;

    fseek( fp, 20L, SEEK_SET );

    for( int i = 0; i < stage_width_ * stage_height_; i++ ) {
        fread( &chips_[ i ].id_, sizeof( char ), 1, fp );

        chips_[ i ].trim_x_ = chips_[ i ].id_ % 12 * 64;
        chips_[ i ].trim_y_ = chips_[ i ].id_ / 12 * 64;

        chips_[ i ].x_ = 64 * (i % stage_width_);
        chips_[ i ].y_ = 64 * (i / stage_width_);

        if( chips_[ i ].id_ == 4 || chips_[ i ].id_ == 5 || chips_[ i ].id_ == 10 || chips_[ i ].id_ == 11 ) {
            chips_[ i ].solid_ = 0;
        }
        else {
            chips_[ i ].solid_ = 1;
        }
    }


    return true;
}

void Player::update() {

    if( walking_ == 1 ) {
       /* if( aim_ == 0 ) {
            //y_ += 4;
        }
        else if( aim_ == 1 ) {
            //x_ -= 4;
        }
        else if( aim_ == 2 ) {
            //y_ -= 4;
        }
        else if( aim_ == 3 ) {
            //x_ += 4;
        }
        else if( aim_ == 4 ) {
            //x_ -= 4; y_ -= 4;
        }
        else if( aim_ == 5 ) {
            //x_ -= 4; y_ += 4;
        }
        else if( aim_ == 6 ) {
            //x_ += 4; y_ += 4;
        }
        else if( aim_ == 7 ) {
            //x_ += 4; y_ -= 4;
        }*/
        cnt_ += 4; 
        if( cnt_ >= 64 ) {
            cnt_ = 0; walking_ = 0;
        }

    }

    if( walking_ == 0 ) {
        if( CheckHitKey( KEY_INPUT_UP ) && CheckHitKey( KEY_INPUT_LEFT ) && iswhere_ % stage_width_ != 0 ) {
            if( chips_[ iswhere_ - (stage_width_ + 1) ].solid_ == 0 ) {
                walking_ = 1;
                iswhere_ -= stage_width_ + 1;
            }
            aim_ = 4;
        }
        else if( CheckHitKey( KEY_INPUT_DOWN ) && CheckHitKey( KEY_INPUT_LEFT ) && iswhere_ % stage_width_ != 0 ) {
            if( chips_[ iswhere_ + (stage_width_ - 1) ].solid_ == 0 ) {
                walking_ = 1;
                iswhere_ += stage_width_ - 1;
            }
            aim_ = 5;
        }
        else if( CheckHitKey( KEY_INPUT_DOWN ) && CheckHitKey( KEY_INPUT_RIGHT ) && iswhere_ % stage_width_ != (stage_width_ - 1) ) {
            if( chips_[ iswhere_ + (stage_width_ + 1) ].solid_ == 0 ) {
                walking_ = 1;
                iswhere_ += stage_width_ + 1;
            }
            aim_ = 6;
        }
        else if( CheckHitKey( KEY_INPUT_UP ) && CheckHitKey( KEY_INPUT_RIGHT ) && iswhere_ % stage_width_ != (stage_width_ - 1) ) {
            if( chips_[ iswhere_ - (stage_width_ - 1) ].solid_ == 0 ) {
                walking_ = 1;
                iswhere_ -= stage_width_ - 1;
            }
            aim_ = 7;
        }
        else if( CheckHitKey( KEY_INPUT_DOWN ) ) {
            if( chips_[ iswhere_ + stage_width_ ].solid_ == 0 ) {
                walking_ = 1;
                iswhere_ += stage_width_;
            }
            aim_ = 0;
        }
        else if( CheckHitKey( KEY_INPUT_LEFT ) && iswhere_ % stage_width_ != 0 ) {
            if( chips_[ iswhere_ - 1 ].solid_ == 0 ) {
                walking_ = 1;
                iswhere_ -= 1;
            }
            aim_ = 1;
        }
        else if( CheckHitKey( KEY_INPUT_UP ) ) {
            if( chips_[ iswhere_ - stage_width_ ].solid_ == 0 ) {
                walking_ = 1;
                iswhere_ -= stage_width_;
            }
            aim_ = 2;
        }
        else if( CheckHitKey( KEY_INPUT_RIGHT ) && iswhere_ % stage_width_ != (stage_width_ - 1) ) {
            if( chips_[ iswhere_ + 1 ].solid_ == 0 ) {
                walking_ = 1;
                iswhere_ += 1;
            }
            aim_ = 3;
        }
    }

   walk_count_++;
    if( walk_count_ == 20 ) {
        walk_animate_ = 1;
    }
    if( walk_count_ == 40 ) {
        walk_animate_ = 0;
    }
    if( walk_count_ == 60 ) {
        walk_animate_ = 2;
    }if( walk_count_ == 80 ) {
        walk_animate_ = 0;
        walk_count_ = 0;
    }

}

void Player::draw() {
    DrawRectGraph( 640, 320, 64 * (walk_animate_)+(192 * (aim_ >= 4)), 96 * (aim_ % 4), 64, 96, texture_, 1, 0, 0 );
    //DrawFormatString( (iswhere_ % stage_width_) * 64, (iswhere_ / stage_width_) * 64, 0x00FFFF, "Å°" );
}

void Player::destroy() {
    DeleteGraph( texture_ );
}