
static const uint8_t boilPin   = 14; //D5
void setup(void) {
  Serial.begin(115200);
  Serial.println("");
  pinMode(boilPin, OUTPUT);      // sets the digital pin as output

  digitalWrite(boilPin, HIGH);

 


}

void loop(void) {
  digitalWrite(boilPin,LOW);
  delay(1000);
  digitalWrite(boilPin,HIGH);
  delay(1000);

}
