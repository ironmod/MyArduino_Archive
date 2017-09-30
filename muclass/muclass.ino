#include <Servo.h>;

const int BAD=13;
const int GOOD=12;
const int ELEVATOR=10;
const int LASER=8;
const int LED_STRIP=7;
const int THETATAU=6;
const int MULTILED=3;
const int ELEVATOR_SENSOR=1;
const int COIN_SENSOR=0;


int val=0;
int liftTime=5000;
int liftStrength=130;
int pos=0;
int ambient=0;
int i;
int brightness=0;
int fadeAmount=5;
int wait_time=5000;

Servo disc;

void getAmbient(int sensor);
int checkLaser(int sensor);
void flash(int pin, int time, int num_times);
void move(int time);
void fade(int pin, int time);
void elevator();
void run();


void setup(){
   Serial.begin(9600);
   Serial.println("Welcome to the Mu Class Project");
   Serial.println("Created Spring Semester 2012");
   
   pinMode(BAD, OUTPUT);
   pinMode(GOOD, OUTPUT);
   pinMode(ELEVATOR, OUTPUT);
   pinMode(LASER, OUTPUT);
   pinMode(LED_STRIP, OUTPUT);
   pinMode(THETATAU, OUTPUT);
   pinMode(MULTILED, OUTPUT);
   
   pinMode(ELEVATOR_SENSOR, INPUT);
   pinMode(COIN_SENSOR, INPUT);
   
   disc.attach(9);  
   disc.write(90);
   digitalWrite(LASER, HIGH);
   flash(LED_STRIP, 100, 10);
   flash(GOOD, 50, 25);
   flash(BAD, 50, 25);
   flash(MULTILED, 50, 50);
   run();
   run();
   run();
   run();
   run();
}

void loop(){
     if (checkLaser(COIN_SENSOR)){
       flash(MULTILED, 50, 2); 
       flash(LED_STRIP,50,10);
       move(100);
       run(); 
       
     }
     else {
       fade(MULTILED, 100);
     }
     
}

void run(){
  int start_time=millis();
  int has_broke_laser=0;
  while (has_broke_laser<1){
    if (checkLaser(ELEVATOR_SENSOR)){
        Serial.print("Time since dispensed ");
        Serial.println((millis()-start_time)/1000);
        elevator();
        has_broke_laser++; 
        start_time=millis();
    }
    else if((millis()-start_time)>wait_time){
      Serial.print("Time since dispensed ");
      Serial.println((millis()-start_time)/1000);
      digitalWrite(BAD, HIGH);
      move(100);
    }  
  }
}
  

void getAmbient(int sensor){  //Gets the ambient(without the laser) reading from the photodiode
  digitalWrite(LASER,LOW);
  delay(100);
  ambient=analogRead(sensor);
  Serial.print("AMBIENT:  ");
  Serial.println(ambient);
  delay(100);
  digitalWrite(LASER,HIGH);
  delay(100);
}

int checkLaser(int sensor){ //Returns 1 if laser broken, 0 otherwise
  getAmbient(sensor);
  int withLaser=analogRead(sensor);
   for(i=0; i<1000; i++){
     if(analogRead(sensor)<withLaser-(.3*withLaser)){
       Serial.println("Laser Broken");
       flash(MULTILED, 500,1);
       flash(LED_STRIP,800,1);
       return 1; 
     }
     fade(MULTILED, 25);
     
     /*if(i=500)
       Serial.print("With LASER=  ");
       Serial.println(analogRead(sensor));
       delay(10);
       */
   }
  return 0;
}

void flash(int pin, int time, int num_times){
  for(i=0; i<num_times; i++){
    digitalWrite(pin,HIGH);
    delay(time);
    digitalWrite(pin, LOW);
    delay(time); 
  } 
}

void move(int time){ //Rotates the turntable
  Serial.println("Turntable activated");
  disc.write(0);
  delay(time);
  disc.write(90);
}

void fade(int pin, int time){  //Fades leds per given time
    analogWrite(pin, brightness);
   
    brightness= brightness + fadeAmount;
    
    if (brightness==0 || brightness==255){
      fadeAmount= -fadeAmount;
    }
    
    delay(time);
}
  
void elevator(){  //Starts Elevator at full power, then kicks down strength
  Serial.println("Elevator is moving");
  analogWrite(ELEVATOR,255);
  delay(100);
  analogWrite(ELEVATOR,liftStrength);
  delay(liftTime);
}  
  

  

