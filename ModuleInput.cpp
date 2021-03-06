#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleLoader.h"
#include "ModuleRenderer3D.h"
#include "ModuleImGui.h"
#include "imgui.h"
#include "ModuleFileSystem.h"

#define MAX_KEYS 300

ModuleInput::ModuleInput(bool start_enabled) : Module(start_enabled)
{
	keyboard = new KEY_STATE[MAX_KEYS];
	memset(keyboard, KEY_IDLE, sizeof(KEY_STATE) * MAX_KEYS);
	memset(mouse_buttons, KEY_IDLE, sizeof(KEY_STATE) * MAX_MOUSE_BUTTONS);
	SetName("Input");
}

// Destructor
ModuleInput::~ModuleInput()
{
	delete[] keyboard;
}

// Called before render is available
bool ModuleInput::Init(JSON_File* conf)
{
	LOG_OUT("Init SDL input event system");
	bool ret = true;
	SDL_Init(0);

	if(SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
	{
		LOG_OUT("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
		ret = false;
	}

	return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate(float dt)
{
	SDL_PumpEvents();

	const Uint8* keys = SDL_GetKeyboardState(NULL);
	
	for(int i = 0; i < MAX_KEYS; ++i)
	{
		if(keys[i] == 1)
		{
			if(keyboard[i] == KEY_IDLE)
				keyboard[i] = KEY_DOWN;
			else
				keyboard[i] = KEY_REPEAT;
		}
		else
		{
			if(keyboard[i] == KEY_REPEAT || keyboard[i] == KEY_DOWN)
				keyboard[i] = KEY_UP;
			else
				keyboard[i] = KEY_IDLE;
		}
	}

	Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);

	mouse_x /= SCREEN_SIZE;
	mouse_y /= SCREEN_SIZE;
	mouse_z = 0;

	for(int i = 0; i < 5; ++i)
	{
		if(buttons & SDL_BUTTON(i))
		{
			if(mouse_buttons[i] == KEY_IDLE)
				mouse_buttons[i] = KEY_DOWN;
			else
				mouse_buttons[i] = KEY_REPEAT;
		}
		else
		{
			if(mouse_buttons[i] == KEY_REPEAT || mouse_buttons[i] == KEY_DOWN)
				mouse_buttons[i] = KEY_UP;
			else
				mouse_buttons[i] = KEY_IDLE;
		}
	}

	mouse_x_motion = mouse_y_motion = 0;

	bool quit = false;
	SDL_Event e;
	while(SDL_PollEvent(&e))
	{
		App->imgui->ImGuiInput(&e);
		switch(e.type)
		{
			case SDL_MOUSEWHEEL:
			mouse_z = e.wheel.y;
			break;

			case SDL_MOUSEMOTION:
			mouse_x = e.motion.x / SCREEN_SIZE;
			mouse_y = e.motion.y / SCREEN_SIZE;

			mouse_x_motion = e.motion.xrel / SCREEN_SIZE;
			mouse_y_motion = e.motion.yrel / SCREEN_SIZE;
			break;

			case SDL_QUIT:
			quit = true;
			break;

			case SDL_WINDOWEVENT:
			if(e.window.event == SDL_WINDOWEVENT_RESIZED)
				App->renderer3D->OnResize(e.window.data1, e.window.data2);
			break;
			

			case SDL_DROPFILE:
			char* drop_filedir = e.drop.file;
			std::string filetext = GetExtension(drop_filedir);
			int filetype = App->fs->GetTypeFromExtension(filetext.c_str());
			if (filetype == ExtensionType::et_geometry) {

				App->loader->LoadFBX(drop_filedir);
			}
			SDL_free(drop_filedir);
			drop_filedir = nullptr;
			break;
			
		}
	}

	if(quit == true || keyboard[SDL_SCANCODE_ESCAPE] == KEY_UP)
		return UPDATE_STOP;

	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
	LOG_OUT("Quitting SDL input event subsystem");
	SDL_QuitSubSystem(SDL_INIT_EVENTS);
	return true;
}

const float ModuleInput::GetNormalizedX() const
{
	int w;
	w = App->window->GetWidth();


	float normalized_x = (float)(mouse_x / (float)w);
	return normalized_x;
}

const float ModuleInput::GetNormalizedY() const
{
	int h;

	h = App->window->GetHeight();


	float normalized_y = (float)(mouse_y / (float)h);

	return normalized_y;
}

void ModuleInput::ImGuiDraw()
{
	if (ImGui::CollapsingHeader(this->GetName())) {

		ImGui::Text("Mouse Position");
		ImGui::Text("X: %d", mouse_x);
		ImGui::Text("Y: %d", mouse_y);
		ImGui::Separator();
		ImGui::Text("Wheel: %d", mouse_z);
		ImGui::Separator();
		ImGui::Text("X motion: %d", mouse_x_motion);
		ImGui::Text("Y motion: %d", mouse_y_motion);
		

	}
}
int ModuleInput::GetMouseWheel() const
{
	return mouse_z;
}
