// ESP8266 Timer Example
// SwitchDoc Labs  October 2015 has been incorperated into this file
// Openhab rest example also incorperated https://github.com/Br3nda/openhab-rest-esp8266 

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



extern "C" {
#include "user_interface.h"
}

os_timer_t myTimer;

bool tickOccured;

// start of timerCallback
void timerCallback(void *pArg) {

      tickOccured = true;

} // End of timerCallback

void user_init(void) {
 /*
  os_timer_setfn - Define a function to be called when the timer fires

void os_timer_setfn(
      os_timer_t *pTimer,
      os_timer_func_t *pFunction,
      void *pArg)

Define the callback function that will be called when the timer reaches zero. The pTimer parameters is a pointer to the timer control structure.

The pFunction parameters is a pointer to the callback function.

The pArg parameter is a value that will be passed into the called back function. The callback function should have the signature:
void (*functionName)(void *pArg)

The pArg parameter is the value registered with the callback function.
*/

      os_timer_setfn(&myTimer, timerCallback, NULL);

/*
      os_timer_arm -  Enable a millisecond granularity timer.

void os_timer_arm(
      os_timer_t *pTimer,
      uint32_t milliseconds,
      bool repeat)

Arm a timer such that is starts ticking and fires when the clock reaches zero.

The pTimer parameter is a pointed to a timer control structure.
The milliseconds parameter is the duration of the timer measured in milliseconds. The repeat parameter is whether or not the timer will restart once it has reached zero.

*/

      os_timer_arm(&myTimer, 5000, true);
} // End of user_init




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

  tickOccured = false;
  user_init();

}

void loop(void) {
if (tickOccured == true)
 {

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

 yield();





}
