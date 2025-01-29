#include <BleMouse.h>

const byte LedPin = 8;
BleMouse bleMouse("BMouse", "MB", 69);
unsigned long lastMove = 0;
unsigned long lastBlink = 0;
unsigned long interval = 5000; //random(40,58) * 1000; 
unsigned long AbsStartTime = millis(); 
unsigned long currentMillis = millis();
byte in2 = 0;
byte mmove = 0;
  unsigned long startTime = 0;
  int duration = 0;
        int x = 0;
        int y = 0;

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

void every(int interv, void (*function)(),unsigned long &variable ){
  unsigned long cMillis = millis();
  if(cMillis - variable >= interv ) {
     (*function)();
     variable = cMillis;
  }
}


void handle_mouse() {
  currentMillis = millis();
  if(bleMouse.isConnected()) {
    digitalWrite(LedPin, HIGH);    
    if(currentMillis - lastMove >= interval - 2000) { if(in2 == 0) { digitalWrite(LedPin, LOW); Serial.println("Move in 2 sec .."); in2++; } }
    if(currentMillis - lastMove >= interval - 1000) { if(in2 == 1) { digitalWrite(LedPin, HIGH); Serial.println("Move in 1 sec .."); in2++; } }
    if(currentMillis - lastMove >= interval) { 
      if (mmove == 0) { 
        digitalWrite(LedPin, LOW); 
        duration = (random(3) * 100) + 100;
        x = random(5) - 2;
        y = random(5) - 2;
        Serial.println("Moving mouse : X = "+String(x)+" Y = "+String(y)+" Dur = "+String(duration) );
        mmove++; 
        startTime = millis();
        
        interval = random(40,58) * 1000;
        Serial.println("Interval = "+String(interval)+"");
        
      }
    }
    if (mmove == 1) {
      if (bleMouse.isConnected()) {
         if(millis()<startTime+duration) {
           bleMouse.move(x,y);
           Serial.println("X = "+String(x)+" Y = "+String(y) );
         }
         else if(millis()<startTime+duration*2) {
           bleMouse.move(-x,-y);
           Serial.println("X = "+String(-x)+" Y = "+String(-y) );
         } 
         else { lastMove = currentMillis; mmove=0;
           digitalWrite(LedPin, HIGH); in2=0;
           Serial.println("END");
         }
      }
    }  
  } else { 
     //if(currentMillis - lastBlink >= 500 ) { 
     // digitalWrite(LedPin, !digitalRead(LedPin));
     // lastBlink = currentMillis;
     every(500,switchLed,lastBlink);
  }
}



void moveMouse(int x, int y, int duration) { 
 
}

// need forward declarations here
void function2();
void function1(void (*)());


void loop1() {
    function1(function2);
}


void function2() {
    //do something
}

void setup1()
{
  Serial.begin(9600);
  byte y = 0x35;
  byte *ptr;
  ptr = &y;     //& (ampersand sign) is used to get the address of RAM location that holds y
  Serial.println(y, HEX); //shows: 35
  //---------------------------
  *ptr = 0x45;  //store 0x45 into a RAM location whose address is in ptr
  Serial.println(y, HEX); //shows: 45
}
