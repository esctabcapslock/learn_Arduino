int micPin = A0;
int motionPin = 6;
int lightPin = 7;
int motionOutPin = 2;
int lightOutPin = 3;
int micOutPin = 4;

void setup(){
    // 핀 설정
    pinMode(motionPin, INPUT);
    pinMode(lightPin, INPUT);
    pinMode(motionOutPin, OUTPUT);
    pinMode(lightOutPin, OUTPUT);
    pinMode(micOutPin, OUTPUT);
    // 시리얼모니터 설정
    Serial.begin(9600);
}

void loop(){
    // 값 받아오기
    int motionValue = digitalRead(motionPin);
    int lightValue = digitalRead(lightPin);
    int micValue = analogRead(micPin);

    digitalWrite(motionOutPin,motionValue?HIGH:LOW);
    digitalWrite(lightOutPin,lightValue?HIGH:LOW);
    // 마이크의 경우, 아닐로그 신호로 받은 뒤 80보다 클 경우 점등하도록 작성
    digitalWrite(micOutPin,micValue>80?HIGH:LOW);
    delay(10);  
}