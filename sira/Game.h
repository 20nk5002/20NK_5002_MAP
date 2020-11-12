#pragma once

#include"field.h"
#include"player.h"

struct Game {
    Field field;
    Player player;

    bool init();
    bool update();
    void draw();
    void destroy();
};
