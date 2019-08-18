volatile byte masterWheels;
volatile byte slaveWheels;
volatile float steps;
volatile float steps_counter;

//--------------Team Dependant------------//
// Direction bytes
byte fwd;
byte rev;
byte rotl;
byte rotr;
byte strl;
byte strr;

// Motor bytes
byte allmotion = B01010101;
byte leftmotion;
byte rightmotion;
byte frontmotion;
byte rearmotion;
byte right45;
byte left45;

//Measurements
float distance;
float steps_per_inch;
float steps_per_degree;
float straight;
float arc180;
float start_dist;
float threashold;
