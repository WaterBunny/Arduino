#!/usr/bin/perl -W
# #### WaterBunny ####
# Module: dump_data.pl
# Description: Script to dump the logged Data to a File
#
# Copyright (C) 2013  WaterBunny
# Torsten Amshove <torsten@amshove.net>, Stefan Moestel <stefan@moestel.org>
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License along
# with this program; if not, write to the Free Software Foundation, Inc.,
# 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.

use Device::SerialPort;
use POSIX qw(strftime);

# Print usage
if($#ARGV < 0){
  print "Usage: dump_data.pl <SerialPort> [<File>]\n";
  exit 1;
}

my $serial_port = $ARGV[0];
my $logfile_name;

# Logfile is optional - if not set, choose date and time as filename
if($#ARGV < 1){
  $logfile_name = strftime "%Y%m%d_%H%M%S.csv", localtime;  
}else{
  $logfile_name = $ARGV[1];
}

# open serial and logfile
my $port = Device::SerialPort->new($serial_port) or die "ERROR: Could not open serial port $serial_port: $!\n";
open FILE, ">", $logfile_name or die "ERROR: Could not open logfile $logfile_name: $!\n";
 
# configure serial interface
$port->baudrate(9600);
$port->databits(8);
$port->parity("none");
$port->stopbits(1);
 
# send commands to WaterBunny
$port->write("\n");     # avoid errors, if there are some characters send before
$port->write("read\n"); # get data from WaterBunny

# read data from serial
print "Looking for serial data ..\n";
my $data = 0;
my $clear = 0;
while (1) {
  my $char = $port->lookfor();
  chop($char);
 
  if ($char) {
    # break loop, if END is reached 
    if($char eq "---- END LOG DUMP ----"){
      print "End of data found - dumping data completed!\n";

      # remove data from WaterBunny?
      print "Delete data from WaterBunny? (y/n)\n";
      my $answ = <STDIN>;
      chomp($answ);
      if($answ eq "y"){
        print "Clearing WaterBunny data ..\n";
        $port->write("clear\n");
        $port->write("health\n");
        $data = 0;
        $clear = 1;
      }else{
        last;
      }
    }

    # look, if clearing data was successful
    if($clear && $char =~ /^SD-CARD LOGFILE SIZE: ([0-9]*)$/){
      if($1 == 0){
        print "WaterBunny data cleared\n";
      }else{
        print "Sorry, something went wrong - logfile size on WaterBunny: $1\n";
      }
      last;
    }

    # write data to file, if START was found before
    if($data){
      print FILE $char."\n"; 
    }

    # mark found of START
    if($char eq "---- START LOG DUMP ----"){ 
      $data = 1;
      print "Beginning of data found - dumping data to file ..\n";
    }
  }
}

# close handles
$port->close();
close(FILE);
