#pragma once
#ifndef _MOVE_H_
#define _MOVE_H_

#include "Transform.h"

// this is a simple component that allows an object to be moved with the arrows at a giveb speed
//It is just for testing purposes in order to be able to serialize the scene without losing the moving behavoiur (of the moving object that emmits sounds)

class Move : public Component {

public:

	Move(GameObject* own);
	Move();
	~Move();

	void Update();
	void UI_draw();
	void Serialize(JSON_File* doc);

private:

	Transform* target;
	float speed = 0.1f;
};



#endif
