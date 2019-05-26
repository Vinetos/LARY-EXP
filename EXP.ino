/**
 *
 * Motor shield A
 *
 */
const int BREAK_A_PIN = 9;
const int DIR_A_PIN = 12;
const int SPEED_A_PIN = 3;

/**
 * Ultrasonic sensor
 */
const int TRIGGER_PIN = 5;
const int ECHO_PIN = 6;

const int LED_PIN = 13;// Obvious

const int OPERATING_TIME = 2800; // Time during which the motor will be enabled (in ms)
const int TRIGGER_DISTANCE = 3; // Do the action if <= TRIGGER_DISTANCE (in cm)

// defines variables
long duration;
int distance;
bool done = false; // Has the sensor already triggered ?

void setup() {
  // Motor A
  pinMode(BREAK_A_PIN, OUTPUT); // Brake
  pinMode(DIR_A_PIN, OUTPUT); // Direction

  // Sensor
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);

  // LED
  pinMode(LED_PIN, OUTPUT);

  // Enable console ouput for debug
  Serial.begin(9600);
}

void loop() {
  if(done) { // Run the program only once and switch on the led
    digitalWrite(LED_PIN, HIGH);
    return;
  }

  // Reset the trigger pin
  delayMicroseconds(2);
  // Set Trigger pin to high for 10ms
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);

  // Get the elapsed time (time travel of the wave)
  duration = pulseIn(ECHO_PIN, HIGH);
  // distance = time * speed  / 2 (round-trip)
  distance = duration * 0.034 / 2; // in cm

  if(distance <= TRIGGER_DISTANCE) { // If the robot is near the sensor
    digitalWrite(BREAK_A_PIN, LOW);// Disable brake
    digitalWrite(DIR_A_PIN, HIGH); // Set the direction to the trigonometric sense
    analogWrite(SPEED_A_PIN, 255); // Max speed
    digitalWrite(LED_PIN, HIGH); // Switch on the LED
    delay(OPERATING_TIME); // Wait
    analogWrite(SPEED_A_PIN, 0); // Stop acceleration
    done = true;
  }
  // Print the distance in the console
  Serial.print("Distance: ");
  Serial.println(distance);

  // Wait before re-running the program (not spamming the console)
  delay(300);
}
