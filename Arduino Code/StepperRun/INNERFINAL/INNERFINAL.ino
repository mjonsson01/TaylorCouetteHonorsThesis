#include <AccelStepper.h>

#define PUL 7  // Step pin
#define DIR 5  // Direction pin
#define ENA 4  // Enable pin
#define CVINNER 17.34529125f //steps per second to Re conversion

AccelStepper stepper(AccelStepper::DRIVER, PUL, DIR);

float maxSpeed = 0;       // Starting speed in steps/sec
float smallStepSize = 10;        // Speed increment for m/l
float bigStepSize = 50;   // Speed increment for M/L
bool motorActive = false;   // Only change speed when motor is running
unsigned long lastPrintTime = 0;
bool waitingToStop = false;
// float conversionInner = 13876.233/800; // multiply by steps per second (to refer to RPS) to get ReInner
int speedSign = 1;  // +1 for forward, -1 for backward

void setup() {
  Serial.begin(115200);
  pinMode(ENA, OUTPUT);
  digitalWrite(ENA, LOW);  // Enable driver

  stepper.setAcceleration(50);
  stepper.setMaxSpeed(maxSpeed);
}

void loop() {
    if (motorActive) {
      stepper.run();

    if (waitingToStop && abs(stepper.speed()) < 0.01) {
      Serial.println("Motor has fully stopped.");
      motorActive = false;
      waitingToStop = false;
    }

    // Print speed every 0.5 seconds
    if (millis() - lastPrintTime > 500) {
      // Print Out Cylinder Re and Angular Speed.
      Serial.print("INNER CYLINDER | ");
      Serial.print("Motor Target Speed: ");
      Serial.print(maxSpeed);
      Serial.print(" | Actual Speed: ");
      Serial.print(stepper.speed());
      Serial.print(" steps/sec |");
      Serial.print(" Re_Inner = ");
      Serial.println(CVINNER*stepper.speed());

      lastPrintTime = millis();
    }
  }

  if (Serial.available()) {
    char command = Serial.read();

    switch (command) {
      case 'f':
        Serial.println("Moving forward 100000 steps");
        digitalWrite(DIR, HIGH);
        motorActive = true;  // Reactivate
        waitingToStop = false; // Set flag to make sure we print correctly
        speedSign = 1;
        stepper.setMaxSpeed(maxSpeed);
        stepper.setSpeed(speedSign * maxSpeed);
        stepper.moveTo(1e9);  // some 
        break;

      case 'b':
        Serial.println("Moving backward 100000 steps");
        digitalWrite(DIR, LOW);
        motorActive = true;  // Reactivate
        waitingToStop = false; // Set flag to make sure we print correctly
        speedSign = -1;
        stepper.setMaxSpeed(maxSpeed);
        stepper.setSpeed(speedSign * maxSpeed);
        stepper.moveTo(-1e9);  // some really large position
        break;
        
      case 's':
        Serial.println("Stopping motor");
        maxSpeed = 0; // to correct target speed state variable maxSpeed
        stepper.stop();  // Initiate smooth deceleration
        waitingToStop = true;
        break;
        
      case 'e':
      // Emergency stop
        Serial.println("IMMEDIATE STOP");
        stepper.stop();
        maxSpeed = 0;
        stepper.setMaxSpeed(maxSpeed);
        motorActive = false;
        break;

      case 'r':
        Serial.println("Resetting position to zero");
        stepper.setCurrentPosition(0);
        break;

       case 'M':  // More speed, big step in speed
        if (motorActive) {
          maxSpeed += bigStepSize;
          stepper.setMaxSpeed(maxSpeed);
          stepper.setSpeed(speedSign * maxSpeed);
          Serial.print("Increased speed to ");
          Serial.println(maxSpeed);
        } else {
          Serial.println("Motor inactive. Press 'f' or 'b' to start motion.");
        }
        break;

      case 'L':  // Less speed, big step in speed
        if (motorActive) {
          maxSpeed -= bigStepSize;
          if (maxSpeed < 1) maxSpeed = 1;
          stepper.setMaxSpeed(maxSpeed);
          stepper.setSpeed(speedSign * maxSpeed);
          Serial.print("Decreased speed to ");
          Serial.println(maxSpeed);
        } else {
          Serial.println("Motor inactive. Press 'f' or 'b' to start motion.");
        }
        break;
      case 'm':  // More speed, small step
        if (motorActive) {
          maxSpeed += smallStepSize;
          stepper.setMaxSpeed(maxSpeed);
          stepper.setSpeed(speedSign * maxSpeed);
          Serial.print("Increased speed to ");
          Serial.println(maxSpeed);
        } else {
          Serial.println("Motor inactive. Press 'f' or 'b' to start motion.");
        }
        break;
#define CVOUTER -20.36186375f //steps per second to Re conversion
Serial.print(" steps/sec |");
Serial.print(" Re_Outer = ");
Serial.println(CVOUTER*stepper.speed());
      case 'l':  // Less speed, small step
        if (motorActive) {
          maxSpeed -= smallStepSize;
          if (maxSpeed < 1) maxSpeed = 1;
          stepper.setMaxSpeed(maxSpeed);
          stepper.setSpeed(speedSign * maxSpeed);
          Serial.print("Decreased speed to ");
          Serial.println(maxSpeed);
        } else {
          Serial.println("Motor inactive. Press 'f' or 'b' to start motion.");
        }
        break;
    }
  }
}