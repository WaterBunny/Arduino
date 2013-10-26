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
  Serial.println("Initializing SD-Card Storage ...");
  if (!storageSdCard.begin(STORAGE_CHIPSELECT, SPI_HALF_SPEED)) storageSdCard.initErrorHalt();

  storageLogFile.open(STORAGE_LOGFILE_NAME, O_RDWR | O_APPEND | O_CREAT);
  if(!storageLogFile.isOpen()) storageSdCard.errorHalt_P(PSTR("file.open"));
}

//////////////////////
//// Read Logfile ////
//////////////////////
void storage_read(){
  int data;
  storageLogFile.rewind(); // Jump to beginning of File
  while((data = storageLogFile.read()) >= 0) Serial.write(data);
}

//////////////////////////
//// Write to Logfile ////
//////////////////////////
void storage_write(String &line){
  storageLogFile.println(line);
  storageLogFile.sync();
}

///////////////////////
//// Clear Logfile ////
///////////////////////
void storage_clear(){
  storageLogFile.truncate(0);
  storageLogFile.sync();
}

/////////////////////
//// Show health ////
/////////////////////
void storage_health(){
  Serial.print(F("SD-CARD LOGFILE STATUS: "));
  if(storageLogFile.isOpen()) Serial.println(F("OK"));
  else Serial.println(F("ERROR - LogFile not opened."));
  
  Serial.print(F("SD-CARD LOGFILE SIZE: "));
  if(storageLogFile.isOpen()){
    Serial.println(storageLogFile.fileSize());
  }else Serial.println(F("ERROR - LogFile not opened."));
}
