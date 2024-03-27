#include <SNP_Light.h>

#define RO_PIN 10
#define DI_PIN 11
#define DE_PIN 7

SNP_Light snpLight(RO_PIN, DI_PIN, DE_PIN);
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
