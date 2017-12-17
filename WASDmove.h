#pragma once
#ifndef _WASDMOVE_H_
#define _WASDMOVE_H_


#include "Component.h"
#include "Transform.h"
// for testing purposes, applied to the camera
class Wasd : public Component {

public:


	Wasd(GameObject* own);
	Wasd();
	~Wasd();

	void Update();
	void UI_draw();
	void Serialize(JSON_File* doc);

private:

	Transform* target;
	float speed = 0.1f;

};



#endif
