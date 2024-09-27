// capacitive sensing includes
#include <CapacitiveSensor.h>

// constant: 1M-Ohm resistor between pins 4 & 2, pin 2 is sensor pin
CapacitiveSensor sensor = CapacitiveSensor(4,2);

void setup() {
  Serial.begin(9600);
}

void loop() {
  long measurement =  sensor.capacitiveSensor(30);
  
  Serial.println(measurement);
  delay(10);
}
