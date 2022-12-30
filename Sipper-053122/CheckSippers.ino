/********************************************************
  Check Sippers
********************************************************/
void  CheckSippers() {
  ReadBatteryLevel();  //Read battery level
  sleeptimerfunction ();  // Is it time to log data? (Edit variable "logfreq" in a_header to change this timing)

  // Monitor Left Sip
  leftmillis = millis();

  while (digitalRead (LeftSip) == LOW) {
    digitalWrite (outLeft, HIGH); //Left output HIGH
    display.fillCircle(31, 3, 2, WHITE);
    display.display();

    if (digitalRead (LeftSip) == HIGH) {
      LeftCount++;
      LeftDuration += ((millis() - leftmillis)/(1000.00));
    }
  }

  // Monitor Right Sip
  rightmillis = millis();

  while (digitalRead (RightSip) == LOW) { // if right sip beam is broken
    digitalWrite (outRight, HIGH);  // Right output HIGH
    display.fillCircle(83, 3, 2, WHITE);
    display.display();

    if (digitalRead (RightSip) == HIGH) {
      RightCount++;
      RightDuration += ((millis() - rightmillis)/(1000.00));
    }
  }

  // Show time elapsed when C is pressed
  while (digitalRead (buttonC) == LOW) {
    DisplayTimeElapsed();
  }

  // Toggle between screen being off with Button B
  if (digitalRead (buttonB) == LOW) {
    if (SleepDisplay == true) {
      SleepDisplay = false;
      display.clearDisplay();
      display.setCursor(10, 10);
      display.println("Display ON");
      display.display();
      Blink (RED_LED, 50, 2);
      delay (500);
    }

    else {
      SleepDisplay = true;
      display.clearDisplay();
      display.setCursor(10, 10);
      display.println("Display OFF");
      display.display();
      Blink (RED_LED, 50, 2);
      delay (500);
    }
  }
}
