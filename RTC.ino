/*
  #### WaterBunny ####
  Module: RTC
  Description: Functions to work with the RTC
  
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

///////////////////////////////
//// Set RTC Time and Date ////
///////////////////////////////
void rtcSetTime(String dateTime){
  tmElements_t newTime;
  unsigned int newHour, newMin, newSec, newDay, newMonth, newYear;
  char dateTimeChar[20];
  
  if(dateTime.length() != 19){
    Serial.println(F("ERROR: Dateformat wrong"));
    return;
  }
  dateTime.toCharArray(dateTimeChar,dateTime.length()+1);
  
  if(sscanf(dateTimeChar,"%d:%d:%d %d-%d-%d",&newHour,&newMin,&newSec,&newDay,&newMonth,&newYear) != 6){
    Serial.println(F("ERROR: Dateformat wrong"));
    return;
  }
  newTime.Hour = newHour;
  newTime.Minute = newMin;
  newTime.Second = newSec;
  newTime.Day = newDay;
  newTime.Month = newMonth;
  newTime.Year = CalendarYrToTm(newYear);
  
  if(RTC.write(newTime)) Serial.println(F("Date and Time successful set"));
  else Serial.println(F("ERROR: Date and Time couldn't be set"));
}

//////////////////////////////
//// Get Timestamp of RTC ////
//////////////////////////////
String rtcGetTimestamp(){
  String timestamp = "";

  RTC.read(rtcTime);
  timestamp += tmYearToCalendar(rtcTime.Year);
  timestamp += "-";
  timestamp += rtcTime.Month;
  timestamp += "-";
  timestamp += rtcTime.Day;
  timestamp += " ";
  if(rtcTime.Hour < 10) timestamp += "0";
  timestamp += rtcTime.Hour;
  timestamp += ":";
  if(rtcTime.Minute < 10) timestamp += "0";
  timestamp += rtcTime.Minute;
  timestamp += ":";
  if(rtcTime.Second < 10) timestamp += "0";
  timestamp += rtcTime.Second;
  
  return timestamp;
}
