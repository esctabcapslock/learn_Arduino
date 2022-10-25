// 디지철 input

int mic_analog_in = 0; // input
int sensorValue = 0;
void setup(){
    Serial.begin(9600);
}

void loop(){
    sensorValue = digitalRead(mic_analog_in);
    Serial.println(sensorValue,DEC);
}
