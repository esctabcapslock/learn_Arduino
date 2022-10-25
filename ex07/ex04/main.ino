// ctrl m+j

#include<SoftwareSerial.h>
const int LED_PIN = 6;

SoftwareSerial bt_serial(2,3);

byte buffer[512];
int buffer_index;

void setup(){
    
    Serial.begin(9600);
    bt_serial.begin(9600);
    buffer_index = 0;
}

void loop(){
    if(bt_serial.available()>0){
        byte data = (byte) bt_serial.read();
        Serial.print("input: ");
        Serial.println(data);
        buffer[buffer_index++] = data;
        if(data=='\n'){
            // tx part
            buffer[buffer_index] = 0;
            Serial.println((char*) buffer);
            bt_serial.write(buffer, buffer_index);
            buffer_index = 0;
        }
    }
}