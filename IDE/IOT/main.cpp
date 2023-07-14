//----------------------Skeleton Code--------------------//
#include <WiFi.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

//    Can be client or even host   //
#ifndef STASSID
#define STASSID "EDITH007"  // Replace with your network credentials
#define STAPSK  "surya123"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;


void OTAsetup() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    delay(5000);
    ESP.restart();
  }
  ArduinoOTA.begin();
}

void OTAloop() {
  ArduinoOTA.handle();
}

//-------------------------------------------------------//
bool F;
bool a0 = 0, a1 = 0, b0 = 0, b1 = 0;
void setup(){
  OTAsetup();

  //-------------------//
  // Custom setup code //
  //-------------------//
  pinMode(2, INPUT);   
  pinMode(4, INPUT);   
  pinMode(6, INPUT);
  pinMode(8, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  OTAloop();
  delay(10);  // If no custom loop code ensure to have a delay in loop
  //-------------------//
  // Custom loop code  //
  //-------------------//
  /*digitalWrite(2, HIGH);   
  digitalWrite(4, HIGH);   
  digitalWrite(5, HIGH);   
  delay(100);
  digitalWrite(2, LOW);   
  digitalWrite(4, LOW);   
  digitalWrite(5, LOW);   
  delay(100);*/// put your main code here, to run repeatedly:
  a0 = digitalRead(2);
  a1 = digitalRead(4);
  b0 = digitalRead(6);
  b1 = digitalRead(8);
  digitalWrite(13, LOW);

  F = (a1&&!b1)||(a1&&a0&&!b0)||(a0&&!b0&&!b1);

  if(F == 1)
  {
	digitalWrite(13, HIGH);
  }
  else
  {
	digitalWrite(13, LOW);
  }
}
