#pragma once

struct Chip {
    int x_, y_; //�����Ђ�
    int trim_x_, trim_y_; //�т�����͈�
    int id_; //�`�b�v�΂�
    int solid_;
    Chip(); //�R���X�g���N�^
};

class Field {
private:
    int texture_;//�O���t�B�b�N�n���h��
    Chip* chips_;//�`�b�v�\���̃|�C���^
    int width_, height_; //�c���ɕ���ł���`�b�v�̌�

    int x_, y_;
    int walking_;
    int iswhere_;
    int cnt_;
    int aim_;

public:
    Field(); //�R���X�g���N�^
    ~Field(); //�f�X�g���N�^

    bool init();
    void update();
    void draw();
    void destroy();
};