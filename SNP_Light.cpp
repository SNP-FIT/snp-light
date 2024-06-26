#include "Arduino.h"
#include "SNP_Light.h"

SNP_Light::SNP_Light(uint8_t rxPin, uint8_t txPin, uint8_t dePin)
{
  _rxPin = rxPin;
  _txPin = txPin;
  _dePin = dePin;
}

void SNP_Light::begin(void)
{
  if (_dePin != NO_DE_PIN)
  {
    pinMode(_dePin, OUTPUT);
    digitalWrite(_dePin, LOW);
  }

#if defined(__AVR__) || defined(__ESP8266__)
  _softwareSerial = new SoftwareSerial(_rxPin, _txPin);
  _serial = _softwareSerial;
  _softwareSerial->begin(9600);

#elif defined(ESP32)
  Serial1.begin(9600, SERIAL_8N1, _rxPin, _txPin);
  _serial = &Serial1;
#endif // #if defined(__AVR__) || defined(__ESP8266__)

  _charTimeout = (10 * 2500000) / 9600;
  _frameTimeout = (10 * 4500000) / 9600;
}

uint32_t SNP_Light::read(void)
{
  uint8_t buf[8] = {0x02, 0x04, 0x00, 0x00, 0x00, 0x02, 0x71, 0xf8};
  if (_dePin != NO_DE_PIN)
    digitalWrite(_dePin, HIGH);
  _serial->write(buf, 8);
  _serial->flush();
  if (_dePin != NO_DE_PIN)
    digitalWrite(_dePin, LOW);

  uint8_t readBuf[10];
  uint16_t numBytes = 0;
  uint32_t startTime = 0;
  do
  {
    if (_serial->available())
    {
      startTime = micros();
      readBuf[numBytes] = _serial->read();
      numBytes++;
    }
  } while (micros() - startTime <= _charTimeout && numBytes < 10);
  while (micros() - startTime < _frameTimeout)
    ;
  // ID | FUNC | SIZE | MID-LOW | LOW | HIGH | MID-HIGH | CRC-LOW | CRC-HIGH
  // --> uint32_t lux : HIGH | MID-HIGH | MID-LOW | LOW
  uint32_t lux = ((uint32_t)readBuf[5] << 24) | ((uint32_t)readBuf[6] << 16) |
                 ((uint32_t)readBuf[3] << 8) | ((uint32_t)readBuf[4]);

  while (_serial->available())
  {
    _serial->read();
  }

  return lux;
}
