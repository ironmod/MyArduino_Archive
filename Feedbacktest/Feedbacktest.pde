int readFeedback=A0;
int feedbackValue=0;
int old_feedback=0;
int open_pos=2;
int close_pos=3;
int open_neg=4;
int close_neg=5;
int user=0;
int check=0;
int init_feedbackValue=0;
void setup(){
  Serial.begin(9600);
  Serial.println("Starting...");
  pinMode(open_pos, OUTPUT);
  pinMode(open_neg, OUTPUT);
  pinMode(close_pos, OUTPUT);
  pinMode(close_neg, OUTPUT);
  
  digitalWrite(open_pos, HIGH);
  digitalWrite(open_neg, HIGH);
  digitalWrite(close_pos, HIGH);
  digitalWrite(close_neg, HIGH);
  init_feedbackValue=analogRead(readFeedback);
  Serial.print("Initial value: ");
  Serial.println(feedbackValue);
}
void loop (){
  old_feedback=feedbackValue;
  feedbackValue=analogRead(readFeedback);
  if (old_feedback != feedbackValue)
 {
    Serial.println("Reading feedback...");
    Serial.println(feedbackValue);
 }
  if (Serial.available()){
    user=Serial.read();
    Serial.println("Serial Read");
  }

  if (user=='R')
  {
     digitalWrite(open_pos, LOW);
      digitalWrite(open_neg, LOW);
      Serial.println("Opening Doors...");
   }
        if(feedbackValue<700){
        digitalWrite(open_pos, HIGH);
        digitalWrite(open_neg, HIGH);
       Serial.println("Stopping Doors...");
       check=1;
      }

  if(user=='D' && check==1){
    digitalWrite(close_pos, LOW);
    digitalWrite(close_neg, LOW);
    Serial.println("Closing Doors..");
    if(feedbackValue == init_feedbackValue ){
      
      digitalWrite(close_pos, HIGH);
      digitalWrite(close_pos, HIGH);
    }
  }
}
