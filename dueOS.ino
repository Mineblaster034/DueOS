// I based this on
// Demo Code for SerialCommand Library
// Steven Cogswell
// May 2011

//it will be updated soon

#include <SerialCommand.h> 

#define arduinoLED 13   // Arduino LED on board

SerialCommand sCmd;     // The demo SerialCommand object

//by me, going to use this for the update.
String processor = "AVR based. !!It is better to use an arduino due!!";
String prompt = "NoUser@system";

#if defined(__SAM3X8E__)
#define processor   "ARM Cortex M3"
#endif
//end of my own stuff


void setup() {
  pinMode(arduinoLED, OUTPUT);      // Configure the onboard LED for output
  digitalWrite(arduinoLED, LOW);    // default to LED off
  

  Serial.begin(9600);         //note: should be higher! (Mineblaster034)

  Serial.println(prompt);

  // Setup callbacks for SerialCommand commands
  sCmd.addCommand("ledOn",     LED_on);          // Turns LED on
  sCmd.addCommand("ledOff",    LED_off);         // Turns LED off
  sCmd.addCommand("hello",     sayHello);        // Echos the string argument back
  sCmd.addCommand("p",         processCommand);
  sCmd.addCommand("echo",      echo);
  sCmd.addCommand("ledBlink",  LED_blink);
  sCmd.addCommand("CPU_info",  CPU_info);
  sCmd.setDefaultHandler(unrecognized);          // Handler for command that isn't matched  (says "What?")

}

void loop() {
  while(!Serial.available());
  sCmd.readSerial();     // We don't do much, just process serial commands
}


void LED_on() {
  Serial.println("LED on");
  digitalWrite(arduinoLED, HIGH);
}

void LED_off() {
  Serial.println("LED off");
  digitalWrite(arduinoLED, LOW);
}

void LED_blink(){
  Serial.println("blink led 2 times");
  digitalWrite(arduinoLED, HIGH);
  delay(1000);
  digitalWrite(arduinoLED, LOW);
  delay(1000);
  digitalWrite(arduinoLED, HIGH);
  delay(1000);
  digitalWrite(arduinoLED, LOW);
  
  
}

//also mine
void CPU_info(){
  Serial.println(processor);
}
//-------------

void sayHello() {
  char *arg;
  arg = sCmd.next();    // Get the next argument from the SerialCommand object buffer
  if (arg != NULL) {    // As long as it existed, take it
    Serial.print("Hello ");
    Serial.println(arg);
  }
  else {
    Serial.println("Hello, whoever you are");
  }
}


void processCommand() {
  int aNumber;
  char *arg;

  Serial.println("We're in processCommand");
  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atoi(arg);    // Converts a char string to an integer
    Serial.print("First argument was: ");
    Serial.println(aNumber);
  }
  else {
    Serial.println("No arguments");
  }

  arg = sCmd.next();
  if (arg != NULL) {
    aNumber = atol(arg);
    Serial.print("Second argument was: ");
    Serial.println(aNumber);
  }
  else {
    Serial.println("No second argument");
  }
}


//partially cloned from above  
void echo(){
  char *arg;

  arg = sCmd.next();
  Serial.println(arg);
}
//-----------------------


// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command) {
  Serial.println("System error: unknown command");
  Serial.print(command);
  Serial.println(" <-----[here]");
}
