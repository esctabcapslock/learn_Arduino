// C:\\Users\\User\\Documents\\Arduino\\libraries\\Cytron_ESPWiFi_Shield\\src

#include <CytronWiFiShield.h>
#include <CytronWiFiClient.h>
#include <CytronWiFiServer.h>
#include <SoftwareSerial.h>

const char *ssid = "QWERTY";
const char *pass = "113333555555";
// IPAddress ip(192, 168, 1 ,242);

const byte LED_PIN = 5;
const int LED_ON_THRESHOLD = 500;
const byte LED_1 = 6;
const byte LED_2 = 7;
bool LED_1_state = true;
bool LED_2_state = true;

ESP8266Server server(80);

const char htmlHeader[] = "HTTP/1.1 200 OK\r\n"
                        "Content-Type: text/html\r\n"
                        "Connection: close\r\n\r\n";

const char htmlEnd[] = "\r\n";

const char onoffLink[] = "<br><a href=./on>on</a><br><a href=./off>off</a><br><a href=./>home</a><br>";

// 예제 코드를 보면 문자열을 조각내서 넣음.
// 아무생각 없이 한 줄에 몰아 넣으면 효율적이겠거니 생각했는데.
// 생각해보니 이 방식이 컴파일러를 거치면 더 효율적임.

                          
void setup() {
  pinMode(LED_PIN,OUTPUT);
  pinMode(LED_1,OUTPUT);
  pinMode(LED_2,OUTPUT);

  
  // put your setup code here, to run once:
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
 
  if(!wifi.begin(2, 3))
  {
    Serial.println(F("Error talking to shield"));
    while(1);
  }
  Serial.println(wifi.firmwareVersion());
  Serial.print(F("Mode: "));Serial.println(wifi.getMode());// 1- station mode, 2- softap mode, 3- both
  // Uncomment these 2 lines if you are using static IP Address
  // Serial.println(F("Setup wifi config"));
  // wifi.config(ip);
  Serial.println(F("Start wifi connection"));
  if(!wifi.connectAP(ssid, pass))
  {
    Serial.println(F("Error connecting to WiFi"));
    while(1);
  } 
  Serial.print(F("Connected to "));Serial.println(wifi.SSID());
  Serial.println(F("IP address: "));
  Serial.println(wifi.localIP());
  wifi.updateStatus();
  Serial.println(wifi.status()); //2- wifi connected with ip, 3- got connection with servers or clients, 4- disconnect with clients or servers, 5- no wifi
  // clientTest();
  server.begin();


  digitalWrite(LED_1, LED_1_state);
  digitalWrite(LED_2, LED_2_state);
}

// void htmlTagWrite(ESP8266Client* client, String tag, String parm, String body){
//     client->print("<div><");
//     client->print(tag);
//     client->print(' ');
//     client->print(parm);
//     client->print('>');
//     client->print(body);
//     client->print('<');
//     client->print(tag);
//     client->print("></div>");
//     client->print("</html>\r\n");
// }
// void htmlWrite(ESP8266Client* client, String title, String bgColor, String ftColor,  String body1, String body2){
//     client->print(htmlHeader);
//     client->print("<title>");
//     client->print(title);
//     client->print("</title><body bgcolor=");
//     client->print(bgColor);
//     client->print(" size=5 color=");
//     client->print(ftColor);
//     client->print(">");
//     client->print(body1);
//     client->print(body2);
//     client->print("</font>");

//     client->print("</html>\r\n");
// }

void darkpage(ESP8266Client* client, bool flag, bool led){
  client->print("<body ");
  if(!flag)client->print("bgcolor=\"0\" style=\"color:#fff\"");
  client->print(">Room is currently ");
  client->print(flag?"BRIGHT":"DARK");
  client->print("<br>");
  client->print(onoffLink);
  client->print("<br>");

  client->print("LED is");
  client->print(led?"ON":"OFF");
  client->print("</body>");
}

void loop() {
  // put your main code here, to run repeatedly:
  serverTest();
}

void serverTest()
{
  ESP8266Client client = server.available();
  
  if(client.available()>0)
  {
    String req = client.readStringUntil('\r'); 
    // First line of HTTP request looks like "GET /path HTTP/1.1"
    // Retrieve the "/path" part by finding the spaces
    int addr_start = req.indexOf(' ');
    int addr_end = req.indexOf(' ', addr_start + 1);
    if (addr_start == -1 || addr_end == -1) {
      Serial.print(F("Invalid request: "));
      Serial.println(req);
      return;
    }
    req = req.substring(addr_start + 1, addr_end);
    Serial.print(F("Request: "));
    Serial.println(req);
    // client.flush(); 바꾸라고 함.
    client.readString();


    int sensen_light = analogRead(A0);
    Serial.print("Current intencity: ");
    Serial.println(sensen_light);
    client.print(htmlHeader);


    if(req.equals("/"))
    {
      IPAddress ip = wifi.localIP();
      String ipStr = String(ip[0]) + '.' + String(ip[1]) + '.' + String(ip[2]) + '.' + String(ip[3]);
      
      client.print("Hello from ESP8266 at ");
      client.print(ipStr);
      client.print("<br>team 20<br>*** ***<br>");

      client.print("<button onclick=\"fetch('/1')\">");
      client.print("1");
      client.print("</button>");
      client.print("<button onclick=\"fetch('/2')\">");
      client.print("2");
      client.print("</button>");
      
      client.print(onoffLink);
    }
    
    
    else if(req.equals("/info")){
      String toSend = wifi.firmwareVersion();
      toSend.replace("\r\n","<br>");
      client.print(toSend);
    }


    else if(req.equals("/team_info")) {
      client.print("<title>HTML example page</title><body size=5 bgcolor=#d90000 style=\"color:#00a500\">team 20<br>*** ***<br><a href=./>move to top</a><br><a href=./test>move to test</a></body>");
    }

    else if(req.equals("/test")) client.print("<title>HTML test page</title><body size=5 bgcolor=#0f0 style=\"color:#f0f\">team 20<br>*** ***<br><a href=./team_info>move to team_info</a></body>");

    else if(req.equals("/on")){
      digitalWrite(LED_PIN, HIGH);
      darkpage(&client, analogRead(A0)>LED_ON_THRESHOLD, true);
    }
    else if(req.equals("/off")){
      digitalWrite(LED_PIN, LOW);
      darkpage(&client, analogRead(A0)>LED_ON_THRESHOLD, false);
    }

    else if(req.equals("/1")){
      // 1번 LED 껏다키기
      digitalWrite(LED_1, LED_1_state);
      LED_1_state = !LED_1_state;
    }
    else if(req.equals("/2")){
      // 2번 LED 껏다키기
      digitalWrite(LED_2, LED_2_state);
      LED_2_state = !LED_2_state;
    }
    else client.write("404 Not Found\r\n");
    
    client.print(htmlEnd);
    client.stop();
  }
}

/*
void clientTest()
{
  const char destServer[] = "wifitest.adafruit.com";
  ESP8266Client client;
  if (!client.connect(destServer, 80))
  {
    Serial.println(F("Failed to connect to server."));
    client.stop();
    return;
  }
  
  const char *httpRequest = "GET /testwifi/index.html HTTP/1.1\r\n"
                           "Host: wifitest.adafruit.com\r\n"
                           "Connection: close\r\n\r\n";
  if(!client.print(httpRequest))
  {
    Serial.println(F("Sending failed"));
    client.stop();
    return;;
  }

  // set timeout approximately 5s for server reply
  int i=5000;
  while (client.available()<=0&&i--)
  {
    delay(1);
    if(i==1) {
      Serial.println(F("Timeout"));
      return;
      }
  }

  while (client.available()>0)
  {
    //char c = (char)client.read();
    //Serial.print(c);
    Serial.write(client.read());
  }
  
  client.stop();
}
*/