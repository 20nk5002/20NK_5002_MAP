#pragma once

struct Chip {
    int x, y; //ざっひょ
    int trim_x, trim_y; //びょっが範囲
    int id; //チップばんご
    int solid;
    Chip(); //コンストラクタ
};

class Field {
private:
    int texture;//グラフィックハンドル
    Chip* chips;//チップ構造体ポインタ
    int width, height; //縦横に並んでいるチップの個数

    int x, y;
    int walking;
    int iswhere;
    int cnt;
    int aim;

public:
    Field(); //コンストラクタ
    ~Field(); //デストラクタ

    bool init();
    void update();
    void draw();
    void destroy();
};