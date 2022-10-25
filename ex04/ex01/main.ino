#define TRIGGER_PIN 12
#define ECHO_pIN 11

void setup(){
    Serial.begin(9600);
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_pIN, INPUT);
    
}

long microsecondsToCentimeters(long microseconds){
    return microseconds/29/2;
}

void loop(){
    long duraction, cm;
    digitalWrite(TRIGGER_PIN,HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIGGER_PIN,LOW);

    duraction = pulseIn(ECHO_pIN, HIGH);
    cm = microsecondsToCentimeters(duraction);

    Serial.print(cm);
    Serial.println("cm");
    delay(300);
}

