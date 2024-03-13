#pragma once
#include "Component.h"
#include "Incl.h"

struct BoxRect {
    float Xmax;
    float Xmin;

    float Ymax;
    float Ymin;

    float Zmax;
    float Zmin;
};

class Collider
{
public:

	Collider();
	void CreateBoxCollide(Vertex vertices[], uint16_t indices[], int vertexCount);
    bool IsCollide(BoxRect* boxrect2);
    BoxRect* GetBox();

private:
    BoxRect hisBoxRect;
    
};