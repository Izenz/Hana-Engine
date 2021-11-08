#pragma once
#include <vector>

using namespace std;

class Animation
{
public:
	float speed;
	vector<SDL_Rect> frames;

private:
	float current_frame;

public:
	Animation() : frames(), speed(1.0f), current_frame(0.0f)
	{}

	/*
	Would be better to have another function like Update() to modify the instance of the class and let GetCurrentFrame just return the value that it
	should provide.

	Update(){
		current_frame += speed;
		if(current_frame >= frames.size())
			current_frame = 0.0f;
	}

	SDL_Rect& GetCurrentFrame()
	{
		return frames[(int)current_frame];
	}
	
	Should call currentAnimation->Update() in ModulePlayer.Update();
	*/

	SDL_Rect& GetCurrentFrame()
	{
		current_frame += speed;
		if(current_frame >= frames.size())
			current_frame = 0.0f;
		return frames[(int)current_frame];
	}
};