#include <Servo.h>

Servo base;
Servo armBack;
Servo armFront;
Servo claw;
const int pingPin = 12;

const int s0 = 8;
const int s1 = 9;
const int s2 = 10;
const int s3 = 11;
const int led = 4;
const int sensorOut = 7;
int red = 0;
int blue = 0;
int green = 0;
int clearFreq = 0;
int pos = 0;

void setup() {
  pinMode(s0, OUTPUT);
  pinMode(s1, OUTPUT);
  pinMode(s2, OUTPUT);
  pinMode(s3, OUTPUT);
  pinMode(led, OUTPUT);
  pinMode(sensorOut, INPUT);
  base.attach(0);
  claw.attach(2);
  base.write(0);
}

void loop() {
  // b -> blue
  // B -> black
  // r -> red
  // g -> green
  /*base.write(180);
  delay(1600);
  blockSearch();*/
  
  moveBase('B');
  moveBase('g');


}

int distanceCm() {
 int duration, cm;
 pinMode(pingPin, OUTPUT);
 digitalWrite(pingPin, LOW);
 delayMicroseconds(2);
 digitalWrite(pingPin, HIGH);
 delayMicroseconds(5);
 digitalWrite(pingPin, LOW); 
 duration = pulseIn(pingPin, HIGH);
 cm = duration / 29 / 2;
 Serial.print(cm);
 Serial.print("cm");
 Serial.println();
 delay(100);
 return cm;
}

void moveBase(char posit) {
  if (posit == 'B') {
    for (int i = pos; i <= 180; i++) {
      base.write(i);
      delay(15);
    }
    pos = 180;
    delay(1000);
  } else if (posit == 'g') {
      if (pos >= 135) {
        for (int i = pos; i >= 135; i--) {
          base.write(i);
          delay(15);
        }
      } else {
        for (int i = pos; i <= 135; i++) {
          base.write(i);
          delay(15);
        }
      }
    pos = 105;
    delay(1000);
  } else if (posit == 'b') {
      if (pos >= 80) {
        for (int i = pos; i >= 80; i--) {
          base.write(i);
          delay(15);
        }
    } else {
        for (int i = pos; i <= 80; i++) {
          base.write(i);
          delay(15);
        }
      }
    pos = 80;
    delay(1000);
  } else if (posit == 'r') {
      if (pos >= 35) {
        for (int i = pos; i >= 35; i--) {
          base.write(i);
          delay(15);
        }
      } else {
        for (int i = pos; i <= 35; i++) {
          base.write(i);
          delay(15);
        }
      }
    pos = 35;
    delay(1000);
  }
}

void moveClaw() {
  claw.write(0);
  delay(1000);
  //claw.write(180);
  //delay(1000);
}

char colour() {
  digitalWrite(s0, LOW);
  digitalWrite(s1, HIGH);
  digitalWrite(led, HIGH);
  
  delay(250);
  
  //reading red:
  digitalWrite(s2, LOW);
  digitalWrite(s3,LOW);
  red = pulseIn(sensorOut, LOW);
  delay(100);
  
  //reading green:
  digitalWrite(s2, HIGH);
  digitalWrite(s3, HIGH);
  green = pulseIn(sensorOut, LOW);
  delay(100);
  
  //reading blue:
  digitalWrite(s2, LOW);
  digitalWrite(s3, HIGH);
  blue = pulseIn(sensorOut, LOW);
  
  if (blue < red && blue < green) {
    Serial.println("Blue");
    return 'b';
  }
  
  if (red < blue && red < green) {
    Serial.println("Red");
    return 'r';    
  }
  
  if (green < blue && green < red) {
     Serial.println("Green");
    return 'g'; 
  }
  
  //change condition once black is working
  if (1 == 0) {
    Serial.println("Black");
    return('B'); 
  }
  return -1;
}

void retract() {
  
}

void unretract() {
  
}

//moves base until finds obstacle, then stops
void blockSearch() {
  for (int i = 135; i >= 0; i--) {
    if (distanceCm() <= 10) {
      return;
    }
    base.write(i);
    pos = i;
    delay(45);
  }
}
