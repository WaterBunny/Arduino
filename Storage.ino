/*
  #### WaterBunny ####
  Module: Storage
  Description: Functions to work with the Logfile

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
void storage_init(){
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
}

//////////////////////
//// Read Logfile ////
//////////////////////
void storage_read(){
  storageLogFile.seek(0); // Jump to beginning of File   
  while(storageLogFile.available()){
    Serial.write(storageLogFile.read());
  }
}

//////////////////////////
//// Write to Logfile ////
//////////////////////////
void storage_write(){
//    storageLogFile.seek(storageLogFile.size()); // Jump to End of File
//    storageLogFile.println("clear");
}

///////////////////////
//// Clear Logfile ////
///////////////////////
void storage_clear(){
  storageLogFile.close();
  SD.remove(STORAGE_LOGFILE_NAME);
  storageLogFile = SD.open(STORAGE_LOGFILE_NAME, FILE_WRITE);
}

/////////////////////
//// Show health ////
/////////////////////
void storage_health(){
  Serial.print("SD-CARD STATUS: ");
  if(storageLogFile) Serial.println("OK");
  else Serial.println("ERROR - SD-Card not initialized or LogFile not opened.");
    
  Serial.print("SD-CARD LOGFILE SIZE: ");
  if(storageLogFile){
    storageLogFile.seek(0); // Jump to beginning of File
    Serial.println(storageLogFile.size());
  }else Serial.println("ERROR - LogFile not opened.");
}
