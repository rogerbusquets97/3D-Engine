#include "Move.h"
#include "ModuleInput.h"
#include "Application.h"
#include "TimeManager.h"
#include "ModuleImGui.h"

Move::Move(GameObject * own) : Component(own)
{
	target = (Transform*)own->FindComponentbyType(TRANSFORM);
	SetType(MOVE);
	Setname("Movement");
	speed = 0.1f;
}

Move::Move()
{
	SetType(MOVE);
	Setname("Movement");
	speed = 0.1f;
}

Move::~Move()
{
}

void Move::Update()
{
	if (owner != nullptr) {
		target = (Transform*)owner->FindComponentbyType(TRANSFORM);
	}
	if (App->tm->GetGameState() == IN_PLAY) {
		if (target != nullptr) {
			if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT) {
				target->SetPosition(target->GetPosition() + float3(0, 0, speed));
			}
			else if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT) {
				target->SetPosition(target->GetPosition() + float3(0, 0, -speed));
			}
			else if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) {
				target->SetPosition(target->GetPosition() + float3(-speed, 0, 0));
			}
			else if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) {
				target->SetPosition(target->GetPosition() + float3(speed, 0, 0));
			}
		}
	}

}

void Move::UI_draw()
{
	if (ImGui::CollapsingHeader("Movement")) {
		ImGui::SliderFloat("Speed", &speed, 0.f, 1.f);
	}
}

void Move::Serialize(JSON_File * doc)
{
	if (doc == nullptr)
		return;

	doc->SetNumber("type", type);
	doc->SetNumber("ownerUID", (owner != nullptr) ? owner->GetUID() : -1);
	doc->SetString("name", name);
}
