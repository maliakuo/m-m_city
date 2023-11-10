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

#define GREEN_PIN 21  // GIOP21 pin connected to button
#define YELLOW_PIN 13  // GIOP21 pin connected to button

#define GREEN_LED 16  // GIOP21 pin connected to button
#define RED_LED 25  // GIOP21 pin connected to button

// Variables will change:
int greenLastState = LOW;  // the previous state from the input pin
int greenCurrentState;     // the current reading from the input pin

int yellowLastState = LOW;  // the previous state from the input pin
int yellowCurrentState;     // the current reading from the input pin

Servo myservo;  // create servo object to control a servo
Servo barrier;
// twelve servo objects can be created on most boards

int pos = 0;  

// initialize the stepper library
Stepper myStepper(stepsPerRevolution, IN1, IN3, IN2, IN4);


void setup() {
  // initialize digital pin GPIO18 as an output.
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);

  pinMode(GREEN_PIN, INPUT_PULLUP);
  pinMode(YELLOW_PIN, INPUT_PULLUP);

    // set the speed at 5 rpm
  myStepper.setSpeed(15);

  myservo.attach(14);  // attaches the servo on pin 14 to the servo object
  barrier.attach(26);
  // initialize the serial port
  Serial.begin(115200);
  
}

// the loop function runs over and over again forever
void loop() {
  greenCurrentState = digitalRead(GREEN_PIN);
  yellowCurrentState = digitalRead(YELLOW_PIN);

  if (greenLastState == HIGH && greenCurrentState == LOW) {
    Serial.println("green pressed");

    // turn RED LED off
    digitalWrite(RED_LED, LOW);  // turn the LED off
    delay(500);             // wait for 500 milliseconds
    Serial.println("red led off");

    // turn GREEN LED on
    digitalWrite(GREEN_LED, HIGH); // turn the LED on
    Serial.println("turn GREEN LED on");

    // gate open
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      barrier.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    Serial.println("gate open");

    delay(500);             // wait for 500 milliseconds

    // propel the car 
    for (pos = 140; pos <= 320; pos += 60) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }

    Serial.println("car push");

    // close barrier
    for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      barrier.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    Serial.println("close barrier");

    
    // servo resets
    for (pos = 320; pos >= 140; pos -= 1) { // goes from 180 degrees to 0 degrees
      myservo.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    Serial.println("reset servo");

    // green LED OFF
    digitalWrite(GREEN_LED, LOW);  // turn the LED off
    Serial.println("green off");
    delay(500);   

    // red LED on
    digitalWrite(RED_LED, HIGH); // turn the LED on
    Serial.println("red on");
    delay(500);             // wait for 500 milliseconds

  } 
  
  // else if (greenLastState == LOW && greenCurrentState == HIGH) {
  //   Serial.println("green released");
  // }

  else if (yellowLastState == HIGH && yellowCurrentState == LOW) {
    Serial.println("yellow pressed");

    // gate open
    for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
      // in steps of 1 degree
      barrier.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    Serial.println("gate open");

    delay(500);   

    // car back
    Serial.println("counterclockwise");
    myStepper.step(-stepsPerRevolution);
    myStepper.step(-stepsPerRevolution);
    myStepper.step(-stepsPerRevolution);
    myStepper.step(-stepsPerRevolution);

    delay(1000);
    Serial.println("car back");

    Serial.println("clockwise");
    myStepper.step(stepsPerRevolution);
    myStepper.step(stepsPerRevolution);
    myStepper.step(stepsPerRevolution);
    myStepper.step(stepsPerRevolution);
    delay(500);

    // close barrier
    for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
      barrier.write(pos);              // tell servo to go to position in variable 'pos'
      delay(15);                       // waits 15ms for the servo to reach the position
    }
    Serial.println("gate close");

  } 

  // else if (yellowLastState == LOW && yellowCurrentState == HIGH) {
  //   Serial.println("yellow released");
  // }
  else {
    digitalWrite(RED_LED, HIGH); // turn the LED on
     Serial.println("neutral state");
      Serial.println("red on");
  }

  greenLastState = greenCurrentState;
  yellowLastState = yellowCurrentState;



  // digitalWrite(RED_LED, HIGH); // turn the LED on
  // delay(10000);             // wait for 500 milliseconds
  // digitalWrite(RED_LED, LOW);  // turn the LED off
  // delay(500);             // wait for 500 milliseconds

  // digitalWrite(GREEN_LED, HIGH); // turn the LED on
  // delay(10000);             // wait for 500 milliseconds
  // digitalWrite(GREEN_LED, LOW);  // turn the LED off
  // delay(500);   

  // for (pos = 90; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
  //   barrier.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(15);                       // waits 15ms for the servo to reach the position
  // }

  // for (pos = 90; pos <= 270; pos += 12) { // goes from 0 degrees to 180 degrees
  //   // in steps of 1 degree
  //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(15);                       // waits 15ms for the servo to reach the position
  // }

  // for (pos = 0; pos <= 90; pos += 1) { // goes from 0 degrees to 180 degrees
  //   // in steps of 1 degree
  //   barrier.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(15);                       // waits 15ms for the servo to reach the position
  // }
  
  // for (pos = 270; pos >= 90; pos -= 1) { // goes from 180 degrees to 0 degrees
  //   myservo.write(pos);              // tell servo to go to position in variable 'pos'
  //   delay(15);                       // waits 15ms for the servo to reach the position
  // }


  // Serial.println("clockwise");
  // myStepper.step(stepsPerRevolution);
  // delay(1000);

  // // step one revolution in the other direction:
  // Serial.println("counterclockwise");
  // myStepper.step(-stepsPerRevolution);
  // delay(1000);

}
