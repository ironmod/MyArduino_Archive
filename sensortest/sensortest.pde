int I0; //top left sensor input +24V
int I1; //top right sensor
int I2; //bottom left sensor
int I3; //bottom right sensor
int sensor_TL; //status of top left sensor on hoist
int sensor_TR; //status of top right sensor
int sensor_BL; //status of bottom left sensor
int sensor_BR; //status of bottom right sensor

void setup () {
  Serial.begin (9600);
  Serial.println("Master Output");
  pinMode(I0, INPUT);
  pinMode(I1, INPUT);
  pinMode(I2, INPUT);
  pinMode(I3, INPUT);
  digitalWrite(I0, LOW);
  digitalWrite(I1, LOW);
  digitalWrite(I2, LOW);
  digitalWrite(I3, LOW);
}

void loop (){
  read_Sensors();
  send_wireless();
}

void read_Sensors(){
  sensor_TL = digitalRead(I0);
  sensor_TR = digitalRead(I1);
  sensor_BL = digitalRead(I2);
  sensor_BR = digitalRead(I3);
}

void send_wireless() {
    if(sensor_TL==1 || sensor_TR==1 || sensor_BL==1 || sensor_BR==1)
    Serial.println("1");
}

