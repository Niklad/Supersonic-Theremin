#include <RunningMedian.h>

int playPin = 2;
int trigPin = 11;    // Trigger
int echoPin = 12;    // Echo
int pin7 = 7;

RunningMedian samples = RunningMedian(19);

void setup() {
    // initialize serial communications (for debugging only):
    Serial.begin(9600);
    //Define inputs and outputs
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
    pinMode(pin7, OUTPUT);
}

void loop() {
  if (digitalRead(playPin)) {
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5); 
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);  
     
    samples.add(pulseIn(echoPin, HIGH));

    long median = samples.getMedian();
    
    // change the minimum and maximum input numbers below depending on the range
    // your sensor's giving:
    int thisPitch = map(median, 200, 4000, 80, 300);
    // play the pitch:
    tone(9, thisPitch, 10);
    delay(1);        // delay in between reads for stability
    // index++;
  }
  else {
    noTone(9);
    samples.clear();
    delay(1);
  } 
}
