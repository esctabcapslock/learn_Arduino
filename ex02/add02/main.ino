#include<IRremote.h> // IRremote 2.7.0
#include<LiquidCrystal_I2C.h>

const int rcvPin = 8;
IRrecv irrecv(rcvPin); //  IR 관련
decode_results results; // IR 출력 저장
LiquidCrystal_I2C lcd(0x27, 16,2); // 사용방법


void setup(){
    // LCD 초기화
    lcd.init();
    lcd.backlight();

    
    Serial.begin(9600); // 시리얼 통신 사용
    irrecv.enableIRIn(); // 응답받기                                                                            
    
    lcd.setCursor(0,0);
    lcd.print("start");
}

// IR 응답에 대해 해당되는 버튼의 숫자를 응답하는 함수
int getNumber(unsigned long value){
            switch (value)
        {
        case 0XFF30CF:
            return 1;
        case 0XFF18E7:
            return 2;
        case 0XFF7A85:
            return 3;
        case 0XFF10EF:
            return 4;
        case 0XFF38C7:
            return 5;
        case 0XFF5AA5:
            return 6;
        case 0XFF42BD:
            return 7;
        case 0XFF4AB5:
            return 8;
        case 0XFF52AD:
            return 9;
        case 0XFF6897:
            return 0;
        default:
         return 72;
    }
}


void loop(){
    if(irrecv.decode(&results)){
        Serial.println(results.value,HEX); //응답신호 출력
        delay(200); //입력받고 대기
        irrecv.resume(); //다음신호 받기

        char btn = getNumber(results.value) + '0'; // 0~9는 숫자, 나머지는 'x'로 출력되도록 함.
        lcd.clear(); // 초기화
        lcd.setCursor(0,0);
        lcd.print("button val: "); // 초기 입력
        lcd.print(&btn); // 버튼 번호 입력
    }
}