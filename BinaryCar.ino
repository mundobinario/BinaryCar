/*
Author: Axel Romero - https://www.youtube.com/c/MundoBinarioByAxel
Date: 12.05.2021
Project: Binary car
Description: Control a car using HC05 and AppInventor
*/

//Declare variables
//Ultrasonic sensor
int trigPin = 3;
int echoPin = 4;


//Motors
int motorL1 = 5;  // INPUT 1 - LEFT
int motorL2 = 6;  // INPUT 2 - LEFT
int motorR1 = 10; // INPUT 3 - RIGHT 
int motorR2 = 9;  // INPUT 4 - RIGHT

//Helpers
int vel = 100;
int minDistance = 2;
int maxDistance = 10;
int distance;
char dataFromApp = 'S';

void setup()
{
  Serial.begin(9600);
  pinMode(echoPin, INPUT);    // echo as input
  pinMode(trigPin, OUTPUT);   // trigger as output
  
  //Output variables
  pinMode(motorL1, OUTPUT);  
  pinMode(motorL2, OUTPUT);
  pinMode(motorR1, OUTPUT);
  pinMode(motorR2, OUTPUT);  
}
 
void loop()
{
    // Calculate distance
    distance = calculateDistance(); 

    // if car is >=2cm and <= 10cm It will stop
    //if (distance >= minDistance &&distance <= maxDistance)
    //{
    //   dataFromApp = 'S';       
    //}

    
  
    //Wait new data
    if(Serial.available() > 0){
      dataFromApp = Serial.read();
    }
    
    switch (dataFromApp) {
    case 'U':
      up();        
      break;
    case 'D':
      down();
      break;
    case 'L':
      left();
      break;
    case 'R':
      right();
      break;
    case 'S':
      stop();
      break;
    }   
    delay(20);
}

void up(){
  digitalWrite(motorL1, 0);
  digitalWrite(motorL2, vel);
  digitalWrite(motorR1, 0);
  digitalWrite(motorR2, vel);    
}

void down(){
  digitalWrite(motorL1, vel);
  digitalWrite(motorL2, 0);
  digitalWrite(motorR1, vel);
  digitalWrite(motorR2, 0);
}

void right(){
  digitalWrite(motorL1, 0);
  digitalWrite(motorL2, vel);
  digitalWrite(motorR1, 0);
  digitalWrite(motorR2, 0);
 
}

void left(){
  digitalWrite(motorL1, 0);
  digitalWrite(motorL2, 0);
  digitalWrite(motorR1, 0);
  digitalWrite(motorR2, vel);
  
}

void stop(){
  digitalWrite(motorR1, 0);
  digitalWrite(motorR2, 0);
  digitalWrite(motorL1, 0);
  digitalWrite(motorL2, 0); 
}

int calculateDistance() {
  
  int duration, dist; 
  
  digitalWrite(trigPin, HIGH);
  delay(1);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  dist = duration / 58.2;
  
  delay(10);
  return dist;
}
