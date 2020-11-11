#pragma once

struct PChip {
    int x, y; //�����Ђ�
    int trim_x, trim_y; //�т�����͈�
    int id; //�`�b�v�΂�
    int solid;
    PChip(); //�R���X�g���N�^
};

struct Player {
    int texture;
    PChip* chips;
    int x, y;
    int walkcount;
    int walkanimate;
    int aim = 0;
    int walking = 0;
    int cnt = 0;
    int iswhere = 0;

    int stagewidth, stageheight;

    Player(); //�R���X�g���N�^
    ~Player(); //�f�X�g���N�^

    bool init();
    void update();
    void draw();
    void destroy();

};