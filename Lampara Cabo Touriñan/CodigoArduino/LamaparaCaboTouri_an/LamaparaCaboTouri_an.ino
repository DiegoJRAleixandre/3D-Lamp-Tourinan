
#include <Servo.h>

Servo myServo;

int dirServo=0;

int const potPin = A3;
int const lightPin = A2;
int const faroPin = A1;

int potVal=0;
int lightVal=0;
int faroVal=0;
int angle = 90;

const int greenLEDPin=2;
const int blueLEDPin=3;
const int redLEDPin=4;

int redValue=0;
int greenValue=0;
int blueValue=0;


void setup() {
  // put your setup code here, to run once:
  myServo.attach(9);

  Serial.begin(9600);

  pinMode(greenLEDPin,OUTPUT);
  pinMode(blueLEDPin,OUTPUT);
  pinMode(redLEDPin,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:

  //Movimiento continuo del servo siempre que tenga corriente

    //debug();
    
    lightVal = analogRead(lightPin);
    delay(5);
    faroVal = analogRead(faroPin);
    delay(5);
    if (lightVal>1020){
      potVal = analogRead(potPin);
      selectColor(potVal);
      setColor();
    }else if (faroVal>1020){
      potVal = analogRead(potPin);
      selectColor(potVal);
      setColor();
      moveServo();
      delay(15);
 
    } else {
      todoApagado();
      delay(5);
    }

}

void todoApagado(void){
  analogWrite(redLEDPin,0);
  analogWrite(greenLEDPin,0);
  analogWrite(blueLEDPin,0);
  myServo.write(90);
}

void selectColor(int Pot){
  extern int redValue;
  extern int greenValue;
  extern int blueValue;

  if (Pot<127){
    redValue=255;
    greenValue=255;
    blueValue=255;
  }else if (Pot>127 && Pot<254){
    redValue=148;
    greenValue=0;
    blueValue=211;
  }else if (Pot>254 && Pot<381){
    redValue=75;
    greenValue=0;
    blueValue=130;
  }else if (Pot>381 && Pot<508){
    redValue=0;
    greenValue=0;
    blueValue=255;
  }else if (Pot>508 && Pot<635){
    redValue=0;
    greenValue=255;
    blueValue=0;
  }else if (Pot>635 && Pot<762){
    redValue=255;
    greenValue=255;
    blueValue=0;
  }else if (Pot>762 && Pot<889){
    redValue=255;
    greenValue=127;
    blueValue=0;
  } else {
    redValue=255;
    greenValue=0;
    blueValue=0;
  }
  
}
void setColor(void){
  extern int redValue;
  extern int greenValue;
  extern int blueValue;
  
  analogWrite(redLEDPin,redValue);
  analogWrite(greenLEDPin,greenValue);
  analogWrite(blueLEDPin,blueValue);
  
}

void moveServo(void){
  extern int dirServo;
  extern int angle;
  if (dirServo==0){
    if (angle<180){
    myServo.write(angle);
    angle ++;
    }else{
      dirServo=1;
    }
  } else {
    if (angle>15){
      myServo.write(angle);
      angle --;
    } else {
      dirServo=0;
    }
  }
}

void debug(void){
  Serial.print("Valor del potenciometro: ");
  Serial.print(potVal);
  Serial.print(" \t Luz solo: ");
  Serial.print(lightVal);
  Serial.print(" \t Faro: ");
  Serial.print(faroVal);
  Serial.print(" \t Angle: ");
  Serial.print(angle);
  Serial.print(" \n ");
}

