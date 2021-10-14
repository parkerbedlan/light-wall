

int val =0; 
unsigned long Time;
int newVal1 = 0; 
int newVal2 = 0;
int i;
boolean toggle0 = false;
boolean toggle1 = false;
int numReadings = 30;
 int LED = 7;
 int CLOCK = 13;
 int PULSE = 12;
 int AIN1 = A0;
 int AIN2 = A1;
 int LED2 = 4;

void setup() {
  
  // put your setup code here, to run once:
 cli();
  pinMode(LED,OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(AIN1, INPUT);
  Serial.begin(115200);

  pinMode(CLOCK, OUTPUT);
  TCCR0A = 0;
  TCCR0B = 0;
  TCNT0 = 0;
  OCR0A=3;//4mz
  TCCR0A |= (1<<WGM01);
  TCCR0B |= (1<<CS00);//prescaler 1 
  TIMSK0 |= (1 << OCIE0A);
 
  

  pinMode(PULSE, OUTPUT);//sets 2mh hertz signal for pulse clock on timer 0 pins 5 and 6 
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 19999;
  TCCR1B |=(1<< WGM12);
  TCCR1B|= (1<<CS10);
  TIMSK1 |= (1<<OCIE1A);

}
ISR(TIMER1_COMPA_vect){
  if(toggle1){
    digitalWrite(CLOCK,HIGH);
    toggle1 = false;
  }
  else{
    digitalWrite(CLOCK,LOW);
    toggle1 = true;
  }
  
}
ISR(TIMER0_COMPA_vect){
  if(toggle0){
    digitalWrite(PULSE,HIGH);
    toggle0 = false;
  }
  else{
    digitalWrite(PULSE,LOW);
    toggle0 = true;
  }
  
}
void loop() {
  // put your main code here, to run repeatedly:
  for (i = 0; i< numReadings; i++){
    newVal1 = newVal1 + analogRead(AIN1);
    newVal2 = newVal2 + analogRead(AIN2);
    delayMicroseconds(50);
  }
  newVal1 = (newVal1 / (numReadings/1.01))-1; 
  newVal2 = newVal2 / (numReadings); 
    Serial.print("X: "); Serial.print(newVal1); Serial.print("  ");
    Serial.print("Y: "); Serial.print(newVal2); Serial.print("  ");
    Serial.println("");

// digitalWrite(LED2, HIGH);

  if (newVal1 > 57){
    digitalWrite(LED,HIGH);
  }
  else{digitalWrite(LED,LOW);}

}
