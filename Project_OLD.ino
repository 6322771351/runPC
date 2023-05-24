#define trigPinCOUNTER 13
#define echoPinCOUNTER 12
#define trigPinSPEED 11
#define echoPinSPEED 10

// Counter Global Variables
int counter = 0;
int currentState = 0;
int previousState = 0;

// Speedmeter Global Variables
long duration;
int FirstDistance=0;
int SecondDistance=0;
double speed=0;
int distance=1;
float Time = 2.0;
float delayedtime = 1000*Time;


void setup() {
 Serial.begin (9600);
 // Counter PIN_SETUP
 pinMode(trigPinCOUNTER, OUTPUT);
 pinMode(echoPinCOUNTER, INPUT);
 //pinMode (A0, INPUT);
 
 

 // Speedmeter PIN_SETUP
 pinMode(trigPinSPEED, OUTPUT);
 pinMode(echoPinSPEED, INPUT);
 pinMode(9, OUTPUT);
 digitalWrite(9, LOW);

// 7-segment PIN_SETUP
}

void loop() {
  // Calspeed();
  Counter();
  //if (digitalRead(A0)==0){
  //  counter = 0;
  //}
}


void Counter(){
  long duration;
  long distance;
  digitalWrite(trigPinCOUNTER, LOW); 
  delayMicroseconds(2); 
  digitalWrite(trigPinCOUNTER, HIGH);
  delayMicroseconds(10); 
  digitalWrite(trigPinCOUNTER, LOW);
  duration = pulseIn(echoPinCOUNTER, HIGH);
  distance = (duration/2) / 29.1;
  if (distance <= 10){ 
    currentState = 1;
  }
  else {
    currentState = 0;
  }
  delay(100);
  if(currentState != previousState){
    if(currentState == 1){
      counter = counter + 1;
      Serial.println(counter);
    }
  }
}


float Caldistance(){

  // Clears  trigPinSPEED
  digitalWrite(trigPinSPEED, LOW);
  delayMicroseconds(2);

  // Set  trigPinSPEED HIGH for 10 micro sec 
  digitalWrite(trigPinSPEED, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinSPEED, LOW);

  // Read  echoPinSPEED, returns the wave travel time in micro sec
  duration = pulseIn(echoPinSPEED, HIGH);

  //Caldistance
  distance= duration*0.034/2;

  // Print distance on Serial Monitor
  Serial.print("Distance in cm : ");
  Serial.println(distance);

  return distance;
}


void Calspeed(){

  //get the first distance
  FirstDistance = Caldistance(); 
  
  //waits 2 seconds
  delay(delayedtime); 
  
  //gets the second distance
  SecondDistance = Caldistance(); 

  // calculating the difference 
  speed = (FirstDistance - SecondDistance)/Time;  
   
  // print speed on serial monitor
  Serial.print("the speed (cm/s) is  :  ");
  Serial.println(speed);

  // LED turn on if speed exceed 20 cm/sec
  if (speed > 20){
    digitalWrite(9, HIGH);
    Serial.println("Slow Down!!!!!");
    Serial.println("========================");
  }
  else{
    digitalWrite(9, LOW);
    Serial.println("You Are Good");
    Serial.println("========================");
  }
}