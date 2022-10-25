/*
C:\Users\User\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.5\libraries\SPI\src
C:\Users\User\Documents\Arduino\libraries\rfid-1.4.9\src
*/

#include<SPI.h>
#include<MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN,RST_PIN);

class Minimap
{
    private:
        byte value[10]; // value
        byte key[10][10]; // key 값 저장
        byte top; // 얼마나 저장공간을 차지하고 있는지
        const byte LENGTH = 10; // 저장할 수 있는 key 개수

    public:
        Minimap(); // 생성자
        byte* get(byte size, byte* keyvalue); // key에 해당되는 값의 포인터를 가져오는 함수
};

Minimap::Minimap(){ // 생성자 함수. 값을 모두 0으로 초기화할 것.
    Serial.println("init Minimap");
    top = 0;
    for (byte i=0; i<10; i++) for(byte j=0; j<10; j++) key[i][j] = 0; // 없어도 되는 코드이긴 하다.
    for (byte i=0; i<10; i++) value[i] = 0;
}

byte* Minimap::get(byte size, byte* keyvalue){ // 적당한 uid값을 주면 저장 위치의 포인터를 반환한다.
    bool f = false;
    byte i;
    for(i=0; i<top; i++){
        f = true;
        for(byte j=0; j<(size); j++){
            if (key[i][j] != keyvalue[j]) {
                f = false; 
                break;
            }
        }
        if(f) break;
    }
    if(f){
        // 같은 값이 존재
        // Serial.print("same value exist, id:");
        // Serial.println(i);
        return value+i; // 포인터 반환
    }else{
        // 새 값을 추가해야 함
        // Serial.print("same value no exist, top:");
        // Serial.println(top);
        if (top == LENGTH) return NULL; // 꽉 찬 경우 에러
        for(int j=0; j<(size); j++) key[top][j] = keyvalue[j];
        top ++;
        return value+i; // 포인터 반환
    }
}


Minimap minimap; // 사용자 지정 맵 생성

void setup(){
    // 예제 코드를 따름.
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("scan card to see UID and type");
    // test(); // 객체 테스트
}

void loop(){

    if(!mfrc522.PICC_IsNewCardPresent()) return;
    

    Serial.println("reading... 1/2");

    if(!mfrc522.PICC_ReadCardSerial()) return;

    // 성공적으로 읽은 상태임.


    Serial.println("reading... 2/2"); // 성공적으로 읽었음을 알려줌

    byte* p = minimap.get(mfrc522.uid.size, mfrc522.uid.uidByte); // 맵 객체를 이용해 포인터를 반환
    (*p)++;
    Serial.print("count: ");
    Serial.println(*p); // 읽은 횟수를 출력

    delay (1000);
}

void test(){ // 저 minimap 클래스가 정상 적동하는지 확인하는 코드
    Serial.println("test start!!");
    byte uid1[10] = {1,2,3,4};
    byte uid2[10] = {1,6,7,8};
    byte size = 4;

    byte* v1 = minimap.get(size, uid1); // 0임
    (*v1)++; // 1이 됨
    byte* v2 = minimap.get(size, uid2); // 0이 됨
    (*v2)+=10; // 10이 됨
    Serial.println((int)v1, HEX); // 
    Serial.println((int)v2, HEX);

    Serial.print("uid 1: ");
    Serial.println(*minimap.get(size, uid1)); // 1이 나와야 함

    Serial.print("uid 2: ");
    Serial.println(*minimap.get(size, uid2)); // 10이 나와야 함

}