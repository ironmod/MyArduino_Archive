const int sensorMin = 0 ;      // sensor minimum, discovered through experiment
const int sensorMax = 20;    // sensor maximum, discovered through experiment

void setup() {
  pinMode (2,OUTPUT);//attach pin 2 to vcc
  pinMode (5,OUTPUT);//attach pin 5 to GND
  // initialize serial communication:
  Serial.begin(9600);

  pinMode(6, OUTPUT);  
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);

  digitalWrite(6, LOW);
  digitalWrite(9, LOW);
  digitalWrite(10, LOW);
}

void loop()
{
digitalWrite(2, HIGH);
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, inches, cm;
  int case_state;
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(3, OUTPUT);// attach pin 3 to Trig
  digitalWrite(3, LOW);
  delayMicroseconds(2);
  digitalWrite(3, HIGH);
  delayMicroseconds(5);
  digitalWrite(3, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode (4, INPUT);//attach pin 4 to Echo
  duration = pulseIn(4, HIGH);
  
  // convert the time into a distance
  inches = microsecondsToInches(duration);
  cm = microsecondsToCentimeters(duration);
  case_state = case_machine(inches);
 
  //Serial.print(inches);
  //Serial.print("in, ");
  //Serial.print(cm);
  //Serial.print("cm");
 // Serial.println();
 

  delay(10);
}


