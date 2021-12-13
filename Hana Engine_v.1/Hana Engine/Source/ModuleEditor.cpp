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
#include <shellapi.h>

ModuleEditor::ModuleEditor()
{
	cam = new ModuleEditorCamera();
}

// Destructor
ModuleEditor::~ModuleEditor()
{
	delete cam;
}

// Called before render is available
bool ModuleEditor::Init()
{
	// Init Dear ImGui Context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer);
	ImGui_ImplOpenGL3_Init("#version 120");

	ImGui::StyleColorsDark();
	
	cam->Init();

	return true;
}

update_status ModuleEditor::PreUpdate()
{
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();

	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui::NewFrame();
	
	cam->PreUpdate();

	return update_status::UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleEditor::Update()
{
	DrawWindowMainMenu();

	if (showConsole)		Output->DrawConsole(&showConsole);
	if (showEngineInfo)		DrawEngineInfoWindow(&showEngineInfo);
	if (showTimeWindow)		Time->DrawTimeWindow(&showTimeWindow);

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

void ModuleEditor::DrawWindowMainMenu() {

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			// TODO: Add option to select files so the user can add search and select textures/models.
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window")) {
			if (ImGui::MenuItem("Console", NULL, false, &showConsole))
				showConsole = !showConsole;
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {
			if (ImGui::MenuItem("About us"))
				ShellExecute(0, 0, "https://github.com/Izenz/Hana-Engine", 0, 0, SW_SHOW);
			if (ImGui::MenuItem("Engine Info", NULL, false, &showEngineInfo))
				showEngineInfo = !showEngineInfo;
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void ModuleEditor::DrawEngineInfoWindow(bool* p_open) const {
	
	if (!ImGui::Begin("Hana Engine: Info", p_open)) {
		ImGui::End();
		return;
	}

	ImGui::Text("Engine: Hana Engine.");
	ImGui::Text("Author: Joel Herraiz Marti.");
	ImGui::Text("Engine used for Game Development during UPC's AAA Videogame Development Master.");
	ImGui::Text("Built using SDL 2.0 and OpenGL 2.1, Assimp, MathGeoLib, ImGui & DevIL.");

	ImGui::End();
	
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


