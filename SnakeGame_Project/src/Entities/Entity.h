#pragma once
#include "Snake.h"

class Entity{
    public:
        virtual void drawObject(Snake* snake) = 0;
        virtual void objectSpawner(int x, int y) = 0;
        virtual bool checkCrashed(Snake* snake) = 0;
        
};