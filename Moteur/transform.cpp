#include "transform.h"

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

	void identity() //pour reset les matrice et vecteurs
	{
		vSca = { 1,1,1 };
		mSca = XMLoadFloat3(&vSca);

		vDir = { 1,1,1 };
		vRight = { 1,1,1 };
		vUp = { 1,1,1 };
		qRot = { 0,0,0,1 };
		mRot = XMLoadFloat4(&qRot);

		vPos = { 0,0,0 };
		mSca = XMLoadFloat3(&vPos);

	}

	void rotate(float yaw, float pitch, float roll) //fonction pour tourner la matrice sur elle meme     yaw = x, pitch = y , roll = z
	{

	}
};