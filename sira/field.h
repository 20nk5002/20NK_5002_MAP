#pragma once

struct Chip {
    int x, y; //ざっひょ
    int trim_x, trim_y; //びょっが範囲
    int id; //チップばんご
    int solid;
    Chip(); //コンストラクタ
};

struct Field {
    int texture;//グラフィックハンドル
    Chip* chips;//チップ構造体ポインタ
    int width, height; //縦横に並んでいるチップの個数

    Field(); //コンストラクタ
    ~Field(); //デストラクタ

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

    Player(); //コンストラクタ
    ~Player(); //デストラクタ

    bool init();
    void update();
    void draw();
    void destroy();

};