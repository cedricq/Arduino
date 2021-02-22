int pressureSensorPin = A0;    
int flowSensorPin = A1;    
int controlFilteredPin = A2;  
int potarPin = A3;
int speedPin = A4;

int controlPin = 5;   

#define P_MIN     0.0      
#define P_MAX     68.9476  // 1 psi in mbar
#define RAW_MAX   1023     // ADC 10 bits : 2^10 - 1
#define MAX_MEASURED_SPEED  60000.0   // Max measurable speed in rpm

bool led_state = true;
int ledPin = 13;           // select the pin for the LED

float maxon_convertToRPM(int raw, int raw_max, float speed_max)
{
  return ( (float)raw * speed_max ) / raw_max ;
}

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
  int controlFiltered = analogRead(controlFilteredPin) ;
  
  int potar = analogRead(potarPin) ;
  unsigned int output = map(potar, 0, 1023, 0, 255) ;
  analogWrite(controlPin, output) ;

  int rawSpeed = analogRead(speedPin) ;
  float speedRPM = maxon_convertToRPM(rawSpeed, RAW_MAX * 4 / 5, MAX_MEASURED_SPEED) ;
  
  int rawFlow = analogRead(flowSensorPin) ;
  float flowLmin = sensirion_convertToLMin(rawFlow, RAW_MAX);

  int rawPressure = analogRead(pressureSensorPin) ;
  float pressureMbar = honeywell_convertToPressure(rawPressure, P_MIN, P_MAX, RAW_MAX);

  Serial.print(flowLmin);
  Serial.print("\t");
  Serial.print(pressureMbar);
  Serial.print("\t");
  Serial.print(speedRPM);
  Serial.print("\n");
  
  // turn the ledPin on
  toggle_pin(ledPin);

  delay(100);
}
