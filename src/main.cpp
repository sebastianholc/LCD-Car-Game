#include<Arduino.h>
#include<LiquidCrystal.h>

/*
    LAST CHANGES:
    delay() in main loop changed into millis()
*/

/*
    TO DO:
    join separate obstacles into one list
*/

LiquidCrystal lcd(8, 9, 4, 5, 6, 7);

int getBtnValue();


// CLASSES
class Player {
public:

    String CAR = "DXD";
    bool positionY = 0;

    void Steering() {
        if (getBtnValue() < 150) { positionY = 0; } // UP
        else if (getBtnValue() < 300) { positionY = 1;} // DOWN
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
        if (positionX < 0 ) { positionX = 16; }
    }



};


// OBJECTS
Player car;
Obstacle obstacle(16,0);
Obstacle obstacle2(8,1);

void checkCollision(Obstacle& obst);

void setup() {
  lcd.begin(16, 2);  
}


unsigned long previousMillis = 0;
const long interval = 100;

void loop() {

    unsigned long currentMillis = millis();
  
    if (currentMillis - previousMillis > 100) {

        previousMillis = currentMillis;

        lcd.clear();

        car.Steering(); 
        obstacle.moveLeft();
        obstacle2.moveLeft();
        
        checkCollision(obstacle);
        checkCollision(obstacle2);

        car.Write();
        obstacle.Write();
        obstacle2.Write();
        
    }
    

}

// BUTTONS
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

// OTHER
void checkCollision(Obstacle& obst) {
    if (car.positionY == obst.positionY && obst.positionX == 0) { gameOver(); }
}

void gameOver() {
    lcd.clear();
    lcd.print("GAME OVER!");
    delay(2000);
}