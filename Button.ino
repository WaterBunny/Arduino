/*
  #### WaterBunny ####
  Module: Button
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

void button_init(){
  pinMode(BUTTON, INPUT);
  digitalWrite(BUTTON, HIGH);
  attachInterrupt(1,button_push,CHANGE);
}

void button_push(){
  int state = digitalRead(BUTTON);
  
  // Button pressed? Store DownTime
  if(state == LOW && buttonLastState == HIGH){
    buttonDownTime = millis();
  }

  // Button released? Store UpTime and do some magic
  if(state == HIGH && buttonLastState == LOW){
    buttonUpTime = millis();

    if((buttonUpTime - long(BUTTON_HOLD_TIME)) > buttonDownTime){
      // Button Hold
      startRecording = !startRecording;
      recordWatermark = false;
    }else{
      // Button Press
      recordWatermark = true;
    }
  }
  
  buttonLastState = state;
}
