#include "ComponentCamera.h"
#include "Transform.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleImGui.h"


ComponentCamera::ComponentCamera(GameObject * own) : Component(own)
{

	Setname("Camera");
	camera = new Camera3D();
	SetType(CAMERA);

	
	

	
}

ComponentCamera::ComponentCamera()
{
	Setname("Camera");
	camera = new Camera3D();
	SetType(CAMERA);
}

ComponentCamera::~ComponentCamera()
{
}

void ComponentCamera::Start()
{
}

void ComponentCamera::Update()
{
	
	Transform* trans = (Transform*)GetOwner()->FindComponentbyType(TRANSFORM);

	camera->SetPosition(trans->GetPosition());
	camera->SetZDir(trans->GetGlobalTransform().WorldZ());
	camera->SetYDir(trans->GetGlobalTransform().WorldY());



}

void ComponentCamera::CleanUp()
{
	delete camera;
}

Camera3D * ComponentCamera::GetCamera() const
{
	return camera;
}

bool ComponentCamera::IsInside(AABB & bounding_box)
{
	return camera->IsInside(bounding_box);
}

void ComponentCamera::UI_draw()
{
	if (ImGui::CollapsingHeader("Camera")) {
		ImGui::Checkbox("Camera culling", &camera->culling);
	}
}

bool ComponentCamera::GetCulling() const
{
	return camera->GetCulling();
}

void ComponentCamera::Serialize(JSON_File * doc)
{
	if (doc == nullptr)
		return;

	doc->SetNumber("type", type);
	doc->SetNumber("ownerUID", (owner != nullptr) ? owner->GetUID() : -1);
	doc->SetString("name", name);
}
