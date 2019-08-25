void varsInt(byte dir, float dist, long del, float ratio, byte master, byte slave) {
  ctc3_setup();
  ctc4_setup();
  PORTL = dir;
  float stepf = dist*steps_per_inch;
  masterWheels = master;
  slaveWheels = slave;

  noInterrupts();
  //OCR4A = 16 * del - 1;//setup speed for master
  OCR4A = 16 * del;
  TCNT4 = 0;//reset
  float temp = del * ratio;
  long slaveDelay = temp;
  //OCR3A = slaveDelay * 16 - 1;//setup speed for slave 
  OCR3A = slaveDelay * 16;
  TCNT3 = 0;//reset
  steps = stepf;
  steps_counter = 0;  //reset step counter
  interrupts();
} 

void ctc4_setup() {
  noInterrupts();
  TCCR4A = 0;  // clear counter control register
  TCCR4B = 0;
  TCNT4 = 0;

  OCR4A = 16000; // compare match register – 1000 usecond delay
          // countCompareValue = delayInMicroseconds * 16
          // countCompareValue = 16000000 / prescaler / desired frequency
  TCCR4B |= (1 << WGM42); // count to compare mode
  TCCR4B |= (1 << CS40); // 1 prescaler
  TIMSK4 |= (1 << OCIE4A); // enable timer compare interrupt
  interrupts();
}

void ctc3_setup() {
  noInterrupts();
  TCCR3A = 0;  // clear counter control register
  TCCR3B = 0;
  TCNT3 = 0;
 // OCR3A = 16000; // compare match register – 1000 usecond delay
          // countCompareValue = delayinmicroseconds * 16 
          // countCompareValue = 16000000 / prescaler / desired frequency
  TCCR3B |= (1 << WGM32); // count to compare mode
  TCCR3B |= (1 << CS30); // 1 prescaler
  TIMSK3 |= (1 << OCIE3A); // enable timer compare interrupt
  interrupts();
}
//3: Slave
ISR(TIMER3_COMPA_vect) { // timer compare ISR
  if (steps > 0) {
    PORTL ^= slaveWheels;
  }
  steps_counter++;
}

//4: Master
ISR(TIMER4_COMPA_vect) { // timer compare ISR
  if (steps > 0) {
    PORTL ^= masterWheels;
  }
  steps--;
}

void vars( byte dir, float dist, long del, float ratio, byte master,byte slave){
  PORTL = dir;
  float stepf=dist*steps_per_inch;
  long steps=stepf;

 long masterCount =0;
 long slaveCount =0;
 long stepCount =0;

 float temp = del * ratio;
 long slaveDelay =  temp;

 while(stepCount < steps){
    if(masterCount > del){
        PORTL ^= master;//Step masterwheels
        masterCount = 0;
        stepCount++;
    }
    if(slaveCount > slaveDelay){
      PORTL ^= slave;//step slave wheels
      slaveCount = 0;//rest
    }
    masterCount++;
    slaveCount++;
 }
}

void varsIntTurn(byte dir, float dist, long del, float ratio, byte master, byte slave) {
  ctc3_setup();
  ctc4_setup();
  PORTL = dir;
  float stepf = dist*steps_per_degree;
  masterWheels = master;
  slaveWheels = slave;

  noInterrupts();
  //OCR4A = 16 * del - 1;//setup speed for master
  OCR4A = 16 * del;
  TCNT4 = 0;//reset
  float temp = del * ratio;
  long slaveDelay = temp;
  //OCR3A = slaveDelay * 16 - 1;//setup speed for slave 
  OCR3A = slaveDelay * 16;
  TCNT3 = 0;//reset
  steps = stepf;
  steps_counter = 0;  //reset step counter
  interrupts();

}

void acceleration(byte dir, float dist, long del,int N){
   float total_dis = N*(N+1)/2 * 3 * start_dis; // check commanded distance and number of steps
   if(total_dis > dist){
        float m = sqrt((dist/start_dis) * 2/3); // correct if necessary
        N = m;
        }
   
   float mid_dis = dist-start_dis*3*N*(N+1)/2;
   
  for(int i =1; i<=N;i++){
    vars(dir, start_dis * i, del/i, straight, rightmotors, leftmotors);
        }
   
   vars(dir, mid_dis, del/N, straight, rightmotors, leftmotors);
   
  for(int i=N; i>0; i--){
   vars(dir, start_dis *2*i, del/i, straight, rightmotors, leftmotors);
        }
}
