#pragma once

#include"field.h"
#include"player.h"

class Game {
private:
    Field field;
    Player player;

public:
    bool init();
    bool update();
    void draw();
    void destroy();
};
