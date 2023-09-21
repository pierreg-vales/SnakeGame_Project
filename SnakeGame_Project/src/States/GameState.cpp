#include "GameState.h"

//--------------------------------------------------------------
GameState::GameState() {
    foodSpawned = false;
    cellSize = 25;
    boardSizeWidth = 64;
    boardSizeHeight = 36;
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
    scoreText.load("gameFont.ttf", 15);
    for (int i = 0; i<ofRandom(20, 30); i++){
        obstacleX = ofRandom(1,boardSizeWidth-1);
        obstacleY = ofRandom(1, boardSizeHeight-1);
        obstacleType = ofRandom(1, 3);
        obstacles.push_back(new StaticEntity(obstacleX*25, obstacleY*25, cellSize, obstacleType));
        
    }
    
    powerupText.load("gameFont.ttf", 15);
    powerupON = false; 
    speedOn = false;
    godMode = false;
    powerup = "";
    fps = 0;
    score = 0;

    for (int rowsIT = 0; rowsIT <= boardSizeWidth; rowsIT++){
        for (int columns = 0; columns <= boardSizeHeight; columns++){
            rows.push_back(0);
        }
        map.push_back(rows);
        rows.clear();
    }


    
}
//--------------------------------------------------------------
GameState::~GameState() {
    delete snake;
}
//--------------------------------------------------------------
void GameState::reset() {
    delete snake;
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
    foodSpawned = false;
    setFinished(false);
    setNextState("");
    speedOn = false;
    betterApple=false;
    powerup = "";
    fps = 0;
    score = 0;

    decay = ofGetFrameRate() * 10;  
    red = 255;
    blue = 0;
    green = 0;
}
//--------------------------------------------------------------
void GameState::update() {
    
    

    if(snake->isCrashed()) {
        this->setNextState("LoseState");
        this->setFinished(true);
        return;
    }
    
    
    

    if(snake->getHead()[0] == currentFoodX && snake->getHead()[1] == currentFoodY) {
        snake->grow();
        foodSpawned = false;
        score += 10;
    }
    foodSpawner();

    if (speedOn){
        fps = 5;
        powerup = "";
        if (ofGetElapsedTimef() - timer >= 15){
            speedOn = false;
        }
    }
    else {fps = 10;}
    if(ofGetFrameNum() % fps == 0) {
        snake->update();
        for (StaticEntity* obs : obstacles){
            if (obs->checkCrashed(snake)){
                this->setNextState("LoseState");
                this->setFinished(true);
                return;
            }
        }
    }

    if (godMode){
        if (ofGetElapsedTimef()-timer <= 10){
            snake->setGodMode(true);
        } else {
            snake->setGodMode(false);
            godMode = false;
            powerup = "";
        } 
    }
    
    if (score == 60 && speedStop){
        powerup = " SPEEDON!";
        powerupON = false;
        decay = ofGetFrameRate() * 30;  
        red = 255;
        blue = 0;
        green = 0; 
    }
    else if(score == 110 && betterAppleStop){
        powerup=" BETTERAPPLE!";
          
         
    }
    else if(score==160 && godModeStop){
        powerup=" GODMODE!";
    }

    
    if (decay == 0){
        foodSpawned = false;
        decay = ofGetFrameRate() * 30;  
        red = 255;
        blue = 0;
        green = 0;
    }
    if (!powerupON){
        decay--;
    }
    if (ofGetFrameNum()%4  == 0){
            red -= 0.3;
            blue += 0.3;
            green += 0.3;
    }

    vector<vector<int>> body = snake->getBody();
    for (int bodyIT = 0; bodyIT < body.size(); bodyIT++){
        for (int rowsIT = 0; rowsIT<map.size();rowsIT++){
            for (int columns = 0; columns < map[rowsIT].size(); columns++){
                if (body[bodyIT][0] == columns && body[bodyIT][1]==rowsIT){
                    map[rowsIT][columns] = 1;
                    break; 
                } else { map[rowsIT][columns] = 0;}
            }
        }
    }

}
//--------------------------------------------------------------
void GameState::draw() {
    drawBoardGrid();
    snake->draw();
    for (StaticEntity* obs : obstacles){
        obs->drawObject(snake);
    }
    ofSetColor(red,blue,green);
    drawFood();
    ofSetColor(255,0,0);
    scoreText.drawString("Score:" + to_string(score), ofGetWidth()/2 - 45, 25);
    powerupText.drawString("PowerUP" + powerup, 25, 25);
    ofSetColor(255);
    // for (int rowsIT = 0; rowsIT<map.size();rowsIT++){
    //     for (int columns = 0; columns < map[rowsIT].size(); columns++){
    //         ofDrawBitmapString(to_string(map[rowsIT][columns]), rowsIT*25, columns*25);
    //     }
    // }
    
}
//--------------------------------------------------------------
void GameState::keyPressed(int key) {

    if(key != OF_KEY_LEFT && key != OF_KEY_RIGHT && key != OF_KEY_UP && key != OF_KEY_DOWN && key !='u' && key != 'a' && key !='p' && key !='b') { return; }

    switch(key) {
        case OF_KEY_LEFT:
            snake->changeDirection(LEFT);
            break;
        case OF_KEY_RIGHT:
            snake->changeDirection(RIGHT);
            break;
        case OF_KEY_UP:
            snake->changeDirection(UP);
            break;
        case OF_KEY_DOWN:
            snake->changeDirection(DOWN);
            break;
        //undo case
        case 'u':
            if(snake->getBody().size()>2){
                snake->shrink();
            }
            break;
        case 'a':
            score+=10;
            break;
        case 'p':
            this->setNextState("PauseState");
            this->setFinished(true);
            return;
            break;
        case 'b':
            if(powerup!=""){
                if(powerup==" SPEEDON!"){
                    speedOn=true;
                    timer=ofGetElapsedTimef();
                    speedStop = false; 
                    break;
                
            }
            else if(powerup==" BETTERAPPLE!"){
                snake->grow();
                snake->grow();
                powerup="";
                betterAppleStop = false;
            }
            else if(powerup==" GODMODE!"){
                godMode = true;
                timer = ofGetElapsedTimef();
                godModeStop = false; 
            }
            powerup="";
        } 
        break; 
    }
}
//--------------------------------------------------------------
void GameState::foodSpawner() {
    if(!foodSpawned) {
        bool isInSnakeBody;
        do {
            isInSnakeBody = false;
            currentFoodX = ofRandom(1, boardSizeWidth-1);
            currentFoodY = ofRandom(1, boardSizeHeight-1);
            for(unsigned int i = 0; i < snake->getBody().size(); i++) {
                if(currentFoodX == snake->getBody()[i][0] and currentFoodY == snake->getBody()[i][1]) {
                    isInSnakeBody = true;
                }
            }
        } while(isInSnakeBody);
        foodSpawned = true;
    }
}
//--------------------------------------------------------------
void GameState::drawFood() {
   
    if(foodSpawned && score!=50 && score!=100 && score!=150) {
             ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
    }
    else if(foodSpawned && score==50){
         ofSetColor(ofColor::yellow);
        ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
        speedStop = true;

    }
    else if(foodSpawned && score==100){
         ofSetColor(ofColor::orange);
        ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
        betterAppleStop = true;
}
 else if(foodSpawned && score==150){
         ofSetColor(ofColor::pink);
        ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
        godModeStop = true;
 }
}

//--------------------------------------------------------------
void GameState::drawStartScreen() {
    ofSetColor(ofColor::black);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());
    ofSetColor(ofColor::white);
    string text = "Press any arrow key to start.";
    ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-11);
    return;
}
//--------------------------------------------------------------

//--------------------------------------------------------------
void GameState::mousePressed(int x, int y, int button){

ofRectangle continueButtonRect(ofGetWidth()/2-40, ofGetHeight()/2+70, 75, 75);
    if(button==OF_MOUSE_BUTTON_LEFT){
    
        if(continueButtonRect.inside(x, y)) {
          paused=false;
        }
    }
}






//--------------------------------------------------------------
void GameState::drawBoardGrid() {
    
    ofDrawGrid(25, 64, false, false, false, true);
    
    // ofSetColor(ofColor::white);
    // for(int i = 0; i <= boardSize; i++) {
    //     ofDrawLine(i*cellSize, 0, i*cellSize, ofGetHeight());
    //     ofDrawLine(0, i*cellSize, ofGetWidth(), i*cellSize);
    // }
}
//--------------------------------------------------------------

