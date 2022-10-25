void setup(){
    Serial.begin(9600);
}

void loop(){
    int sensorValue1 = digitalRead(A0);
    Serial.println(sensorValue1);
    delay(100);
}