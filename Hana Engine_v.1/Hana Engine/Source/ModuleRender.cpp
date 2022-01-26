#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleEditor.h"
#include "ModuleEditorCamera.h"
#include "ModuleDebugDraw.h"
#include "ModuleWindow.h"
#include "ModuleScene.h"
#include "SDL.h"
#include "GL/glew.h"


ModuleRender::ModuleRender()
{
	context = nullptr;
}

// Destructor
ModuleRender::~ModuleRender()
{
	delete context;
}

// Called before render is available
bool ModuleRender::Init()
{
	LOG("Creating Renderer context");

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits
	
	context = SDL_GL_CreateContext(App->window->window);
	
	GLenum err = glewInit();
	LOG("Using Glew %s", glewGetString(GLEW_VERSION));

	LOG("Vendor: %s", glGetString(GL_VENDOR));
	LOG("Renderer: %s", glGetString(GL_RENDERER));
	LOG("OpenGL version supported %s", glGetString(GL_VERSION));
	LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glEnable(GL_DEPTH_TEST); // Enable depth test
	glEnable(GL_CULL_FACE); // Enable cull backward faces
	glDisable(GL_SCISSOR_TEST);
	//glDisable(GL_STENCIL_TEST);

	glFrontFace(GL_CCW); // Front faces will be counter clockwise

	return true;
}

update_status ModuleRender::PreUpdate()
{
	int window_height, window_width;

	SDL_GetWindowSize(App->window->window, &window_width, &window_height);
	glViewport(0, 0, window_width, window_height);

	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return update_status::UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_GL_SwapWindow(App->window->window);
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	LOG("Destroying renderer");

	//Destroy window
	SDL_GL_DeleteContext(context);

	return true;
}

void ModuleRender::WindowResized(unsigned width, unsigned height)
{
	LOG("OS Window resized");
	App->window->SetWindowSize(width, height);
}



