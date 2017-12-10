#include "Listener.h"
#include "Camera.h"
#include "ComponentCamera.h"
#include "ModuleAudio.h"

Listener::Listener(GameObject * own) : Component(own)
{
	Setname("Audio Listener");
	SetType(LISTENER);

}

Listener::Listener()
{
}

Listener::~Listener()
{
}

void Listener::Update()
{
	//Update Listener Positioin

	ComponentCamera* comp_cam = (ComponentCamera*)this->owner->FindComponentbyType(CAMERA);
	
	if (comp_cam != nullptr) {
		Camera3D* cam = comp_cam->GetCamera();

		float3 front = cam->GetFront();
		float3 up = cam->GetUp();
		float3 pos = cam->GetPos();

		AkListenerPosition ak_pos;
		ak_pos.Set(pos.x, pos.z, pos.y, front.x, front.z, front.y, up.x, up.z, up.y);

		AK::SoundEngine::SetPosition(id,ak_pos);

		
	}
	else {

		LOG_OUT("Listener attached to an object without a camera");

	}



}
