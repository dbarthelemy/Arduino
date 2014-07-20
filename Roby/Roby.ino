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

#define kTestSpeed 255
#define kTestWait 5000
int testState = 0;

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
  /*
   *  Motor testing
   */
  switch(testState) {
    case 0:
    leftMotorEnabled = 0;
    leftMotorSpeed = 0;
    leftMotorDirection = 1;
    rightMotorEnabled = 0;
    rightMotorSpeed = 0;
    rightMotorDirection = 1;
    testState = 1;
    break;
    case 1:
    leftMotorEnabled = 1;
    leftMotorSpeed = kTestSpeed;
    leftMotorDirection = 1;
    rightMotorEnabled = 1;
    rightMotorSpeed = kTestSpeed;
    rightMotorDirection = 0;
    testState = 2;
    break;
    case 2:
    leftMotorEnabled = 1;
    leftMotorSpeed = kTestSpeed;
    leftMotorDirection = 0;
    rightMotorEnabled = 1;
    rightMotorSpeed = kTestSpeed;
    rightMotorDirection = 1;
    testState = 3;
    break;
    case 3:
    leftMotorEnabled = 1;
    leftMotorSpeed = kTestSpeed;
    leftMotorDirection = 1;
    rightMotorEnabled = 1;
    rightMotorSpeed = kTestSpeed;
    rightMotorDirection = 1;
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

  delay(kTestWait);
}

