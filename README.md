SmoothAnalogInput (for Arduino)
=======
Based on Richard Lee's original repo
* Blog: http://rl337.org/2012/01/11/smooth-analog-input-class-for-arduino/
* GIT repo: https://github.com/rl337/Arduino
Inspired by Arduino code example "Smoothing": https://www.arduino.cc/en/Tutorial/Smoothing


SmoothAnalogInput -- Smooths out analog input over some specified number of samples.

example:

Servo servo;
SmoothAnalogInput ai;
int last;
void setup() {
  Serial.begin(9600);
  servo.attach(7);
  ai.attach(A0);
  last = -1;
}

void loop() {
  int sensorReading = ai.read();

  int scaled = map(sensorReading, 0, 1024, 0, 180);
  if (scaled != last) {
    last = scaled;
    Serial.println(scaled);
    servo.write(scaled);
  }
}
