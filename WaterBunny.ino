/*
  #### WaterBunny ####

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
#define SERIAL_BAUD 9600

// SD-Storage
#define STORAGE_LOGFILE_NAME "BUNNY.LOG" // Name of LogFile on SD-Card
#define STORAGE_CHIPSELECT 10 // ChipSelect-Pin for SD-Card on SPI-Bus

////////////////////////////////////////////
//// Initialisation of global variables ////
////////////////////////////////////////////
// Serial
String serialInputString = ""; // String/Command typed in serial console to Bunny

// SD-Storage
File storageLogFile;

///////////////
//// Setup ////
///////////////
void setup(){
  //// General
  pinMode(STATUS_LED, OUTPUT);
  
  //// Init Serial Interface
  Serial.begin(SERIAL_BAUD);
  serialInputString.reserve(200); // Max. Size of serial command
  
  //// Init SD-Card
  // Note that even if it's not used as the CS pin, the hardware SS pin 
  // (10 on most Arduino boards, 53 on the Mega) must be left as an output 
  // or the SD library functions will not work. 
  pinMode(10, OUTPUT);
  
  Serial.println("Initializing SD-Card Storage ...");
  if (!SD.begin(STORAGE_CHIPSELECT)){
    Serial.println("initialization failed!");
  }else{
    Serial.println("initialization done.");
    storageLogFile = SD.open(STORAGE_LOGFILE_NAME, FILE_WRITE); // Open File for Read & Write
  }
  
  //// Show prompt
  Serial.print("> ");
}

void loop(){
  if(storageLogFile){
    
  }else{
    // Error-Blinking if SD-Card or Logfile is nor ready
    digitalWrite(STATUS_LED,HIGH);
    delay(500);
    digitalWrite(STATUS_LED,LOW);
    delay(500);
  }
}

void serial_show_help(){
  Serial.println("### Welcome to WaterBunny CLI ###");
  Serial.println("Try one of these to talk to the Bunny");
  Serial.println("  help   - Show this help and the available commands");
  Serial.println("  read   - Gives you the output of the logfile");
  Serial.println("  clear  - Clears the logfile");
  Serial.println("  health - Show some health of Bunny");
}

void serial_process_cmd(){
  if(serialInputString == "help" || serialInputString == ""){
    //// Show help
    serial_show_help();
  }else if(serialInputString == "read"){
    //// Print content of Logfile
    Serial.println("---- START LOG DUMP ----");

    storageLogFile.seek(0); // Jump to beginning of File   
    while(storageLogFile.available()){
      Serial.write(storageLogFile.read());
    }
    
    Serial.println("---- END LOG DUMP ----");
  }else if(serialInputString == "clear"){
    //// Clear the logfile
    storageLogFile.close();
    SD.remove(STORAGE_LOGFILE_NAME);
    storageLogFile = SD.open(STORAGE_LOGFILE_NAME, FILE_WRITE);
    Serial.println("LogFile cleared");
    Serial.print("New Size: ");
    Serial.println(storageLogFile.size());
//    storageLogFile.seek(storageLogFile.size()); // Jump to End of File
//    storageLogFile.println("clear");
  }else if(serialInputString == "health"){
    //// Show some Health-Status
    Serial.println("---- START HEALTH ----");
    
    Serial.print("SD-CARD STATUS: ");
    if(storageLogFile) Serial.println("OK");
    else Serial.println("ERROR - SD-Card not initialized or LogFile not opened.");
    
    Serial.print("SD-CARD LOGFILE SIZE: ");
    if(storageLogFile){
      storageLogFile.seek(0); // Jump to beginning of File
      Serial.println(storageLogFile.size());
    }else Serial.println("ERROR - LogFile not opened.");
    
    Serial.println("---- END HEALTH ----");
  }else{
    //// Command not found
    Serial.println("Command not found");
  }
}

void serialEvent(){
  while (Serial.available()){
    char inChar = (char)Serial.read();
    serialInputString += inChar;
    Serial.print(inChar); // Show command in Terminal

    if (inChar == '\n'){
      serialInputString.trim();
      Serial.println(serialInputString);
      serial_process_cmd();
      serialInputString = "";
      Serial.print("> ");
    }
  }
}
