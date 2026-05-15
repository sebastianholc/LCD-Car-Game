#include<Arduino.h>
#include<LiquidCrystal.h>

/*
    Logika sterowania samochodem zrobiona.
    Cały gracz zamknięty do jednej klasy.
    Zrobiona również klasa od przeszkody.
*/

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int getBtnValue();

class Player {
public:

    String CAR = "DXD";
    bool positionY = 0;

    void Steering() {
        if (getBtnValue() < 150) { positionY = 0; } // UP
        else if (getBtnValue() < 300) { positionY = 1;} // DOWn
    }

    void Write() {
        lcd.setCursor(0,positionY);
        lcd.print(CAR);
    }

};

class Obstacle {
public:
    
    int positionX;
    int positionY;

    String OBSTACLE = "H";

    Obstacle(int posX,int posY) {
        positionX = posX;
        positionY = posY;
    }

    void Write() {
        lcd.setCursor(positionX,positionY);
        lcd.print(OBSTACLE);
    }

    void moveLeft() {
        positionX -= 1;
    }



};

Player car;
Obstacle obstacle(16,0);

void setup() {
  lcd.begin(16, 2);

  
}

void loop() {
  
    car.Steering(); 
    obstacle.moveLeft();
    
    car.Write();
    obstacle.Write();
    
    checkCollision();

    delay(100);
    lcd.clear();
    

}

void checkBtnValues() {
    
    /*
    NOTHING = 1023
    UP = 108
    DOWN = 259
    RIGHT = 0
    LEFT = 420
    SELECT = 667
    */
    
    int buttonOutput = analogRead(A0);
    lcd.print(buttonOutput);
    delay(100);
    lcd.clear();
    
}

int getBtnValue() {
    int buttonOutput = analogRead(A0);
    return buttonOutput;
}

void checkCollision() {
    if (car.positionY == obstacle.positionY && obstacle.positionX == 0) { gameOver(); }
}

void gameOver() {
    lcd.clear();
    lcd.print("GAME OVER!");
    delay(2000);
}