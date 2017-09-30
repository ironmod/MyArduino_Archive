int case_machine (int inches ) {
  
    int range = map(inches, sensorMin, sensorMax, 0, 3);

  // do something different depending on the 
  // range value:
  switch (range) {
  case 0:    // your hand is on the sensor
    //Serial.println("dark");
    digitalWrite(6, LOW);
    digitalWrite(10, LOW);
    digitalWrite(9, LOW);
    break;
  case 1:    // your hand is close to the sensor
    digitalWrite(9, LOW);
    digitalWrite(6, LOW);
    
    digitalWrite(10, HIGH);
    //Serial.println("dim");
    break;
  case 2:    // your hand is a few inches from the sensor
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    
    digitalWrite(6, HIGH);
   // Serial.println("medium");
    break;
  case 3:    // your hand is nowhere near the sensor
      digitalWrite(6, LOW);
    digitalWrite(10, LOW);
    
    digitalWrite(9, HIGH);
   // Serial.println("bright");
    break;
  } 
  
}
