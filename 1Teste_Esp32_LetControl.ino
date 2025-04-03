#include <WiFi.h>
#include <WiFiUdp.h>
#include <HTTPClient.h>

WiFiClient client;

const char *ssid = "HOME";
const char *pass = "1234";
String ip = "";
String site = "http://"+ip+"/fluxo_agua/dados.php?"; 

#define SENSOR_PIN 2

volantile int pulseCont = 0;
float flowRate = 0.0;
float totalLiters = 0.0;

void IRAM_ATTR pulseCounter(){
  pulseCont++;
}
void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WIFI.bengin(ssid,pass);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi Conectado")
  Serial.println("Endereço IP:  ");
  Serial.println(WiFi.LocalIP());

  pinMode(SENSOR_PIN, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), pulseConter, FALLING);

}

void loop() {
  // put your main code here, to run repeatedly:
  detachInterrupt(SENSOR_PIN);
  float flowRate = (pulseCont / 7.5);
  totalLiters += (flowRate /60.0);
  pulseCount = 0;
  attachInterrupt(digitalPinToInterrupt(SENSOR_PIN), pulseCounter, FALLING);
  Serial.print("Vazão: ");
  Serial.print(flowRate);
  Serial.println("L/min");
  Serial.print("Total de Litros: ");
  Serial.println(totalLiters);

  String parametros = site + "&vazao" + String(flowRate) + "&total_litros=" + String(totalliters);
  HTTPClient http;
  http.begin(parametros);
  int httpCode = http.GET();
  Serial.println("Código HTTP:" + String(httpCode));
  http.end();
  delay(10000)

}
