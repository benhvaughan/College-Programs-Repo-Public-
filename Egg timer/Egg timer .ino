//(1) Libraries
#include <LiquidCrystal.h>                                   //includes function for LCD (l44)
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;  //(l48)
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);                   //create an instance of a lcd class //(l49)



//(2) Constants
const int startButtonPin = 10;
const int stopButtonPin = 9;
const int chooseButtonPin = 8;
const int buzzer = 7;


//(3) Variables
String topLineLCD = "Welcome to      ";
String bottomLineLCD = "Egg Timer           ";
int systemState = 0;
int startButtonState = 0;  //to hold the current state of buttons
int stopButtonState = 0;
int chooseButtonState = 0;
bool isChoosen = false;
//timer variables
unsigned long currentTime = 0;  //record the current time in ms since uno started
unsigned long startTime = 0;    //timer start time in ms since uno started
int interval = 3000;            //timer interval in ms
int waitTime = 180;
int cooktime = 0;




void setup() {  //(4) Setup
  // put your setup code here, to run once:
  lcd.begin(16, 2);    //starts lcd with 16 colunms(0-15) and 2 rows(0-1)
  Serial.begin(9600);  //start serial comms
  updateLCD();         //update LCD to show welcome message
  pinMode(buzzer, OUTPUT);
}

void loop() {  //(5) loop
  // put your main code here, to run repeatedly:
  //Section 1 - Read Buttons, Sensors and check time
  startButtonState = digitalRead(startButtonPin);
  stopButtonState = digitalRead(stopButtonPin);
  chooseButtonState = digitalRead(chooseButtonPin);
  currentTime = millis();  //millis returns time in ms since pwr on.


  //Section 2 - Button Actions
  if (startButtonState == HIGH) {  //if start pressed do ...
   // delay(800);
    systemState = 1;
    //(cooktime = cooktime + 60);
  } else if (stopButtonState == HIGH) {  //if stop pressed do ...
    systemState = 0;
  } else if (chooseButtonState == HIGH) {  //if choose pressed do ...
    isChoosen = true;
  }



  //Section 3  - Action System States
  if (systemState == 0) {                     //state 0 - welcome state
    topLineLCD = "Welcome to      ";          //can only be 16 chars (whitespace to 16)
    bottomLineLCD = "Egg Timer            ";  //can only be 16 chars (whitespace to 16)
    updateLCD();                              //update LCD

  } else if (systemState == 1) {  //state 1 - choose state
    updateLCD();
    topLineLCD = "Choose time     ";
    bottomLineLCD = String(cooktime/60) + "  Minutes";
    if(startButtonState == HIGH) {
    (cooktime = cooktime + 60);
    delay(800); }
    } 
    if (cooktime > 360) {
      (cooktime = 120);
    }
    if (isChoosen) {           //if choosen move to system state 2
      systemState = 2;
      startTime = currentTime;  //record start time for timing in next state (2).
      isChoosen = false;        //reset state varible for next choosing
    }
  else if (systemState == 2) { //state 2 - processing state
    topLineLCD = "Egg cooking        ";
    updateLCD();  //update LCD
    // if time now - start time is greater than 1000ms do something
    if (currentTime - startTime >= 1000) {
      //(do something every sec)
      cooktime--;  //increment by 1
      bottomLineLCD = "Please Wait  " + String(cooktime) + "    ";
      updateLCD;
      if (cooktime == 0) {  //if wait time is 10 (>9)
      cooktime =120;
        systemState = 3;
      }
      startTime = currentTime;  //record start time for timing in next state (3).
    }


  } else if (systemState == 3) {  //state 3 - processing state
    topLineLCD = "Egg complete!!!!      ";
    bottomLineLCD = "ENJOY!!!!     ";
    if (systemState == 3) {
      tone(buzzer, 1000, 300);
      tone(buzzer, 500, 300);
    }
    if (systemState == 4) {
      noTone(buzzer);
    }
    if (systemState == 4) {
      noTone(buzzer);
    }
    if (systemState == 2) {
      noTone(buzzer);
    }
    if (systemState == 1) {
      noTone(buzzer);
    }
    if (systemState == 0) {
      noTone(buzzer);
    }
    updateLCD();  //update LCD
  }

  //Section 4  - Write info to LCD



}  ///end of loop

void updateLCD() {
  lcd.home();  //set cursor to 0 col, 0 row (i.e. top corner)
  lcd.print(topLineLCD);
  lcd.setCursor(0, 1);  //set cursor to 0 col, row 1 (start of sec line)
  lcd.print(bottomLineLCD);
}