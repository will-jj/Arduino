#include <ESP8266WiFi.h>

#include  "Openhab.h"
const char* ssid = "ree";
const char* pass = "ree";
static const uint8_t boilPin   = 14; //D5

const char* host = "192.168.ree.ree";
const int port = 8080;
String response;
int retry = 0;
String item_boil = "boiler";
String item_boil_conf = "boiler_confirm";

Openhab hab = Openhab(host, port);
void getFromOpenHab() {
  Serial.print("Getting from hab\n");
  response = hab.get(item_boil);

}

void sendToOpenHab(String value) {
  Serial.print("Sending to hab\n");
  hab.put(item_boil_conf, value);
}

void setup(void) {
  pinMode(boilPin, OUTPUT);      // sets the digital pin as output
  digitalWrite(boilPin, HIGH);

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

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

}

void loop(void) {
  delay(5000);

  if (WiFi.status() == WL_CONNECTED) {
    getFromOpenHab();

    if (response == "ON") {
      digitalWrite(boilPin, LOW); //active low also
      sendToOpenHab("ON");
      retry = 0;
    }
    else if (response == "OFF")
    {
      digitalWrite(boilPin, HIGH); //active low also
      sendToOpenHab("OFF");
      retry = 0;
    }
    else {
      retry = retry + 1;
    }

    if (retry > 5) {
      digitalWrite(boilPin, HIGH); //active low also
      sendToOpenHab("OFF");
    }


  }
  
  else {
    digitalWrite(boilPin, HIGH); //active low also


  }





}
