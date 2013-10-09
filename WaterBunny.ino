
String serialInputString = "";

void setup(){
  Serial.begin(9600);
  serialInputString.reserve(200); // Max. Size of serial command
  Serial.print("> ");
}

void loop(){

}

void serial_show_help(){
  Serial.println("### Welcome to WaterBunny CLI ###");
  Serial.println("Try one of these to talk to the Bunny");
  Serial.println("  help   - Show this help and the available commands");
  Serial.println("  read   - Gives you the output of the logfile");
  Serial.println("  clear  - Clears the logfile");
}

void serial_process_cmd(){
  if(serialInputString == "help" || serialInputString == ""){
    serial_show_help();
  }else{
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
