#pragma once
#include "transform.h"

using namespace DirectX;

	void Transform::identity() //pour reset les matrice et vecteurs
	{
		fSca = { 1.f,1.f,1.f };
		mSca = XMLoadFloat3(&fSca);

		fDir = { 1.0f,1.0f,1.0f };
		fRight = { 1.0f,1.0f,1.0f };
		fUp = { 1.0f,1.0f,1.0f };
		qRot = { 0.0f,0.0f,0.0f,1.0f };
		mRot = XMLoadFloat4(&qRot);

		fPos = { 0.0f,0.0f,0.0f };
		mPos = XMLoadFloat3(&fPos);

	}

	void Transform::rotate(float yaw, float pitch, float roll) //fonction pour tourner la matrice sur elle meme     pitch = x, yaw = y , roll = z
	{
		//conversion des angles en radians
		yaw = XMConvertToRadians(yaw);
		pitch = XMConvertToRadians(pitch);
		roll = XMConvertToRadians(roll);


		// Créer un quaternion pour chaque rotation (delta)
		const XMFLOAT3 _dir = fDir;
		const XMFLOAT3 _right = fRight;
		const XMFLOAT3 _up = fUp;


		//XMFLOAT4 quat1;
		XMVECTOR quat;
		XMVECTOR quatRot;
		XMVECTOR quatCurrentRot = XMLoadFloat4(&qRot);

		quat = XMQuaternionRotationAxis(XMLoadFloat3(&_dir), roll);
		quatRot = quat;
		quat = XMQuaternionRotationAxis(XMLoadFloat3(&_right), pitch);
		quatRot *= quat;
		quat = XMQuaternionRotationAxis(XMLoadFloat3(&_up), yaw);
		quatRot *= quat;

		// Ajouter la rotation delta à la rotation actuelle de l’objet
		quatCurrentRot *= quatRot;

		XMStoreFloat4(&qRot, quatCurrentRot);

		// Convertir le quaternion en une matrice de rotation (magique)
		XMMATRIX matRot;
		matRot = XMMatrixRotationQuaternion(quatRot);
		XMFLOAT4X4 mRot;
		XMStoreFloat4x4(&mRot, matRot);


		// Mettre à jour les axes de notre objet (3 vecteurs)
		fRight.x = mRot._11;
		fRight.y = mRot._12;
		fRight.z = mRot._13;
		fUp.x = mRot._21;
		fUp.y = mRot._22;
		fUp.z = mRot._23;
		fDir.x = mRot._31;
		fDir.y = mRot._32;
		fDir.z = mRot._33;

	}

	void Transform::Update_mPos()
	{
		mPos = XMVectorSet(fPos.x, fPos.y, fPos.z, 1.0f);
	}

	void Transform::Update_WorldMatrix()
	{
		XMVECTOR pos = XMLoadFloat3(&fPos);
		XMVECTOR right = XMLoadFloat3(&fRight);
		XMVECTOR up = XMLoadFloat3(&fUp);
		XMMATRIX mMatrix = XMMatrixLookAtLH(pos, right, up);

		XMStoreFloat4x4(&matrix, mMatrix);
	}
