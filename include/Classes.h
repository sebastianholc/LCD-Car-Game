#pragma once
#include<Arduino.h>
#include<LiquidCrystal.h>

class Player {
private:
    const char* CAR = "DXD";
    int positionY = 0;

public:    

    void Steering(int btnValue) {
        if (btnValue < 150) { positionY = 0; } // UP
        else if (btnValue < 300) { positionY = 1;} // DOWN
    }

    void Write(LiquidCrystal& display) {
        display.setCursor(0,positionY);
        display.print(CAR);
    }

    int getPositionY() { return positionY; }

};

class Obstacle {
private:    
    const char* OBSTACLE = "H";
    int positionX;
    int positionY;

public:

    Obstacle(int posX,int posY) {
        positionX = posX;
        positionY = posY;
    }

    void Write(LiquidCrystal& lcd) {
        lcd.setCursor(positionX,positionY);
        lcd.print(OBSTACLE);
    }

    void moveLeft() {
        positionX -= 1;
        if (positionX < 0 ) { positionX = 16; }
    }

    int getPositionX() { return positionX; }
    int getPositionY() { return positionY; }



};