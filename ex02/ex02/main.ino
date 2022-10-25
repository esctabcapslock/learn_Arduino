// pin 연결 설정.
int redPin = 13;
int greenPin = 11;
int bluePin = 12;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()
{
  // setColor 함수에 RGB 값을 넣어 RGB 또는 두 가지 색상을 섞는다.
  //밝기: 0~255
  setColor(255, 0, 0); // red
  delay(2000);
  setColor(0, 255, 0); // green
  delay(2000);
  setColor(0, 0, 255); // blue
  delay(2000);
  setColor(255, 255, 0); // yellow
  delay(2000);
  setColor(255, 0, 255); // purple
  delay(2000);
  setColor(0, 255, 255); // aqua
  delay(2000);
  setColor(255, 255, 255); // white
  delay(2000);
  setColor(0, 0, 0); // Off
  delay(2000);
}
// RGB 값을 받아 analogWrite를 통해 각 핀에 연결된 LED에 전달 함수
void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}