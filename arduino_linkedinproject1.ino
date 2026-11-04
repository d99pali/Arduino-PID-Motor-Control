/*
  OPEN-LOOP MOTOR TEST - CONTINUOUS RUN
*/

const int motorEnable = 9;
const int motorInput1 = 7;
const int motorInput2 = 8;
const int encoderA = 2;

const float PULSES_PER_REV = 227.2;

volatile unsigned long encoderCount = 0;

const int pwmValues[] = {100, 130, 160, 190, 220, 255};
const int numberOfTests = 6;

const unsigned long sampleTime = 100;
const unsigned long testDuration = 5000;
const unsigned long stabilizationTime = 1000;

void countEncoderPulse() {
  encoderCount++;
}

void setup() {
  Serial.begin(9600);

  pinMode(motorEnable, OUTPUT);
  pinMode(motorInput1, OUTPUT);
  pinMode(motorInput2, OUTPUT);
  pinMode(encoderA, INPUT_PULLUP);

  digitalWrite(motorInput1, HIGH);
  digitalWrite(motorInput2, LOW);

  attachInterrupt(
    digitalPinToInterrupt(encoderA),
    countEncoderPulse,
    RISING
  );

  analogWrite(motorEnable, 0);

  Serial.println("CONTINUOUS OPEN LOOP TEST");
  Serial.println("PWM,Average RPM");
}

void loop() {

  for (int i = 0; i < numberOfTests; i++) {

    int currentPWM = pwmValues[i];

    // Change speed without stopping the motor
    analogWrite(motorEnable, currentPWM);

    unsigned long testStart = millis();
    unsigned long previousSample = testStart;

    float rpmSum = 0;
    int sampleCount = 0;

    bool stabilized = false;

    while (millis() - testStart < testDuration) {

      unsigned long currentTime = millis();

      if (currentTime - previousSample >= sampleTime) {

        float dt =
          (currentTime - previousSample) / 1000.0;

        previousSample = currentTime;

        noInterrupts();
        unsigned long pulses = encoderCount;
        encoderCount = 0;
        interrupts();

        // Allow one second for speed to stabilize
        if (!stabilized &&
            currentTime - testStart >= stabilizationTime) {

          stabilized = true;
          rpmSum = 0;
          sampleCount = 0;

        } else if (stabilized) {

          float rpm =
            (pulses * 60.0) /
            (PULSES_PER_REV * dt);

          rpmSum += rpm;
          sampleCount++;
        }
      }
    }

    float averageRPM = 0;

    if (sampleCount > 0) {
      averageRPM = rpmSum / sampleCount;
    }

    Serial.print(currentPWM);
    Serial.print(",");
    Serial.println(averageRPM);
  }

  analogWrite(motorEnable, 0);

  Serial.println("TEST COMPLETE");

  while (true) {
    delay(1000);
  }
}
