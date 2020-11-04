#pragma once

struct Chip {
    int x, y; //�����Ђ�
    int trim_x, trim_y; //�т�����͈�
    int id; //�`�b�v�΂�
    int solid;
    Chip(); //�R���X�g���N�^
};

struct Field {
    int texture;//�O���t�B�b�N�n���h��
    Chip* chips;//�`�b�v�\���̃|�C���^
    int width, height; //�c���ɕ���ł���`�b�v�̌�

    Field(); //�R���X�g���N�^
    ~Field(); //�f�X�g���N�^

    bool init();
    void update();
    void draw();
    void destroy();
};

struct Player {
    int texture;
    int x, y;
    int walkanimate;
    int aim = 0;
    int walking = 0;
    int cnt = 0;

    Player(); //�R���X�g���N�^
    ~Player(); //�f�X�g���N�^

    bool init();
    void update();
    void draw();
    void destroy();

};