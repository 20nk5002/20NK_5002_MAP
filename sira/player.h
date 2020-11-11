#pragma once

struct PChip {
    int x, y; //ざっひょ
    int trim_x, trim_y; //びょっが範囲
    int id; //チップばんご
    int solid;
    PChip(); //コンストラクタ
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

    Player(); //コンストラクタ
    ~Player(); //デストラクタ

    bool init();
    void update();
    void draw();
    void destroy();

};