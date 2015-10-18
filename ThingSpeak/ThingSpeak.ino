#include <SoftwareSerial.h>

#define AP_SSID     F("<El Nombre de su WiFi>")
#define AP_PASS     F("<Su clave de la WiFi>")

#define TS_HOST     F("api.thingspeak.com")
#define TS_PORT     80
#define TS_API_KEY  F("<Su API_KEY>")

#define RX_ARDUINO  10      // TX en ESP8266
#define TX_ARDUINO  11      // RX en ESP8266

SoftwareSerial esp8266(RX_ARDUINO, TX_ARDUINO);

void setup()
{
  Serial.begin(9600);   // para depurar
  while (!Serial){      // para el caso de placas Leonardo
  }

  // utilizamos el firmware AT v0.50 SDK 1.4.0_150918 - noboot
  // el firmware fue configurado como AT+UART_DEF=9600,8,1,0,0
  esp8266.begin(9600);
  esp8266_init();
}

void loop()
{
  // obtiene el valor de los sensores
  int value1 = random(-100, 100);
  int value2 = random(200, 300);

  // Necesitamos todo como string
  String value = F("field1=");
  value += value1;
  value += F("&field2=");
  value += value2;
  
  String post = "POST /update HTTP/1.1\n";
  post += F("Host: ");
  post += TS_HOST;
  post += F("\n");
  post += F("Connection: close\n");
  post += F("X-THINGSPEAKAPIKEY: ");
  post += TS_API_KEY;
  post += F("\n");
  post += F("Content-Type: application/x-www-form-urlencoded\n");
  post += F("Content-Length: ");
  post += value.length();
  post += F("\n\n");
  post += value;  

  Serial.println(post);
  Serial.flush();
  
  // lo enviamos a ThingSpeak
  esp8266.print(F("AT+CIPSTART=\"TCP\",\""));
  esp8266.print(TS_HOST);
  esp8266.print(F("\","));
  esp8266.print(TS_PORT);
  esp8266.print(F("\r\n"));
  esp8266_clearInput(3000);

  esp8266.print(F("AT+CIPSEND="));
  esp8266.print(post.length());
  esp8266.print(F("\r\n"));
  esp8266_clearInput(300);
  esp8266.print(post);
  esp8266_clearInput(3000);

  delay(10000);
}

void esp8266_init(){
  esp8266_clearInput(1000);
  esp8266.print(F("AT+RST\r\n"));
  esp8266_clearInput(1000);
  //esp8266.print(F("ATE0\r\n"));
  //esp8266_clearInput(100);
  esp8266.print(F("AT+CWMODE=1\r\n"));
  esp8266_clearInput(300);
  esp8266.print(F("AT+CWJAP_CUR=\""));
  esp8266.print(AP_SSID);
  esp8266.print(F("\",\""));
  esp8266.print(AP_PASS);
  esp8266.print(F("\"\r\n"));
  esp8266_clearInput(8000);
  esp8266.print(F("AT+CIPSTA_CUR?\r\n"));
  esp8266_clearInput(2000);
  esp8266.print(F("AT+CIPMUX=0\r\n"));
  esp8266_clearInput(2000);
}

void esp8266_clearInput(int ms){
  byte ch;
  unsigned long t = millis() + ms;
  while((long)(millis() - t)<0){
    if(esp8266.available()){
      ch = esp8266.read();
      Serial.write(ch);
    }
  }
}

