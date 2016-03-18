
#include "scheduling.h"
#include "driverlib/interrupt.h"


ScheduleLibrary schedulelibrary;
void setup()
{  
  
  Serial.begin(9600);
  schedulelibrary.initTimer();
  schedulelibrary.setTimerToswitchon(60);
  schedulelibrary.setTimerToswitchoff(60);
}

void loop()
{

}

