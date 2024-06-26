#ifndef SNP_LIGHT_H
#define SNP_LIGHT_H

#include "Arduino.h"
#if defined(__AVR__) || defined(__ESP8266__)
#include <SoftwareSerial.h>
#endif // #if defined(__AVR__) || defined(__ESP8266__)

#define NO_DE_PIN 255

class SNP_Light
{
public:
  SNP_Light(uint8_t rxPin, uint8_t txPin, uint8_t dePin = NO_DE_PIN);
  void begin(void);
  uint32_t read(void);

private:
  uint8_t _rxPin;
  uint8_t _txPin;
  uint8_t _dePin;
#if defined(__AVR__) || defined(__ESP8266__)
  SoftwareSerial *_softwareSerial;
#endif // #if defined(__AVR__) || defined(__ESP8266__)
  Stream *_serial;
  uint32_t _charTimeout;
  uint32_t _frameTimeout;
};

#endif // SNP_LIGHT_H
