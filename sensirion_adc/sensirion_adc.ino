int sensorPin = A0;    // select the input pin for the potentiometer
int ledPin = 13;      // select the pin for the LED
int sensorRawValue = 0;  // variable to store the value coming from the sensor
int sensorFlowValue = 0;  // variable to store the value coming from the sensor
bool led_state = true;

float convertToLMin(int raw){
    return (212.5F * ( ((float)raw / 5.0F) - 1 ) ) - 10 ;

}

void toggle_pin(int pin_id){
  if (digitalRead(pin_id) == HIGH  )
    digitalWrite(ledPin, LOW);
  else
    digitalWrite(ledPin, HIGH);  
} 

void setup() {
  Serial.begin(9600);
  // declare the ledPin as an OUTPUT:
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // read the value from the sensor:
  sensorRawValue = analogRead(sensorPin);
  sensorFlowValue = convertToLMin(sensorRawValue);

  Serial.print(sensorRawValue); 
  Serial.print('\t'); 
  Serial.println(sensorFlowValue);
  
  // turn the ledPin on
  toggle_pin(ledPin);
  
  delay(100);
}
