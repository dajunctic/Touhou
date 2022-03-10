#ifndef CHARACTER
#define CHARACTER
#include "GameObject.h"
#include "Bullet.h"

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
	void SetPos(double x, double y);

	void Load(SDL_Renderer * screen, string character_name);
	void Update();
	void Show(SDL_Renderer * screen);

	void Move();
	void SetMove(bool truth) { is_move = truth;};
	void SetStatus(int status_) { current_status = status_ ;};
	void Keydown(bool truth) { is_key = truth;};
	bool IsKeydown() { return is_key;};

	void AddBullet();
	void Shoot(bool truth){ is_shoot = truth;};
private:
	int current_frame;
	int number_frames;
	int time_per_frame;
	int time_count;
	int current_status;

	int move_speed;
	bool is_move, is_key;
	double move_x, move_y;

	double x, y;
	pair<int,int> move_vector[TOTAL_ACTION] = {{0, 0}, {-1 , 0}, {1 , 0}, {0 , -1}, {0 , 1} };

	SDL_Rect frame_clip[TOTAL_ACTION][MAX_FRAMES];

	Object player[TOTAL_ACTION];

	/* About yinyang circle arround character */
	Object yinyang[3];
	double yin_x;
	double yin_y;

	int current_yinyang = 0;
	double yinyang_angle = 0;
	double second_yin_x = 58;
	double yinyang_speed = PI;

	/* Add queue bullet */
	

	vector<pair<pair<int,int>, int> > weapon;
	Object char_bullet[10];
	bool is_shoot = false;
};


#endif // !CHARACTER


