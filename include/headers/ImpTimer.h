#ifndef IMP_TIMER_H_
#define IMP_TIMER_H_

#include "Touhou.h"

class ImpTimer {
public:
	ImpTimer();
	~ImpTimer();

	void start();
	void stop();
	void paused();
	void unpaused();

	int getTicks();

	bool isStarted();
	bool isPaused();
private:
	int start_tick_;
	int paused_tick_;

	bool is_paused_;
	bool is_started_;

};

#endif // !IMP_TIMER_H_


