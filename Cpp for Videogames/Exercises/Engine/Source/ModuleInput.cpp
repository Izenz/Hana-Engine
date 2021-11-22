#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"
#include "ModuleEditorCamera.h"
#include "ModuleEditor.h"

ModuleInput::ModuleInput()
{}

// Destructor
ModuleInput::~ModuleInput()
{}

// Called before render is available
bool ModuleInput::Init()
{
	LOG("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::Update()
{
	SDL_Event sdlEvent;
	const Uint8* keyboard_state_array = SDL_GetKeyboardState(NULL);

	while (SDL_PollEvent(&sdlEvent) != 0)
	{
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			return UPDATE_STOP;
		case SDL_WINDOWEVENT:
			if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
			break;
		case SDL_KEYDOWN:
			if (keyboard_state_array[SDL_SCANCODE_W]) {
				App->editor->cam->MoveForward();
			}
			if (keyboard_state_array[SDL_SCANCODE_S]) {
				App->editor->cam->MoveBackwards();
			}
			if (keyboard_state_array[SDL_SCANCODE_D]) {
				App->editor->cam->MoveRight();
			}
			if (keyboard_state_array[SDL_SCANCODE_A]) {
				App->editor->cam->MoveLeft();
			}
			if (keyboard_state_array[SDL_SCANCODE_RIGHT]) {
				App->editor->cam->RotateCamera(CAM_AXIS::Y, App->editor->cam->GetRotationSpeed() * App->GetDeltaTime());
			}
			if (keyboard_state_array[SDL_SCANCODE_LEFT]) {
				App->editor->cam->RotateCamera(CAM_AXIS::Y, -App->editor->cam->GetRotationSpeed() * App->GetDeltaTime());
			}
			if (keyboard_state_array[SDL_SCANCODE_UP]) {

			}
			if (keyboard_state_array[SDL_SCANCODE_DOWN]) {

			}

			break;
		case SDL_MOUSEBUTTONDOWN:
			HandleMouseButtonClick(sdlEvent.button);
			break;
		case SDL_MOUSEBUTTONUP:
			HandleMouseButtonRelease(sdlEvent.button);
		}
	}

	keyboard = SDL_GetKeyboardState(NULL);

	//ImGui_ImplSDL2_ProcessEvent(&sdlEvent);

	return UPDATE_CONTINUE;
}


// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

void ModuleInput::HandleMouseButtonClick(SDL_MouseButtonEvent& mouseEvent) {
	if (mouseEvent.button == SDL_BUTTON_LEFT) {
		// Handle left click
		App->editor->cam->SetRotationLock(true);
	}
	if (mouseEvent.button == SDL_BUTTON_RIGHT) {
		// Handle right click
	}
}

void ModuleInput::HandleMouseButtonRelease(SDL_MouseButtonEvent& mouseEvent) {
	if (mouseEvent.button == SDL_BUTTON_LEFT) {
		// Handle left click
		App->editor->cam->SetRotationLock(false);
	}
	if (mouseEvent.button == SDL_BUTTON_RIGHT) {
		// Handle right click
	}
}
