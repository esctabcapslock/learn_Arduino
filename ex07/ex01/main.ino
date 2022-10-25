// ctrl m+j

#include<SoftwareSerial.h>
SoftwareSerial bt_serial(2,3);
void setup(){
    Serial.begin(9600);
    bt_serial.begin(9600);
    pinMode(13, OUTPUT);
}

void loop(){
    if(bt_serial.available()>0){
        byte data = (byte) bt_serial.read();
        Serial.println(data);
        if(data=='h') digitalWrite(13,HIGH);
        else if(data=='l') digitalWrite(13,LOW);
    }
}