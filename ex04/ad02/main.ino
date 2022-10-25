#define TRIGGER_PIN 12
#define ECHO_pIN 11

void setup(){
    Serial.begin(9600);
    pinMode(TRIGGER_PIN, OUTPUT);
    pinMode(ECHO_pIN, INPUT);
    
    pinMode(5, OUTPUT);
    pinMode(6, OUTPUT);
    pinMode(7, OUTPUT);
}

long microsecondsToCentimeters(long microseconds){
    return microseconds/29/2;
}


void ledTurnOn(bool a, bool b, bool c){
  digitalWrite(5,a?HIGH:LOW);
  digitalWrite(6,b?HIGH:LOW);
  digitalWrite(7,c?HIGH:LOW);
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

  if (cm<4) ledTurnOn(0,0,0);
  else if (cm<8) ledTurnOn(1,0,0);
  else if (cm<12) ledTurnOn(1,1,0);
  else ledTurnOn(1,1,1);

    delay(300);
}

