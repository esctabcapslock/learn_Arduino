
/*

"C:\\Users\\User\\AppData\\Local\\Arduino15\\packages\\arduino\\hardware\\avr\\1.8.5\\libraries\\SoftwareSerial\\src",
"C:\\Users\\User\\Documents\\Arduino\\libraries\\TinyGPS-master",
"C:\\Users\\User\\Documents\\Arduino\\libraries\\LiquidCrystal_I2C-1.1.2",    
*/


#include <SoftwareSerial.h>
#include<LiquidCrystal_I2C.h>
#include <TinyGPS.h>

LiquidCrystal_I2C lcd(0x27, 16,2); // 사용방법
TinyGPS gps;
SoftwareSerial ss(4, 3);

void setup(){
    Serial.begin(9600);
    ss.begin(4800);
    Serial.println("helloq");
    lcd.init(); // LCD 초기화
    lcd.backlight(); // 백라이트
    lcd.clear(); // 초기화
    lcd.setCursor(0,0);
    lcd.print("start"); // 시작했다고 표시

}

void loop()
{
  bool newData = false;
  unsigned long chars;
  unsigned short sentences, failed;

    // For one second we parse GPS data and report some key values
    // GPS에서 데이터를 받은 뒤, 파싱한다.
    for (unsigned long start = millis(); millis() - start < 1000;){
    while (ss.available()){
        char c = ss.read();
        //   Serial.print("input: ");
        //   Serial.print(c, HEX); // uncomment this line if you want to see the GPS data flowing
        //   Serial.println("");

        // Did a new valid sentence come in?
        if (gps.encode(c)) newData = true;

        }
    }
    


  if (newData){ // 응답을 받았을 경우 출력
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);
    Serial.print("LAT=");
    Serial.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Serial.print(" LON=");
    Serial.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    Serial.print(" SAT=");
    Serial.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    Serial.print(" PREC=");
    Serial.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());


    // lcd에도 출력. 길이가 길기 때문에 0.5초 간격으로 표시되도록 설정하였다.
    lcd.print("LA:");
    lcd.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    lcd.setCursor(0,7);
    lcd.print(" LO:");
    lcd.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    delay(500);
    lcd.clear();

    lcd.setCursor(0,7);
    lcd.print(" SA:");
    lcd.print(gps.satellites() == TinyGPS::GPS_INVALID_SATELLITES ? 0 : gps.satellites());
    lcd.print(" PR:");
    lcd.print(gps.hdop() == TinyGPS::GPS_INVALID_HDOP ? 0 : gps.hdop());
    delay(500);
    

    // 데이터 받았는지 표시
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("newData exists");

    }else{ // 데이터가 없다고 표시
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("no newData");
    }
  
    gps.stats(&chars, &sentences, &failed);
    // lcd에 gps 관련 정보를 출력한다.
    lcd.setCursor(0,7);
    lcd.print("C:");
    lcd.print(chars);
    lcd.print(" S:");
    lcd.print(sentences);
    lcd.print(" E:");
    lcd.print(failed);

    // 시리얼 모니터에도 출력한다.
    Serial.print(" CHARS=");
    Serial.print(chars);
    Serial.print(" SENTENCES=");
    Serial.print(sentences);
    Serial.print(" CSUM ERR=");
    Serial.println(failed);

    if (chars == 0)
        Serial.println("** No characters received from GPS: check wiring **");
}