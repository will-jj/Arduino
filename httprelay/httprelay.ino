#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "ree";
const char* pass = "ree";
ESP8266WebServer server(80);
static const uint8_t boilPin   = 14; //D5
void setup(void) {
  Serial.begin(115200);
  Serial.println("");
  pinMode(boilPin, OUTPUT);      // sets the digital pin as output
      WiFi.mode(WIFI_STA);

  WiFi.begin(ssid, pass);
   //Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  digitalWrite(boilPin, HIGH);

  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", []() {
    server.send(200, "text/plain", "Open /servo?value=90 to control servo");
  });

  server.on("/temp", []() {
    String p1 = "{ \"device\": { \"status\": { \"temperature\": " + String(random(20, 25)) + "}}}";
    server.send(200, "text/plain", p1);
  });

  server.on("/servo", []() {
    String sval = server.arg("value");
    int ival = sval.toInt();
    Serial.print("Servo: ");
    Serial.println(ival);
    if (ival==1) 
    {
      digitalWrite(boilPin, LOW); //active low also
      digitalWrite(LED_BUILTIN, LOW); //led active low 
    }
    else {
      digitalWrite(boilPin, HIGH); //active low also
       digitalWrite(LED_BUILTIN, HIGH); //led active low  
    }
  
  server.send(200, "text/plain", String(ival, DEC));
  
});

server.begin();
Serial.println("HTTP server started");

}

void loop(void) {
  //new if statement to hopefully fix the disconnect issues
  if (WiFi.status() != WL_CONNECTED){
    WiFi.begin(ssid,pass);
    Serial.print("r");
    while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print("e");
  }
  }
  server.handleClient();
}
