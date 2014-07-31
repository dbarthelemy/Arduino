#include <NewPing.h>

const int controlLeftMotorEN2 = 2;
const int controlLeftMotorEN1 = 3;
const int enableLeftMotor = 9;
const int controlRightMotorEN3 = 4;
const int controlRightMotorEN4 = 5;
const int enableRightMotor = 10;

int leftMotorEnabled = 0;
int leftMotorSpeed = 0;
int leftMotorDirection = 0;
int rightMotorEnabled = 0;
int rightMotorSpeed = 0;
int rightMotorDirection = 0;
int duration = 0;
int testState = 0;

#define kMaxSpeed 255
#define kMedSpeed 180
#define TRIGGER_PIN  12
#define ECHO_PIN     11
#define MAX_DISTANCE 200
 
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

void setup() {
  pinMode(controlLeftMotorEN1, OUTPUT);
  pinMode(controlLeftMotorEN2, OUTPUT);
  pinMode(enableLeftMotor, OUTPUT);
  digitalWrite(enableLeftMotor, LOW);
  
  pinMode(controlRightMotorEN3, OUTPUT);
  pinMode(controlRightMotorEN4, OUTPUT);
  pinMode(enableRightMotor, OUTPUT);
  digitalWrite(enableRightMotor, LOW);
}

void loop() {
  if (duration == 0) {
    /*
     *  Motor testing
     */
    switch(testState) {
      case 0:
        stop();
        duration = 500;
        testState = 1;
        break;
      case 1:
        turnRight();
        duration = 800;
        testState = 2;
        break;
      case 2:
        stop();
        duration = 500;
        testState = 3;
        break;
      case 3:
        goForward();
        duration = 5000;
        testState = 0;
        break;
      default:    
        testState = 0;
    }
    
    /*
     *  Motor control
     */
    if(leftMotorDirection == 0) {
      digitalWrite(controlLeftMotorEN1, HIGH);
      digitalWrite(controlLeftMotorEN2, LOW);
    }
    else {
      digitalWrite(controlLeftMotorEN1, LOW);
      digitalWrite(controlLeftMotorEN2, HIGH);
    }
    
    if(leftMotorEnabled == 1) {
      analogWrite(enableLeftMotor, leftMotorSpeed);
    }
    else {
      analogWrite(enableLeftMotor, 0);
    }
  
    if(rightMotorDirection == 0) {
      digitalWrite(controlRightMotorEN3, HIGH);
      digitalWrite(controlRightMotorEN4, LOW);
    }
    else {
      digitalWrite(controlRightMotorEN3, LOW);
      digitalWrite(controlRightMotorEN4, HIGH);
    }
    
    if(rightMotorEnabled == 1) {
      analogWrite(enableRightMotor, rightMotorSpeed);
    }
    else {
      analogWrite(enableRightMotor, 0);
    }
  }
  else if (testState == 0) {
    // Check if any object is detected
    int distance = sonar.ping_cm();
    if (distance <= 40) {
      duration = 0;
    }
    else {
      duration -= 100;
    }
  }
  else {
      duration -= 100;
  }
  delay(100);
}

void stop() {
  leftMotorEnabled = 0;
  leftMotorSpeed = 0;
  leftMotorDirection = 1;
  rightMotorEnabled = 0;
  rightMotorSpeed = 0;
  rightMotorDirection = 1;  
}

void turnRight() {
  leftMotorEnabled = 1;
  leftMotorSpeed = kMedSpeed;
  leftMotorDirection = 1;
  rightMotorEnabled = 1;
  rightMotorSpeed = kMedSpeed;
  rightMotorDirection = 0;
}

void turnLeft() {
  leftMotorEnabled = 1;
  leftMotorSpeed = kMedSpeed;
  leftMotorDirection = 0;
  rightMotorEnabled = 1;
  rightMotorSpeed = kMedSpeed;
  rightMotorDirection = 1;
}

void goForward() {
  leftMotorEnabled = 1;
  leftMotorSpeed = kMaxSpeed;
  leftMotorDirection = 1;
  rightMotorEnabled = 1;
  rightMotorSpeed = kMaxSpeed;
  rightMotorDirection = 1;
}

