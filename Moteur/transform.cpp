#pragma once
#include <windows.h> // for XMVerifyCPUSupport
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>

using namespace DirectX;

struct transform
{
	//vecteur scale et matrice associé
	XMFLOAT3 sca;
	XMFLOAT3X3 mSca;

	//vecteurs pour stocker les directions
	XMFLOAT3 vDir;
	XMFLOAT3 vRight;
	XMFLOAT3 vUp;
	XMFLOAT4 qRot;
	XMFLOAT4X4 mRot;

	//vecteur position et matrice associé
	XMFLOAT3 vPos;
	XMFLOAT3X3 mPos;

	XMFLOAT4X4 matrix; //matrice world

	void identity() //pour reset les matrice et vecteurs
	{

	}

	void rotate(float yaw, float pitch, float roll) //fonction pour tourner la matrice sur elle meme     yaw = x, pitch = y , roll = z
	{

	}
};