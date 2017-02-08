#include <SimbleeForMobile.h>

#define LED 6

void setup() {
  pinMode(LED, OUTPUT);
  
  SimbleeForMobile.deviceName = "Project 3";
  SimbleeForMobile.advertisementData = "temp";
  SimbleeForMobile.begin();
}

int switchID;
int textID;
int flag;

void loop() {
  if(SimbleeForMobile.updatable && (flag==1)) {
    SimbleeForMobile.updateValue(textID, analogRead(4));
  }

  Simblee_ULPDelay(SECONDS(1));
  SimbleeForMobile.process();
}

void SimbleeForMobile_onConnect()
{
}

void ui() {
  SimbleeForMobile.beginScreen(GRAY);
  
  textID = SimbleeForMobile.drawText(100, 100, 1, BLACK, 92);
  switchID = SimbleeForMobile.drawSwitch(150, 200);

  SimbleeForMobile.endScreen();
}

void ui_event(event_t &event) {
  if(event.id == switchID){
    digitalWrite(LED,event.value);
    flag = event.value;
  }
}

