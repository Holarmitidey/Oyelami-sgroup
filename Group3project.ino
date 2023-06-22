// IR library 
#include <IRremote.h>

// Servo library
#include <Servo.h>

//Define the IR reciever pin
const int irReceiverPin = 2;

//Define the Relay module pins
const int relayForwardPin = 3;  
const int relayReversePin = 4;  

//Define IR remote necessity
const unsigned long forwardButtonCode = 0xFD50AF;   
const unsigned long reverseButtonCode = 0xFD10EF; 
IRrecv irReceiver(irReceiverPin);
decode_results irResults;

//Define ultrasonic necessity
int trigger_pin = 5;
int echo_pin = 6;
int time;
int distance;


// Define servo motor pin
const int servoPin = 7;

Servo Myservo;

void setup() {
  // Initialize IR receiver
  irReceiver.enableIRIn();

  // Intialize ultrasonic pin
  pinMode(trigger_pin, OUTPUT);
  pinMode(echo_pin, INPUT);

  // Initialize relay module pins
  pinMode(relayForwardPin, OUTPUT);
  pinMode(relayReversePin, OUTPUT);

  // Initialize relays to OFF state
  digitalWrite(relayForwardPin, LOW);
  digitalWrite(relayReversePin, LOW);

  // Initialize servo motor
  Myservo.attach(servoPin);
}

void loop() {
  if (irReceiver.decode(&irResults)) {

    // Check if the forward button is pressed
    if (irResults.value == forwardButtonCode) {
      forward();
    }
    
    // Check if the reverse button is pressed
    else if (irResults.value == reverseButtonCode) {
      reverse();
    }

    irReceiver.resume();
  }


  

  if (checkObstacle()) {
    push();
    delay(20);
    returnBack();
  }
}

void forward() {
  // Activate the forward polarity
  digitalWrite(relayForwardPin, HIGH);
  digitalWrite(relayReversePin, LOW);
}

void reverse() {
  // Activate the reverse polarity
  digitalWrite(relayForwardPin, LOW);
  digitalWrite(relayReversePin, HIGH);
}

void push() {
  // servo forward
  Myservo.write(180);
  }

void returnBack() {
  // servo backwards
  Myservo.write(0);
  }

  bool checkObstacle() {
  // Trigger the ultrasonic sensor to send a pulse
  digitalWrite(trigger_pin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_pin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_pin, LOW);

  // Measure the duration of the echo pulse
  unsigned long time = pulseIn(echo_pin, HIGH);

  // Calculate the distance based on the speed of sound
  float distance = time * 0.034 / 2;

  // Check if an obstacle is detected within a certain range
  if (distance = 20) {
    return true;  // Obstacle detected
  } else {
    return false; // No obstacle detected
  }
} 
