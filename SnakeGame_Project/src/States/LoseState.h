#pragma once

#include "State.h"
#include "ofMain.h"
#include "Snake.h"
#include "ofTrueTypeFont.h"


class LoseState : public State {

    public:
    LoseState();
    ~LoseState();
    void reset();
    void update();
    void draw();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button){}
    ofTrueTypeFont score; 
    Snake* snake;

};