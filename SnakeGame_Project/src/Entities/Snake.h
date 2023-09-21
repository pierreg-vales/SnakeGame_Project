#pragma once
#include <vector>

enum Direction {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        NONE
    };

class Snake {

private:
    std::vector<std::vector<int>> body;
    Direction direction;
    int boardSizeWidth, boardSizeHeight; 
    int segmentSize;
    bool crashed;
    bool godMode = false;

public:
    Snake(int segmentSize, int boardSizeW, int boardSizeH);
    ~Snake();

    void pausedSnake();

    void update();
    void draw();
    void changeDirection(Direction d);
    void checkSelfCrash();
    void grow();
    void shrink();
    bool isCrashed() {
        return this->crashed;
    }
    void setCrashed(){
        crashed = !crashed;
    }
    std::vector<int> getHead() {
        return this->body[0];
    }
    std::vector<int> getTail() {
        return this->body[this->body.size() - 1];
    }
    std::vector<std::vector<int>> getBody() {
        return this->body;
    } 
    
    bool getGodMode(){
        return godMode; 
    }
    bool setGodMode(bool x){
        godMode = x;
        return godMode;  
    }

    bool stopped=false;
};
