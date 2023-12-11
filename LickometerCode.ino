/********************************************************
  Sippers V1.0
  Adapted by David L. Haggerty
  Orginally Written by Lex Kravitz and Meaghan Creed
  https://hackaday.io/project/160388-automated-mouse-homecage-two-bottle-choice-test-v2

  December, 2023

  Functions & Changes:
  - Pre-defined bout data logging removed - data will automatically log after every single beam break interaction (similar to FED3 nosepokes)
  - Change to sleep functionality (sceen on and off mode still enabled, but "CPU is not put to sleep" to keep data logging functions quick and without error)
  - Removed "shock" output functionality 
  - Write code to ensure latest boards manager and libraries are supported 
  - Added RTC flashing to this script - User no longer need to set the RTC then flash the software functionlaity - a single file now does both
  - Millis now writes to the output file during datalogging, this is more accruate than date/time column when determining bout durations and times between bouts and helpful in analysis
    
  Planned updates
  - BNC things (out and in [read,write,interupt], specific time writing and logging to datafiles, allow for BNC start pulse to sync clocks, etc.)

  This project code includes code from:
  *** Adafruit, who made the hardware breakout boards and associated code ***

  Cavemoa's excellent examples of datalogging with the Adalogger:
  https://github.com/cavemoa/Feather-M0-Adalogger

  Uses Arduino Time library http://playground.arduino.cc/code/time
  Maintained by Paul Stoffregen https://github.com/PaulStoffregen/Time

  Uses Arduino Zero RTC library https://www.arduino.cc/en/Reference/RTC
  Maintained by Arturo Guadalupi https://github.com/arduino-libraries/RTCZero

  This project is released under The MIT license:

  Copyright (c) 2023 David Haggerty

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
********************************************************/


/********************************************************
  Setup code
********************************************************/
#include "a_Header.h" //See "a_Header.h" for #defines and other constants 

void setup() {
  SetRTC();
  StartUpCommands();
}

/********************************************************
  Main loop
********************************************************/
void loop() {
  UpdateDisplay();
  CheckSippers();
  GoToSleep ();
  wakeUp();
}