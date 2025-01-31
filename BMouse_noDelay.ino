#include <BleMouse.h>

BleMouse bleMouse("BMouse", "MB", 69);

const byte LedPin = 8;
unsigned long lastMove = 0, lastBlink = 0, lastConn = 0 , startTime = 0; 
unsigned long currentMillis = millis(), AbsStartTime = currentMillis; 
unsigned long interval = 5000; //random(40,58) * 1000;
int duration = 0, x = 0, y = 0;
bool connected = false;
byte in2 = 0, mmove = 0;


void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting Bmouse!");
  bleMouse.begin();
  Serial.println("Interval = "+String(interval)+"");
  pinMode(LedPin, OUTPUT);
}

void loop() {
  if (millis() % 100 == 0 ) {
  handle_mouse();
  }
}

void switchLed() {
  digitalWrite(LedPin, !digitalRead(LedPin));
}

void every(int interv, void (*function)(),unsigned long &variable, bool reset){
  unsigned long cMillis = millis();
  if(cMillis - variable >= interv ) {
     (*function)();
     if (reset) { variable = cMillis; }
  }
}

void moveMouse(int x,int y) {
  bleMouse.move(x,y);
  Serial.println("X = "+String(x)+" Y = "+String(y) );
}

void in2sec() {
  if(in2 == 0) { digitalWrite(LedPin, LOW); Serial.println("Move in 2 sec .."); in2++; }
}

void in1sec() {
  if(in2 == 1) { digitalWrite(LedPin, HIGH); Serial.println("Move in 1 sec .."); in2++; }
}

void move() {
  if (mmove == 0) { 
    digitalWrite(LedPin, LOW); 
    interval = random(40,58) * 1000;
    duration = (random(3) * 100) + 100;
    x = random(5) - 2;
    y = random(5) - 2;         
    Serial.println("Moving mouse : X = "+String(x)+" Y = "+String(y)+" Dur = "+String(duration)+" Interval = "+String(interval) );
    mmove++; 
    startTime = millis();
  }
  if (mmove == 1) {
    if (bleMouse.isConnected()) {
      if(millis()<startTime+duration) { moveMouse(x,y); }
        else if(millis()<startTime+duration*2) { moveMouse(-x,-y); } 
        else { lastMove = currentMillis; mmove=0;
          digitalWrite(LedPin, HIGH); in2=0;
        }
    }
  }  
}
void restartESP(){
  ESP.restart();
}

void handle_mouse() {
  currentMillis = millis();
  if(bleMouse.isConnected()) {
    digitalWrite(LedPin, HIGH);    
    connected = true;
    every(interval - 2000,in2sec,lastMove,0);
    every(interval - 1000,in1sec,lastMove,0);
    every(interval,move,lastMove,1);
  } else { 
    if (connected) { lastConn = currentMillis;  connected = false; }
    every(500,switchLed,lastBlink,1);
    every(15000,restartESP,lastConn,1);
  }
}
