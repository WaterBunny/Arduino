/*
  #### WaterBunny ####
  Module: Accelerometer
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

///////////////////////
//// Init-Funktion ////
///////////////////////
void acc_init(){
  acc.begin();                   // Setup SPI protocol, issue device soft reset
  acc.beginMeasure();            // Switch ADXL362 to measure mode  
//  acc.checkAllControlRegs();     // Burst Read all Control Registers, to check for proper setup
}
