#include <SoftwareSerial.h> 

#define DO_NOTHING   0
#define GO_FW   1
#define GO_BW   2
#define GO_R   3
#define GO_L   4

#define ENA_PIN   6
#define EN1_PIN   7
#define EN2_PIN   3
#define EN3_PIN   4
#define EN4_PIN   2
#define ENB_PIN   5

#define DELAY_UNIT  10 

//#define BT_SERIAL_RX    11 //Rx pin
//#define BT_SERIAL_TX    10 //Tx pin

const int DoNothing = DO_NOTHING;
const int GoForward = GO_FW;
const int GoBackward = GO_BW;
const int GoRight = GO_R;
const int GoLeft= GO_L;

const int RightMotorBackward   = EN1_PIN;
const int RightMotorForward   = EN2_PIN;
const int LeftMotorForward    = EN3_PIN;
const int LeftMotorBackward    = EN4_PIN;
const int RightMotorStart = ENA_PIN;
const int LeftMotorStart  = ENB_PIN;

int iSpeed              = 255; //speed, range 0 to 255
int incomingByte = 0; // for incoming serial data
int defaultDelay = 10;  //delay for moving operations

void LeftForward(int d){
  analogWrite(LeftMotorStart, iSpeed);
  digitalWrite(LeftMotorForward, HIGH);
  digitalWrite(LeftMotorBackward, LOW);
  delay(d * DELAY_UNIT);
}

void LeftBackward(int d){
  analogWrite(LeftMotorStart, iSpeed);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, HIGH);
  delay(d * DELAY_UNIT);
}

void LeftStop(int d){
  analogWrite(LeftMotorStart, iSpeed);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  delay(d * DELAY_UNIT);
}

void RightBackward(int d){
  analogWrite(RightMotorStart, iSpeed);
  digitalWrite(RightMotorBackward, HIGH);
  digitalWrite(RightMotorForward, LOW);
  delay(d * DELAY_UNIT);
}

void RightForward(int d){
  analogWrite(RightMotorStart, iSpeed);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(RightMotorForward, HIGH);
  delay(d * DELAY_UNIT);
}

void RightStop(int d){
  analogWrite(RightMotorStart, iSpeed);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  delay(d * DELAY_UNIT);
}

void Stop(int d){
  analogWrite(LeftMotorStart, iSpeed);
  digitalWrite(LeftMotorForward, LOW);
  digitalWrite(LeftMotorBackward, LOW);
  analogWrite(RightMotorStart, iSpeed);
  digitalWrite(RightMotorBackward, LOW);
  digitalWrite(RightMotorForward, LOW);
  delay(d * DELAY_UNIT);
}

void Forward(int d){
  RightForward(d);
  LeftForward(d);
}

void Backward(int d){
  RightBackward(d);
  LeftBackward(d);
}

void Right(int d){
  LeftForward(d);
  RightBackward(d);
}

void Left(int d){
  LeftBackward(d);
  RightForward(d);
}


void setup() 
{
    //start receiving serial
    Serial.begin(9600);

    //motor connections
    pinMode(RightMotorBackward,   OUTPUT); 
    pinMode(RightMotorForward,   OUTPUT); 
    pinMode(LeftMotorForward,    OUTPUT); 
    pinMode(LeftMotorBackward,    OUTPUT); 
    pinMode(RightMotorStart, OUTPUT);
    pinMode(LeftMotorStart,  OUTPUT);
    
}

void loop() 
{
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    switch (incomingByte) {
      case DoNothing:
        break;
      case GoForward:
        Forward(defaultDelay);
        break;
      case GoBackward:
        Backward(defaultDelay);
        break;
      case GoRight:
        Right(defaultDelay);
        break;
      case GoLeft:
        Left(defaultDelay);
        break;
      default:
        // statements
        break;
    }
    Stop(defaultDelay);
  }
}
