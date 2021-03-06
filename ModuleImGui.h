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
#include "GameObject.h"
#include "ImGui\ImGuizmo\ImGuizmo.h"

class Module;
class Application;
class ConfigPanel;
class PlayPause;

class ModuleImGui : public Module {
public:
	ModuleImGui(bool start_enabled = true);
	~ModuleImGui();

	bool Init(JSON_File* conf);
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();
	void LoadStyle(char* name);
	void ImGuiInput(SDL_Event* ev);
	void Draw();
	float GetRandomValue(float range_1, float range_2);
	void LogFps(float fps, float ms);
	void AddPanel(Panel* panel);
	void Setproperties(bool set);
	GameObject* curr_obj;
	bool HoveringWindow();

private:

	std::list<Panel*> panels;
	bool show_test_window = false;
	bool geometry = false;
	bool properties = false;
	bool about = false;
	bool save = false;
	bool load = false;
	//Console* console = nullptr;
	ConfigPanel* configuration = nullptr;
	PlayPause* playpause = nullptr;
	float x, y, z, r,posx,posy,posz,h,d;
	char save_scene_name[50];
	char load_scene_name[50];

	ImGuizmo::OPERATION curr_operation;
	ImGuizmo::MODE curr_mode;
	
	///just for testing mathgeolib///
};
	