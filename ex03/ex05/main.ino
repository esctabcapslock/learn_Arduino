int lightPin = 10; // 포토레지스터?
int lightAnalogPin = A0; // 포토레지스터?
int ledPin = 11;

void setup(){
    pinMode(ledPin, OUTPUT);
    Serial.println("hello");
    // pinMode(inputPin, INPUT);
    Serial.begin(9600);
}

void loop(){
    int reading = analogRead(lightAnalogPin);
    Serial.print("analog: ");
    Serial.println(reading);

    Serial.print("digital: ");
    Serial.println(digitalRead(lightPin));
    if(digitalRead(lightPin)==1){
        digitalWrite(ledPin,1);
    }else{
        digitalWrite(ledPin,0);

    }
    delay(10);  
}