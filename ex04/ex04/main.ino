#include<ADXL345.h>
#include<Wire.h>

/*

"C:\\Users\\User\\Documents\\Arduino\\libraries\\ADXL345",
"C:\\Users\\User\\AppData\\Local\\Arduino15\\packages\\arduino\\hardware\\avr\\1.8.5\\libraries\\Wire\\src",
*/
ADXL345 acc;
int sw = 3;
int buzzer = 4;
unsigned long atart_time = 0, elapsed_time = 0;
boolean state = false;
double Xg, Yg, Zg;
double bXg=0, bYg = 0, bZg = 0;
int count = 0, motion = 0;

void switchFn(){
    state != 
}



void setup(){
    acc.begin();
    Serial.begin(9600);
    acc.setRange(acc.RANGE_16G);
    delay(100);
}

void loop(){
    double Xg, Yg, Zg;
    acc.read(&Xg, &Yg, &Zg);
    Serial.pr
}