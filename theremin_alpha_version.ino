#include <RunningMedian.h>

int playPinLow = 2;     // button pin
int playPinHigh = 3;    // button pin
int trigPin = 11;       // Trigger
int echoPin = 12;       // Echo

unsigned int minRange = 200;
unsigned int maxRange = 4000;       
float lowMinFreq = 41.20;    // E1
float lowMaxFreq = 82.41;    // E2
float highMinFreq = 82.41;   // E2
float highMaxFreq = 164.8;   // E3

// make a buffer with recent samples
unsigned int windowSize = 19;
RunningMedian samples = RunningMedian(windowSize);

void setup() {
    // initialize serial communications (for debugging only):
    Serial.begin(9600);
    // define inputs and outputs
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() {
  if (digitalRead(playPinLow) || digitalRead(playPinHigh)) {
    // trigger sending a sonic pulse on trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5); 
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);  
    
    // add pulse length to samples
    samples.add(pulseIn(echoPin, HIGH));
    // calculate the median of buffered samples for stability
    long median = samples.getMedian();
    // change the minimum and maximum input numbers below depending on the range
    // your sensor's giving:
    int frequency{};
    if (digitalRead(playPinLow) && median <= maxRange){
        frequency = map(median, minRange, maxRange, lowMinFreq, lowMaxFreq);
    }
    else if (digitalRead(playPinHigh) && median <= maxRange){
        frequency = map(median, minRange, maxRange, highMinFreq, highMaxFreq);
    }
        
    // play the pitch:
    tone(9, frequency, 16);
    // delay in between reads for stability
    delay(1);        
  }
  else {
    noTone(9);
    // start with a clear buffer after stopping
    samples.clear();
    delay(1);
  } 
}
