#include "Character.h"

Character::Character() {
	current_frame = -1;
	current_status = IDLE;
	x = y = 0;

	memset(frame_clip, 0, sizeof(frame_clip));
}
Character::~Character() {

}
void Character::Set(int number_frames_, int time_per_frame_){
	number_frames = number_frames_;
	time_per_frame = time_per_frame_;
}
void Character::Load(SDL_Renderer * screen, string character_name) {
	string status[TOTAL_ACTION] = { "", "_left", "_right" };
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
}
void Character::Update() {
	current_frame++;
	current_frame %= number_frames;
}
void Character::Show(SDL_Renderer * screen) {

	SDL_Texture* p_object = player[current_status].GetObject();
	SDL_Rect rect = player[current_status].GetRect();

	SDL_Rect renderquad = { rect.x, rect.y, rect.w / number_frames, rect.h };
	SDL_RenderCopy(screen, p_object, frame_clip[current_status], &renderquad);
}