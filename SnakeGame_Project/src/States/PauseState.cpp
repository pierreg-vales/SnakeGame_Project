#include "PauseState.h"

//--------------------------------------------------------------
PauseState::PauseState() {
    continueButton.load("continue_button.png");

}   
//--------------------------------------------------------------
PauseState::~PauseState() {

}
//--------------------------------------------------------------
void PauseState::reset() {
    setFinished(false);
    setNextState("");
    return;
}
//--------------------------------------------------------------
void PauseState::update() {

}
//--------------------------------------------------------------
void PauseState::draw() {
        
    ofSetColor(0,0,0);
    ofDrawRectangle(0,0,ofGetWidth(),ofGetHeight());

    ofSetColor(255);
        continueButton.draw(ofGetWidth()/2-105,ofGetHeight()/2,200,200);
    

    }
    
//--------------------------------------------------------------
void PauseState::keyPressed(int key) {}
 

//--------------------------------------------------------------
void PauseState::mousePressed(int x, int y, int button){

ofRectangle continueButtonRect(ofGetWidth()/2-40, ofGetHeight()/2+70, 75, 75);
    if(button==OF_MOUSE_BUTTON_LEFT){
    
        if(continueButtonRect.inside(x, y)) {
        this->setNextState("GameState");
        this->setFinished(true);
        
        return;
        }
    }
}