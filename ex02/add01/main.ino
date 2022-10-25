const int rpin = 9;
const int gpin = 10;
const int bpin = 11;

void setup(){
    // 초기 설정
    pinMode(rpin,OUTPUT);
    pinMode(gpin,OUTPUT);
    pinMode(bpin,OUTPUT);
}

// 각 값에 대해 LED를 작동시킨다.
void setColor(int r, int g, int b){
    // 켜기
    analogWrite(rpin,r);
    analogWrite(gpin,g);
    analogWrite(bpin,b);
}


int br = 0;

void loop(){

    // br 값이 시간에 따라 점점 커지도록
    if (br>255) br = 0;
    setColor(br,br,br);
    delay(100);
    br += 10;
}