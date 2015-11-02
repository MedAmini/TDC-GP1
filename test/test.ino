
int Start = 4;
int Stop = 7;
void setup(){
  pinMode(Start,OUTPUT);
  pinMode(Stop,OUTPUT);
  digitalWrite(Start, LOW);
  digitalWrite(Stop, LOW);
}

void loop(){
  
    digitalWrite(Start, HIGH);
    delayMicroseconds(1);
    digitalWrite(Start, LOW); 
    delayMicroseconds(1);// the time needed to count.........................
    digitalWrite(Stop, HIGH);
    delayMicroseconds(1);
    digitalWrite(Stop, LOW);
    delay(1000);
    
}
