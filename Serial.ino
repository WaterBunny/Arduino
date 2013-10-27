/*
  #### WaterBunny ####
  Module: Serial
  Description: Functions to communicate to Bunny

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

///////////////////////
//// Init-Funktion ////
///////////////////////
void serial_init(){
  Serial.begin(SERIAL_BAUD);
  serialInputString.reserve(10); // Max. Size in byte of serial command
}

//////////////////////
//// Serial Event ////
//////////////////////
// This function is called when data is available on serial
// http://arduino.cc/en/Reference/SerialEvent
void serialEvent(){
  while (Serial.available()){
    char inChar = (char)Serial.read();
    if((inChar >= 32 && inChar < 127) || inChar == 13 || inChar == 10){ // Ignore non-printable characters (beside CR/LF (ENTER) and Space)
      serialInputString += inChar;
      Serial.print(inChar); // Show command in Terminal

      if (inChar == '\n'){
        serialInputString.trim(); // Remove line break
        serial_process_cmd(); // Interpret given command
        serialInputString = ""; // Reset command-variable
        Serial.print(F("> ")); // Show prompt
      }
    }
  }
}

///////////////////////////
//// Show Command Help ////
///////////////////////////
void serial_show_help(){
  Serial.println(F("### Welcome to WaterBunny CLI ###"));
  Serial.println(F("Try one of these to talk to the Bunny"));
  Serial.println(F("  help    - Show this help and the available commands"));
  Serial.println(F("  read    - Gives you the output of the logfile"));
  Serial.println(F("  clear   - Clears the logfile"));
  Serial.println(F("  time    - Displays the Date and Time"));
  Serial.println(F("  settime - Configures the Date and Time"));
  Serial.println(F("    Use: settime HH:MM:SS DD-MM-YYYY"));
  Serial.println(F("  health  - Show some health of Bunny"));
}

//////////////////////////////////////
//// Process given serial command ////
//////////////////////////////////////
void serial_process_cmd(){
  if(serialInputString == "help" || serialInputString == ""){
    // Show help
    serial_show_help();
  }else if(serialInputString == "read"){
    // Print content of Logfile
    Serial.println(F("---- START LOG DUMP ----"));
    Serial.println(F(STORAGE_HEADER));
    storage_read();
    Serial.println(F("---- END LOG DUMP ----"));
  }else if(serialInputString == "clear"){
    // Clear the logfile
    storage_clear();
    Serial.println(F("LogFile cleared"));
  }else if(serialInputString == "time"){
    // Displays the Date and Time
    Serial.println(rtc_get_timestamp());
  }else if(serialInputString.substring(0,7) == "settime"){
    // Configures the Date and Time
    rtc_set_time(serialInputString.substring(8));
  }else if(serialInputString == "health"){
    // Show some Health-Status
    Serial.println(F("---- START HEALTH ----"));
    
    // General
    Serial.print(F("RAM FREE: "));
    Serial.println(FreeRam());
    
    // RTC
    rtc_health();
    
    // Storage
    storage_health();

    Serial.println(F("---- END HEALTH ----"));
  }else{
    // Command not found
    Serial.println(F("Command not found"));
  }
}
