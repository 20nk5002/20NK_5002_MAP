#pragma once

struct PChip {
    int x_, y_; //�����Ђ�
    int trim_x_, trim_y_; //�т�����͈�
    int id_; //�`�b�v�΂�
    int solid_;
    PChip(); //�R���X�g���N�^
};

class Player {
private:
    int texture_;
    PChip* chips_;
    int x_, y_;
    int walk_count_;
    int walk_animate_;
    int aim_ = 0;
    int walking_ = 0;
    int cnt_ = 0;
    int iswhere_ = 0;

    int stage_width_, stage_height_;

public:
    Player(); //�R���X�g���N�^
    ~Player(); //�f�X�g���N�^

    bool init();
    void update();
    void draw();
    void destroy();

};