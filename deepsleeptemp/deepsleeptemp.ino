#include <ESP8266WiFi.h>
//#include <ESP8266WebServer.h>
#include <Wire.h>
#include "ClosedCube_HDC1080.h"
//#include <ESP8266HTTPClient.h>
#include  "Openhab.h"
const char* ssid = "reeee";
const char* pass = "reeee";

const char* host = "192.168.ree.ree";
const int port = 8080;


String item_name = "Second_Temp";
String item_hum = "Second_Hum";

Openhab steve = Openhab(host, port);

void sendToOpenHab(String value) {
  String response = steve.put(item_name, value);
  Serial.print(response);
}

void sendToOpenHabH(String value) {
  String response = steve.put(item_hum, value);
  Serial.print(response);
}

double temp;

double humid;
ClosedCube_HDC1080 hdc1080;

void setup(void){
    WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  Serial.println("");
  Serial.println("meme");
//  pinMode(boilPin, OUTPUT);      // sets the digital pin as output
  WiFi.begin(ssid, pass);
  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  hdc1080.begin(0x40,4,5);
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
//  
//  server.on("/", [](){
//    server.send(200, "text/plain", "Open /servo?value=90 to control servo");
//  });
//    
//    server.on("/temp", [](){
//     
//    String p1 = "{\"temp\": "+String(hdc1080.readTemperature())+",\"humid\":"+String(hdc1080.readHumidity())+"}";
//    server.send(200, "text/plain", p1);
//  });
//
//  
//
//  server.begin();
//  Serial.println("HTTP server started");
  
  sendToOpenHab(String(hdc1080.readTemperature()));
    sendToOpenHabH(String(hdc1080.readHumidity()));

  ESP.deepSleep(3e8); // 20e6 is 20 microseconds



}
 
void loop(void){
  //server.handleClient();
//  http.begin("http://192.168.1.70:8080/rest/items/Second_Temp");
//  http.addHeader("Content-Type: text/plain", "application/json");
//  http.POST("16.6");
//  http.writeToStream(&Serial);
//  http.end();

  
} 
