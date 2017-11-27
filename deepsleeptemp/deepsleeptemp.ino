#include <ESP8266WiFi.h>
#include <Wire.h>
#include "ClosedCube_HDC1080.h"
#include  "Openhab.h"
const char* ssid = "ree";
const char* pass = "ree";

const char* host = "192.168.ree.ree";
const int port = 8080;

static const uint8_t sensVDD   = 14; //D5

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

void setup(void) {
  pinMode(sensVDD, OUTPUT);      // sets the digital pin as output
  digitalWrite(sensVDD, HIGH);
  WiFi.mode(WIFI_STA);
  Serial.begin(115200);
  Serial.println("");
  Serial.println("meme");
  WiFi.begin(ssid, pass);

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  hdc1080.begin(0x40, 4, 5); //D1 - SCL D2 - SDA 
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  sendToOpenHab(String(hdc1080.readTemperature()));
  sendToOpenHabH(String(hdc1080.readHumidity()));
  digitalWrite(sensVDD, LOW); // turn off sensor super low power achieved?
  ESP.deepSleep(3e8); // 3e8 is 5 min D0-RST (for wake)


}

void loop(void) {


}
