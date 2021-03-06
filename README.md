SmoothAnalogInput (for Arduino)
=======
Based on Richard Lee's original repo
* Blog: http://rl337.org/2012/01/11/smooth-analog-input-class-for-arduino/
* GIT repo: https://github.com/rl337/Arduino
Inspired by Arduino code example "Smoothing": https://www.arduino.cc/en/Tutorial/Smoothing


SmoothAnalogInput -- Smooths out analog input over some specified number of samples.

Example:
```Arduino
Servo servo;
SmoothAnalogInput ai;
int last;

void setup() {
  Serial.begin(9600);
  servo.attach(7);
  ai.setup(A0, 24); // attach to pin A0, use 24 samples to calculate running average
  last = -1;
}

void loop() {
  int sensorReading = ai.read(); // read analog input and return running average

  int scaled = map(sensorReading, 0, 1024, 0, 180);
  if (scaled != last) {
    last = scaled;
    Serial.println(scaled);
    servo.write(scaled);
  }
}
```
