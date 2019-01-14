XBee xBee = XBee(&xBee_Serial, ID);
String previousCommand="";
long SpamTimer=15;

//setup function for xBee
void xBeeSetup() {
  pinMode(radioLED_pin, OUTPUT);
  Serial.begin(9600);
  String header = "GPS Time,Type,Message";
//  logRadio(header);
}

//function that simply beacons data to ground without logging
void beacon(String data) {
  if (millis()-prevTime>=60000){
    prevTime = millis();
    xBee.send(data);
  } 
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
  else if (command.equals(previousCommand))
  {xBee.send("No spam. No same command every 15 seconds");
  }
  else {  //otherwise, log, then process the command
    digitalWrite(radioLED_pin, HIGH);
//    String data = getGPStime() + ",RX," + command;
//    logRadio(data);
    digitalWrite(radioLED_pin, LOW);
  }
  
  //all commands go in a series of if-else statements; if a command matches a certain string, do a certain thing
  //keep commands short when possible - ~2-4 characters A-Z 0-9 only. At a minimum include ability to request data.
  if (command.equals("CUT" + String(smartUnit))) {
    xBee.send("Attempting cut...");
    smart.release();
    released = true;
    xBee.send("\nSee you on the other side...");
    previousCommand=command;
    SpamTimer=millis()/1000.0+15.0;
  }
//   else if (command.equals("TLEFT")) {
//    xBee.send("Sending time...");
//    float TRemain = cutTime-millis()/60000.0;
//    xBee.send("\nTime remaining is "+String(TRemain)+" min");
//    previousCommand=command;
//    SpamTimer=millis()/1000.0+15.0;
//  }
//      else if (command.substring(0,3)=="ADD")
//  {xBee.send("Attempting add...");
//    String TAdd=command.substring(3);
//  cutTime=cutTime+TAdd.toFloat();
//  float TRemain=cutTime-millis()/60000.0;
//   xBee.send("\nTime remaining is "+String(TRemain)+" min");
//   previousCommand=command;
//   SpamTimer=millis()/1000.0+15.0;
//  }
//  else if (command.substring(0,3)=="SUB")
//  {xBee.send("Attempting sub...");
//    String TSub=command.substring(3);
//  cutTime=cutTime-TSub.toFloat();
//  float TRemain=cutTime-millis()/60000.0;
//   xBee.send("\nTime remaining is "+String(TRemain)+" min");
//   previousCommand=command;
//   SpamTimer=millis()/1000.0+15.0;
//  }
 /*
  else if (command.equals("+1")) {
    xBee.send("Attempting +1...");
    cutTime = cutTime+1;
    float TRemain = cutTime-millis()/60000.0;
    xBee.send("\nTime remaining is "+String(TRemain)+" min");
    previousCommand=command;
    SpamTimer=millis()/1000.0+15.0;
  }
  else if (command.equals("-1")) {
    xBee.send("Attempting -1");
    cutTime = cutTime-1;
    float TRemain = cutTime-millis()/60000.0;
    xBee.send("\nTime remaining is "+String(TRemain)+" min");
    previousCommand= command;
    SpamTimer=millis()/1000.0+15.0;
  }
  else if (command.equals("+2")) {
    cutTime = cutTime+2;
    float TRemain = cutTime-millis()/60000.0;
    xBee.send("\nTime remaining is "+String(TRemain)+" min");
  }
  else if (command.equals("-2")) {
    cutTime = cutTime-2;
    float TRemain = cutTime-millis()/60000.0;
    xBee.send("\nTime remaining is "+String(TRemain)+" min");
  }
  else if (command.equals("+4")) {
    cutTime = cutTime+4;
    float TRemain = cutTime-millis()/60000.0;
    xBee.send("\nTime remaining is "+String(TRemain)+" min");
  }
  else if (command.equals("-4")) {
    cutTime = cutTime-4;
    float TRemain = cutTime-millis()/60000.0;
    xBee.send("\nTime remaining is "+String(TRemain)+" min");
  }
  else if (command.equals("+8")) {
    cutTime = cutTime+8;
    float TRemain = cutTime-millis()/60000.0;
    xBee.send("\nTime remaining is "+String(TRemain)+" min");
  }
  else if (command.equals("-8")) {
    cutTime = cutTime-8;
    float TRemain = cutTime-millis()/60000.0;
    xBee.send("\nTime remaining is "+String(TRemain)+" min");
  }
  else if (command.equals("+16")) {
    cutTime = cutTime+16;
    float TRemain = cutTime-millis()/60000.0;
    xBee.send("\nTime remaining is "+String(TRemain)+" min");
  }
  else if (command.equals("-16")) {
    cutTime = cutTime-16;
    float TRemain = cutTime-millis()/60000.0;
    xBee.send("\nTime remaining is "+String(TRemain)+" min");
  }
  else if (command.equals("+32")) {
    cutTime = cutTime+32;
    float TRemain = cutTime-millis()/60000.0;
    xBee.send("\nTime remaining is "+String(TRemain)+" min");
  }
  else if (command.equals("-32")) {
    cutTime = cutTime-32;
    float TRemain = cutTime-millis()/60000.0;
    xBee.send("\nTime remaining is "+String(TRemain)+" min");
  }
*/

  //-----Add more commands as needed-----
   else { //if received command doesn't match any expected strings, inform ground of error
     String message = "Error: " + command + " - command not recognized";
     sendXBee(message);
   }
}

void SpamControl() {
  if (previousCommand!="" && millis()/1000.0>SpamTimer)
  {previousCommand="";
  }
}
