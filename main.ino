#include <RunningMedian.h>

byte playPinLow = 2;     // button pin
byte playPinMid = 3;     // button pin
byte playPinHigh = 4;    // button pin
byte trigPin = 11;       // Trigger
byte echoPin = 12;       // Echo

// change minRange and maxRange depending on the usable range of your sensor:
unsigned int minRange = 350;                                     // set a few cm away from the sensor, get too close and it will be bad
unsigned int maxToneRange = 2000;                                // set to a distance that won't cause too many false negatives
unsigned int maxRange = 1.2 * maxToneRange;                      // set to a distance that won't cause too many false negatives
// using logarithmic scaling for physically even spacing of notes:
unsigned int a = 2^16 - 1;                                       // scaling factor for resolution
unsigned int minRange_log = a * log(minRange) / log(2);   
unsigned int maxToneRange_log = a * log(maxToneRange) / log(2);
unsigned int maxRange_log = a * log(maxRange) / log(2);

float lowMinFreq = 41.20;             // E1
float lowMaxFreq = 2 * lowMinFreq;    // E2
float midMinFreq = lowMaxFreq;        // E2
float midMaxFreq = 2 * midMinFreq;    // E3
float highMinFreq = midMaxFreq;       // E3
float highMaxFreq = 2 * midMaxFreq;   // E4

// size of buffer window, higher bufferSize should give more stable tone but more latency:
byte bufferSize = 25; 
RunningMedian samples = RunningMedian(bufferSize); // buffer of size bufferSize

void setup() {
    Serial.begin(9600); // initialize serial communications (for debugging only)
    
    // defining inputs and outputs:
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(playPinLow, INPUT);
    pinMode(playPinMid, INPUT);
    pinMode(playPinHigh, INPUT);
}

void loop() {
  if (digitalRead(playPinLow) || digitalRead(playPinMid) || digitalRead(playPinHigh)) {
    // trigger sending a sonic pulse on trigPin
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5); 
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);  
    
    samples.add(pulseIn(echoPin, HIGH)); // add pulse length to samples
    // calculate the median of buffered samples for stability
    long median_log = a * log(samples.getMedian()) / log(2); 
    int frequency{};
    // Use different tone range depending on button input
    if (digitalRead(playPinLow) && median_log <= maxRange_log){
        frequency = constrain(map(median_log, minRange_log, maxToneRange_log, lowMinFreq, lowMaxFreq), lowMinFreq, lowMaxFreq);
    }
    if (digitalRead(playPinMid) && median_log <= maxRange_log){
        frequency = constrain(map(median_log, minRange_log, maxToneRange_log, midMinFreq, midMaxFreq), midMinFreq, midMaxFreq);
    }
    if (digitalRead(playPinHigh) && median_log <= maxRange_log){
        frequency = constrain(map(median_log, minRange_log, maxToneRange_log, highMinFreq, highMaxFreq), highMinFreq, highMaxFreq);
    }

    tone(9, frequency); // play the pitch:
    delay(1);               // delay in between reads for stability, might not be needed
  }
  else {
    noTone(9);        // don't play a tone
    samples.clear();  // clear the buffer between plays 
    delay(1);         // might not be needed, will test later
  } 
}
