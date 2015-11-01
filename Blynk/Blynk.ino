
// Requerido por Blynk
//#define BLYNK_DEBUG
#define BLYNK_PRINT Serial

#include <ESP8266_SoftSer.h>
#include <BlynkSimpleShieldEsp8266_SoftSer.h>
#include <SoftwareSerial.h>
#include <SimpleTimer.h>

SimpleTimer timer;
SoftwareSerial EspSerial(10, 11); // RX, TX
ESP8266 wifi(EspSerial);
char auth[] = "auth token";

// Requerido por sensor DHT
#include "DHT.h"
#define DHTPIN 2
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // inicializamos para debug
  Serial.begin(9600);
  while(!Serial);

  // inicializamos el LED
  pinMode( 13, OUTPUT);

  // inicializamos el ESP8266
  EspSerial.begin(9600);
  delay(1000);

  // inicializamos el sensor DHT
  dht.begin();

  // inicializamos Blynk
  Blynk.begin(auth, wifi, "ssid", "pass");
  
  // Enviamos los datos cada 2 segundos (ajustar segun cada sensor DHT)
  timer.setInterval(5000L, sendData);
}

void loop()
{
  Blynk.run();
  timer.run();
}

void sendData() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Chequeamos si alguna lectura falla
  if (isnan(h) || isnan(t)) {
    //Serial.println("Error al leer el sensor DHT");
    return;
  }

  // Heat Index - Celsius
  float hic = dht.computeHeatIndex(t, h, false);

  Serial.println("Enviando data...");
  Serial.println(h);
  Serial.println(t);
  Serial.println(hic);
  
  Blynk.virtualWrite(V1, h);
  Blynk.virtualWrite(V2, t);
  Blynk.virtualWrite(V3, hic);
}
