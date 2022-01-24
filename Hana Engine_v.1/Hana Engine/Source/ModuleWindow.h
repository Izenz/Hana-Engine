#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include "SDL/include/SDL.h"

class Application;

class ModuleWindow : public Module
{
public:

	ModuleWindow();

	// Destructor
	virtual ~ModuleWindow();

	// Called before quitting
	bool Init();

	// Called before quitting
	bool CleanUp();

	void GetWindowSize(unsigned& w, unsigned& h) const;
	void SetWindowSize(unsigned w, unsigned h);
	void SetVsync(bool vsync);
	void WindowMenu();
	//The window we'll be rendering to
	SDL_Window* window = NULL;

	//The surface contained by the window
	SDL_Surface* screen_surface = NULL;
private:
	int w_width, w_height;
	int max_width, max_height;
	bool fullscreen;
	bool resizable = true;
	int refresh_rate;
	bool vsync = true;
};

#endif // __ModuleWindow_H__