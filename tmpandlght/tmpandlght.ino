//Light and temperature sensing programme that prints the value to an LCD with the help of a button
//Made by, Ben 22/11/22


#include <LiquidCrystal.h> //Include library for LCD

const int rs = 13, en = 12, d4 = 11, d5 = 10, d6 = 9, d7 = 8; //Initialising pins for LCD (custom)
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

//Constants
const byte buzzer = 7; //buzzer pin
const byte tmpSense = A0; //temp sensor pin
const byte lghtSense = A1; //light sensor pin
const byte button = 6; //button pin

//Strings
String toplineLcd; //string for top line of LCD
String bottomlineLCD; //string for bottom line of LCD -- This allows for easy manipulation of the display controllable universally or in each scope

//Variables
int lightsenseVal = 0; // light sensor reading store
int tempsenseVal = 0; // temp sensor reading store
int buttonState = 0; // button state reading store
float temp = 0;     // Temp value in C store

//Custom function to initialise pins, start serial monitor, play a buzzer tone and print to the lcd when this process completes
void initialisation() {
  lcd.begin(16, 2); // begin LCD comms
  Serial.begin(9600); // init serial monitor
  pinMode(buzzer, OUTPUT); // setting buzzer to output 
  pinMode(button, INPUT); // setting button to input to enable the state to be read
  tone(buzzer, 900); //setting buzzer to play tone 900hz
  delay(250); // for 250ms 
  noTone(buzzer); //preventing the buzzer from playing tone
  toplineLcd = "Initalisation"; //printing to the LCD initialisation using the toplineLCD string
  bottomlineLCD = "Complete"; //printing to the LCD complete using the bottomlineLCD string
  updateLCD(); //calling the UpdateLCD function to update the LCD with the new string values 
  delay(1000); //delaying the progression of the code to prolong the message on the LCD 
}
//Custom function to update the LCD screen 
void updateLCD() { //custom LCD function to enable for easier programming of the LCD display 
  lcd.home(); //resetting LCD 
  lcd.setCursor(0, 0); //setting cursor to the top line at the beggining to start writing
  lcd.print(toplineLcd); //printing the string toplineLCD
  lcd.setCursor(0, 1); //setting cursor to next line at the beggining to print the bottomlineLCD string value
  lcd.print(bottomlineLCD); //printing the bottomlinelCD string value 
}
// Custom function that prints a value on the LCD if the light level is below and above a predefined limit
void lightsense() { //Light sensor value custom function
  lightsenseVal = analogRead(lghtSense); //lightsensevalue equals digitalread of lghtsense (A1)
  int lightLevel = analogRead(lghtSense); //Light level equals digitalread of lghtsense (A1) -- init for map below
  lightLevel = map(lightLevel, 0, 1023, 0, 100); //Reducing the values displayed from 0-1024 to 0-100 using a map to allow for easier interpretation through serial monitor or lCD 
  Serial.println(lightLevel) //printing lightlevel to serial monitor as a value between 0 - 100 
  if (lightLevel < 20) { //if loop to display a message on the LCD if the light level falls below the preset value of 20
    bottomlineLCD = "Its dark   "; // setting string to equal a value to be displayed on top line of lcd 
    toplineLcd = "Light Level:   "; // setting string to equal a value to be displayed on bottom line of lcd 
    updateLCD(); // calling the updatelcd function to update the display 
  } else { // if the light level value is above 20 == print a different message on the display 
    bottomlineLCD = "Its light  "; // changing string value 
    toplineLcd = "Light Level:    "; // changing string value 
    updateLCD(); //calling updatelcd function to change display text
  }
}
//Custom function that prints a value on the LCD when the button is pressed to display temperature
void tempsense() { //custom function to interpret temperature sensor value and convert it to a celsius reading and display it on LCD
  float voltage = (tempsenseVal / 1024.0) * 5; // pt1 of equation to convert raw data to celsius reading 
  float temp = (voltage - 0.5) * 100; // pt2 of equation to convert raw data to celsius reading 
  tempsenseVal = analogRead(tmpSense); // setting the temperature sensor value to equal the analog read of temperature sensor (A0). 
  toplineLcd = ("Temperature    "); // changing string value 
  delay(900); // pausing loop to prevent too fast printing of the data to the LCD 
  updateLCD(); //calling the update lcd function to update the display 
}
//Custom function - Main funtion in the loop to run both tempsense and lightsense when button is high/low
void buttonrun() { //the main function that decides what data is displayed on the LCD depending on the buttonstate 
  buttonState = digitalRead(button); // setting the variable buttonstate equal to the digitalread of the button (6)
  if (buttonState == HIGH) { //if loop that calls tempsense function if the button is pressed and held (high)
    tempsense(); // function that displays the temperature sensor data on the LCD 
  } else lightsense(); // if the button is not pressed and held, the lightsense function will be called to display the data 
}
//Setup here, run once
void setup() { // setup
  initialisation(); // calling the initialisation function to define pins, set pinmodes, start lcd and serial monitor, display text on LCD to show the user the system has initialised
  updateLCD(); // calling the updateLCD function to alter the text on the LCD 
}
//Loop here, run repeatedly 
void loop() { //loop 
  buttonrun(); //calling the buttonrun function that loops in the void loop to decide what data to display on the LCD screen.
}
