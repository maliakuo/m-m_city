/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-light-sensor
 */

#include <Stepper.h>

#define LIGHT_SENSOR_PIN 26 // ESP32 pin GIOP36 (ADC0)
#define IN1 17
#define IN2 5
#define IN3 18
#define IN4 19
// the number of the LED pin
const int ledPin = 16;  // 16 corresponds to GPIO16
const int ledPin2 = 32;  
const int ledPin3 = 14;  


const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution

// initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);


// setting PWM properties
const int freq = 5000;
const int ledChannel = 0;
const int resolution = 8;
 

void setup() {
  // initialize serial communication at 9600 bits per second:
  // configure LED PWM functionalitites
  ledcSetup(ledChannel, freq, resolution);

  myStepper.setSpeed(15);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(ledPin, ledChannel);
  ledcAttachPin(ledPin2, ledChannel);
  ledcAttachPin(ledPin3, ledChannel);

  Serial.begin(9600);
}

void loop() {
  // reads the input on analog pin (value between 0 and 4095)
  int analogValue = analogRead(LIGHT_SENSOR_PIN);
  int ledVal = 255 - (analogValue * 255 / 4095);

  Serial.print("Analog Value = ");
  Serial.print(analogValue);   // the raw analog reading
  Serial.print("Led Value = ");
  Serial.println(ledVal);   // the raw analog reading

  ledcWrite(ledChannel, ledVal);

  myStepper.step(stepsPerRevolution);


}
