//0 Bad
//1 Good
#include <Servo.h>
Servo servo;
int lightvalue;
int serialinput;
boolean continous = false ;
int posG = 80; //degree of good chilli
int posB = 135; //degree of bad chilli
int ldr = A0;


void Check() { //check chilli pass yet
  lightvalue = analogRead(ldr);
  //Serial.println("kjhgf");
  if (lightvalue < 650) { //have chilli                calibrate
    if (continous == false) {
      continous = true;
    }
  }
  else {
    if (continous == true) { // don't have chilli
      continous = false;
      Serial.println(2);
    }
  }
}


void Servocontrol() {
  if (Serial.available() > 0) {
    serialinput = Serial.parseInt();
    //Serial.println(serialinput);
  if (serialinput == 0) {
    //Serial.print("dogood ");
    servo.write(posB);
    delay(1);
  }
  else if (serialinput == 1) {
    //Serial.print("dobad ");
    servo.write(posG);
    delay(1);
  }
}

}

void setup() {
  Serial.begin(9600);
  servo.attach(9);
  pinMode(ldr, INPUT);
  servo.write(posG);
  delay(500);
  servo.write(posB);
  delay(500);
  continous = false;
}

void loop() {
  Servocontrol();
  delay(1);
  Check();
  //Serial.println("outcheck");
  delay(1);
  
  
}
