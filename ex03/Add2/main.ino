
int lightAnalogPin = A0;
int ledPin = 11;

void setup(){
    pinMode(ledPin, OUTPUT); // 설정
    Serial.begin(9600);
}

void loop(){
    int value = analogRead(lightAnalogPin); // 값 읽기
    Serial.print("analog: ");
    Serial.println(value); // 값 출력
    digitalWrite(ledPin,value>400?HIGH:LOW); // 400보다 크면 어두우므로 LED 점등
    delay(10);  
}