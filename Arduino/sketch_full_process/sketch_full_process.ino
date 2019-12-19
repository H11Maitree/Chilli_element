//0 Bad
//1 Good
#include <Servo.h>
Servo servo;
int lightvalue;
int serialinput;
boolean continous = false ;
int posG = 30; //degree of good chilli
int posB = 120; //degree of bad chilli
int ldr = A0;

unsigned long time; // queue
int indexfront_ti = 0;
int indexback_ti = 0;
int indexfront_co = 0;
int indexback_co = 0;
unsigned long queuetime[20];
boolean queuecomand[20];

void addti() {
  // 6000 mean 6 seconds
  queuetime[indexback_ti] = millis() + 6000;
  indexback_ti++;
  if (indexback_ti == 20) {
    indexback_ti = 0;
  }
}
void addco(boolean boo) {
  queuecomand[indexback_co] = boo;
  indexback_co++;
  if (indexback_co == 20) {
    indexback_co = 0;
  }
}
void popti() {
  queuetime[indexfront_ti] = 0;
  indexfront_ti++;
  if (indexfront_ti == 20) {
    indexfront_ti = 0;
  }
}
void popco() {
  queuecomand[indexfront_co] = 0;
  indexfront_co++;
  if (indexfront_co == 20) {
    indexfront_co = 0;
  }
}
int ittimetodothefront() {
  if (indexfront_ti != indexback_ti ) {
    if (queuetime[indexfront_ti] <= millis()) {
      boolean commandcell = queuecomand[indexfront_co];
      popti();
      popco();
      if (commandcell) {
        //1 good
        return 1;
      }
      else {
        //0 bad
        return 0;
      }
    }
    else {
      return 2;
    }
  }
  else {
    //2 mean not yet
    return 2;
  }
}


void Check() { //check chilli pass yet
  lightvalue = analogRead(ldr);
  //Serial.println("kjhgf");
  if (lightvalue < 359) { //have chilli
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

void Recieve() { //recieve 0 or 1 //serial communication
  if (Serial.available() > 0) {
    serialinput = Serial.parseInt();
    //Serial.println(serialinput);
  }
  if (serialinput == 0) {
    //servo.write(posG);
    //delay(100);
    addti();
    addco(false);
  }
  else if (serialinput == 1) {
    addti();
    addco(true);
  }
}
void Servocontrol() {
  int isnow = ittimetodothefront();
  if (isnow == 0) {
    //bad chilie
    servo.write(posB);
    delay(100);
  }
  if (isnow == 1){
    //good chilie
    servo.write(posG);
    delay(100);
  }

}

void setup() {
  Serial.begin(9600);
  servo.attach(9);
  pinMode(ldr, INPUT);
  servo.write(0);
  delay(500);
  servo.write(180);
  delay(500);
  continous = false;
}

void loop() {
  Check();
  //Serial.println("outcheck");
  delay(1);
  Recieve();
  delay(1);
  Servocontrol();
  delay(1);
}
