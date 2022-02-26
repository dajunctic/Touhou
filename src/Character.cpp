#include "Character.h"

Character::Character() {
	current_frame = -1;
	time_count = -1;
	current_status = IDLE;
	x = y = 0;
	yin_x = yin_y;

	move_speed = 2.6;
	is_move = false;
	is_key = false;
	move_x = move_y = 0;

	memset(frame_clip, 0, sizeof(frame_clip));
}
Character::~Character() {
	for(int i = 0 ; i < TOTAL_ACTION ; i++)
		player[i].Free();
}
void Character::Set(int number_frames_, int time_per_frame_){
	number_frames = number_frames_;
	time_per_frame = time_per_frame_;
}
void Character::SetPos(float x_, float y_){
	x = x_;
	y = y_;

	yin_x = x - 20;
	yin_y = y + 10;
}
void Character::Move(){
	move_x = move_vector[current_status].first;
	move_y = move_vector[current_status].second;
};
void Character::Load(SDL_Renderer * screen, string character_name) {
	string status[TOTAL_ACTION] = { "", "_left", "_right", "" , ""};
	for(int i = 0 ; i < TOTAL_ACTION ; i++){
		/* Load Sprite Sheet */
		string path = "res/img/" + character_name + status[i] + ".png" ;
		player[i].LoadImage(screen, path);

		/* Horizontal Sprite Sheet*/
		int imageWidth = player[i].GetRect().w;
		int imageHeight = player[i].GetRect().h;
		int frameWidth = imageWidth / number_frames;

		//cout << "SIZE IMAGE: " << imageWidth  << " " << imageHeight << endl ;

		for(int k = 0 ; k < number_frames ; k++){
			frame_clip[i][k].x = k * frameWidth;
			frame_clip[i][k].y = 0;
			frame_clip[i][k].w = frameWidth;
			frame_clip[i][k].h = imageHeight;
		}
	}

	/* Load yinyang circle around character */
	for(int i = 0; i < 3 ; i++){
		string path = "res/img/yinyang_0" + to_string(i) + ".png";
		yinyang[i].LoadImage(screen, path);
	}
}
void Character::Update() {
	if(is_move) {
		x += move_x * move_speed;
		y += move_y * move_speed;

		yin_x = x - 20;
		yin_y = y + 10;
	}


	time_count ++;
	if(time_count % time_per_frame == 0) {
		current_frame++;

		if(current_status == LEFT or current_status == RIGHT){
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
void Character::Show(SDL_Renderer * screen) {

	SDL_Texture* p_object = player[current_status].GetObject();
	SDL_Rect rect = player[current_status].GetRect();

	SDL_Rect renderquad = { int(x) , int(y) , rect.w / number_frames, rect.h };
	SDL_RenderCopy(screen, p_object, &frame_clip[current_status][current_frame], &renderquad);

	/* Yinyang arround character */
	SDL_Texture* yinyang_object = yinyang[current_yinyang].GetObject();
	SDL_Rect yinyang_rect = yinyang[current_yinyang].GetRect();
	SDL_Rect yinyang_renderquad = { int(yin_x), int(yin_y), yinyang_rect.w, yinyang_rect.h};
	SDL_Point center = { yinyang_rect.w / 2, yinyang_rect.h / 2};

//	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
    SDL_RenderCopyEx( screen, yinyang_object, NULL, &yinyang_renderquad, yinyang_angle , &center, SDL_FLIP_NONE );

	SDL_Rect yinyang_renderquad2 = { int(yin_x  + second_yin_x), int(yin_y), yinyang_rect.w, yinyang_rect.h};
	SDL_RenderCopyEx( screen, yinyang_object, NULL, &yinyang_renderquad2, yinyang_angle , &center, SDL_FLIP_NONE );

}
