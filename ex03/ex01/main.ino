int mic_analog_in = A0; // ์๋ ๋ก๊ทธ input
int sensorValue = 0;
void setup(){
    Serial.begin(9600);
}

void loop(){
    sensorValue = analogRead(mic_analog_in);
    Serial.println(sensorValue,DEC);
}
