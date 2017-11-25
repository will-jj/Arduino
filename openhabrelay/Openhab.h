/**
 * Openhab.h
 *
 * https://github.com/Br3nda/openhab-rest-esp8266 
 */

#ifndef Openhab_h
#define Openhab_h

#include "Arduino.h"
#include "ESP8266WiFi.h"


class Openhab {

  public:
    Openhab(const char* host, const int port);

    String url(String item);

    String get(String item);
    String put(String item, String state);

    String send(String request);

  private:
    const char* _host;
    int    _port;
    String _params;
 
};

#endif
