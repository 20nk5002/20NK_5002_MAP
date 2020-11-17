#pragma once

class Fade {
private:
    int fade_;

public:
    Fade();
    ~Fade();

    bool fadeplus();
    bool fademinus();
    void draw();
};