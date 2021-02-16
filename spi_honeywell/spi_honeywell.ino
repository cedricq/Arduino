#include <SPI.h>

#define SENSOR_CS 4

#define P_MIN     -68.9476      
#define P_MAX     68.9476  // 1 psi in mbar
#define RAW_MAX   16000    // ADC 15 bits ??

SPISettings spi_settings(2000000, MSBFIRST, SPI_MODE0);


float honeywell_convertToPressure(unsigned int raw, float pmin, float pmax, int raw_max)
{
  return ( ( pmax - pmin ) * ( raw - 0.1f * raw_max ) / ( 0.8f * raw_max ) ) + pmin ;
}

void setup() 
{
  Serial.begin(9600);

  pinMode (SENSOR_CS, OUTPUT);
  
  SPI.begin();  
}

void loop() 
{
  SPI.beginTransaction(spi_settings);
  digitalWrite (SENSOR_CS, LOW);
  
  unsigned int byte1 = SPI.transfer(0); 
  unsigned int byte2 = SPI.transfer(0);

  digitalWrite (SENSOR_CS, HIGH);
  SPI.endTransaction();

  unsigned int raw = byte1 * 256 + byte2;

  float pressureMbar = honeywell_convertToPressure(raw, P_MIN, P_MAX, RAW_MAX);
  
  Serial.print("Byte1 : "); 
  Serial.print(byte1); 
  Serial.print("\tByte2 : "); 
  Serial.print(byte2); 
  Serial.print("\tRaw : "); 
  Serial.print(raw);  
  Serial.print("\tPressure : "); 
  Serial.println(pressureMbar);  
}
