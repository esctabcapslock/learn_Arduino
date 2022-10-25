// Arduino: Initialize
const int RED = 7;// RED LED
const int YELLOW = 6;// YELLOW LED
const int GREEN = 5;// GREEN LED

void setup()
{
 Serial.begin(9600);// serial baud rate 9600
 pinMode(RED, OUTPUT);
 pinMode(YELLOW, OUTPUT);
 pinMode(GREEN, OUTPUT);
}

void loop()
{
 digitalWrite(RED, 1);
 delay(1000);
 digitalWrite(YELLOW, 1);
 delay(1000);
 digitalWrite(GREEN, 1);
 delay(1000);
 digitalWrite(RED, 0);
 delay(1000);
 digitalWrite(YELLOW, 0);
 delay(1000);
 digitalWrite(GREEN, 0);
 delay(1000);
}
