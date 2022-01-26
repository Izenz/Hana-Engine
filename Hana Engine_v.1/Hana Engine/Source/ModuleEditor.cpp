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
	for (int it = 0; it <= (int) WINDOW_TYPES::MAX; ++it) {
		window_active[it] = false;
	}

	// TODO: Ask if theres a fancier way to init this.
	window_active[(int)WINDOW_TYPES::GAME_VIEW] = true;
	window_active[(int)WINDOW_TYPES::HIERARCHY] = true;
	window_active[(int)WINDOW_TYPES::INSPECTOR] = true;
	window_active[(int)WINDOW_TYPES::RESOURCES] = true;
	window_active[(int)WINDOW_TYPES::EXPLORER] = true;
	window_active[(int)WINDOW_TYPES::CONSOLE] = true;
	window_active[(int)WINDOW_TYPES::TIME_CONTROL] = true;
}

// Destructor
ModuleEditor::~ModuleEditor()
{
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

	return true;
}

update_status ModuleEditor::PreUpdate()
{
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();

	// Enable docking system
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	// Custom ImGui Style
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowMenuButtonPosition = ImGuiDir_None;


	ImGui::NewFrame();

	return update_status::UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleEditor::Update()
{
	DrawEditorMainMenu();
	DrawEditorEnvironment();
	
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	return update_status::UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
	return update_status::UPDATE_CONTINUE;
}

void ModuleEditor::DrawEditorEnvironment() {
	
	CreateDockingSpace();
	LoadSceneInEditor();

	if (window_active[(int)WINDOW_TYPES::GAME_VIEW])			DrawGameSceneWindow(&window_active[(int)WINDOW_TYPES::GAME_VIEW]);
	if (window_active[(int)WINDOW_TYPES::HIERARCHY])			DrawHierarchyWindow(&window_active[(int)WINDOW_TYPES::HIERARCHY]);
	if (window_active[(int)WINDOW_TYPES::INSPECTOR])			DrawInspectorWindow(&window_active[(int)WINDOW_TYPES::INSPECTOR]);
	if (window_active[(int)WINDOW_TYPES::RESOURCES])			DrawResourcesWindow(&window_active[(int)WINDOW_TYPES::RESOURCES]);
	if (window_active[(int)WINDOW_TYPES::EXPLORER])				DrawExplorerWindow(&window_active[(int)WINDOW_TYPES::EXPLORER]);
	if (window_active[(int)WINDOW_TYPES::ENGINE_INFO])			DrawEngineInfoWindow(&window_active[(int)WINDOW_TYPES::ENGINE_INFO]);
	if (window_active[(int)WINDOW_TYPES::ENGINE_CONFIG])		DrawEngineConfigWindow(&window_active[(int)WINDOW_TYPES::ENGINE_CONFIG]);
	if (window_active[(int)WINDOW_TYPES::IMGUI_DEMO])			ImGui::ShowDemoWindow();
	if (window_active[(int)WINDOW_TYPES::CONSOLE])				Output->DrawConsole(&window_active[(int)WINDOW_TYPES::CONSOLE]);
	if (window_active[(int)WINDOW_TYPES::TIME_CONTROL])			DrawTimeControlWindow(&window_active[(int)WINDOW_TYPES::TIME_CONTROL]);
}

void ModuleEditor::LoadSceneInEditor() {
	ImGui::Begin(default_scene_name, &scene_open);
	{
		// Using a Child allow to fill all the space of the window.
		ImGui::BeginChild("SceneDockspace");
		ImGuiID scenedockspaceId = ImGui::GetID("SceneDockspace");
		ImGui::DockSpace(scenedockspaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
		ImGui::EndChild();
	}
	ImGui::End();

}

void ModuleEditor::DrawEditorMainMenu() {

	if (ImGui::BeginMainMenuBar()) {
		if (ImGui::BeginMenu("File")) {
			if (ImGui::MenuItem("Open")) {}
			if (ImGui::MenuItem("Save")) {}
			if (ImGui::MenuItem("Load")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit")) {
			if (ImGui::MenuItem("Undo")) {}
			if (ImGui::MenuItem("Redo")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Create")) {
			if (ImGui::MenuItem("Empty GameObject")) {}
			if (ImGui::BeginMenu("Primitives")) {
				if (ImGui::MenuItem("Plane")) {}
				if (ImGui::MenuItem("Sphere")) {}
				if (ImGui::MenuItem("Cube")) {}
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window")) {
			if (ImGui::BeginMenu("Core Editor")) {
				if (ImGui::MenuItem("Console", NULL, &window_active[(int)WINDOW_TYPES::CONSOLE])) {}
				if (ImGui::MenuItem("Game View", NULL, &window_active[(int)WINDOW_TYPES::GAME_VIEW])) {}
				if (ImGui::MenuItem("Hierarchy", NULL, &window_active[(int)WINDOW_TYPES::HIERARCHY])) {}
				if (ImGui::MenuItem("Inspector", NULL, &window_active[(int)WINDOW_TYPES::INSPECTOR])) {}
				if (ImGui::MenuItem("Engine Config", NULL, &window_active[(int)WINDOW_TYPES::ENGINE_CONFIG])) {}
				if (ImGui::MenuItem("Explorer", NULL, &window_active[(int)WINDOW_TYPES::EXPLORER])) {}
				if (ImGui::MenuItem("Resources", NULL, &window_active[(int)WINDOW_TYPES::RESOURCES])) {}
				if (ImGui::MenuItem("Time Control", NULL, &window_active[(int)WINDOW_TYPES::TIME_CONTROL])) {}
				ImGui::EndMenu();
			}
			if (ImGui::MenuItem("ImGUI Demo", NULL, &window_active[(int)WINDOW_TYPES::IMGUI_DEMO])) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")){
			// TODO: Add documentation windows when we can.
			if (ImGui::MenuItem("Documentation")) {}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Development")) {
			if (ImGui::MenuItem("About us"))
				ShellExecute(0, 0, "https://github.com/Izenz/Hana-Engine", 0, 0, SW_SHOW);
			if (ImGui::MenuItem("Engine Info", NULL, &window_active[(int)WINDOW_TYPES::ENGINE_INFO])) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void ModuleEditor::CreateDockingSpace() const {
	// Create the docking environment
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_NoBackground;

	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin("InvisibleWindow", nullptr, windowFlags);
	ImGui::PopStyleVar(3);

	ImGuiID dockSpaceId = ImGui::GetID("InvisibleWindowDockSpace");

	ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);
	ImGui::End();
}

void ModuleEditor::DrawEngineInfoWindow(bool* is_open) const {
	
	if (!ImGui::Begin("Hana Engine: Info", is_open)) {
		ImGui::End();
		return;
	}

	ImGui::Text("Engine: Hana Engine.");
	ImGui::Text("Author: Marius Dambean & Joel Herraiz.");
	ImGui::Text("Engine used for Game Development during UPC's AAA Video game Development Master.");
	ImGui::Text("Built using SDL 2.0 and OpenGL 2.1, Assimp, MathGeoLib, ImGui & DevIL.");

	ImGui::End();
}

void ModuleEditor::DrawGameSceneWindow(bool* is_open) const {
	unsigned tex = App->scene->GetSceneFramebuffer();

	ImGui::Begin("GameWindow", is_open);
	{
		ImGui::BeginChild("GameRender");
		const ImVec2 wsize = ImGui::GetContentRegionAvail();
		

		ImGui::Image(reinterpret_cast<void*>(tex), wsize, ImVec2(0, 1), ImVec2(1, 0));
		App->scene->UpdateRenderValues(wsize.x, wsize.y);
		ImGui::EndChild();
	}
	ImGui::End();
}

// Called before quitting
bool ModuleEditor::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
	
	return true;
}

void ModuleEditor::DrawHierarchyWindow(bool* is_open) const {
	ImGui::Begin("Hierarchy", is_open);
	{
	}
	ImGui::End();
}

void ModuleEditor::DrawInspectorWindow(bool* is_open) const {
	ImGui::Begin("Inspector", is_open);
	{
	}
	ImGui::End();
}

void ModuleEditor::DrawResourcesWindow(bool* is_open) const {
	ImGui::Begin("Resources", is_open);
	{
	}
	ImGui::End();
}

void ModuleEditor::DrawExplorerWindow(bool* is_open) const {
	ImGui::Begin("Explorer", is_open);
	{
	}
	ImGui::End();
}

void ModuleEditor::DrawEngineConfigWindow(bool* is_open) const {
	ImGui::Begin("Engine Config", is_open);
	{
	}
	ImGui::End();
}

void ModuleEditor::DrawTimeControlWindow(bool* is_open) const {
	const float ItemSpacing = ImGui::GetStyle().ItemSpacing.x;
	const ImVec2 ButtonSize = ImVec2(100.0f, 0.0f);
	ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar;

	ImGui::SetNextWindowSize(ImVec2(400,60));
	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 10.0f));

	ImGui::Begin("TimeControl", is_open, windowFlags);
	ImGui::SameLine((ImGui::GetWindowWidth() * 0.5) - ItemSpacing - ButtonSize.x);
	if(ImGui::Button("Play", ButtonSize)) {
		Time->StartGameClock();
	}
	ImGui::SameLine();
	if(ImGui::Button("Stop", ButtonSize)) {
		Time->StopGameClock();
	}
	ImGui::PopStyleVar(3);
	ImGui::End();
}
