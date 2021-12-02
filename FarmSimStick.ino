#include "Joystick.h"
#include "Settings.h"
#include "Controls.h"
#include "RotaryEncoder.h"

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID, JOYSTICK_TYPE_JOYSTICK,
                  JOYSTICK_DEFAULT_BUTTON_COUNT, JOYSTICK_DEFAULT_HATSWITCH_COUNT,
                  true, true, true, true, true, true, true, true, true, true, true);
RotaryEncoder rotaryEncoder(Joystick, 0, 32, 0, 360, 16);

void setup() {
  // Set Range Values
  Joystick.setXAxisRange(-127, 127);
  Joystick.setYAxisRange(-127, 127);
  Joystick.setZAxisRange(-127, 127);
  Joystick.setRxAxisRange(0, 360);
  Joystick.setRyAxisRange(360, 0);
  Joystick.setRzAxisRange(0, 720);
  Joystick.setRudderRange(255, 0);
  Joystick.setThrottleRange(0, 255);
  Joystick.setAcceleratorRange(0, 255);
  Joystick.setBrakeRange(0, 255);
  Joystick.setSteeringRange(255, 0);
  
  Joystick.begin(false);
	Serial.begin(9600);

  rotaryEncoder.setup(ROT_CLK_PIN, ROT_DT_PIN, ROT_SW_PIN);

  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(ON_PIN, INPUT_PULLUP);
  pinMode(SW_JOYSTICK_PIN, INPUT_PULLUP);
}

void loop() {
  // System Disabled
  if (digitalRead(ON_PIN) != 0)
  {
    // Turn indicator light off.
    digitalWrite(LED_BUILTIN, 0);
    rotaryEncoder.reset();
    return;
  }

  // Turn indicator light on.
  digitalWrite(LED_BUILTIN, 1);

  updateJoystick(Joystick);
  rotaryEncoder.update();
  
  Joystick.sendState();
}