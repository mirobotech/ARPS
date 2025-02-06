/*
Project:  ARPS Sumo Robot Starter Program
Activity: mirobotech/arps
Date:     February 5, 2025

Use this starter program template to create a simple Sumo robot using
an Arduino UNO and ARPS2 circuit board. Follow the instructions in
the program comments to test your motors and optical floor sensors,
and then expand your program to complete your Sumo robot!

This program was designed for making simple classroom Sumo robots
that compete within the Robo-Sumo rules on the mirobo.tech website
(https://mirobo.tech/robo-sumo-rules) and can easily be adapted for
making other kinds of beginner robots.

See the https://mirobo.tech/arps webpage for additional ARPS
resources, programming activities, and starter programs.
*/

// Define I/O pins used by ARPS human interface devices
const int SW2 = 0;      // Pushbuttons SW2 and SW3 are supported on Arduino
const int SW3 = 1;      // UNO R4 Minima and Arduino UNO R4 WiFi
const int SW4 = 2;      // Pushbuttons SW4 and SW5 work on all Arduino UNO R3
const int SW5 = 3;      // and Arduino UNO R4 circuit boards

const int LED2 = 5;     // ARPS LEDs
const int LED3 = 6;
const int LED4 = 9;
const int LED5 = 10;

const int BEEPER = 11;  // ARPS Piezo beeper LS1

// Define I/O pins for special purpose interface devices
const int M1A = 5;      // Motor 1 - output A
const int M1B = 6;      // Motor 1 - output B
const int M2A = 9;      // Motor 2 - output A
const int M2B = 10;     // Motor 2 - output B

const int IR = 4;       // IR demodulator input

const int LED6 = 7;     // LED6 output and +5V supply for left floor/line sensors Q1 and Q2
const int LED7 = 8;     // LED7 output and +5V supply for right floor sensor Q3
const int Q1 = A0;      // Left floor/line sensor phototransistor
const int Q2 = A1;      // Right line sensor phototransistor
const int Q3 = A1;      // Right floor sensor phototransistor

const int H1 = 18;      // Header H1
const int H2 = 13;      // Header H2 (shared with SONAR and onboardLED)
const int TRIG = 13;    // Ultrasonic SONAR distance sensor TRIG(ger) output
const int H3 = 12;      // Header H3 (shared with SONAR)
const int ECHO = 12;    // Ultrasonic SONAR distance sensor ECHO input
const int H4 = 19;      // Header H4

const int ATEMP = A2;   // Analog temperature sensor U1 Vout pin
const int ADIV = A3;    // Analog voltage divider (R20/R21) tap

// Define mode constants
const int TEST = 0;		  // Test mode
const int STARTUP = 1;	// Startup delay
const int SEARCH = 2;	  // Search mode
const int ATTACK = 3;	  // Attack mode

// Define program variables
int SW2state;           // Button state variables
int SW3state;
int SW4state;
int SW5state;
int mode;				        // Program operating mode
int floorLeft;			    // Left floor sensor value
int floorRight;			    // Right floor sensor value
int range;           	  // SONAR range

// Setup code runs once to configure I/O pins before running main loop
void setup() {
  Serial.begin(9600);   // Start the serial port at 9600 bps for UNO R3
  // Serial.begin(115200); // Start the serial port at 115200 bps for UNO R4

  pinMode(SW2,INPUT_PULLUP);
  pinMode(SW3,INPUT_PULLUP);
  pinMode(SW4,INPUT_PULLUP);
  pinMode(SW5,INPUT_PULLUP);
  pinMode(LED2,OUTPUT); // LEDs and motors share the same pins
  pinMode(LED3,OUTPUT);
  pinMode(LED4,OUTPUT);
  pinMode(LED5,OUTPUT);
  pinMode(BEEPER,OUTPUT);
  pinMode(LED_BUILTIN,OUTPUT);
  pinMode(IR,INPUT);
  pinMode(LED6,OUTPUT);
  pinMode(LED7,OUTPUT);
  pinMode(Q1,INPUT);
  pinMode(Q2,INPUT);    // Q2 and Q3 share the same pin
  pinMode(H1,INPUT);    // Define unused header pins as input
  pinMode(TRIG,OUTPUT); // H2/TRIG SONAR output (if installed)
  pinMode(ECHO,INPUT);  // H3/ECHO SONAR input
  pinMode(H4,INPUT);    // Define unused header pins as input
  tone(BEEPER, 4000, 100);  // Say hello and print startup messages
  Serial.println(F("Starting ARPS2 Sumo!"));

  // Start the robot...
  stop();               // Start with the motors off
  mode = TEST;          // Test mode for sensors and motors
  // mode = STARTUP;       // Sumo pre-fight startup mode
}

// Main loop code repeats forever
void loop() {
  // while() loops within loop() are like mini self-contained loop()s.
  // Use the mode variable to switch program operating modes.

  while(mode == TEST) {
    // Test the motors, optical sensors, and SONAR module here:

    // Motor test - verify the operation of each motor direction.
    goFwd();
    delay(1000);
    stop();
    
    // Floor sensor test - record light and dark values from each
    // floor sensor, and use thse to determine threshold values to
    // keep your robot in the Sumo ring.
    floorLeft = analogRead(Q1);	// Left phototransistor (Q1) light level
    Serial.print("Q1 Level: ");
    Serial.println(floorLeft);
    
    // Add your own SONAR distance sensor test code here:
    
    delay(1000);
  }
  
  while(mode == STARTUP) {
    // STARTUP mode - waits for a button to be pressed and then
    // starts a five second delay before switching to SEARCH mode.
    
    mode = SEARCH;
  }

  while(mode == SEARCH) {
    // SEARCH mode - use the SONAR module to search for an opponent
    // within the Sumo ring, and use the floor sensors to remain in
    // the ring. If an opponent is found, switch to ATTACK mode.

  }

  while(mode == ATTACK) {
    // ATTACK mode - push the opponent out of the Sumo ring while
    // using the floor sensors to remain in the ring. If an opponent
    // is no longer detected, switch back to SEARCH mode.

  }
}

/*
Sample motor functions. Create additional functions for every
direction that your robot needs to drive in. Can you come up with
eight different directions? Does your robot need to use all eight?
Creating all of the motor direction functions ahead of time will
let you easily adapt your robot for other tasks later.
*/

// Run motors in opposite directions to make the robot go forward.
// (Assumes both motors are wired to ARPS the same way.)
void goFwd(void) {
  digitalWrite(M1A, HIGH);      // Left motor rotates CCW
  digitalWrite(M1B, LOW);
  digitalWrite(M2A, LOW);       // Right motor rotates CW
  digitalWrite(M2B, HIGH);
}

// Stop both motors
void stop(void) {
  digitalWrite(M1A, LOW);     // Left motor
  digitalWrite(M1B, LOW);
  digitalWrite(M2A, LOW);     // Right motor
  digitalWrite(M2B, LOW);
}

// Add other functions for your robot here. It will need a SONAR
// function to detect an opposing robot, and could implement floor
// sensing functions to shorten the program code in the SEARCH and
// ATTACK functions. If the IR demodulator is installed in your
// robot, an IR remote transmitter can be used to start the bout.
