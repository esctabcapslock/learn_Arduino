#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); // LCD 사용 방법 선언 (2 라인, 16 자).
void setup(){
    Serial.begin(9600);
    Serial.println("1");
    lcd.init();      // Initilize LCD
    Serial.println("2");
    lcd.backlight(); // turn on background light for LCD
    Serial.println("3");
}
void loop(){

    lcd.setCursor(0, 0); //첫 번째 줄의 첫 번째 칸으로 커서 이동. 시작점
    lcd.print("Hello");
    lcd.setCursor(7, 0); // LCD의 맨 앞에서 부터 7칸 공백
    lcd.print("world");
    delay(3000); // delay 3 seconds
    lcd.clear(); // clear the LCD
    lcd.print("I am Arduino");
    delay(3000); // delay 3 seconds
    lcd.clear(); // clear the LCD
}