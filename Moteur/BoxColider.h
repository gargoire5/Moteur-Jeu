#pragma once
#include "Component.h"

class BoxColider;
struct BoxGeo
{
	float fLeftSide = FLT_MAX;
	float fRightSide = -FLT_MAX;
	float fTopSide = -FLT_MAX;
	float fBotSide = FLT_MAX;
	float fFrontSide = FLT_MAX;
	float fBackSide = -FLT_MAX;
};

class BoxColider : public Component
{
public:
	static const int ID = 3;

	virtual int GetID() {
		return ID;
	}

	void Init(Mesh* pMesh);
	void BoxColider::Init(float fHight, float fDepth, float fWidth);

	bool IsColidWith(BoxGeo* pBoxGeo, Entity* pEntity);
	BoxGeo* GetBoxGeo();

private:
	BoxGeo _pBoxGeo;
};

