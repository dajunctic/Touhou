#ifndef GAME_TIME_H_
#define GAME_TIME_H_

#include "Touhou.h"

class Time{
public:

	Time(){};
	~Time(){};

	void Update(){
		if(!is_start) return;

		count_time ++;
		if(count_time % FPS == 0) se ++;
	}
	bool CheckSeconds(int FPS_) {
		return (count_time % FPS_ == 0);
	}
	int GetFrameTime() const { return count_time - FPS * se;};
	int GetSeconds() const { return se ;};
	bool CheckTime(const int& s,int f = 0) const { return se == s and (count_time - FPS * se) == f; };
	bool CheckPeriod(const int&st, const int& en) const {
	//	cout << component_time << endl;
		return (st <= se and se < en);
	}

	void Start(){
		is_start = true;
		se = 0;
	}
	void Reset(){
		count_time = 0; 
		se = 0 ;
	};

	void End(){	is_start = false;}

private:
	int count_time = 0;
	int se = 0;// second
	
	bool is_start = false;
};


#endif // !GAME_TIME_H_


