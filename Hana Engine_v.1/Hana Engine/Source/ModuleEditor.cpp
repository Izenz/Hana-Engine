#include "Globals.h"
#include "Application.h"
#include "ModuleEditor.h"
#include "ModuleWindow.h"
#include "ModuleEditorCamera.h"
#include "ModuleRender.h"
#include "SDL.h"
#include "GL/glew.h"
#include "imgui.h"
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

ModuleEditor::ModuleEditor()
{
	cam = new ModuleEditorCamera();
}

// Destructor
ModuleEditor::~ModuleEditor()
{
}

// Called before render is available
bool ModuleEditor::Init()
{
	/* --------------------------------------> Already done in ModelRender.cpp
	LOG("Creating Renderer context");

	// Init SDL
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits

	context = SDL_GL_CreateContext(App->window->window);
	*/

	// Init Dear ImGui Context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer);
	ImGui_ImplOpenGL3_Init("#version 120");

	ImGui::StyleColorsDark();
	
	cam->Init();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEditor::PreUpdate()
{
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();
	
	cam->PreUpdate();

	return update_status::UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleEditor::Update()
{
	
	ImGui::ShowDemoWindow();

	ImGui::Begin("TriAngle Editor", 0, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("Files")) {
			//IMGUI_DEMO_MARKER("Menu/Files");
			ImGui::MenuItem("Save", NULL, true);
			ImGui::MenuItem("Load", NULL, true);

			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}

	
	ImGui::Text("Engine: TriAngle Engine.");
	ImGui::Text("Author: Joel Herraiz Marti.");
	ImGui::Text("Engine used for Game Development during UPC's AAA Videogame Development Master.");
	ImGui::Text("Built using SDL 2.0 and OpenGL 2.1");
	ImGui::Checkbox("Read?", &b);
	ImGui::End();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	
	cam->Update();

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{

	cam->PostUpdate();
	
	return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleEditor::CleanUp()
{
	delete cam;

	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	
	
	return true;
}

void ModuleEditor::WindowResized(unsigned width, unsigned height)
{
}

