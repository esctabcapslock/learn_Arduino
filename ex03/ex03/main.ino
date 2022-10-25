// 디지철 input

int mic_analog_in = A0; // 아날로그 input
int LED3_pin = 3;
int LED4_pin = 4;
int LED5_pin = 5;
int sensorValue = 0;
void setup(){
    pinMode(LED3_pin,OUTPUT);
    pinMode(LED4_pin,OUTPUT);
    pinMode(LED5_pin,OUTPUT);
    Serial.begin(9600);
}

void loop(){
    sensorValue = analogRead(mic_analog_in);

    // 센서 값에 따라 출력값 설정

    if (sensorValue<30) digitalWrite(LED3_pin,HIGH);
    else digitalWrite(LED3_pin,LOW);

    if (sensorValue>=30 && sensorValue<60) digitalWrite(LED4_pin,HIGH);
    else digitalWrite(LED4_pin,LOW);

    if (sensorValue>=60) digitalWrite(LED5_pin,HIGH);
    else digitalWrite(LED5_pin,LOW);

    Serial.println(sensorValue,DEC);
    delay(200);
}
