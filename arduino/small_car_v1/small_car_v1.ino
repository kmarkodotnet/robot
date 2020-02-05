#include <SoftwareSerial.h> 

#define ASCII_BASE 48
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

const int DoNothing = ASCII_BASE + DO_NOTHING;
const int GoForward = ASCII_BASE + GO_FW;
const int GoBackward = ASCII_BASE + GO_BW;
const int GoRight = ASCII_BASE + GO_R;
const int GoLeft= ASCII_BASE + GO_L;

const int RightMotorBackward   = EN1_PIN;
const int RightMotorForward   = EN2_PIN;
const int LeftMotorForward    = EN3_PIN;
const int LeftMotorBackward    = EN4_PIN;
const int RightMotorStart = ENA_PIN;
const int LeftMotorStart  = ENB_PIN;

int iSpeed              = 255; //speed, range 0 to 255
int oldIncomingByte = -1;
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
  RightForward(0);
  LeftForward(0);
  delay(d * DELAY_UNIT);
}

void Backward(int d){
  RightBackward(0);
  LeftBackward(0);
  delay(d * DELAY_UNIT);
}

void Right(int d){
  LeftForward(0);
  RightBackward(0);
  delay(d * DELAY_UNIT);
}

void Left(int d){
  LeftBackward(0);
  RightForward(0);
  delay(d * DELAY_UNIT);
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

    
    Serial.println(1);
}

void loop() 
{
  //if (Serial.available() > 0) {
    //delay(1000);
    //Serial.write(1);
    //Serial.write("as");
    incomingByte = Serial.read();
    if(oldIncomingByte != incomingByte ){
      switch (incomingByte) {
          case DoNothing:
            Stop(defaultDelay);
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
            break;
      }      
    }
    oldIncomingByte = incomingByte;
    //Serial.println("asd");
    //Stop(defaultDelay);
  //}
}
