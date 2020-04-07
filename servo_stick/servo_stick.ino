#include <Servo.h>
Servo servo;

const int MIN_X = 515; // measured middle position on vertical axis
const int MAX_X = 980; // measured top position on vertical axis

const int MOTOR_CMD_PIN = 8;
const int X_IN = A1;                                                                                            

int raw_x_pos;
int x_pos;

void setup() {
  servo.attach( MOTOR_CMD_PIN ) ;
  servo.write( 0 );
  
  pinMode( X_IN, INPUT ) ;                     

  Serial.begin( 115200 );
  while ( !Serial ) {
    ; // wait for serial port to connect. Needed for Native USB only
  }
}

void loop() {
  raw_x_pos = analogRead ( X_IN ) ;  

  // Clamping to calibrated values
  if ( raw_x_pos < MIN_X ) x_pos = MIN_X;
  if ( raw_x_pos > MAX_X ) x_pos = MAX_X;
  
  int cmd = map( x_pos, MIN_X, MAX_X, 50, 150 );

  servo.write ( cmd ) ;
  
  Serial.print( "Read stick X: " ); Serial.print( raw_x_pos );
  Serial.print( " - Corrected stick X: " ); Serial.print( x_pos );
  Serial.print( " - Motor Command: " ); Serial.print( cmd );
  Serial.println( "");

  delay (60) ;
}
