#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "ree";
const char* pass = "ree";
int boilPin = 1;
ESP8266WebServer server(80);

void setup(void){
  Serial.begin(115200);
  Serial.println("");
  pinMode(boilPin, OUTPUT);      // sets the digital pin as output
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
  
  server.on("/", [](){
    server.send(200, "text/plain", "Open /servo?value=90 to control servo");
  });

    server.on("/temp", [](){
    String p1 = "{ \"device\": { \"status\": { \"temperature\": "+String(random(20,25))+"}}}";
    server.send(200, "text/plain", p1);
  });

  server.on("/servo", [](){
    String sval = server.arg("value");
    int ival = sval.toInt();
    Serial.print("Servo: ");
    Serial.println(ival);
    myservo.write(ival);
    server.send(200, "text/plain", String(ival, DEC));
  });

  server.begin();
  Serial.println("HTTP server started");
  
  myservo.attach(D5);   // Servo attached to D5 pin on NodeMCU board
  myservo.write(0);
}
 
void loop(void){
  server.handleClient();
} 
