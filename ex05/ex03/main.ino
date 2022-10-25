#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN,RST_PIN);
MFRC522::MIFARE_Key key;

byte buffer[16]={0X20,0X22,0X16, 0X72,0X20,6,7,8,9,10,9,8,7,6,5,4};
byte block;

MFRC522::StatusCode status;

void setup(){
    Serial.begin (9600);
    SPI.begin();
    mfrc522.PCD_Init();
    for (byte i= 0; i < 6 ;  i++) key.keyByte[i]=0xff;
    block = 15;
    Serial.println ("Scan Card to see UID and type...");
}


void loop(){
// Look for new cards
if (!mfrc522.PICC_IsNewCardPresent ()) {
return;

}

// Select one of the cards

if (!mfrc522.PICC_ReadCardSerial()) return;

status = mfrc522.PCD_Authenticate (MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
Serial.println (mfrc522.GetStatusCodeName (status) );

status = mfrc522.MIFARE_Write(block, buffer, 16);
Serial.println (mfrc522.GetStatusCodeName (status) );

mfrc522.PICC_DumpToSerial (&(mfrc522.uid) );

delay (1000);
}
