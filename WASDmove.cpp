#include "WASDmove.h"
#include "TimeManager.h"
#include "ModuleImGui.h"
#include "Application.h"
#include "ModuleInput.h"

Wasd::Wasd(GameObject * own) : Component(own)
{
	target = (Transform*)own->FindComponentbyType(TRANSFORM);
	SetType(WASD);
	Setname("Move");
	speed = 0.1f;
}

Wasd::Wasd()
{
	SetType(WASD);
	Setname("Movement");
	speed = 0.1f;
}

Wasd::~Wasd()
{
}

void Wasd::Update()
{
	if (owner != nullptr) {
		target = (Transform*)owner->FindComponentbyType(TRANSFORM);
	}
	if (App->tm->GetGameState() == IN_PLAY) {
		if (target != nullptr) {
			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) {
				target->SetPosition(target->GetPosition() + float3(0, 0, speed));
			}
			else if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
				target->SetPosition(target->GetPosition() + float3(0, 0, -speed));
			}
			else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) {
				target->SetPosition(target->GetPosition() + float3(-speed, 0, 0));
			}
			else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) {
				target->SetPosition(target->GetPosition() + float3(speed, 0, 0));
			}
		}
	}
}

void Wasd::UI_draw()
{
	if (ImGui::CollapsingHeader("Movement")) {
		ImGui::SliderFloat("Speed", &speed, 0.f, 1.f);
	}
}

void Wasd::Serialize(JSON_File * doc)
{

	if (doc == nullptr)
		return;

	doc->SetNumber("type", type);
	doc->SetNumber("ownerUID", (owner != nullptr) ? owner->GetUID() : -1);
	doc->SetString("name", name);
}
