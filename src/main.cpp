#include <Adafruit_PWMServoDriver.h>
#include <Arduino.h>
#include <Wire.h>

#if defined(ARDUINO_ARCH_RP2040)
TwoWire i2c(2, 3);
#define I2C_PORT i2c
#else
#define I2C_PORT &Wire
#endif

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40, I2C_PORT);

// Depending on your servo make, the pulse width min and max may vary, you
// want these to be as small/large as possible without hitting the hard stop
// for max range. You'll have to tweak them as necessary to match the servos you
// have!

#define THUMBPORT 4
#define THUMBIN 200   // In
#define THUMBOUT 500  // Out
#define INDEXPORT 0
#define INDEXIN 150   // In
#define INDEXOUT 550  // Out
#define MIDDLEPORT 1
#define MIDDLEOUT 200  // Out
#define MIDDLEIN 500   // In
#define RINGPORT 2
#define RINGIN 200   // In
#define RINGOUT 500  // Out
#define PINKYPORT 3
#define PINKYOUT 200  // Out
#define PINKYIN 500   // In

#define USMIN \
  600  // This is the rounded 'minimum' microsecond length based on the minimum
       // pulse of 150
#define SERVO_FREQ 50

// our servo # counter
uint8_t servonum = 0;

void setup() {
  Serial.begin(115200);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);  // Analog servos run at ~50 Hz updates
  delay(10);
}

void loop() {
  Serial.println("Enter data:");
  while (Serial.available() == 0) delay(10);
  String input = Serial.readString();
  if (input.length() == 6) {
    uint16_t thumb = input[0] == '1' ? THUMBOUT : THUMBIN + 100;
    uint16_t index = input[1] == '1' ? INDEXOUT : INDEXIN;
    uint16_t middle = input[2] == '1' ? MIDDLEOUT : MIDDLEIN;
    uint16_t ring = input[3] == '1' ? RINGOUT : RINGIN;
    uint16_t pinky = input[4] == '1' ? PINKYOUT : PINKYIN;

    pwm.setPWM(THUMBPORT, 0, thumb);
    pwm.setPWM(INDEXPORT, 0, index);
    pwm.setPWM(MIDDLEPORT, 0, middle);
    pwm.setPWM(RINGPORT, 0, ring);
    pwm.setPWM(PINKYPORT, 0, pinky);
  } else {
    Serial.println("Invalid input. Please enter a string of length 5.");
  }
}