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

	void Load(SDL_Renderer * screen, string character_name);
	void Set(int frame_count, int time_per_frame);
	void Update();
	void Show(SDL_Renderer * screen);
protected:
	int current_frame;
	int number_frames;
	int time_per_frame;
	int current_status;

	float x, y;

	SDL_Rect frame_clip[TOTAL_ACTION][MAX_FRAMES];

	Object player[TOTAL_ACTION];
};

#endif // !CHARACTER


