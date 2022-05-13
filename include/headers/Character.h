#ifndef CHARACTER
#define CHARACTER
#include "GameImage.h"
#include "Bullet.h"
#include "Enemy.h"
#include "GamePhysics.h"

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
	SDL_Rect getRect();

	void Load(SDL_Renderer * screen, string character_name);
	void Update();
	void Show(SDL_Renderer * screen);

	void Move();
	void SetMove(bool truth) { is_move = truth;};
	void PressShift(bool truth){ is_shift = truth;}
	void SetStatus(int status_) { current_status = status_ ;};
	void Keydown(bool truth) { is_key = truth;};
	bool IsKeydown() { return is_key;};
	bool BorderCollision();

	void AddBullet();
	void HandleBullet(vector<Enemy> & enemy, int * score);
	void Shoot(bool truth){ is_shoot = truth;};
	double GetRadius() const{ return radius; };
	pair<double, double> GetCenter() const { return {center_x, center_y};};
	void Die(bool truth){ is_die = truth; };
	bool IsDie() const { return is_die; };
	void setRessurect(bool truth) { is_ressurect = truth; };
	bool isRessurect() const { return is_ressurect; };

	void pause();
	void resume();
	
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
	double center_x, center_y;
	pair<int,int> move_vector[TOTAL_ACTION] = {{0, 0}, {-1 , 0}, {1 , 0}, {0 , -1}, {0 , 1} };

	SDL_Rect frame_clip[TOTAL_ACTION][MAX_FRAMES];

	Image player[TOTAL_ACTION];

	/* About yinyang circle arround character */
	Image yinyang[3];
	double yin_x;
	double yin_y;

	int current_yinyang = 2;
	double yinyang_angle = 0;
	double second_yin_x = 58;
	double yinyang_speed = PI;

	/* Add queue bullet */
	

	vector<pair<pair<int,int>, int> > weapon;
	Image char_bullet[10];
	bool is_shoot = false;
	int bullet_power[3] = {3, 1, 2};


	/* Press Shift */
	bool is_shift;

	Image magic_circle;
	double circle_speed, circle_angle;

	double radius = 5;

	// Handle die //
	bool is_die = false;
	bool is_ressurect = false;
	int time_ressurect = -1; 
	Image ressurect_img;


	bool is_paused = false;

};


#endif // !CHARACTER


