#pragma once

struct Chip {
    int x_, y_; //ざっひょ
    int trim_x_, trim_y_; //びょっが範囲
    int id_; //チップばんご
    int solid_;
    Chip(); //コンストラクタ
};

class Field {
private:
    int texture_;//グラフィックハンドル
    Chip* chips_;//チップ構造体ポインタ
    int width_, height_; //縦横に並んでいるチップの個数

    int x_, y_;
    int walking_;
    int iswhere_;
    int cnt_;
    int aim_;

public:
    Field(); //コンストラクタ
    ~Field(); //デストラクタ

    bool init();
    void update();
    void draw();
    void destroy();
};