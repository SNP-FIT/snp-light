#include <SNP_Light.h>

#define RX_PIN 10
#define TX_PIN 11

SNP_Light snpLight(RX_PIN, TX_PIN, NO_DE_PIN);
uint32_t lux = 0;

void setup()
{
  Serial.begin(9600);

  snpLight.begin();
}

void loop()
{
  delay(2000);

  lux = snpLight.read();
  Serial.print("lux = ");
  Serial.println(lux);
}
