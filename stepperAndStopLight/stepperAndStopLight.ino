/*
 * This ESP32 code is created by esp32io.com
 *
 * This ESP32 code is released in the public domain
 *
 * For more detail (instruction and wiring diagram), visit https://esp32io.com/tutorials/esp32-led-blink
 */


#include <Stepper.h>
#include <Servo.h>

const int stepsPerRevolution = 2048;  // change this to fit the number of steps per revolution

// ULN2003 Motor Driver Pins
#define IN1 19
#define IN2 18
#define IN3 5
#define IN4 17
Servo myservo;  // create servo object to control a servo
Servo barrier;
// twelve servo objects can be created on most boards

int pos = 0;  

// initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);


void setup() {
  // initialize digital pin GPIO18 as an output.
  pinMode(25, OUTPUT);
  pinMode(16, OUTPUT);

    // set the speed at 5 rpm
  myStepper.setSpeed(5);

  myservo.attach(14);  // attaches the servo on pin 14 to the servo object
  barrier.attach(26);
  // initialize the serial port
  Serial.begin(115200);
  
}

// the loop function runs over and over again forever
void loop() {
  digitalWrite(25, HIGH); // turn the LED on
  delay(10000);             // wait for 500 milliseconds
  digitalWrite(25, LOW);  // turn the LED off
  delay(500);             // wait for 500 milliseconds

  digitalWrite(16, HIGH); // turn the LED on
  delay(10000);             // wait for 500 milliseconds
  digitalWrite(16, LOW);  // turn the LED off
  delay(500);   

    for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    barrier.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  for (pos = 90; pos <= 270; pos += 12) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }

  for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    barrier.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }
  
  for (pos = 270; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(15);                       // waits 15ms for the servo to reach the position
  }


  Serial.println("clockwise");
  myStepper.step(stepsPerRevolution);
  delay(1000);

  // step one revolution in the other direction:
  Serial.println("counterclockwise");
  myStepper.step(-stepsPerRevolution);
  delay(1000);

}
