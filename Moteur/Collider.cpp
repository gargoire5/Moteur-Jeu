#include "Collider.h"
#include "Mesh.h"


Collider::Collider()
{

}

void Collider::CreateBoxCollide(Vertex vertices[], uint16_t indices[], int vertexCount)
{
    int indiceXmax = 0;
    int indiceXmin = 0;

    int indiceYmax = 0;
    int indiceYmin = 0;

    int indiceZmax = 0;
    int indiceZmin = 0;

    for (int i = 1; i < vertexCount; i++) //parcourt la liste des points
    {
        if (vertices[i].Pos.x > vertices[indiceXmax].Pos.x) //test du x
        {
            indiceXmax = vertices[i].Pos.x; //point le plus a droite => yellow
        }
        if (vertices[i].Pos.x < vertices[indiceXmin].Pos.x) //test du x
        {
            indiceXmin = vertices[i].Pos.x; //point le plus a gauche => Red
        }

        if (vertices[i].Pos.y > vertices[indiceYmax].Pos.y) //test du y
        {
            indiceYmax = vertices[i].Pos.y; //point le plus en haut => cyan
        }
        if (vertices[i].Pos.y < vertices[indiceYmin].Pos.y) //test du y
        {
            indiceYmin = vertices[i].Pos.y; //point le plus en bas => Red
        }

        if (vertices[i].Pos.z > vertices[indiceZmax].Pos.z) //test du z
        {
            indiceZmax = vertices[i].Pos.z; //point le plus en arriere => Red
        }
        if (vertices[i].Pos.z < vertices[indiceZmin].Pos.z) //test du z
        {
            indiceZmin = vertices[i].Pos.z; //point le plus en avant => green
        }
    }
    
    hisBoxRect.Xmax = indiceXmax;
    hisBoxRect.Xmin = indiceXmin;

    hisBoxRect.Ymax = indiceYmax;
    hisBoxRect.Ymin = indiceYmin;

    hisBoxRect.Zmax = indiceZmax;
    hisBoxRect.Zmin = indiceZmin;
}

bool Collider::IsCollide(BoxRect* boxrect2)
{
    bool isCollideX = false;
    bool isCollideY = false;
    bool isCollideZ = false;

    //test X

    if ((hisBoxRect.Xmin >= boxrect2->Xmin) && (hisBoxRect.Xmin <= boxrect2->Xmax)) //si l'entité la touche par la droite
    {
        isCollideX = true;
    }
    else if ((hisBoxRect.Xmax >= boxrect2->Xmin) && (hisBoxRect.Xmax <= boxrect2->Xmin)) //si l'entité la touche par la gauche
    {
        isCollideX = true;
    }
    else
    {
        isCollideX = false;
    }

    //test Y
    if ((hisBoxRect.Ymin >= boxrect2->Ymin) && (hisBoxRect.Ymin <= boxrect2->Ymax)) //si l'entité la touche par au dessus
    {
        isCollideY = true;
    }
    else if ((hisBoxRect.Ymax >= boxrect2->Ymin) && (hisBoxRect.Ymax <= boxrect2->Ymax)) //si l'entité la touche par en dessous
    {
        isCollideY = true;
    }
    else
    {
        isCollideY = false;
    }

    //test Z
    if ((hisBoxRect.Zmin >= boxrect2->Zmin) && (hisBoxRect.Zmin <= boxrect2->Zmax)) //si l'entité la touche par l'arriere 
    {
        isCollideZ = true;
    }
    else if ((hisBoxRect.Zmax >= boxrect2->Zmin) && (hisBoxRect.Zmax <= boxrect2->Zmax)) //si l'entité la touche par l'avant
    {
        isCollideZ = true;
    }
    else
    {
        isCollideZ = false;
    }

    //test final collision
    return isCollideX && isCollideY && isCollideZ;
}

BoxRect* Collider::GetBox()
{
    return &hisBoxRect;
}