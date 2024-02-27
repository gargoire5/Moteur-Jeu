#pragma once
#include <windows.h> // for XMVerifyCPUSupport
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>

using namespace DirectX;

struct transform
{
	//vecteur scale et matrice associé
	XMFLOAT3 vSca;
	XMVECTOR mSca;

	//vecteurs pour stocker les directions
	XMFLOAT3 vDir;
	XMFLOAT3 vRight;
	XMFLOAT3 vUp;
	XMFLOAT4 qRot;
	XMVECTOR mRot;

	//vecteur position et matrice associé
	XMFLOAT3 vPos;
	XMVECTOR mPos;

	XMFLOAT4X4 matrix; //matrice world

	void identity(); //pour reset les matrice et vecteurs

	void rotate(float yaw, float pitch, float roll); //fonction pour tourner la matrice sur elle meme     yaw = x, pitch = y , roll = z
};