#include <RunningMedian.h>

byte playPinLow = 2;     // button pin
byte playPinHigh = 3;    // button pin
byte trigPin = 11;       // Trigger
byte echoPin = 12;       // Echo

unsigned int minRange = 200;
unsigned int maxRange = 4000;       
float lowMinFreq = 41.20;    // E1
float lowMaxFreq = 82.41;    // E2
float highMinFreq = 82.41;   // E2
float highMaxFreq = 164.8;   // E3

byte windowSize = 19; // size of buffer window
RunningMedian samples = RunningMedian(windowSize); // buffer of size windowSize

void setup() {
    Serial.begin(9600); // initialize serial communications (for debugging only)
    
    // defining inputs and outputs:
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(playPinLow, INPUT);
    pinMode(playPinHigh, INPUT);
}

void loop() {
  if (digitalRead(playPinLow) || digitalRead(playPinHigh)) {
    // trigger sending a sonic pulse on trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5); 
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);  
    
    samples.add(pulseIn(echoPin, HIGH)); // add pulse length to samples
    long median = samples.getMedian(); // calculate the median of buffered samples for stability
    // change the minimum and maximum input numbers below depending on the range
    // your sensor's giving:
    int frequency{};
    if (digitalRead(playPinLow) && median <= maxRange){
        frequency = map(median, minRange, maxRange, lowMinFreq, lowMaxFreq);
    }
    if (digitalRead(playPinHigh) && median <= maxRange){
        frequency = map(median, minRange, maxRange, highMinFreq, highMaxFreq);
    }

    tone(9, frequency, 16); // play the pitch:
    delay(1); // delay in between reads for stability, might not be needed
  }
  else {
    noTone(9); // don't play a tone
    delay(1); // might not be needed, will test later
  } 
}
