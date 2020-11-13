#pragma once

#include"field.h"
#include"player.h"

class Game {
private:
    Field field_;
    Player player_;

public:
    bool init();
    bool update();
    void draw();
    void destroy();
};
