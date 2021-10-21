#include "Globals.h"
#include "Application.h"
#include "ModuleScene.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "SDL/include/SDL.h"

ModuleScene::ModuleScene()
{}

ModuleScene::~ModuleScene()
{}

bool ModuleScene::Init()
{
	LOG("Creating Scene Context...");
	bool ret = true;
	

	return ret;
}

bool ModuleScene::Start()
{
	bool ret = true;

	return ret;
}

update_status ModuleScene::PreUpdate()
{
	return UPDATE_CONTINUE;
}

update_status ModuleScene::Update()
{
	SDL_RenderClear(render);
	if (!texture) {
		texture = App->textures->Load("Sprites.png");
	}

	if (texture) {
		Blit(texture, 0, 0, nullptr);
	}

	SDL_RenderPresent(render);
	return UPDATE_CONTINUE;
}

update_status ModuleScene::PostUpdate()
{
	return UPDATE_CONTINUE;
}