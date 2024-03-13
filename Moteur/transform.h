#pragma once
#include <windows.h> // for XMVerifyCPUSupport
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>

using namespace DirectX;

struct Transform
{
public:
	Transform();
public:
	//vecteur scale et matrice associé
	XMFLOAT3 fSca;
	XMFLOAT4X4 mSca;

	//vecteurs pour stocker les directions
	XMFLOAT3 fRight;  
	XMFLOAT3 fUp;     
	XMFLOAT3 fDir;    
	XMFLOAT4 qRot;
	XMFLOAT4X4 mRot;

	//vecteur position et matrice associé
	XMFLOAT3 fPos;
	XMFLOAT4X4 mPos;

	XMFLOAT4X4 matrix; //matrice world

	void identity(); //pour reset les matrice et vecteurs
	void identityRot();

	void rotate(float yaw, float pitch, float roll); //fonction pour tourner la matrice sur elle meme     yaw = x, pitch = y , roll = z

	void Update_mPos();
	void Update_mSca();
	void Update_WorldMatrix();
};