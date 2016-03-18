/*
 * scheduling.h
 *
 *
 *      Author: preethibodduluri
 */

#ifndef SCHEDULING_H_
#define SCHEDULING_H_
#include "Energia.h"


#define TIMER_TIMA_TIMEOUT  0x00000001


class ScheduleLibrary
{

private:

public:
	void initTimer ();
    void setTimerToswitchon(int time_in_seconds_for_on);
    void setTimerToswitchoff(int time_in_seconds_for_off);
};




extern ScheduleLibrary scheduling;
extern "C" void Switch_on_device  (void);
extern "C" void Switch_off_device (void);


#endif /* SCHEDULING_H_ */
