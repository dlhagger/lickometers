void LogData() {
  SD.begin(cardSelect, SD_SCK_MHZ(4));

  //fix filename (the .CSV extension can become corrupted) and open file
  filename[16] = '.';
  filename[17] = 'C';
  filename[18] = 'S';
  filename[19] = 'V';
  logfile = SD.open(filename, FILE_WRITE);

  //if FED3 cannot open file put SD card icon on screen
  if (!logfile) {
    error(3);
  }

  /////////////////////////////////
  // Log data and time
  /////////////////////////////////
  logfile.print(rtc.getMonth());
  logfile.print("/");
  logfile.print(rtc.getDay());
  logfile.print("/");
  logfile.print(rtc.getYear());
  logfile.print(" ");
  logfile.print(rtc.getHours());
  logfile.print(":");
  if (rtc.getMinutes() < 10)
    logfile.print('0');  // Trick to add leading zero for formatting
  logfile.print(rtc.getMinutes());
  logfile.print(":");
  if (rtc.getSeconds() < 10)
    logfile.print('0');  // Trick to add leading zero for formatting
  logfile.print(rtc.getSeconds());
  logfile.print(",");

  /////////////////////////////////
  // Log FED device number
  /////////////////////////////////
  logfile.print(Sip);  //
  logfile.print(",");

  /////////////////////////////////
  // Log milliseconds
  logfile.print(millis());
  logfile.print(",");
  /////////////////////////////////

  /////////////////////////////////
  // Log Left Stats
  /////////////////////////////////
  logfile.print(LeftCount);  //
  logfile.print(",");
  logfile.print(LeftDuration);  //
  logfile.print(",");

  /////////////////////////////////
  // Log Right Stats
  /////////////////////////////////
  logfile.print(RightCount);  //
  logfile.print(",");
  logfile.print(RightDuration);  //
  logfile.print(",");

  /////////////////////////////////
  // Log battery voltage
  /////////////////////////////////
  ReadBatteryLevel();
  logfile.println(measuredvbat);  //

  /////////////////////////////////
  // logfile.flush write to the SD card
  /////////////////////////////////
  //Blink(RED_LED, 50, 3);
  logfile.flush();
  logfile.close();
}

void CreateFile() {
  // see if the card is present and can be initialized:
  if (!SD.begin(cardSelect, SD_SCK_MHZ(4))) {
    error(2);
  }

  // Name filename in format F###_MMDDYYNN, where MM is month, DD is day, YY is year, and NN is an incrementing number for the number of files initialized each day
  strcpy(filename, "SIP_____________.CSV");  // placeholder filename
  getFilename(filename);
}

void CreateDataFile() {
  getFilename(filename);
  logfile = SD.open(filename, FILE_WRITE);
  if (!logfile) {
    error(3);
  }
}

//Write the header to the datafile
void writeHeader() {
  // Write data header to file of microSD card
  logfile.println("MM:DD:YYYY hh:mm:ss, Device, Millis, LeftCount, LeftDuration, RightCount, RightDuration, BatteryVoltage");
  logfile.close();
  LogData();
}

void error(uint8_t errno) {
  if (suppressSDerrors == false) {
    DisplaySDError();
    while (1) {
      uint8_t i;
      for (i = 0; i < errno; i++) {
        Blink(GREEN_LED, 25, 2);
      }
    }
  }
}

void getFilename(char *filename) {
  filename[3] = Sip / 100 + '0';
  filename[4] = Sip / 10 + '0';
  filename[5] = Sip % 10 + '0';
  filename[7] = rtc.getMonth() / 10 + '0';
  filename[8] = rtc.getMonth() % 10 + '0';
  filename[9] = rtc.getDay() / 10 + '0';
  filename[10] = rtc.getDay() % 10 + '0';
  filename[11] = (rtc.getYear()) / 10 + '0';
  filename[12] = (rtc.getYear()) % 10 + '0';
  filename[16] = '.';
  filename[17] = 'C';
  filename[18] = 'S';
  filename[19] = 'V';
  for (uint8_t i = 0; i < 100; i++) {
    filename[14] = '0' + i / 10;
    filename[15] = '0' + i % 10;

    if (!SD.exists(filename)) {
      break;
    }
  }
  return;
}
void sleeptimerfunction() {
  if (rtc.getEpoch() - sleeptimer >= 2) {//Sleep after 2 seconds without activity on Sipper
    sleepReady = true;
  }
}
