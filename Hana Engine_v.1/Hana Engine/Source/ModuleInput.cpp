#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"

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

update_status ModuleInput::PreUpdate() {
	mouse_pos_dif = float2::zero;
	mouse_wheel_dif = float2::zero;

	return update_status::UPDATE_CONTINUE;
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
			return update_status::UPDATE_STOP;
		case SDL_WINDOWEVENT:
			if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
			break;
		case SDL_KEYDOWN:
			if (keyboard_state_array[SDL_SCANCODE_W] && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
				App->scene->GetCamera()->MoveForward(keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_S] && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
				App->scene->GetCamera()->MoveBackwards(keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_D] && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
				App->scene->GetCamera()->MoveRight(keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_A] && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
				App->scene->GetCamera()->MoveLeft(keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_Q] && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
				App->scene->GetCamera()->MoveUp(keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_E] && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
				App->scene->GetCamera()->MoveDown(keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_F] && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
				// Focus camera around geometry
				App->scene->GetCamera()->FocusModel();
			}
			if (keyboard_state_array[SDL_SCANCODE_RIGHT] && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
				App->scene->GetCamera()->RotateCamera(CAM_AXIS::Y_NEGATIVE, keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_LEFT] && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
				App->scene->GetCamera()->RotateCamera(CAM_AXIS::Y, keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_UP] && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
				App->scene->GetCamera()->RotateCamera(CAM_AXIS::X, keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_DOWN] && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
				App->scene->GetCamera()->RotateCamera(CAM_AXIS::X_NEGATIVE, keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_LALT] && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
				App->scene->GetCamera()->ToggleOrbit();
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			HandleMouseButtonClick(sdlEvent.button);
			break;
		case SDL_MOUSEBUTTONUP:
			HandleMouseButtonRelease(sdlEvent.button);
			break;
		case SDL_MOUSEMOTION:
			mouse_pos_dif.x = float(sdlEvent.motion.xrel);
			mouse_pos_dif.y = float(sdlEvent.motion.yrel);
			break;
		case SDL_MOUSEWHEEL:
			if (sdlEvent.wheel.y > 0 && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
				// Scroll up
				App->scene->GetCamera()->MoveForward(keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			else if (sdlEvent.wheel.y < 0 && !ImGui::IsWindowFocused(ImGuiFocusedFlags_AnyWindow)) {
				// Scroll down
				App->scene->GetCamera()->MoveBackwards(keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			break;
		}
	}

	keyboard = SDL_GetKeyboardState(NULL);

	//ImGui_ImplSDL2_ProcessEvent(&sdlEvent);

	return update_status::UPDATE_CONTINUE;
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
		App->scene->GetCamera()->ToggleMouseControl();
	}
	if (mouseEvent.button == SDL_BUTTON_RIGHT) {
		// Handle right click
	}
}

void ModuleInput::HandleMouseButtonRelease(SDL_MouseButtonEvent& mouseEvent) {
	if (mouseEvent.button == SDL_BUTTON_LEFT) {
		// Handle left release
		App->scene->GetCamera()->ToggleMouseControl();
	}
	if (mouseEvent.button == SDL_BUTTON_RIGHT) {
		// Handle right click
	}
}

void ModuleInput::GetMouseMotion(int& x, int& y) {
	x = int(mouse_pos_dif.x);
	y = int(mouse_pos_dif.y);
}
