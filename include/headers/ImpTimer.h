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

class GameTime{
public:

	GameTime(){};
	~GameTime(){};

	void Update(){
		if(!is_start) return;

		count_time ++;
		if(count_time % FPS == 0) component_time ++;
	}
	bool CheckSeconds(int FPS_) {
		return (count_time % FPS_ == 0);
	}
	int GetSeconds() const { return component_time ;};
	int GetMinutes() const { return component_time / 60;};
	int GetHours() const { return component_time / 3600;};

	TimeData GetTime() const { return TimeData(component_time / 3600, (component_time % 3600) / 60, (component_time % 3600) % 60 ) ;};

	void Start(){
		is_start = true;
		component_time = 0;
	}

	void End(){	is_start = false;}

private:
	int count_time = 0;
	int component_time = 0;// second
	
	bool is_start = false;
};


#endif // !IMP_TIMER_H_


