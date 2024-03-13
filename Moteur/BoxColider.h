#pragma once
#include "Component.h"

struct BoxGeo
{
	float fLeftSide = 0;
	float fRightSide = 0;
	float fTopSide = 0;
	float fBotSide = 0;
	float fFrontSide = 0;
	float fBackSide = 0;
};

class BoxColider : public Component
{
public:
	static const int ID = 3;

	virtual int GetID() {
		return ID;
	}

	void Init(Mesh* pMesh);
	bool IsColidWith(BoxGeo* pBoxGeo, Entity* pEntity);
	BoxGeo* GetBoxGeo();

private:
	BoxGeo _pBoxGeo;
};

