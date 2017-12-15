/*
  Analog input, analog output, serial output

 Reads an analog input pin, maps the result to a range from 0 to 255
 and uses the result to set the pulsewidth modulation (PWM) of an output pin.
 Also prints the results to the serial monitor.

 The circuit:
 * potentiometer connected to analog pin 0.
   Center pin of the potentiometer goes to the analog pin.
   side pins of the potentiometer go to +5V and ground
 * LED connected from digital pin 9 to ground

 created 29 Dec. 2008
 modified 9 Apr 2012
 by Tom Igoe

 This example code is in the public domain.

 */

// These constants won't change.  They're used to give names
// to the pins used:
const int analogOutPin0 = 10; 
const int analogOutPin1 = 9;
unsigned long previousMillis = 0;        // will store last time LED was updated

// constants won't change :
const long interval = 1000;           // interval UART out

unsigned long previousMillis1 = 0;        // will store last time LED was updated

// constants won't change :
const long interval1 = 9;           // interval read ADC

double sensorValue0 = 0;        // value read from the pot
double sensorValue1 = 0;        // value read from the pot
double meanPercent = 0.01;
int powerValue = 0;        // value output to the PWM (analog out)

void setup() {
  // initialize serial communications at 9600 bps:
  //pinMode(analogOutPin0, OUTPUT);  
  //pinMode(analogOutPin1, OUTPUT);  
  Serial.begin(115200);
  analogReference(INTERNAL);
  analogWrite(analogOutPin0, 0);
  analogWrite(analogOutPin1, 0); 
//  analogReference(EXTERNAL);
}

void loop() {
  // read the analog in value:
  unsigned long currentMillis = millis(), fraq0, fraq1;

  if (currentMillis - previousMillis1 >= interval1) {
    previousMillis1 = currentMillis;

    sensorValue0 = sensorValue0*(1-meanPercent) + (double(analogRead(A0))*1100/11.5/41.984+20)*meanPercent;
    sensorValue1 = sensorValue1*(1-meanPercent) + (double(analogRead(A1))*1100/11.5/41.984+20)*meanPercent;
  }
  
  if (currentMillis - previousMillis >= interval) {
    // save the last time you blinked the LED
    previousMillis = currentMillis;
    
//    sensorValue0 = double(analogRead(A0))*1100/11.5/41.984+20;
    //sensorValue1 = double(analogRead(A1))*1100/11.5/41.984+20;


//    analogWrite(analogOutPin, outputValue);

    // print the results to the serial monitor:
    fraq0 = long((sensorValue0-floor(sensorValue0))*10);
    fraq1 = long((sensorValue1-floor(sensorValue1))*10);
    Serial.print("T1 ");
 
    Serial.print(long(sensorValue0), DEC);
    Serial.print(".");
    Serial.print(fraq0, DEC);
    Serial.print(" C. ");
    Serial.print("T2 ");
    Serial.print(long(sensorValue1), DEC);
    Serial.print(".");
    Serial.print(fraq1, DEC);
    Serial.print(" C. ");
    Serial.print("Power ");
    Serial.print(long(powerValue), DEC);
    Serial.print(". ");

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  }  
  if (Serial.available() > 0) {
    // get incoming byte:
    if( Serial.read()=='P')
    {
    // read first analog input, divide by 4 to make the range 0-255:
      powerValue = Serial.parseInt();
      Serial.print("Yep! ");
//    Serial.print("powerValue = ");
      Serial.print("New power value is ");
      Serial.print(long(powerValue), DEC);
      Serial.print(". ");
      analogWrite(analogOutPin0, powerValue);
      analogWrite(analogOutPin1, powerValue);      }
  }
}
