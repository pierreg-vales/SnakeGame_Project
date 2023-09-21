#pragma once
#include "Entity.h"
#include "ofMain.h"
#include "Snake.h"
#include <string>

class StaticEntity: public Entity{
    private:
        int x;
        int y;
        int type;
        int cellsize;
        Snake* snake;
        ofImage rockImage;
        ofImage treeImage; 
        bool draw;
    public:
        StaticEntity(int x, int y, int cellsize, int type);
        ~StaticEntity();
        void drawObject(Snake* snake);
        void objectSpawner(int x, int y);
        bool checkCrashed(Snake* snake);
        bool setDraw(){
            return !draw;
        }

        void rock(int x, int y);
        void flower(int x, int y);

        int getX(){
            return x;
        }
        int getY(){
            return y;
        }
        int getType(){
            return type;
        }
        int getCellSize(){
            return cellsize;
        }
};