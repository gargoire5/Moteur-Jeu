#pragma once
#include <windows.h>
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>

using namespace DirectX;

struct Transform
{
public:
	Transform();
public:
	XMFLOAT3 fSca;
	XMFLOAT4X4 mSca;


	XMFLOAT3 fRight;  
	XMFLOAT3 fUp;     
	XMFLOAT3 fDir;    
	XMFLOAT4 qRot;
	XMFLOAT4X4 mRot;

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