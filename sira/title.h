#pragma once

class Title {
private:
    int texture_;

public:
    Title();
    ~Title();

    bool init();
    bool update();
    void draw();
    void destroy();
};