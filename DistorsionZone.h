#pragma once
#ifndef _DISTORSIONZONE_H_
#define _DISTORSIONZONE_H_

#define DEFAULT_RADIUS 10

#include "Component.h"
#include "Geomath.h"

class DistorsionZone : public Component {

public:

	DistorsionZone(GameObject* own);
	DistorsionZone();
	void Update();
	void DebugDraw();
	bool CheckCollision(float3 target);
	void UI_draw();

public:

	std::string bus = "";
	float distorsion_value = 0.f;
	math::OBB zone;
	float radius;
	float size = 1;
};





#endif
