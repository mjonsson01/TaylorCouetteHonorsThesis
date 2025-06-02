// // want to determine the used RPM speed based on input.

// //if I have 1 ms delay, each pulse pair takes 1 millisecond. A pul high/low is a step on its own.

// // If i am set to 400 pulses (just high and low individually per pulse) per revolution, at 1000 pulses per second (from the 1 ms delay on pair)
// //I get 2.5 rps or 150 rpm. Lets test.


// // to set RPM, we take (pulses per second&* revs/pulse aka. (inverse of table pulse/rev)  /2) *60


// #define PUL 7  // Pulse pin
// #define DIR 5  // Direction pin
// #define ENA 4  // Enable pin
// // #define PULperRev 6400
// int delayperiod = 23; //delay in microseconds (1 ms delay)

// //pulse per second is 1/delayperiod
// void setup() {
//     pinMode(PUL, OUTPUT);
//     pinMode(DIR, OUTPUT);
//     pinMode(ENA, OUTPUT);
//     digitalWrite(ENA, LOW); // Enable the driver
//     Serial.begin(750);
// }

// void loop() {
//     if (Serial.available()) {
//         char command = Serial.read();

//         if (command == 'f') { // Forward
//             Serial.println("Going forward 200000 steps");
//             digitalWrite(DIR, HIGH);
//             stepMotor(30000); // Adjust steps as needed
//         }
//         else if (command == 'b') { // Backward
//           Serial.println("Going backward 200 steps");
//             digitalWrite(DIR, LOW);
//             stepMotor(2000);
//         }
//     }
// }

// void stepMotor(int steps) {
//    digitalWrite(ENA, LOW);  // Enable motor before moving
//     for (int i = 0; i < steps; i++) {
//         digitalWrite(PUL, HIGH);
//         delayMicroseconds(delayperiod); // Adjust speed
//         digitalWrite(PUL, LOW);
//         delayMicroseconds(delayperiod);
//     }
//     digitalWrite(ENA, HIGH);  // Disable motor after moving
// }



// Need to add functionality to do a "step" at a certain speed (based from the Re of the system)
// when pressed step (prob tie to space key), continue to next speed. Create a list of target speeds? or Re's ?
// when press space, continue to next step.



// MOTOR SET TO 800 PUL/REV (Quarter Stepping)



// // //////// YIPPEE THIS WORKS
// #include <AccelStepper.h>

// #define PUL 7  // Step pin
// #define DIR 5  // Direction pin
// #define ENA 4  // Enable pin (optional)


// // Function to calculate Reynold's Number. Duplicate Script on Matlab as well.

// // Define AccelStepper instance
// AccelStepper stepper(AccelStepper::DRIVER, PUL, DIR);

// void setup() {
//   Serial.begin(9600);  // Faster serial communication
//   pinMode(ENA, OUTPUT);
//   digitalWrite(ENA, LOW);  // Enable the stepper driver

//   // Stepper motor settings

//   // Stepper set speed in steps per second is really just the amount of PULSES per second. 
//   // We should be able to then convert pulses per second * revs/ pulse to get RPS


//   // 
//   stepper.setMaxSpeed(350);     // Max speed in steps per second
//   stepper.setAcceleration(50);  // Acceleration in steps per second^2
// }

// void loop() {
//   if (Serial.available()) {
//     char command = Serial.read();

//     if (command == 'f') {
//       Serial.println(" Litle Stepper Moving forward 100000 steps");
//       stepper.move(100000);  // Move forward 1000 steps
//     } else if (command == 'b') {
//       Serial.println("Moving backward 1000 steps");
//       stepper.move(-100000);  // Move backward 1000 steps
//     } else if (command == 's') {
//       Serial.println("Stopping motor");
//       stepper.stop();  // Stop smoothly
//     } else if (command == 'r') {
//       Serial.println("Reset position to zero");
//       stepper.setCurrentPosition(0);  // Reset position to zero
//     }
//   }

//   stepper.run();  // Needs to be called continuously for smooth motion
// }

// // #include <AccelStepper.h>

// // #define DRIVER_PUL 7  // Pulse pin
// // #define DRIVER_DIR 6  // Direction pin

// // // Define the stepper motor using driver mode (1 = Step, 2 = Direction)
// // AccelStepper stepper(AccelStepper::DRIVER, DRIVER_PUL, DRIVER_DIR);

// // const int stepsPerRevolution = 200;  // Adjust based on your stepper motor
// // const int microsteps = 16;           // Set this according to your driver microstepping setting

// // void setup() {
// //     Serial.begin(9600);

// //     stepper.setMaxSpeed(1000);  // Max speed in steps per second
// //     stepper.setAcceleration(500);  // Acceleration in steps per second^2
// //     stepper.setSpeed(500);  // Initial speed in steps per second
// // }

// // void loop() {
// //     stepper.runSpeed();  // Run stepper at constant speed

// //     // Calculate RPM
// //     float stepsPerSecond = stepper.speed();  // Speed in steps per second
// //     float rpm = (stepsPerSecond * 60) / (stepsPerRevolution * microsteps);

// //     Serial.print("Speed (steps/sec): ");
// //     Serial.print(stepsPerSecond);
// //     Serial.print(" | RPM: ");
// //     Serial.println(rpm);
// // }


// // #include <AccelStepper.h>

// // #define DRIVER_PUL 7  // Pulse pin
// // #define DRIVER_DIR 5  // Direction pin
// // #define DRIVER_ENA 4  // Enable pin
// // #define POT_SPEED A0  // Potentiometer for speed control

// // // const int stepsPerRevolution = 800;  // Full steps per revolution (adjust for your motor)
// // // const int microsteps = 4;           // Set this based on your DM556S driver microstepping

// // AccelStepper stepper(AccelStepper::DRIVER, DRIVER_PUL, DRIVER_DIR);

// // void setup() {
// //     Serial.begin(115200);

// //     pinMode(DRIVER_ENA, OUTPUT);
// //     digitalWrite(DRIVER_ENA, LOW); // Enable the motor

// //     stepper.setMaxSpeed(4000);  // Max speed in steps per second
// //     stepper.setAcceleration(100);  // Acceleration in steps per second^2
// // }

// // void loop() {
// //     // Read speed from potentiometer and map to a reasonable range
// //     int potValue = analogRead(POT_SPEED);
// //     float targetSpeed = map(potValue, 0, 1023, 200, 2000); // Adjust speed range as needed
// //     stepper.setSpeed(targetSpeed);

// //     stepper.runSpeed(); // Run at the set speed with acceleration

// //     // Calculate RPM
// //     float stepsPerSecond = stepper.speed();
// //     // float rpm = (stepsPerSecond * 60) / (stepsPerRevolution * microsteps);

// //     // Serial.println("Speed (steps/sec): ");
// //     // Serial.print(stepsPerSecond);
// //     Serial.print("Target Speed");
// //     Serial.println(targetSpeed);
// //     // Serial.print(" | RPM: ");
// //     // Serial.println(rpm);

// //     // delay(500);
// // }
#include <AccelStepper.h>

#define PUL 7  // Step pin
#define DIR 5  // Direction pin
#define ENA 4  // Enable pin
#define CVOUTER -20.36186375f //steps per second to Re conversion

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
      Serial.print("OUTER CYLINDER | ");
      Serial.print("Motor Target Speed: ");
      Serial.print(maxSpeed);
      Serial.print(" | Actual Speed: ");
      Serial.print(stepper.speed());
      Serial.print(" steps/sec |");
      Serial.print(" Re_Outer = ");
      Serial.println(CVOUTER*stepper.speed());

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