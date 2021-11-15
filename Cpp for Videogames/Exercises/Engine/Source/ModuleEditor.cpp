#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "SDL.h"
#include "GL/glew.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

ModuleEditor::ModuleEditor()
{
}

// Destructor
ModuleEditor::~ModuleEditor()
{
}

// Called before render is available
bool ModuleEditor::Init()
{
	LOG("Creating Renderer context");

	// Init SDL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits

	context = SDL_GL_CreateContext(App->window->window);

	// Init Dear ImGui Context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer);
	ImGui_ImplOpenGL3_Init("#version 120");

	ImGui::StyleColorsDark();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEditor::PreUpdate()
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	return update_status::UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleEditor::Update()
{
	
	ImGui::Begin("My name is window");
	ImGui::Text("Hi");
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	//SwapBuffers(nullptr);

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{

	
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEditor::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	
	return true;
}

void ModuleEditor::WindowResized(unsigned width, unsigned height)
{
}

