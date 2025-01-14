#include <BleMouse.h>
#include <esp_int_wdt.h>
#include <esp_task_wdt.h>

BleMouse bleMouse("BMouse", "MB", 100);
unsigned long lastMove = 0;
unsigned long interval = 57000; 
unsigned long AbsStartTime = millis(); 

void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Starting Bmouse!");
  bleMouse.begin();
  Serial.println("Interval = "+String(interval)+"");
}

void loop() {
  if(bleMouse.isConnected()) {
    unsigned long currentMillis = millis();
    //if(currentMillis - lastMove >= interval - 2000) { Serial.println("Move in 2 sec ..");  }
    if(currentMillis - lastMove >= interval) {
     if (bleMouse.isConnected()) {
      int duration = random(50,200) + 1;
      int randx = random(5) - 1;
      int randy = random(5) - 1;
      Serial.println("Random numbers : X = "+String(randx)+" Y = "+String(randy) );
      moveMouse(-randx,-randy,duration);
      moveMouse(randx,randy,duration);
      lastMove = currentMillis;
      interval = random(40,58) * 1000;
      Serial.println("Interval = "+String(interval)+"");
     }
    }  
  }
}

void hard_restart() { 
 esp_task_wdt_init(1,true); 
 esp_task_wdt_add(NULL);
 while(true);
}

void moveMouse(int x, int y, int duration) { 
  unsigned long startTime = millis();
  while(millis()<startTime+duration) {
    bleMouse.move(x,y);
    delay(50);  }
}
