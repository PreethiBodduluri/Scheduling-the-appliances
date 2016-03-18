/*
 * scheduling.cpp
 *
 *
 *      Author: preethibodduluri
 */

#include  "scheduling.h"
#include <driverlib/interrupt.h>
#include <driverlib/timer.h>
#include <driverlib/prcm.h>
#include <driverlib/rom_map.h>
#include <driverlib/gpio.h>

int timerOverFlowCounter;
int timer1OverFlowCounter;
int ledPin;
int count_for_on;
int count_for_off;
int value_to_load_for_on;
int countvalue_for_on;
int countvalue_for_off;
int value_to_load_for_off;

void ScheduleLibrary::initTimer()
{
	ledPin = GREEN_LED; // used for testing can be removed
	timerOverFlowCounter= 0 ;
	pinMode(ledPin, OUTPUT); // used for testing can be removed
	// Enable Timer
	MAP_PRCMPeripheralClkEnable(PRCM_TIMERA0, PRCM_RUN_MODE_CLK);
	MAP_PRCMPeripheralClkEnable(PRCM_TIMERA1, PRCM_RUN_MODE_CLK);

	// Reset the Timer
	MAP_PRCMPeripheralReset(PRCM_TIMERA0);
	MAP_PRCMPeripheralReset(PRCM_TIMERA1);


	// Configure the Timer to switch_on the led
	MAP_TimerConfigure( TIMERA0_BASE,TIMER_CFG_ONE_SHOT);
	MAP_TimerPrescaleSet(TIMERA0_BASE, TIMER_A, 0);
	MAP_TimerPrescaleMatchSet(TIMERA0_BASE, TIMER_A, 0);

	// Configure the Timer to switch_off the led
	MAP_TimerConfigure( TIMERA1_BASE,TIMER_CFG_ONE_SHOT);
	MAP_TimerPrescaleSet(TIMERA1_BASE, TIMER_A, 0);
	MAP_TimerPrescaleMatchSet(TIMERA1_BASE, TIMER_A, 0);


    // Register Timer Interrupt
    TimerIntRegister(TIMERA0_BASE, TIMER_A,Switch_on_device);

    TimerIntRegister(TIMERA1_BASE, TIMER_A,Switch_off_device);

    // Setup the interrupt for the TIMERA0 timeout
    MAP_TimerIntEnable(TIMERA0_BASE, TIMER_TIMA_TIMEOUT);

    MAP_TimerIntEnable(TIMERA1_BASE, TIMER_TIMA_TIMEOUT);

}
// This function us used to switch on the appliance.
void ScheduleLibrary::setTimerToswitchon( int time_in_seconds_for_on)
{
	digitalWrite(ledPin, LOW);
	count_for_on = time_in_seconds_for_on;
	countvalue_for_on = time_in_seconds_for_on;
	// load the timer
	MAP_TimerLoadSet(TIMERA0_BASE, TIMER_A, 80000000*53);
	// Enable the timer.
	MAP_TimerEnable(TIMERA0_BASE, TIMER_A);
}
// This function us used to switch off the appliance.
void ScheduleLibrary::setTimerToswitchoff( int time_in_seconds_for_off)
{
	digitalWrite(ledPin, HIGH);
	count_for_off = time_in_seconds_for_off;
    countvalue_for_off = time_in_seconds_for_off;
	// load the timer
	MAP_TimerLoadSet(TIMERA1_BASE, TIMER_A, 80000000*53);
	// Enable the timer.
	MAP_TimerEnable(TIMERA1_BASE, TIMER_A);
}

// 53 seconds is used in one cycle,
//According to the time_in_seconds_for_on / time_in_seconds_for_off is mentioned the appropriate appliance is switched on/off.
void Switch_on_device()
{

	MAP_TimerIntClear(TIMERA0_BASE, TIMER_TIMA_TIMEOUT);
	timerOverFlowCounter = timerOverFlowCounter + 53;
	Serial.println(timerOverFlowCounter);
  if (timerOverFlowCounter >= countvalue_for_on)
  {
	  timerOverFlowCounter = 0;
      Serial.println("Device is ON");
      digitalWrite(ledPin, HIGH);
      //setTimerToswitchoff();
  }
else{
	    value_to_load_for_on = count_for_on - 53;
	    if (value_to_load_for_on > 53 )
	    {
	    	count_for_on = count_for_on - 53;
	    	// load the timer
	    	MAP_TimerLoadSet(TIMERA0_BASE, TIMER_A, 80000000*53);
	        // Enable the timer.
	    	MAP_TimerEnable(TIMERA0_BASE, TIMER_A);
	    }
	    else
	    	{
	   	// load the timer
	    MAP_TimerLoadSet(TIMERA0_BASE, TIMER_A, 80000000*value_to_load_for_on);
	  	// Enable the timer.
    	MAP_TimerEnable(TIMERA0_BASE, TIMER_A);
	    	}
}
}

void Switch_off_device()
{
	MAP_TimerIntClear(TIMERA1_BASE, TIMER_TIMA_TIMEOUT);
	timer1OverFlowCounter = timer1OverFlowCounter + 53;
	Serial.println(timer1OverFlowCounter);
  if (timer1OverFlowCounter >= countvalue_for_off )
  {
	  timer1OverFlowCounter = 0;
      Serial.println("Device is OFF");
      digitalWrite(ledPin, LOW);
  }
else{
	    value_to_load_for_off = count_for_off - 53;
	    if (value_to_load_for_off > 53 )
	    {
	    	count_for_off = count_for_off - 53;
	    	// load the timer
	    	MAP_TimerLoadSet(TIMERA1_BASE, TIMER_A, 80000000*53);
	        // Enable the timer.
	    	MAP_TimerEnable(TIMERA1_BASE, TIMER_A);
	    }
	    else
	    	{
	   	// load the timer
	    MAP_TimerLoadSet(TIMERA1_BASE, TIMER_A, 80000000 * value_to_load_for_off);
	  	// Enable the timer.
    	MAP_TimerEnable(TIMERA1_BASE, TIMER_A);
	    	}
}
}




























