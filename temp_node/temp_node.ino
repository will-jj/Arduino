#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <Wire.h>
#include "ClosedCube_HDC1080.h"

const char* ssid = "ree";
const char* pass = "ree";
int boilPin = 1;
double temp;
int i = 1;
double humid;
ESP8266WebServer server(80);
ClosedCube_HDC1080 hdc1080;
#include <ESP8266HTTPClient.h>

void setup(void){
  Serial.begin(115200);
  Serial.println("");
  Serial.println("HELLO");
  pinMode(boilPin, OUTPUT);      // sets the digital pin as output
  WiFi.begin(ssid, pass);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 // hdc1080.begin(0x40,4,5);
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  
  server.on("/", [](){
    server.send(200, "text/plain", "Open /servo?value=90 to control servo");
  });
    
    server.on("/temp", [](){
     
    String p1 = "{\"temp\": "+String(hdc1080.readTemperature())+",\"humid\":"+String(hdc1080.readHumidity())+"}";
    server.send(200, "text/plain", p1);
  });

  

  server.begin();
  Serial.println("HTTP server started");
  

}
 
void loop(void){
  if (i == 1){
  HTTPClient http;
  http.begin("http://192.168.1.70:8080/rest/items/Second_Temp");
  http.addHeader("Content-Type: text/plain", "Accept: application/json");
  http.POST("15.5");
  http.writeToStream(&Serial);
  http.end();}
  
  i = 10;
  //server.handleClient();
} 
