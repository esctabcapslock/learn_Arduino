const int rpin = 7;
void setup()
{
    Serial.begin(9600); // serial baud rate 9600
    pinMode(rpin,OUTPUT);
}

const int oct[] = {262,294,330,349,392,440,494,523,587,659};



void loop()
{
    // Serial.println("hello!!");
    // delay(1000);

    for(int i=0; i<9; i++){
        tone(rpin,oct[i]/2);
        delay(1000);
    }
}
