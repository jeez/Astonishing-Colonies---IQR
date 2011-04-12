int ledPins[] = {11,12,13,1,1,1};
int signal;


void setup() {

  for(int i=0; i < 6; ++i) {
    pinMode(ledPins[i],OUTPUT);
    digitalWrite(ledPins[i],HIGH);
  }

  Serial.begin(9600);

}


void loop() {

  if(Serial.available()) {
    signal=Serial.read();
    
// turning off the leds from iqr (via pd...)   
    switch(signal) {
    case 0:
      digitalWrite(ledPins[0],LOW);
      break;
    case 1:
      digitalWrite(ledPins[1],LOW);
      break;
    case 2:
      digitalWrite(ledPins[2],LOW);
      break;
    case 3:
      digitalWrite(ledPins[3],LOW);
      break;
    case 4:
      digitalWrite(ledPins[4],LOW);
      break;
    case 5:
      digitalWrite(ledPins[5],LOW);
      break;
    case 6:
      digitalWrite(ledPins[0],HIGH);
      break;
    case 7:
      digitalWrite(ledPins[1],HIGH);
      break;
    case 8:
      digitalWrite(ledPins[2],HIGH);
      break;
    case 9:
      digitalWrite(ledPins[3],HIGH);
      break;
    case 10:
      digitalWrite(ledPins[4],HIGH);
      break;
    case 11:
      digitalWrite(ledPins[5],HIGH);
      break;      
    case 12:                        // reset all the leds
      for(int i=0; i < 6; ++i) {
        digitalWrite(ledPins[i],HIGH);
      }
      break;
    }
  }
}

