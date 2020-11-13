#pragma once

class Title {
private:
    int texture;

public:
    Title();
    ~Title();

    bool init();
    bool update();
    void draw();
    void destroy();
};