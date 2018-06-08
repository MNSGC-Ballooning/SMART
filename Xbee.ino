XBee xBee = XBee(&xBee_Serial, ID);

//setup function for xBee
void xBeeSetup() {
  pinMode(radioLED_pin, OUTPUT);
  xBee_Serial.begin(9600);
  String header = "GPS Time,Type,Message";
//  logRadio(header);
}

//function that simply beacons data to ground without logging
void beacon(String data) {
  digitalWrite(radioLED_pin, HIGH);
  xBee.send(data);
  digitalWrite(radioLED_pin, LOW);
}

//function that sends an xBee message and records it in the radio log
void sendXBee(String message) {
  digitalWrite(radioLED_pin, HIGH);
  xBee.send(message);
  digitalWrite(radioLED_pin, LOW);
//  String data = getGPStime() + ",TX," + message;
//  logRadio(data);
}

//function to check for incoming xBee commands, called repeatedly during loop()
void xBeeCommand() {
  String command = xBee.receive();
  if (command.equals("")) return; //don't do anything if no command was received
  else {  //otherwise, log, then process the command
    digitalWrite(radioLED_pin, HIGH);
//    String data = getGPStime() + ",RX," + command;
//    logRadio(data);
    digitalWrite(radioLED_pin, LOW);
  }
  
  //all commands go in a series of if-else statements; if a command matches a certain string, do a certain thing
  //keep commands short when possible - ~2-4 characters A-Z 0-9 only. At a minimum include ability to request data.
  if (command.equals("ABC")) {
    //-----Do something here-----
  }
  else if (command.equals("123")) {
    //-----Do something else here-----
  }
  //-----Add more commands as needed-----
   else { //if received command doesn't match any expected strings, inform ground of error
     String message = "Error: " + command + " - command not recognized";
     sendXBee(message);
   }
}
