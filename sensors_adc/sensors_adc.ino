int flowSensorPin = A0;    
int pressureSensorPin = A1;    

#define P_MIN     0.0      
#define P_MAX     68.9476  // 1 psi in mbar
#define RAW_MAX   1023     // ADC 10 bits : 2^10 - 1

bool led_state = true;
int ledPin = 13;           // select the pin for the LED

float sensirion_convertToLMin(int raw, int raw_max)
{
  return (212.5F * ( ((float)raw / raw_max) - 0.1 ) ) - 10 ;
}


float honeywell_convertToPressure(unsigned int raw, float pmin, float pmax, int raw_max)
{
  return ( ( pmax - pmin ) * ( raw - 0.1f * raw_max ) / ( 0.8f * raw_max ) ) + pmin ;
}

void toggle_pin(int pin_id){
  if (digitalRead(pin_id) == HIGH  )
    digitalWrite(ledPin, LOW);
  else
    digitalWrite(ledPin, HIGH);  
} 

void setup() 
{
  Serial.begin(9600);
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
}

void loop() 
{ 
  int rawFlow = analogRead(flowSensorPin) ;
  float flowLmin = sensirion_convertToLMin(rawFlow, RAW_MAX);

  int rawPressure = analogRead(pressureSensorPin) ;
  float pressureMbar = honeywell_convertToPressure(rawPressure, P_MIN, P_MAX, RAW_MAX);

  Serial.print("Raw flow : "); 
  Serial.print("0x");
  Serial.print(rawFlow, HEX); 
  Serial.print("   \tFlow (L/min) : "); 
  Serial.print(flowLmin);

  Serial.print("\t\tRaw pressure : "); 
  Serial.print("0x");
  Serial.print(rawPressure, HEX); 
  Serial.print("   \tPressure (mbar) : "); 
  Serial.println(pressureMbar);
  
  // turn the ledPin on
  toggle_pin(ledPin);

  delay(100);
}
