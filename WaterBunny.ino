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
#include <SD.h>

///////////////////////
//// Configuration ////
///////////////////////
// General
#define STATUS_LED 6 // Pin of status LED

// Serial
#define SERIAL_BAUD 9600 // Baud-Rate of serial port

// SD-Storage
#define STORAGE_LOGFILE_NAME "BUNNY.LOG" // Name of LogFile on SD-Card
#define STORAGE_CHIPSELECT 10 // ChipSelect-Pin for SD-Card on SPI-Bus

/////////////////////////////////////
//// Initialise global variables ////
/////////////////////////////////////
// Serial
String serialInputString = ""; // String/Command typed in serial console to Bunny

// SD-Storage
File storageLogFile; // Filehandle of logfile

///////////////
//// Setup ////
///////////////
void setup(){
  // General
  pinMode(STATUS_LED, OUTPUT);
  
  // Init Serial Interface
  serial_init();
  
  // Init SD-Card
  storage_init();
  
  // Show prompt
  Serial.print("> ");
}

//////////////
//// Loop ////
//////////////
long blaBlubb = 0; // TRASH
void loop(){
  if(storageLogFile){
    
    // TRASH START - just to get some values in Logfile - Replace Me with usefull stuff please!!
    unsigned long currentMillis = millis();
 
    if(currentMillis - blaBlubb > 5000) {
      blaBlubb = currentMillis;
      String newLine = "";
      newLine += String(blaBlubb);
      newLine += String(",1,2,3");
      storage_write(newLine);
    }
    // TRASH END
  }else{
    // Error-Blinking if SD-Card or Logfile is nor ready
    digitalWrite(STATUS_LED,HIGH);
    delay(500);
    digitalWrite(STATUS_LED,LOW);
    delay(500);
  }
}
