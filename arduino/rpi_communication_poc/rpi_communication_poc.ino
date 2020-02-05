#include <SoftwareSerial.h> 
char dataString[50] = {0};
int a =0; 
int incomingByte = 0;

void setup() {
  Serial.begin(9600);              //Starting serial communication
  Serial.println(1);
}
  
void loop() {
  a++;                          // a value increase every loop
  //if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if(incomingByte == 49){
      Serial.println("egy");   // send the data
      delay(1000);                  // give the loop some break  
    }
    if(incomingByte == 50){
      Serial.println("ketto");   // send the data
      delay(1000);                  // give the loop some break  
    }
    //Serial.println(1);   // send the data
    //delay(1000);
  //}
}

