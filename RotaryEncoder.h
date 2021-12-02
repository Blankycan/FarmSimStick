#pragma once
#include "Settings.h"
#include "Controls.h"

class RotaryEncoder
{
  public:
    RotaryEncoder(Joystick_& Joystick, int16_t minVal, int16_t maxVal, int16_t minOut, int16_t maxOut, int16_t startVal = 0) :
      mJoystick(Joystick),
      mMinVal(minVal),
      mMaxVal(maxVal),
      mMinOut(minOut),
      mMaxOut(maxOut),
      mStartVal(startVal),
      counter(startVal)
    {
    }

    void applyValue(unsigned int inValue)
    {
      int16_t value = map(inValue, mMinVal, mMaxVal, mMinOut, mMaxOut);
      mJoystick.setRxAxis(value);
    }

    void reset()
    {
      if(counter != mStartVal)
      {
        counter = mStartVal;
        applyValue(counter);
      }
      lastStateCLK = digitalRead(mClkPin);
    }

    void setup(uint8_t clkPin, uint8_t dtPin, uint8_t swPin)
    {
      mClkPin = clkPin;
      mDtPin = dtPin;
      mSwPin = swPin;

      pinMode(mClkPin, INPUT);
      pinMode(mDtPin, INPUT);
      pinMode(mSwPin, INPUT_PULLUP);
      // Read the initial state of CLK
      lastStateCLK = digitalRead(mClkPin);
      applyValue(counter);
    }

    void update()
    {
      currentStateCLK = digitalRead(mClkPin); // Reads the "current" state of the outputA
      // If the previous and the current state of the outputA are different, that means a Pulse has occured
      if (currentStateCLK != lastStateCLK){     
        // If the mDtPin state is different to the mClkPin state, that means the encoder is rotating clockwise
        if (digitalRead(mDtPin) != currentStateCLK) { 
          counter ++;
        } else {
          counter --;
        }
        counter = constrain(counter, mMinVal, mMaxVal);
        applyValue(counter);
      } 
      lastStateCLK = currentStateCLK; // Updates the previous state of the mClkPin with the current state
      
      uint8_t btnState = !digitalRead(mSwPin);
      mJoystick.setButton(BTN_ROTARY_SW, btnState);
    }

  private:
    Joystick_& mJoystick;
    uint8_t mClkPin;
    uint8_t mDtPin;
    uint8_t mSwPin;
    int16_t mMinVal;
    int16_t mMaxVal;
    int16_t mMinOut;
    int16_t mMaxOut;
    int16_t mStartVal;
    int16_t counter;
    int currentStateCLK;
    int lastStateCLK;
};