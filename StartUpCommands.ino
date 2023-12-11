/********************************************************
  Start Up Commands
********************************************************/
void StartUpCommands() {
  Serial.begin(96000);

  /********************************************************
     Start RTC
  ********************************************************/
  rtc.begin();  // initialize RTC

  /********************************************************
    Setting digital pin modes
  ********************************************************/
  pinMode(LeftSip, INPUT);
  pinMode(RightSip, INPUT);
  pinMode(RED_LED, OUTPUT);
  pinMode(GREEN_LED, OUTPUT);
  pinMode(buttonA, INPUT_PULLUP);
  pinMode(buttonB, INPUT_PULLUP);
  pinMode(buttonC, INPUT_PULLUP);
  pinMode(outLeft, OUTPUT);
  pinMode(outRight, OUTPUT);

  /********************************************************
     Attach interrupts to wake the sipper device from sleep
  ********************************************************/
  attachInterrupt(LeftSip, wake, CHANGE);
  attachInterrupt(RightSip, wake, CHANGE);
  attachInterrupt(buttonA, wake, CHANGE);
  attachInterrupt(buttonB, wake, CHANGE);
  attachInterrupt(buttonC, wake, CHANGE);

  /********************************************************
    Setting digital outputs including
  ********************************************************/
  digitalWrite(GREEN_LED, HIGH);
  digitalWrite(RED_LED, LOW);
  digitalWrite(outLeft, LOW);
  digitalWrite(outRight, LOW);

  /********************************************************
    Read stored flash data
  ********************************************************/
  sipper = my_flash_store.read();
  Sip = sipper.deviceNumber;

  /********************************************************
    SD Card setup function
  ********************************************************/
  CreateFile();

  /********************************************************
    Start, clear, and setup the display
  ********************************************************/
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(0);  // Where c is a value from 0 to 255 (sets contrast e.g. brightness)

  display.setRotation(4);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.clearDisplay();
  display.display();

  /********************************************************
     Display start date time and filename
  ********************************************************/
  //delay until button A is pressed to start sipper
  while (digitalRead(buttonA) == HIGH) {
    display.fillRoundRect(00, 0, 132, 11, 1, BLACK);
    leftmillis = millis();
    rightmillis = millis();
    startmillis = millis();
    DisplayStartScreen();

    //Code for starting the sequence to set the clock and sipper #
    if (digitalRead(buttonB) == LOW) {  //if button B is held
      delay(500);
      if (digitalRead(buttonB) == LOW) {
        SetSequence = 1;
        SetClockVars();
        display.clearDisplay();  //after setting variables, return to start screen
        DisplayStartScreen();
      }
    }

    //Code for starting the sequence to set the clock and sipper #
    if (digitalRead(buttonC) == LOW) {  //if button B is held
      delay(500);
      if (digitalRead(buttonC) == LOW) {
        SetSequence = 10;
        display.clearDisplay();  //after setting variables, return to start screen
        DisplayStartScreen();
      }
    }
  }
  Blink(RED_LED, 50, 3);

  //Print some data to Serial Monitor at startup
  Serial.println("FlashMem data:");
  Serial.println(sipper.deviceNumber);
  Serial.print("Filename:");
  Serial.println(filename);

  // Create data file for current session
  CreateDataFile();
  writeHeader();

  StartTime = rtc.getEpoch();  //StartTime for the file
}
