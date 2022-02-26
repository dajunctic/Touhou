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
		TOTAL_ACTION
	};

	Character();
	~Character();

	void Set(int frame_count, int time_per_frame);
	void SetPos(float x, float y);

	void Load(SDL_Renderer * screen, string character_name);
	void Update();
	void Show(SDL_Renderer * screen);

	void Move(float move_x, float move_y);
	void SetMove(bool truth) { is_move = truth;};
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

	SDL_Rect frame_clip[TOTAL_ACTION][MAX_FRAMES];

	Object player[TOTAL_ACTION];
};

#endif // !CHARACTER


