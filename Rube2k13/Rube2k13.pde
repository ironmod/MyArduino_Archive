
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

//r1-r8 is the 8 Solid State Relay module
int r1 = 26;
int r2 = 27;
int r3 = 28;
int r4 = 29;
int r5 = 30;
int r6 = 31;
int r7 = 32;
int r8 = 33;
int r9 = 34;
//r9-12 is the 4 relay module
int r10 = 35;
int r11 = 36;
int r12 = 37;
//tb = terminal block #
int tb9 = 8;   //PIR sensor
int tb10 = 9;  //Analog Laser Read
int tb11 = 10;
int tb12 = 11;

void setup (){
  
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  pinMode(r3, OUTPUT);
  pinMode(r4, OUTPUT);
  pinMode(r5, OUTPUT);
  pinMode(r6, OUTPUT);
  pinMode(r7, OUTPUT);
  pinMode(r8, OUTPUT);
  pinMode(r9, OUTPUT);
  pinMode(r10, OUTPUT);
  pinMode(r11, OUTPUT);
  pinMode(r12, OUTPUT);
  
  digitalWrite(r1, LOW);
  digitalWrite(r2, LOW);
  digitalWrite(r3, LOW);
  digitalWrite(r4, LOW);
  digitalWrite(r5, LOW);
  digitalWrite(r6, LOW);
  digitalWrite(r7, LOW);
  digitalWrite(r8, LOW);
  digitalWrite(r9, HIGH);
  digitalWrite(r10, HIGH);
  digitalWrite(r11, HIGH);
  digitalWrite(r12, HIGH);
  
  pinMode(tb9, INPUT);
     pinMode(BAD, OUTPUT);
   pinMode(GOOD, OUTPUT);
   pinMode(ELEVATOR, OUTPUT);
   pinMode(LASER, OUTPUT);
   pinMode(LED_STRIP, OUTPUT);
   pinMode(THETATAU, OUTPUT);
   pinMode(MULTILED, OUTPUT);
   
   pinMode(ELEVATOR_SENSOR, INPUT);
   pinMode(COIN_SENSOR, INPUT);

   digitalWrite(LASER, HIGH);
   run();
   run();
   run();
   run();
   run();
  
  Serial.begin(9600);
  Serial.print("Setting up...:");
  delay(20000);
  
}

void loop () {
  
  int sensorCheck = digitalRead(tb9);
  if (sensorCheck==1)
  {
     digitalWrite(r3, HIGH);
    digitalWrite(r7, HIGH);
    Serial.println("Opening actuator...");
    delay(15000);
    digitalWrite(r3, LOW);
    digitalWrite(r7, LOW);
    delay(20);
    Serial.println("Closing Actuator...");
    digitalWrite(r2, HIGH);
    digitalWrite(r6, HIGH);
    digitalWrite(r4, HIGH);
    digitalWrite(r8, HIGH);
    delay(10000);
    digitalWrite(r2, LOW);
    digitalWrite(r6, LOW);
    delay(20);
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
     //  flash(MULTILED, 500,1);
       //flash(LED_STRIP,800,1);
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

void elevator(){  //Starts Elevator at full power, then kicks down strength
  Serial.println("Elevator is moving");
  analogWrite(ELEVATOR,255);
  delay(100);
  analogWrite(ELEVATOR,liftStrength);
  delay(liftTime);
}  
  

/*
  digitalWrite(r1, HIGH);
  digitalWrite(r2, HIGH);
  digitalWrite(r3, HIGH);
  digitalWrite(r4, HIGH);
  digitalWrite(r5, HIGH);
  digitalWrite(r6, HIGH);
  digitalWrite(r7, HIGH);
  digitalWrite(r8, HIGH);
  digitalWrite(r9, LOW);
  digitalWrite(r10, LOW);
  digitalWrite(r11, LOW);
  digitalWrite(r12, LOW);
  */
