// capacitive sensing includes
#include <CapacitiveSensor.h>

// constant: 1M-Ohm resistor between pins 4 & 2, pin 2 is sensor pin
CapacitiveSensor sensor = CapacitiveSensor(4, 2);
const int LED_PIN = 5;       // The output pin to which LED is attached
const int numReadings = 10;  // Number of readings to average
float avg = 0;               // Average of the sensor readings
int readings[numReadings];   // Array to store sensor readings
long measurement = 0;        // Measurement of the sensor
int total = 0;               // Variable to store the total of readings
int index = 0;               // Index for storing readings in the array
int threshold = 200;         // Threshold to switch the LED

void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);  // Set the LED pin as an output
  sensor.set_CS_AutocaL_Millis(0xFFFFFFFF);
  for (int i = 0; i < numReadings; i++) {
    readings[i] = 0;  // Initialize all readings to 0
  }
}

void loop() {
  measurement = sensor.capacitiveSensor(30);
  Serial.println(measurement);
  float avg = AverageCalculator(measurement);
  Serial.println("--------------");
  Status(avg);

  // Wait for 10 milliseconds before the next reading
  delay(400);
}

float AverageCalculator(float measurement) {
  // Subtract the oldest reading from the total
  total = total - readings[index];

  // Store the new reading in the array
  readings[index] = measurement;

  // Add the new reading to the total
  total = total + readings[index];

  // Move to the next index in the array
  index = (index + 1) % numReadings;

  // Calculate the average of the last 50 readings
  float average = total / numReadings;

  // Print the average
  Serial.println("Average Reading: " + String(average));
  return average;
}

void Status(float avg) {
  if (avg > threshold) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }
}