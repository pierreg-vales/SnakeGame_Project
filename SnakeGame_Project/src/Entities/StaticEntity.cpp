#include "StaticEntity.h"

StaticEntity::StaticEntity(int x, int y, int cellsize, int type){
    this->x = x;
    this->y = y;
    this->cellsize = cellsize;
    this->type = type;
    rockImage.load("rock.png");
    treeImage.load("tree.png");
}

void StaticEntity::drawObject(Snake* snake){
    if ((this->getX() != snake->getHead()[0] || this->getY() != snake->getHead()[1])){
        if (this->getType() == 1)
            rock(this->getX(), this->getY());
        if (this->getType() == 2){
            flower(this->getX(),this->getY());
        }
    }
    return;
    //draw = true;

}

StaticEntity::~StaticEntity(){}

void StaticEntity::rock(int x, int y){
    ofSetColor(255);
    // ofDrawRectangle(x, y, this->getCellSize()*2,this->getCellSize()*2 );
    rockImage.draw(x, y, this->getCellSize(), this->getCellSize());
    
}

void StaticEntity::flower(int x, int y){
    ofSetColor(255);
    treeImage.draw(x, y, this->getCellSize(), this->getCellSize());
    
}

void StaticEntity::objectSpawner(int x, int y){
    // randomX = ofRandom(ofGetWidth()/64);
    // randomY = ofRandom(ofGetHeight()/36);
    // if (randomX != x || randomY != y){
        // ofSetColor(255);
        // ofDrawRectangle(randomX, randomY, 25, 25);
        // draw = true;
    //}   
}

bool StaticEntity::checkCrashed(Snake* snake){
    if (!snake->getGodMode()){
        if (snake->getHead()[0]==this->getX()/25 && snake->getHead()[1] == this->getY()/25){
            return true; 
        }
    }
    return false;
}