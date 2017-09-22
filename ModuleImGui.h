#pragma once

//#include "Module.h"
#include "Application.h"
#include "ImGui\imconfig.h"
//#include "ImGui\imgui_internal.h"
#include "Panel.h"
#include "Console.h"
#include "ConfigPanel.h"
#include "imgui_impl_sdl.h"
#include "SDL/include/SDL_opengl.h"
#include "Geomath.h"

class Module;
class Application;

class ModuleImGui : public Module {
public:
	ModuleImGui(Application* app, bool start_enabled = true);
	~ModuleImGui();

	bool Init();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();
	void LoadStyle(char* name);
	void ImGuiInput(SDL_Event* ev);
	void Draw();
	float GetRandomValue(float range_1, float range_2);
	void LogFps(float fps, float ms);
	

private:

	std::list<Panel*> panels;
	bool show_test_window = false;
	Console* console = nullptr;
	ConfigPanel* configuration = nullptr;

	
	///just for testing mathgeolib///
};
	