#pragma once

struct PChip {
    int x_, y_; //ざっひょ
    int trim_x_, trim_y_; //びょっが範囲
    int id_; //チップばんご
    int solid_;
    PChip(); //コンストラクタ
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
    Player(); //コンストラクタ
    ~Player(); //デストラクタ

    bool init();
    void update();
    void draw();
    void destroy();

};