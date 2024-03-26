#ifndef SNP_LIGHT_H
#define SNP_LIGHT_H

#include "Arduino.h"
#include <SoftwareSerial.h>

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
  SoftwareSerial *_softwareSerial;
  Stream *_serial;
  uint32_t _charTimeout;
  uint32_t _frameTimeout;
};

#endif // SNP_LIGHT_H
