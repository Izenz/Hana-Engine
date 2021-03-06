#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow()
{
	w_width = INIT_SCREEN_WIDTH;
	w_height = INIT_SCREEN_HEIGHT;
}

// Destructor
ModuleWindow::~ModuleWindow()
{
}

// Called before render is available
bool ModuleWindow::Init()
{
	LOG("Init SDL window & surface");
	bool ret = true;
	if(SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}
	else
	{
		//Create window
		SDL_DisplayMode DM;
		SDL_GetCurrentDisplayMode(0, &DM);
		w_width = int(DM.w * 0.5);
		w_height = int(DM.h * 0.5);
		Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_MAXIMIZED;
		if(FULLSCREEN == true)
		{
			flags |= SDL_WINDOW_FULLSCREEN;
		}

		window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, w_width, w_height, flags);

		if(window == NULL)
		{
			LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			ret = false;
		}
		else
		{
			//Get window surface
			
			screen_surface = SDL_GetWindowSurface(window);
		}
	}

	return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
	LOG("Destroying SDL window and quitting all SDL systems");

	//Destroy window
	if(window != NULL)
	{
		SDL_DestroyWindow(window);
	}

	//Quit SDL subsystems
	SDL_Quit();
	return true;
}

void ModuleWindow::GetWindowSize(unsigned& w, unsigned& h) const {
	w = w_width;
	h = w_height;
}

void ModuleWindow::SetWindowSize(unsigned w, unsigned h) {
	w_width = w;
	w_height = h;
}

void ModuleWindow::SetVsync(bool vsync)
{
	SDL_GL_SetSwapInterval((int)vsync);
}

void ModuleWindow::WindowMenu()
{
	if (ImGui::Checkbox("Fullscreen", &fullscreen))
		//App->window->SetFullScreen(fullscreen);

	ImGui::SameLine();
	if (ImGui::Checkbox("Vsync", &vsync))
		SetVsync(vsync);

	if (!fullscreen) {
		ImGui::Separator();
		if (ImGui::Checkbox("Resizable", &resizable))
			//SetResizable(resizable);

		if (ImGui::SliderInt("Width", &w_width, 0, max_width)) {
			//SetSize(width, height);
		}
		if (ImGui::SliderInt("Height", &w_height, 0, max_height)) {
			//SetSize(width, height);
		}
	}
	ImGui::Text("Monitor Refresh Rate: %d", refresh_rate);
}