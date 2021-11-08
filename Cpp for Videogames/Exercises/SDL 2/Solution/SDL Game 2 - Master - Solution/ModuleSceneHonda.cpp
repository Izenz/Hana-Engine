#include "Globals.h"
#include "Application.h"
#include "ModuleSceneHonda.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModulePlayer.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleFadeToBlack.h"
#include "SDL/include/SDL.h"

ModuleSceneHonda::ModuleSceneHonda(bool start_enabled) : Module(start_enabled)
{
	// ground
	ground.x = 8;
	ground.y = 376;
	ground.w = 896;
	ground.h = 64;

	// Background / sky
	pool.x = 311;
	pool.y = 335;
	pool.w = 336;
	pool.h = 32;
}

ModuleSceneHonda::~ModuleSceneHonda()
{

}

// Load assets
bool ModuleSceneHonda::Start()
{
	LOG("Loading honda scene");
	
	graphics = App->textures->Load("honda_stage.png");

	App->player->Enable();

	App->audio->PlayMusic("honda.ogg");

	return true;
}

// UnLoad assets
bool ModuleSceneHonda::CleanUp()
{
	LOG("Unloading honda scene");

	App->textures->Unload(graphics);
	App->player->Disable();
	
	return true;
}

update_status ModuleSceneHonda::Update()
{
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->fade->FadeToBlack((Module*)App->scene_ken, this);
	}

	return UPDATE_CONTINUE;
}

update_status ModuleSceneHonda::PostUpdate()
{
	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, -115, 160, &ground);
	App->renderer->Blit(graphics, 155, 145, &pool); // sea and sky

	return UPDATE_CONTINUE;
}
