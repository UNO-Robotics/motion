void mov(byte dir, float dist, long del) {
  PORTL = dir;
  float stepf = dist * steps_per_inch;
  long steps = stepf;

   for(long i = 0; i < steps; i++){
    delayMicroseconds(del);
    PORTL ^= motion
   }
}

void turn(byte dir, float dist, long del) {
  PORTL = dir;
  float stepf = dist * steps_per_degree;
  long steps = stepf;

  for(long i = 0; i < steps; i++){
    delayMicroseconds(del);
    PORTL ^= motion
  }
}
