
int Start = 4;
int Stop = 7;
void setup(){
  pinMode(Start,OUTPUT);
  pinMode(Stop,OUTPUT);
         digitalWrite(Start, LOW);
          digitalWrite(Stop, LOW);
}



void loop(){
  
      //start the Timer
      digitalWrite(Start, HIGH);// 
      delayMicroseconds(1);
      //for(int i =0 ; i< 50; i++);
      digitalWrite(Start, LOW);// 
      delayMicroseconds(1);// the time needed to count.........................
      digitalWrite(Stop, HIGH);
      delayMicroseconds(1);
      //for(int i =0 ; i< 50; i++);
      digitalWrite(Stop, LOW);
      //delay(5000);


//digitalWrite(Stop, LOW);
//digitalWrite(Start, LOW);
    
}
