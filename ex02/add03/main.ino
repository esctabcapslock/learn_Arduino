#include <IRremote.h> // IRremote 2.7.0
const int sndOut = 7;
const int rcvPin = 8;
IRrecv irrecv(rcvPin); //  IR 관련
decode_results results; // IR 출력 저장
volatile uint8_t *pinOutput; // Output port register
uint8_t pinMask = 0;         // Pin bitmask

long int octabe[] = {262,294,330,349,392,440,494,523,587,659}; // 옥타브 음계 진동수. 도레미파솔라시도레...

long int _prescaler = 1; // prescaler 값
void applyHz(long int hz){ // 30.5hz ~ 1953.1hz로 범위가 추정됨. 오버플로 때문.
    if (hz<500){ // hz가 낮으면 범위를 초과하기때문에 prescaler를 바꾸자,
        TCCR1B = (1 << WGM12) | (1 << CS11);
        _prescaler = 8;
    }else{
        TCCR1B = (1 << WGM12) | (1 << CS10);
        _prescaler = 1;
    }


    Serial.print("hz change:");
    Serial.println(hz);
    long int divr =  16e6/(hz*_prescaler)/2-1;
    OCR1A = divr;
}

// IR 응답에 대해 해당되는 버튼의 숫자를 응답하는 함수
int getNumber(unsigned long value)
{
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

void setup(){
    irrecv.enableIRIn(); // 응답받기
    Serial.begin(9600); // 시리얼 통신 사용
    pinMode(sndOut,OUTPUT); // 출력설정

    // 다음의 출처를 활용하자.
    // https://www.instructables.com/Arduino-Timer-Interrupts/
    // https://bitbucket.org/teckel12/arduino-new-tone/src/master/NewTone.cpp
    // https://www.microchip.com/en-us/product/ATmega328p
    // https://diyver.tistory.com/140


    TCCR1A = 0;// TCCR1A register 초기화
    TCCR1B = 0;// TCCR1B register 초기화
    TCNT1  = 0;// counter value 초기화
    TCCR1B |= (1 << WGM12);   // CTC mode 사용
    OCR1A = 15624;// 적당한 초기값
    TCCR1B |= (1 << CS10);// 1 prescaler 사용
    TIMSK1 |= (1 << OCIE1A); // 타이머 1 활성화

    // 핀 관련 정보를 레지스터
    pinMask = digitalPinToBitMask(sndOut); // port register bitmask 얻음
    pinOutput = portOutputRegister(digitalPinToPort(sndOut)); // output port register 얻음

    sei(); // 인터럽트 사용
}

void loop(){

    if (irrecv.decode(&results)){
        // Serial.println(results.value, HEX); //응답신호 출력
        delay(50);                         //입력받고 대기
        irrecv.resume();                    //다음신호 받기
        int input = getNumber(results.value); // 0~9는 숫자, 나머지는 'x'로 출력되도록 함.
        if(input<10){
            // applyHz(octabe[input]);
            applyHz((input+1)*100);
        }
    }

    // 디버그용. 옥타브 반복
    // for(int i=0; i<9; i++){
    //     applyHz(octabe[i]);
    //     Serial.print("octabe change: ");
    //     Serial.print(i);
    //     Serial.print(", ");
    //     Serial.println(octabe[i]);
    //     delay(1000);
    // }
}


ISR(TIMER1_COMPA_vect){ 
    // TIMER2는 IRremote.h, timer 0은 delay에서 사용히므로 여기서 사용할 수 없다. ㅠㅠ
    // 하드웨어 문제이므로 namespace같은 것으로 해결할 수 없는 것 같다.
    // 다음 참조
    // https://bitbucket.org/teckel12/arduino-new-ping/wiki/Multiple%20Definition%20of%20%22__vector_7%22%20Error
    // https://forum.arduino.cc/t/library-conflict-irremote-attempting-to-use-standard-c-namespace-approach/628355
    *pinOutput ^= pinMask;
}