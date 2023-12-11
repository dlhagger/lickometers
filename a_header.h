/********************************************************
  Include these libraries
********************************************************/
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <RTCZero.h>
#include <SPI.h>
#include <SdFat.h>
SdFat SD;  //Quick way to make SdFat work with standard SD.h sketches
#include <Adafruit_GFX.h>
#include <TimeLib.h>  //include the Arduino Time library
#include <FlashStorage.h>

/********************************************************
  Set up OLED screen
********************************************************/
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

/********************************************************
  Initialize RTC
********************************************************/
// initialize variables (these will be overwritten so doesn't really matter what they are)
byte months = 1;
byte days = 1;
byte years = 1;
byte hours = 1;
byte minutes = 1;
byte seconds = 1;

char s_month[5];
int tmonth, tday, tyear, thour, tminute, tsecond;
static const char month_names[] = "JanFebMarAprMayJunJulAugSepOctNovDec";

RTCZero rtc;

/********************************************************
  Feather pins being used
********************************************************/
#define RED_LED 13
#define GREEN_LED 8
#define LeftSip 10
#define RightSip 11
#define VBATPIN A7
#define cardSelect 4
#define buttonA 9
#define buttonB 6
#define buttonC 5
#define outLeft A1
#define outRight A3
#define shockOut 12

/********************************************************
  Initialize variables
********************************************************/
int Sip = 1;  //device number
int deviceNumber = 1;
int LeftCount = 0;
int RightCount = 0;
double LeftDuration = 0.0;
double RightDuration = 0.0;
bool sleepReady = false;
unsigned long logtime = 0;
int sleeptimer = rtc.getEpoch();
float measuredvbat = 1.00;
unsigned long BlinkMillis = millis();
unsigned long leftmillis = millis();
unsigned long rightmillis = millis();
unsigned long startmillis = millis();
char buf[21];
int SetSequence = 0;
bool BeAwake = true;
bool SleepDisplay = false;
unsigned long StartTime;
bool suppressSDerrors = false;  //set to true to suppress SD card errors at startup 

/********************************************************
  Setup flash memory
********************************************************/
typedef struct {
  int deviceNumber;
} DeviceConfig;

FlashStorage(my_flash_store, DeviceConfig);
DeviceConfig sipper;

/********************************************************
  Setup SD card
********************************************************/
void dateTime(uint16_t* date, uint16_t* time) {
  // return date using FAT_DATE macro to format fields
  *date = FAT_DATE(rtc.getYear() - 48, rtc.getMonth(), rtc.getDay());

  // return time using FAT_TIME macro to format fields
  *time = FAT_TIME(rtc.getHours(), rtc.getMinutes(), rtc.getSeconds());
}

File logfile;       // Create file object
char filename[21];  // Array for file name data logged to named in setup