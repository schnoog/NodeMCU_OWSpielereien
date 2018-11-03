#include <Arduino.h>
#include "wman.h"
#include "myonewire.h"


void setup() {
    Serial.begin(115200);
    wifisetup();
    otasetup();
    myonewire_setup();
  // put your setup code here, to run once:
}


void loop() {
      ota.loop();
      myonewire_loop();
      

      delay(10);
  // put your main code here, to run repeatedly:
}