/*
C:\Users\User\AppData\Local\Arduino15\packages\arduino\hardware\avr\1.8.5\libraries\SPI\src
C:\Users\User\Documents\Arduino\libraries\rfid-1.4.9\src
*/

#include<SPI.h>
#include<MFRC522.h>
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN,RST_PIN);

void setup(){
    Serial.begin(9600);
    SPI.begin();
    mfrc522.PCD_Init();
    Serial.println("scan card to see UID and type");
}

void loop(){
//    Serial.println("0");

    if(!mfrc522.PICC_IsNewCardPresent()) return;
    

    Serial.println("1");

    if(!mfrc522.PICC_ReadCardSerial()) return;

    Serial.println("2");
    // 카드 디버그 정보 덤프
    
    mfrc522.PICC_DumpToSerial(&(mfrc522.uid));
}