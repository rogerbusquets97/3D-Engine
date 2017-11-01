#include "Transform.h"
#include "ModuleImGui.h"

Transform::Transform(float3 s, Quat rot, float3 pos , GameObject* own) : Component(own)
{
	local_transform.SetIdentity();
	scale = s;
	rotation = rot;
	position = pos;
	Euler_rotation = rot.ToEulerXYZ();
	global_transform.SetIdentity();

	this->SetType(TRANSFORM);
	
}

Transform::Transform(float4x4 trans, GameObject * own) : Component(own)
{
	float3x3 rot;
	local_transform.Set(trans);
	local_transform.Decompose(position, rot, scale);
	Euler_rotation = rot.ToEulerXYZ();
	rotation.FromEulerXYZ(Euler_rotation.x, Euler_rotation.y, Euler_rotation.z);
}

Transform::~Transform()
{
}

void Transform::SetPosition(float3 p)
{
	position = p;

	RecalculateLocalTransform();
}

void Transform::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;

	RecalculateLocalTransform();
}

void Transform::SetScale(float3 s)
{
	scale = s;
	RecalculateLocalTransform();
}

void Transform::SetScale(float x, float y, float z)
{
	scale.x = x;
	scale.y = y;
	scale.z = z;
	RecalculateLocalTransform();
}

void Transform::SetRotation(Quat rot)
{
	rotation = rot;
	RecalculateLocalTransform();
}

void Transform::UI_draw()
{
	if (ImGui::CollapsingHeader("Transform")) {
		ImGui::Text("Position");
		ImGui::InputFloat("x", &position.x);
		ImGui::InputFloat("y", &position.y);
		ImGui::InputFloat("z", &position.z);
		ImGui::Separator();
		ImGui::Text("Rotation:");
		ImGui::InputFloat("x", &Euler_rotation.x);
		ImGui::InputFloat("y", &Euler_rotation.y);
		ImGui::InputFloat("z", &Euler_rotation.z);
		ImGui::Separator();
		ImGui::Text("Scale");
		ImGui::InputFloat("x", &scale.x);
		ImGui::InputFloat("y", &scale.y);
		ImGui::InputFloat("z", &scale.z);
	}
	
}

const float4x4 Transform::GetLocalTransform() const
{
	return float4x4::FromTRS(position, rotation, scale);
}
void Transform::SetLocalTransform(const float4x4 & transform)
{
	local_transform = transform;
}

const float4x4 Transform::GetGlobalTransform() const
{
	return global_transform;
}

void Transform::RecalculateLocalTransform()
{
	local_transform = float4x4::FromTRS(position, rotation, scale);
}
