/**
 * Openhab.cpp
 *
 * https://github.com/Br3nda/openhab-rest-esp8266 
 */

#include "Arduino.h"
#include "ESP8266WiFi.h"
#include "Openhab.h"

#ifdef ARDUINO_ARCH_AVR
#include <avr/pgmspace.h>
#else
#include "pgmspace.h"
#endif

Openhab::Openhab(const char* host, const int port) {
  _host = host;
  _port = port;
  _params = "";
}

String Openhab::url(String item) {

  String result = "http://" + (String)_host + ":" + (String)_port + "/rest/items/" + item + "/state";
  _params = "";
  return result;

}

String Openhab::get(String item) {
  String url = Openhab::url(item);
  String request = "GET " + url +"\n";+ " HTTP/1.1\n";
  //request += "Host: " + (String)_host + "\n";
  //request += "Connection: close\n";

  return Openhab::send(request);
 }

String Openhab::put(String item, String state) {
  String url = Openhab::url(item);
  
  String request = "PUT " + url + " HTTP/1.1\n";
  request += "Host: " + (String)_host + "\n";

  int state_length = state.length();
  request += "Content-Length: " + (String) state_length + "\n";

  request += "Connection: close\n";
  request += "\n";

  request += state;
                   
  return Openhab::send(request);
}

String Openhab::send(String request) {
  WiFiClient client;
  if (!client.connect(_host, _port)) {
    return "ERROR: failed to connect";
    Serial.print("ree");
  }

  client.print(request);
  delay(30);

  String response;  
  while(client.available()){
    
    response += client.readStringUntil('\r');
    
  }
  return response;
}
