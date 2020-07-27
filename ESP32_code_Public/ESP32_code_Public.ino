//ESP32s with Blynk
#define BLYNK_PRINT Serial
#define humid1 A6 //pin34
#define humid2 A7 //pin35
#define pump 32
#define Humid_value 0 //set humid value in EEProm address 0

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <EEPROM.h>

char auth[] = "YOUR AUTH";
char ssid[] = "YOUR WIFI NAME";
char pass[] = "YOUR WIFI PASSWORD";
char server[] = "YOUR IP BLYNK SERVER";
int a,b,humid_pump,time_delay ;

void setup() {
  EEPROM.begin(200);
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 5000 );
    Serial.print ( "." );
  }
  Blynk.begin(auth, ssid, pass, server, 8080);
  
  pinMode(pump,OUTPUT);
  pinMode(humid1,INPUT);
  pinMode(humid2,INPUT);
  a=0;b=0;
  digitalWrite(pump,HIGH);
  EEPROM.get(Humid_value,humid_pump);
  Serial.println(humid_pump);
}



void loop() {
  Blynk.run();
  a =map(analogRead(humid1),1500,3500,100,0);
  b =map(analogRead(humid2),1500,3500,100,0);
  Blynk.virtualWrite(V0,a);
  Blynk.virtualWrite(V1,b);

  delay(2000);

  if (WiFi.status() != WL_CONNECTED){
    ESP.restart();
  }
}


BLYNK_WRITE(V2){
    humid_pump = param.asInt();
    Serial.println(humid_pump);
    EEPROM.put( Humid_value, humid_pump);
    EEPROM.commit();
    Serial.println(humid_pump);
}

BLYNK_WRITE(V3) {
  int status_pump = param.asInt();
  if (status_pump == 1) {

    while ((a + b) / 2 < humid_pump) {
      digitalWrite(pump, LOW);
      a = map(analogRead(humid1), 1500, 3500, 100, 0);
      b = map(analogRead(humid2), 1500, 3500, 100, 0);
      //delete /* and */ to activate realtime monitoring
      /*Blynk.virtualWrite(V0, a);
      Blynk.virtualWrite(V1, b);*/
      delay(100);
    }
    digitalWrite(pump, HIGH);
    ESP.restart();
  } else {
    digitalWrite(pump, HIGH);
  }
}

BLYNK_WRITE(V4) {
  int status_pump = param.asInt();
  if (status_pump == 1) {

    while ((a + b) / 2 < humid_pump) {
      digitalWrite(pump, LOW);
      a = map(analogRead(humid1), 1500, 3500, 100, 0);
      b = map(analogRead(humid2), 1500, 3500, 100, 0);
      //delete /* and */ to activate realtime monitoring
      /*Blynk.virtualWrite(V0, a);
      Blynk.virtualWrite(V1, b);*/
      delay(100);
    }
    digitalWrite(pump, HIGH);
    ESP.restart();
  } else {
    digitalWrite(pump, HIGH);
  }
}
