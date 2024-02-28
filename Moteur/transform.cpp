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

		const XMFLOAT3 dir = fDir;
		const XMFLOAT3 right = fRight;
		const XMFLOAT3 up = fUp;


		//XMFLOAT4 quat1;
		XMVECTOR quat;
		XMVECTOR quatRot;

		quat = XMQuaternionRotationAxis(XMLoadFloat3(&dir), roll);
		quatRot = quat;
		quat = XMQuaternionRotationAxis(XMLoadFloat3(&right), pitch);
		quatRot *= quat;
		quat = XMQuaternionRotationAxis(XMLoadFloat3(&up), yaw);
		quatRot *= quat;

		// Ajouter la rotation delta à la rotation actuelle de l’objet
		mRot *= quatRot;

		// Convertir le quaternion en une matrice de rotation (magique)
		XMMATRIX matRot;
		matRot = XMMatrixRotationQuaternion(quatRot);

		// Mettre à jour les axes de notre objet (3 vecteurs)
		fRight.x = matRot.r[0].m128_f32[0];
		fRight.y = matRot.r[0].m128_f32[1];
		fRight.z = matRot.r[0].m128_f32[2];
		fUp.x = matRot.r[1].m128_f32[0];
		fUp.y = matRot.r[1].m128_f32[1];
		fUp.z = matRot.r[1].m128_f32[2];
		fDir.x = matRot.r[2].m128_f32[0];
		fDir.y = matRot.r[2].m128_f32[1];
		fDir.z = matRot.r[2].m128_f32[2];

	}