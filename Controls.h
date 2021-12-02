#pragma once

void updateButton(Joystick_& Joystick, unsigned int button, unsigned int value)
{
  if(value > 0)
  {
    Joystick.pressButton(button);
  }
  else
  {
    Joystick.releaseButton(button);
  }
}

void updateJoystick(Joystick_& Joystick)
{
  int xAxis = map(analogRead(JOYSTICK_X_PIN), 0, 1023, -127, 127);
  int yAxis = map(analogRead(JOYSTICK_Y_PIN), 0, 1023, -127, 127);
  Joystick.setXAxis(xAxis);
  Joystick.setYAxis(yAxis);
  
  int swJoystick = !digitalRead(SW_JOYSTICK_PIN);
  Joystick.setButton(BTN_JOYSTICK_SW, swJoystick);
}