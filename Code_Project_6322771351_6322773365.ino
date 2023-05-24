#include <LiquidCrystal_I2C.h>

#define trigPinSPEED 11
#define echoPinSPEED 10
#define trigPinCOUNTER 13
#define echoPinCOUNTER 12

// Global Variable
long duration;

// Speedometer Variables
int FirstDistance = 0;
int SecondDistance = 0;
float speed = 0;

// Counter Variables
int counter = 0;
int currentState = 0;
int previousState = 0;

// setup LCD
LiquidCrystal_I2C lcd(0x3F, 16, 2); // I2C address, 16 columns, and 2 rows

void setup(){
  Serial.begin(9600);
  // Initialize the LCD
  lcd.init(); 
  lcd.backlight();
  // Counter PIN Setup
  pinMode(trigPinCOUNTER, OUTPUT);
  pinMode(echoPinCOUNTER, INPUT);
  pinMode(2, INPUT);  // Switch PIN
  // Speedmeter PIN Setup
  pinMode(trigPinSPEED, OUTPUT);
  pinMode(echoPinSPEED, INPUT);
  pinMode(9, OUTPUT); // Red LED
  digitalWrite(9, LOW);
}

void loop(){
  if(digitalRead(2) == 0){
    counter = 0;
  }
  display_numbers();
  Calspeed();
  Counter();
  delay(100);
}

void display_numbers(){
  lcd.clear();                 // clear display
  lcd.setCursor(0, 0);         // move cursor to   (0, 0)
  lcd.print("Counter: ");      // print message at (0, 0)
  lcd.print(counter);          
  
  lcd.setCursor(1, 1);         // move cursor to   (1, 1)
  lcd.print("Speed: ");        // print message at (1, 1)
  if(speed >= 0){
    lcd.print(speed);
  }
  else {
    lcd.print("error");
  }
}


float Caldistance(){
  // Clear trigPinSPEED
  digitalWrite(trigPinSPEED, LOW);
  delayMicroseconds(2);

  // Set trigPinSPEED HIGH for 10 micro sec 
  digitalWrite(trigPinSPEED, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinSPEED, LOW);

  // Read echoPinSPEED, returns the sound wave travel time
  duration = pulseIn(echoPinSPEED, HIGH);

  //Find distance
  float distance = duration*0.034/2;

  // Print distance on Serial Monitor (CHECK)
  if(distance > 0){
    Serial.print("Distance in cm : ");
    Serial.println(distance);
    return distance;
  }
  else {
    return 0;
  }
}


void Calspeed(){
  //get the first distance
  FirstDistance = Caldistance(); 
  //waits 350 milliseconds
  delay(350); 
  //gets the second distance
  SecondDistance = Caldistance(); 

  // calculating the difference 
  speed = (FirstDistance - SecondDistance)/2;  
  // print speed on serial monitor (CHECK)
  Serial.print("the speed (cm/s) is  :  ");
  Serial.println(speed);

 // turn on LED if speed exceed 10 cm/sec
  if (speed > 10){         
    digitalWrite(9, HIGH);
    Serial.println("Too Fast!!!!!");
    Serial.println("========================");
  }
  else{
    digitalWrite(9, LOW);
    Serial.println("You Are Good");
    Serial.println("========================");
  }
}


void Counter(){
  float distance = Caldistance();

  if (distance <= 10){ 
    currentState = 1;
  }
  else {
    currentState = 0;
  }

  delay(10);
  // Check with dummy value (0)
  if(currentState != previousState){
    if(currentState == 1){
      counter = counter + 1;
    }
  }
}
