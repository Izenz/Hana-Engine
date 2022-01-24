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

	// --- Added data about performance ---
	about.system = (unsigned char*)SDL_GetPlatform();
	about.cpu = SDL_GetCPUCount();
	about.ram = SDL_GetSystemRAM() / 1024.0f;
	about.gpu = (unsigned char*)glGetString(GL_RENDERER);
	about.gpu_vendor = (unsigned char*)glGetString(GL_VENDOR);
	glGetIntegerv(GL_GPU_MEMORY_INFO_TOTAL_AVAILABLE_MEMORY_NVX, &about.vram_capacity);
	glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &about.vram_free);
	SDL_GetVersion(&about.sdl_version);
	// ----

	ImGui::StyleColorsDark();
	
	cam->Init();

	return true;
}

update_status ModuleEditor::PreUpdate()
{
	
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();

	// Enable docking system
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
	ImGuiStyle* style = &ImGui::GetStyle();
	style->WindowMenuButtonPosition = ImGuiDir_None;


	ImGui::NewFrame();
	
	cam->PreUpdate();

	return update_status::UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleEditor::Update()
{
	DrawEditorMainMenu();
	DrawEditorEnvironment();
	
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

void ModuleEditor::DrawEditorEnvironment() {
	
	CreateDockingSpace();
	LoadSceneInEditor();

	if (window_active[(int)WINDOW_TYPES::GAME_VIEW])			DrawGameSceneWindow(&window_active[(int)WINDOW_TYPES::GAME_VIEW]);
	if (window_active[(int)WINDOW_TYPES::HIERARCHY])			DrawHierarchyWindow(&window_active[(int)WINDOW_TYPES::HIERARCHY]);
	if (window_active[(int)WINDOW_TYPES::INSPECTOR])			DrawInspectorWindow(&window_active[(int)WINDOW_TYPES::INSPECTOR]);
	if (window_active[(int)WINDOW_TYPES::RESOURCES])			DrawResourcesWindow(&window_active[(int)WINDOW_TYPES::RESOURCES]);
	if (window_active[(int)WINDOW_TYPES::EXPLORER])				DrawExplorerWindow(&window_active[(int)WINDOW_TYPES::EXPLORER]);
	if (window_active[(int)WINDOW_TYPES::EXPLORER])				DrawPerformanceWindow(&window_active[(int)WINDOW_TYPES::PERFORMANCE]);
	if (window_active[(int)WINDOW_TYPES::ENGINE_INFO])			DrawEngineInfoWindow(&window_active[(int)WINDOW_TYPES::ENGINE_INFO]);
	if (window_active[(int)WINDOW_TYPES::IMGUI_DEMO])			ImGui::ShowDemoWindow();
	if (window_active[(int)WINDOW_TYPES::CONSOLE])				Output->DrawConsole(&window_active[(int)WINDOW_TYPES::CONSOLE]);
	if (window_active[(int)WINDOW_TYPES::TIME_CONTROL])				DrawTimeControlWindow(&window_active[(int)WINDOW_TYPES::TIME_CONTROL]);
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
			// TODO: Add option to select files so the user can add search and select textures/models.
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit")) {
			// TODO: Add option to select files so the user can add search and select textures/models.
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Create")) {
			// TODO: Add option to select files so the user can add search and select textures/models.
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window")) {
			if (ImGui::MenuItem("Console", NULL, false, &window_active[(int)WINDOW_TYPES::CONSOLE]))
				window_active[(int)WINDOW_TYPES::CONSOLE] = !window_active[(int)WINDOW_TYPES::CONSOLE];
			if (ImGui::MenuItem("ImGUI Demo", NULL, false, &window_active[(int)WINDOW_TYPES::IMGUI_DEMO]))
				window_active[(int)WINDOW_TYPES::IMGUI_DEMO] = !window_active[(int)WINDOW_TYPES::IMGUI_DEMO];
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help")) {
			if (ImGui::MenuItem("About us"))
				ShellExecute(0, 0, "https://github.com/Izenz/Hana-Engine", 0, 0, SW_SHOW);
			if (ImGui::MenuItem("Engine Info", NULL, false, &window_active[(int)WINDOW_TYPES::ENGINE_INFO]))
				window_active[(int)WINDOW_TYPES::ENGINE_INFO] = !window_active[(int)WINDOW_TYPES::ENGINE_INFO];
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Development")) {
			// TODO: Add option to select files so the user can add search and select textures/models.
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
}

void ModuleEditor::CreateDockingSpace() {
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

void ModuleEditor::DrawEngineInfoWindow(bool* p_open) const {
	
	if (!ImGui::Begin("Hana Engine: Info", p_open)) {
		ImGui::End();
		return;
	}

	ImGui::Text("Engine: Hana Engine.");
	ImGui::Text("Author: Joel Herraiz Marti.");
	ImGui::Text("Engine used for Game Development during UPC's AAA Video game Development Master.");
	ImGui::Text("Built using SDL 2.0 and OpenGL 2.1, Assimp, MathGeoLib, ImGui & DevIL.");

	ImGui::End();
}

void ModuleEditor::DrawGameSceneWindow(bool* p_open) const {
	unsigned tex = App->exercise->GetSceneTexture();

	ImGui::Begin("GameWindow");
	{
		// Using a Child allow to fill all the space of the window.
		ImGui::BeginChild("GameRender");
		ImVec2 wsize = ImGui::GetWindowSize();
		// Because I use the texture from OpenGL, I need to invert the V from the UV.
		ImGui::Image((ImTextureID)tex, wsize, ImVec2(0, 1), ImVec2(1, 0));
		ImGui::EndChild();

		//ImGui::GetWindowDrawList()->AddText(ImVec2(150.0f, 150.f), IM_COL32(255, 0, 0, 255), "FPS: ");
		//ImGui::SetCursorPos(ImVec2(wsize.x * 0.5f, wsize.y * 0.5f));
		//ImGui::Text("FPS: %i", fpsCount);
	}
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

void ModuleEditor::DrawHierarchyWindow(bool* p_open) const {
	ImGui::Begin("Hierarchy");
	{
	}
	ImGui::End();
}

void ModuleEditor::DrawInspectorWindow(bool* p_open) const {
	ImGui::Begin("Inspector");
	{
	}
	ImGui::End();
}

void ModuleEditor::DrawResourcesWindow(bool* p_open) const {
	ImGui::Begin("Resources");
	{
	}
	ImGui::End();
}

void ModuleEditor::DrawExplorerWindow(bool* p_open) const {
	ImGui::Begin("Engine Config");
	{
		App->window->WindowMenu();
	}
	ImGui::End();
}

void ModuleEditor::DrawPerformanceWindow(bool* p_open) {
	ImGui::Begin("Performance");
	{
		static SDL_version version;
		static const float vram_total = about.vram_capacity / 1024.0f;
		float vram_free = about.vram_free / 1024.0f;
		float vram_usage = vram_total - vram_free;
		float frame_rate = 0.0f;

		ImGui::Separator();
		ImGui::Text("System: %s", about.system);
		ImGui::Text("SDL Version: %d.%d.%d", about.sdl_version.major,
			about.sdl_version.minor, about.sdl_version.patch);
		ImGui::Separator();
		ImGui::Text("CPUs: %d", about.cpu);
		ImGui::Text("System RAM: %.1f Gb", about.ram);
		ImGui::Separator();
		ImGui::Text("GPU: %s", about.gpu);
		ImGui::Text("Vendor: %s", about.gpu_vendor);
		ImGui::Text("VRAM: %.1f Mb", vram_total);
		ImGui::Text("Vram Usage:  %.1f Mb", vram_usage);
		ImGui::Text("Vram Available:  %.1f Mb", vram_free);
		ImGui::Separator();
		frame_rate = DrawFPS();
		ImGui::Text("FPS: %i", int(frame_rate));
		char title[25];
		sprintf_s(title, 25, "Framerate %.1f", frame_rate);
		ImGui::PlotHistogram("##framerate", &fps_buffer[0], (int)fps_buffer.size(), 0, title, 0.0f, 1000.f, ImVec2(310, 100));
		sprintf_s(title, 25, "Milliseconds %.1f", ms_buffer.back());
		ImGui::PlotHistogram("##milliseconds", &ms_buffer.front(), ms_buffer.size(), 0, title, 0.0f, 40.0f, ImVec2(310, 100));
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

float ModuleEditor::DrawFPS()
{
	if (draw_fps)
	{
		float fps = Time->GetFPScount();
		if (fps_buffer.size() == GRAPH_BUFFER_LENGTH)
		{
			fps_buffer.erase(fps_buffer.begin());
		}
		fps_buffer.push_back(fps);

		if (ms_buffer.size() == GRAPH_BUFFER_LENGTH)
		{
			ms_buffer.erase(ms_buffer.begin());
		}
		ms_buffer.push_back(Time->GetGameDeltaTime());
		
		return fps;
	}
	else
	{
		return 0.0f;
	}
}

