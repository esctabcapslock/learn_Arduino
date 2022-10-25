#include <SPI.h>
#include <MFRC522.h>

#define SS_PIN 10
#define RST_PIN 9

MFRC522 mfrc522(SS_PIN,RST_PIN);
MFRC522::MIFARE_Key key;


byte buffer[30];
byte size, block;
MFRC522::StatusCode status;

void setup(){
    Serial.begin (9600);
    SPI.begin();
    mfrc522.PCD_Init();
    for (byte i= 0; i < 6 ;  i++) key.keyByte[i]=0xff;
    block = 5;
    size = sizeof(buffer);
    Serial.println ("Scan Card to see UID and type...");
}


void loop(){
// Look for new cards
if (!mfrc522.PICC_IsNewCardPresent ()) return;

// Select one of the cards

if (!mfrc522.PICC_ReadCardSerial()) return;

status = mfrc522.PCD_Authenticate (MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
Serial.println (mfrc522.GetStatusCodeName (status) );

status = mfrc522.MIFARE_Read(block, buffer, &size);
if(status != MFRC522::STATUS_OK){
    Serial.print("MIFARE_read() failed: ");
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
}else{
    Serial.print("MIFARE_read() success: ");
    for(int i=0; i<18; i++){
        Serial.print(buffer[i]);
        Serial.print(",");
    }
}

}
