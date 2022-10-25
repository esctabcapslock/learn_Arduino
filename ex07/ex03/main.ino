// ctrl m+j

#include<SoftwareSerial.h>
const int LED_PIN = 6;

SoftwareSerial bt_serial(2,3);
static int counter = 0;
void setup(){
    pinMode(LED_PIN,OUTPUT);
    Serial.begin(9600);
    bt_serial.begin(9600);
    pinMode(13, OUTPUT);
}

void loop(){
    if(bt_serial.available()>0){
        int data = bt_serial.parseInt();
        Serial.println(data);
        analogWrite(LED_PIN,data);
    }
}