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

	// Get Keyboard and Mouse arrays from SDL and init keys as IDLE
	keyboard = SDL_GetKeyboardState(NULL);
	keyboard_state = new KEY_STATE[NUM_MAX_KEYS];
	memset(keyboard_state, static_cast<int>(KEY_STATE::IDLE), sizeof(KEY_STATE) * NUM_MAX_KEYS);
	memset(mouse_state, static_cast<int>(KEY_STATE::IDLE), sizeof(KEY_STATE) * NUM_MOUSE_BUTTONS);

	return ret;
}

update_status ModuleInput::PreUpdate() {
	SDL_Event sdlEvent;
	
	// KEYBOARD PASS
	for (size_t i = 0; i < NUM_MAX_KEYS; ++i) {
		if (keyboard[i] == (Uint8)KEY_STATE::DOWN) {
			if (keyboard_state[i] == KEY_STATE::IDLE) {
				keyboard_state[i] = KEY_STATE::DOWN;
			}
			else {
				keyboard_state[i] = KEY_STATE::REPEAT;
			}
		}
		else {
			if (keyboard_state[i] == KEY_STATE::DOWN || keyboard_state[i] == KEY_STATE::REPEAT) {
				keyboard_state[i] = KEY_STATE::UP;
			}
			else {
				keyboard_state[i] = KEY_STATE::IDLE;
			}

		}
	}

	// MOUSE PASS
	for (size_t i = 0; i < NUM_MOUSE_BUTTONS; ++i) {
		if (mouse_state[i] == KEY_STATE::DOWN) {
			mouse_state[i] = KEY_STATE::REPEAT;
		}

		if (mouse_state[i] == KEY_STATE::UP) {
			mouse_state[i] = KEY_STATE::IDLE;
		}
	}
	mouse_pos_delta = float2::zero;
	mouse_wheel_delta = float2::zero;

	// SDL Input detection
	while (SDL_PollEvent(&sdlEvent) != 0) {
		ImGuiIO& io = ImGui::GetIO();
		ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
		switch (sdlEvent.type) {
		case SDL_QUIT:
			return update_status::UPDATE_STOP;
		case SDL_WINDOWEVENT:
			if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				window_size.x = sdlEvent.window.data1;
				window_size.y = sdlEvent.window.data2;
				App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
			}
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (io.WantCaptureMouse)	break;
			mouse_state[sdlEvent.button.button] = KEY_STATE::DOWN;
			break;
		case SDL_MOUSEBUTTONUP:
			if (io.WantCaptureMouse)	break;
			mouse_state[sdlEvent.button.button] = KEY_STATE::UP;
			break;
		case SDL_MOUSEMOTION:
			mouse_pos_delta.x = float(sdlEvent.motion.xrel);
			mouse_pos_delta.y = float(sdlEvent.motion.yrel);
			break;
		case SDL_MOUSEWHEEL:
			mouse_wheel_delta.x = float(sdlEvent.wheel.x);
			mouse_wheel_delta.y = float(sdlEvent.wheel.y);
			break;
		case SDL_DROPFILE:
			char* dropped_file_path = sdlEvent.drop.file;
			// TODO: Do something with dropped file
			SDL_free(dropped_file_path);
			break;
		}
	}

	keyboard = SDL_GetKeyboardState(NULL);

	return update_status::UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleInput::Update()
{
	/*
	SDL_Event sdlEvent;

	const Uint8* keyboard_state_array = SDL_GetKeyboardState(NULL);
	while (SDL_PollEvent(&sdlEvent) != 0)
	{
		ImGui_ImplSDL2_ProcessEvent(&sdlEvent);
		ImGuiIO& io = ImGui::GetIO();

		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			return update_status::UPDATE_STOP;
		case SDL_WINDOWEVENT:
			if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
				App->renderer->WindowResized(sdlEvent.window.data1, sdlEvent.window.data2);
			break;
		case SDL_KEYDOWN:
			if (keyboard_state_array[SDL_SCANCODE_W]) {
				App->scene->GetCamera()->MoveForward(keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_S]) {
				App->scene->GetCamera()->MoveBackwards(keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_D]) {
				App->scene->GetCamera()->MoveRight(keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_A]) {
				App->scene->GetCamera()->MoveLeft(keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_Q]) {
				App->scene->GetCamera()->MoveUp(keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_E]) {
				App->scene->GetCamera()->MoveDown(keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_F]) {
				// Focus camera around geometry
				App->scene->GetCamera()->FocusModel();
			}
			if (keyboard_state_array[SDL_SCANCODE_RIGHT]) {
				App->scene->GetCamera()->RotateCamera(CAM_AXIS::Y_NEGATIVE, keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_LEFT]) {
				App->scene->GetCamera()->RotateCamera(CAM_AXIS::Y, keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_UP]) {
				App->scene->GetCamera()->RotateCamera(CAM_AXIS::X, keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_DOWN]) {
				App->scene->GetCamera()->RotateCamera(CAM_AXIS::X_NEGATIVE, keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			if (keyboard_state_array[SDL_SCANCODE_LALT]) {
				ImGui::GetIO().KeyAlt = true;
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
			if (sdlEvent.wheel.y > 0) {
				// Scroll up
				App->scene->GetCamera()->MoveForward(keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			else if (sdlEvent.wheel.y < 0) {
				// Scroll down
				App->scene->GetCamera()->MoveBackwards(keyboard_state_array[SDL_SCANCODE_LSHIFT]);
			}
			break;
		case SDL_DROPFILE:
			char* file_directory = sdlEvent.drop.file;
			break;
		}
	}

	keyboard = SDL_GetKeyboardState(NULL);
	*/
	return update_status::UPDATE_CONTINUE;
}


// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);

	delete[] keyboard_state;
	return true;
}
/*
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
*/
void ModuleInput::GetMouseMotion(int& x, int& y) {
	x = int(mouse_pos_delta.x);
	y = int(mouse_pos_delta.y);
}

