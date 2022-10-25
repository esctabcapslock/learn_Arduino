// ctrl m+j

#include<SoftwareSerial.h>
SoftwareSerial bt_serial(2,3);
static int counter = 0;
void setup(){
    Serial.begin(9600);
    bt_serial.begin(9600);
    pinMode(13, OUTPUT);
}

void loop(){
    bt_serial.print("Tick #");
    bt_serial.println(counter++, DEC);

    delay(1000);
}