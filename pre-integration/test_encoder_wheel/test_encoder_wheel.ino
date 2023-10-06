//#include "rotary_encoder.cpp"
const int WHEEL_ENCODER_PIN = 2;
const bool DEBUG = true;

class RotaryEncoder{

  int counter;
  int wheel_last_interrupt;

  int pin;

  constructor(int pin_,float resolution_){
    
    pin = pin_;
    counter = 0;
    wheel_last_interrupt = 0;

  };

  float GetPosition(){
    return 0;
  }

  void DebouncedCount(){

    if(millis() - wheel_last_interrupt >= 50){
      counter++;
      wheel_last_interrupt = millis();
    }

    if(DEBUG){
      Serial.println(counter);
    }
  }

};



RotaryEncoder encoder;
void setup() {
  // put your setup code here, to run once:
  //pinMode(WHEEL_ENCODER_PIN,INPUT);

  encoder = new RotaryEncoder(WHEEL_ENCODER_PIN,0);
  attachInterrupt(digitalPinToInterrupt(encoder.pin), wheel_interupt, RISING );

  if(DEBUG){
    Serial.begin(9600);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  //int wheel_state = digitalRead(WHEEL_ENCODER_PIN);



}


void wheel_interupt(){

  encoder.DebouncedCount();


}


