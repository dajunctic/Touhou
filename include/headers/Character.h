#ifndef CHARACTER
#define CHARACTER
#include "GameObject.h"

const int MAX_FRAMES = 20;

class Character {
public:
	enum {
		IDLE,
		LEFT,
		RIGHT,
		UP,
		DOWN,
		TOTAL_ACTION
	};
	

	Character();
	~Character();

	void Set(int frame_count, int time_per_frame);
	void SetPos(float x, float y);

	void Load(SDL_Renderer * screen, string character_name);
	void Update();
	void Show(SDL_Renderer * screen);

	void Move();
	void SetMove(bool truth) { is_move = truth;};
	void SetStatus(int status_) { current_status = status_ ;};
	void Keydown(bool truth) { is_key = truth;};
	bool IsKeydown() { return is_key;};
protected:
	int current_frame;
	int number_frames;
	int time_per_frame;
	int time_count;
	int current_status;

	int move_speed;
	bool is_move, is_key;
	float move_x, move_y;

	float x, y;
	pair<int,int> move_vector[TOTAL_ACTION] = {{0, 0}, {-1 , 0}, {1 , 0}, {0 , -1}, {0 , 1} };

	SDL_Rect frame_clip[TOTAL_ACTION][MAX_FRAMES];

	Object player[TOTAL_ACTION];

	/* About yinyang circle arround character */
	Object yinyang[3];
	float yin_x;
	float yin_y;

	int current_yinyang = 0;
	float yinyang_angle = 0;
	float second_yin_x = 58;
	float yinyang_speed = PI;
};


#endif // !CHARACTER


