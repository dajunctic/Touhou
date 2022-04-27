#include "Character.h"

Character::Character() 
{
	current_frame = -1;
	time_count = -1;
	current_status = IDLE;
	x = y = 0;
	yin_x = yin_y;

	move_speed = 3;
	is_move = false;
	is_key = false;
	move_x = move_y = 0;

	memset(frame_clip, 0, sizeof(frame_clip));
	is_shift = false;
	circle_angle = 0;
	circle_speed = 1;
}
Character::~Character() 
{
	// Dont know what to do // 
}
void Character::Set(int number_frames_, int time_per_frame_)
{
	number_frames = number_frames_;
	time_per_frame = time_per_frame_;
}
void Character::SetPos(double x_, double y_)
{
	x = x_;
	y = y_;

	yin_x = x - 20;
	yin_y = y + 10;
}
void Character::Move()
{
	move_x = move_vector[current_status].first;
	move_y = move_vector[current_status].second;
};
void Character::Load(SDL_Renderer * screen, string character_name) 
{
	/*#######################    Load Character     ##########################*/
	string status[TOTAL_ACTION] = { "", "_left", "_right", "" , ""};
	for(int i = 0 ; i < TOTAL_ACTION ; i++)
	{
		/* Load Sprite Sheet */
		string path = "res/img/char/" + character_name + status[i] + ".png" ;
		player[i].Load(screen, path);

		/* Horizontal Sprite Sheet*/
		int imageWidth = player[i].GetRect().w;
		int imageHeight = player[i].GetRect().h;
		int frameWidth = imageWidth / number_frames;

		//cout << "SIZE IMAGE: " << imageWidth  << " " << imageHeight << endl ;

		for(int k = 0 ; k < number_frames ; k++)
		{
			frame_clip[i][k].x = k * frameWidth;
			frame_clip[i][k].y = 0;
			frame_clip[i][k].w = frameWidth;
			frame_clip[i][k].h = imageHeight;
		}
	}

	/*##################  Load yinyang circle around character  ###################*/
	for(int i = 0; i < 3 ; i++)
	{
		string path = "res/img/char/yinyang_0" + to_string(i) + ".png";
		yinyang[i].Load(screen, path);
	}

	/*##################  Load character bullet image      ########################*/
	for(int i = 0 ; i < 3 ; i++)
	{
		string path = "res/img/char/char_bullet_0";
		path = path + to_string(i) + ".png";
		char_bullet[i].Load(screen, path);
	}

	// Load Magic Circle //
	magic_circle.Load(screen, "res/img/char/magic_circle.png");
	ressurect_img.Load(screen , "res/img/char/ressurect.png");
}
SDL_Rect Character::getRect()
{
	SDL_Rect rect = player[current_status].GetRect();

	SDL_Rect border;
	border.x = x;
	border.y = y;
	border.w = rect.w / number_frames;
	border.h = rect.h;
	return border;
}
bool Character::BorderCollision()
{
	SDL_Rect rect = player[current_status].GetRect();

	SDL_Rect border;
	border.x = x;
	border.y = y;
	border.w = rect.w / number_frames;
	border.h = rect.h;

	if(border.x < BOARD_X or border.x + border.w >= BOARD_LIMITED_X or border.y < BOARD_Y or border.y + border.h > BOARD_LIMITED_Y)
		return true;
	return false;
}
void Character::Update() 
{
	center_x = (x + player[current_status].GetRect().w / number_frames + x) / 2;
	center_y = (y + player[current_status].GetRect().h + y) / 2;

	if(is_shift) 
	{
		move_speed = 2.5;

		if(yin_y >= y - 10)
		{
			yin_x += 5 * cos(-50.0 * PI / 180);
			yin_y += 5 * sin(-50.0 * PI / 180);
		}
	}
	else 
	{
		move_speed = 3;

		if(yin_y <= y + 10)
		{
			yin_x -= 5 * cos(-50.0 * PI / 180);
			yin_y -= 5 * sin(-50.0 * PI / 180);
		}
	}

	if(is_move) 
	{
		x += move_x * move_speed;
		y += move_y * move_speed;

		yin_x += move_x * move_speed;
		yin_y += move_y * move_speed; 

		if(BorderCollision())
		{
			x -= move_x * move_speed;
			y -= move_y * move_speed;

			yin_x -= move_x * move_speed;
			yin_y -= move_y * move_speed; 
		}
		center_x = (x + player[current_status].GetRect().w / number_frames + x) / 2;
		center_y = (y + player[current_status].GetRect().h + y) / 2;

		// yin_x = x - 20;
		// yin_y = y + 10;
	}


	time_count ++;
	if(time_count % time_per_frame == 0) 
	{
		current_frame++;

		if(current_status == LEFT or current_status == RIGHT)
		{
			if(current_frame >= number_frames / 2){
				current_frame %= (number_frames / 2);
				current_frame += number_frames / 2;
			}
		}
		
		current_frame %= number_frames;
	}

	/* Yinyang */
	yinyang_angle += yinyang_speed;
	
}
void Character::Show(SDL_Renderer * screen) 
{
	Update();

	/*#########################        Bullet Character            ################################################*/
	for(auto [pos, id] : weapon)
	{
		if(id == 3) id = 2;
		char_bullet[id].SetRect(pos.fi, pos.se);	
		char_bullet[id].Render(screen);
	}


	/*#######################3        Main Character                  ###########################################*/
	{
		if(is_die)
		{
			if(is_ressurect)
			{

				time_ressurect ++;

				if(time_ressurect >= 10)
				{
					circle_angle += circle_speed * 2;
					if(circle_angle >= 360) circle_angle - 360;
					ressurect_img.SetRect(center_x - ressurect_img.GetRect().w / 2, center_y - ressurect_img.GetRect().h / 2);

					ressurect_img.RenderAngle(screen, circle_angle);
				}

				for(int i = 0 ; i <= 120 ; i += 20)
				{
					if(i <= time_ressurect and time_ressurect <= i + 10) return;
				}

				if(time_ressurect == 140)
				{
					is_die = false;
					is_ressurect = false;
					time_ressurect = -1;
				}
				
			}
			else
			{
				/* When life is ended */
				return;
			}
		}

		SDL_Texture* p_object = player[current_status].GetImage();
		SDL_Rect rect = player[current_status].GetRect();

		SDL_Rect renderquad = { int(x) , int(y) , rect.w / number_frames, rect.h };
		SDL_RenderCopy(screen, p_object, &frame_clip[current_status][current_frame], &renderquad);

	}
	/*########################      Yinyang arround character            ####################################### */
	{
		SDL_Texture* yinyang_object = yinyang[current_yinyang].GetImage();
		SDL_Rect yinyang_rect = yinyang[current_yinyang].GetRect();
		SDL_Rect yinyang_renderquad = { int(yin_x), int(yin_y), yinyang_rect.w, yinyang_rect.h};
		SDL_Point center = { yinyang_rect.w / 2, yinyang_rect.h / 2};

		SDL_RenderCopyEx( screen, yinyang_object, NULL, &yinyang_renderquad, yinyang_angle , &center, SDL_FLIP_NONE );

		SDL_Rect yinyang_renderquad2 = { int(2 * center_x - yin_x - 15 ), int(yin_y), yinyang_rect.w, yinyang_rect.h};
		SDL_RenderCopyEx( screen, yinyang_object, NULL, &yinyang_renderquad2, -yinyang_angle , &center, SDL_FLIP_NONE );
	}

	// Magic Circle //

	if(!is_shift) return;
	circle_angle += circle_speed;
	if(circle_angle >= 360) circle_angle - 360;
	magic_circle.SetRect(center_x - magic_circle.GetRect().w / 2, center_y - magic_circle.GetRect().h / 2);

	magic_circle.RenderAngle(screen, circle_angle);

}

void Character::AddBullet()
{
	
	if(weapon.empty())
	{
		if(is_shift)
		{
			weapon.push_back({{x + 2, y + 5}, 0});
		}
		else
		{
			weapon.push_back({{x + 5, y + 5}, 1});
			weapon.push_back({{2 * center_x - (x + 5) - 6, y + 5}, 1});
		}

		weapon.push_back({{yin_x , yin_y}, 2});
		weapon.push_back({{2 * center_x - yin_x - 15  , yin_y}, 3});
	}
	else{

		int it = weapon.size() - 1;
		while(weapon[it].se != 1 and it > 0)
		{
			it--;
		}
		int y_ = weapon[it].fi.se;
		if(y - y_ >= 50)
		{

			if(!is_shift)
			{
				weapon.push_back({{x + 5, y + 5}, 1});
				weapon.push_back({{2 * center_x - (x + 5) - 6 , y + 5}, 1});
			}
		}

		it = weapon.size() - 1;
		while(weapon[it].se != 0 and it > 0)
		{
			it--;
		}
		y_ = weapon[it].fi.se;
		if(y - y_ >= 40)
		{
			if(is_shift)
			{
				weapon.push_back({{x + 2, y + 5}, 0});
			}
		}


		it = weapon.size() - 1;
		while(weapon[it].se != 2 and weapon[it].se != 3 and it > 0)
		{
			it--;
		}
		y_ = weapon[it].fi.se;
		if(yin_y - y_ > 100)
		{
			weapon.push_back({{yin_x , yin_y}, 2});
			weapon.push_back({{2 * center_x - yin_x - 15  , yin_y}, 3});
		}
	}
}

void Character::HandleBullet(vector<Enemy>& enemy)
{
	/* Check collision with the enemy */
	vector<pair<pair<int,int>, int> > temp;

	for(auto &[pos , id] : weapon)
	{
		int x = pos.fi;
		int y = pos.se;

		if(x < 0 or y < 0)
		{
			continue;
		}

		pair<double, double> center_bullet;
		center_bullet.fi = ( x + x + char_bullet[id].GetRect().w) / 2;
		center_bullet.se = ( y + y + char_bullet[id].GetRect().h) / 2;

		SDL_Rect bullet_rect = {x, y, char_bullet[id].GetRect().w, char_bullet[id].GetRect().h};
		bool vanish = false;

		for(auto &xx: enemy)
		{
			pair<double, double> center_enemy = xx.GetCenterPos() ;
			double r = 15;

			SDL_Rect enemy_rect = xx.GetRect();
			if(id >= 2)
			{
				if(PointInCircle(center_bullet, center_enemy, r))
				{
					vanish = true;
					xx.minusHealhPoint(bullet_power[id]);
				}
			}
			else
			{
				if(RectInRect(bullet_rect, enemy_rect))
				{
					vanish = true;
					xx.minusHealhPoint(bullet_power[id]);
				}
			}
		}
		if(vanish)
		{
			continue;
		}

		temp.push_back({{x,y}, id});
	}
	weapon = temp;
	/* Bullet */
	if(is_shoot) AddBullet();

	for(auto &[pos , id] : weapon) 
	{
		if(id == 0 or id == 1) pos.se -= 10;
		if(id == 2 or id == 3){
			if(enemy.empty() or pos.se > 400)
			{
				double _angle = rand()% (80 - 40 + 1) + 40;

				if(id == 2){
					pos.fi += 6 * cos((180.0 - _angle)*PI/180);
					pos.se -= 6 * sin(_angle*PI/180);
				}
				if(id == 3){
					pos.fi += 6 * cos(_angle*PI/180);
        			pos.se -= 6 * sin(_angle*PI/180);
				}
			}else{
				double x = pos.fi + char_bullet[2].GetRect().w / 2;
				double y = pos.se + char_bullet[2].GetRect().h / 2;

				double min_dis = 9999999.0;
				int min_id = 0;

				for(int i = 0 ; i < enemy.size() ; i++){
					double x_ = enemy[i].GetCenterPos().fi;
					double y_ = enemy[i].GetCenterPos().se;

					if(min_dis > distance({x, y}, {x_, y_})){
						min_dis = distance({x, y}, {x_, y_});
						min_id = i;
					}
				}

			//	int min_id = rand()%(enemy.size() - 0 + 1) + 0;

				double x_ = enemy[min_id].GetCenterPos().fi;
				double y_ = enemy[min_id].GetCenterPos().se;

				pair<double,double> v = {x_ - x, y_ - y};

				double angle = acos(cos(v, {1, 0})) / PI * 180;

				
				if(v.se < 0 or (v.fi == 0 and v.se < 0)) angle = -angle ;

				double speed_tmp = min(6.0 , distance({x, y}, {x_, y_}));

				pos.fi += speed_tmp * cos(angle / 180.0 * PI);
				pos.se += speed_tmp * sin(angle / 180.0 * PI);

			}
		}
	}
}