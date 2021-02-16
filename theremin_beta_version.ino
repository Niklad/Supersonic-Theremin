// #include <RunningMedian.h>

// int playPin = 2;     // button pin
// int trigPin = 11;    // Trigger
// int echoPin = 12;    // Echo

// // make a buffer with recent samples
// unsigned int windowSize = 19;
// RunningMedian samples = RunningMedian(windowSize);

// void setup() {
//     // initialize serial communications (for debugging only):
//     Serial.begin(9600);
//     // define inputs and outputs
//     pinMode(trigPin, OUTPUT);
//     pinMode(echoPin, INPUT);
// }

// void loop() {
//   if (digitalRead(playPin)) {
//     // trigger sending a sonic pulse on trigPin
//     digitalWrite(trigPin, LOW);
//     delayMicroseconds(5); 
//     digitalWrite(trigPin, HIGH);
//     delayMicroseconds(10);
//     digitalWrite(trigPin, LOW);  
    
//     // add pulse length to samples
//     samples.add(pulseIn(echoPin, HIGH));
//     // calculate the median of buffered samples for stability
//     long median = samples.getMedian();
//     // change the minimum and maximum input numbers below depending on the range
//     // your sensor's giving:
//     int thisPitch = map(median, 200, 4000, 80, 300);
//     // play the pitch:
//     tone(9, thisPitch, 10);
//     // delay in between reads for stability
//     delay(1);        
//   }
//   else {
//     noTone(9);
//     // start with a clear buffer after stopping
//     samples.clear();
//     delay(1);
//   } 
// }
