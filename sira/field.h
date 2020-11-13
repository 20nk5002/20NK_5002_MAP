#pragma once

struct Chip {
    int x, y; //�����Ђ�
    int trim_x, trim_y; //�т�����͈�
    int id; //�`�b�v�΂�
    int solid;
    Chip(); //�R���X�g���N�^
};

class Field {
private:
    int texture;//�O���t�B�b�N�n���h��
    Chip* chips;//�`�b�v�\���̃|�C���^
    int width, height; //�c���ɕ���ł���`�b�v�̌�

    int x, y;
    int walking;
    int iswhere;
    int cnt;
    int aim;

public:
    Field(); //�R���X�g���N�^
    ~Field(); //�f�X�g���N�^

    bool init();
    void update();
    void draw();
    void destroy();
};