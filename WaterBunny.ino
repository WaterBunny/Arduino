/*
  #### WaterBunny ####
  Module: Main
  Description: Main module with configuration, setup() and loop()
  
  Copyright (C) 2013  WaterBunny
  Torsten Amshove <torsten@amshove.net>, Stefan Moestel <stefan@moestel.org>

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation; either version 2 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc.,
  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
#include <SdFat.h>
#include <DS1307RTC.h>
#include <Wire.h>
#include <Time.h>
#include <SPI.h>
#include <ADXL362.h>

///////////////////////
//// Configuration ////
///////////////////////
// General
#define STATUS_LED 7 // Pin of status LED

// Button
#define BUTTON 3 // Pin of Button
#define BUTTON_INT 1 // Interrupt of Button (see http://arduino.cc/en/Reference/attachInterrupt)
#define BUTTON_HOLD_TIME 1000 // Time in ms to identify a button press as "hold"

// Serial
#define SERIAL_BAUD 9600 // Baud-Rate of serial port

// SD-Storage
#define STORAGE_LOGFILE_NAME "BUNNY.LOG" // Name of LogFile on SD-Card
#define STORAGE_CHIPSELECT 6 // ChipSelect-Pin for SD-Card on SPI-Bus
#define STORAGE_HEADER "Timestamp,CurrentMillis,X-Data,Y-Data,Z-Data,Temperature" // First line of data dump

/////////////////////////////////////
//// Initialise global variables ////
/////////////////////////////////////
// General
boolean startRecording = false;
boolean lastRecordingState = false;
boolean recordWatermark = false;

// Button
int buttonLastState = HIGH;
long buttonUpTime;
long buttonDownTime;

// Time Element
tmElements_t rtcTime; // Actual time of RTC

// Serial
String serialInputString = ""; // String/Command typed in serial console to Bunny

// SD-Storage
SdFat storageSdCard;
SdFile storageLogFile;

// ACC
ADXL362 acc;
int accX, accY, accZ, accTemp;

///////////////
//// Setup ////
///////////////
void setup(){
  // General
  pinMode(STATUS_LED, OUTPUT);

  // Init Button
  button_init();
  
  // Init Serial Interface
  serial_init();
  
  // Init Accelerometer
  acc_init();
  
  // Init SD-Card
  storage_init();
  
  // Show prompt
  Serial.print(F("> "));
}

//////////////
//// Loop ////
//////////////
long blaBlubb = 0; // TRASH
void loop(){
  if(startRecording){
    unsigned long currentMillis = millis();
    
    if(lastRecordingState != startRecording){
      // Show the recording state with the LED
      digitalWrite(STATUS_LED,HIGH);
      
      Serial.println(F("Recording started"));
      lastRecordingState = startRecording;
    }
    
    // If Button is pressed, write a Watermark to Logfile
    if(recordWatermark){
      String newLine = "";
      newLine += rtc_get_timestamp();
      newLine += ",";
      newLine += currentMillis;
      newLine += ",-,-,-,-";
      storage_write(newLine);
      
      recordWatermark = false;
      
      Serial.println(F("Watermark logged"));
      
      // Flash LED to show the Recording of the Watermark
      digitalWrite(STATUS_LED,LOW);
      delay(200);
      digitalWrite(STATUS_LED,HIGH);
    }
      
      
    // TRASH START - just to get some values in Logfile - Replace Me with usefull stuff please!! 
    if(currentMillis - blaBlubb > 5000) {
  
      blaBlubb = currentMillis;
      
      acc.readXYZTData(accX, accY, accZ, accTemp); 
      String newLine = "";
      newLine += rtc_get_timestamp();
      newLine += ",";
      newLine += currentMillis;
      newLine += ",";
      newLine += accX;
      newLine += ",";
      newLine += accY;
      newLine += ",";
      newLine += accZ;
      newLine += ",";
      newLine += accTemp;
      storage_write(newLine);
    }
    // TRASH END
  }else{
    if(lastRecordingState != startRecording){
      // Show the recording state with the LED
      digitalWrite(STATUS_LED,LOW);
      
      Serial.println(F("Recording stopped"));
      lastRecordingState = startRecording;
    }
  }
}
