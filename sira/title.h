#pragma once

struct Title {
    int texture;

    bool init();
    bool update();
    void draw();
    void destroy();
};