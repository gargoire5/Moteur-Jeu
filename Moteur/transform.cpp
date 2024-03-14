#pragma once
#include "transform.h"

using namespace DirectX;

	Transform::Transform()
	{
		identity();
	}
	void Transform::identity() //pour reset les matrice et vecteurs
	{
		fSca = { 1.f,1.f,1.f };
		XMStoreFloat4x4(&mSca,XMMatrixIdentity());

		fDir = { 0.0f,0.0f,1.0f };
		fRight = { 1.0f,0.0f,0.0f };
		fUp = { 0.0f,1.0f,0.0f };
		qRot = { 0.0f,0.0f,0.0f,1.0f };
		mRot = mSca;

		fPos = { 0.0f,0.0f,0.0f };
		mPos = mSca;

		matrix = mSca;
	}

	void Transform::identityRot() //pour reset les matrice et vecteurs
	{
		fDir = { 0.0f,0.0f,1.0f };
		fRight = { 1.0f,0.0f,0.0f };
		fUp = { 0.0f,1.0f,0.0f };
		qRot = { 0.0f,0.0f,0.0f,1.0f };
		XMStoreFloat4x4(&mRot, XMMatrixIdentity());
	}

	void Transform::rotate(float yaw, float pitch, float roll) //fonction pour tourner la matrice sur elle meme     pitch = x, yaw = y , roll = z
	{
		//conversion des angles en radians
		yaw = XMConvertToRadians(yaw);
		pitch = XMConvertToRadians(pitch);
		roll = XMConvertToRadians(roll);

		//XMFLOAT4 quat1;
		XMVECTOR quatCurrentRot;
		quatCurrentRot = XMLoadFloat4(&qRot);

		XMVECTOR quat;
		XMVECTOR quatRot;

		quat = XMQuaternionRotationAxis(XMLoadFloat3(&fDir), roll);
		quatRot = quat;

		quat = XMQuaternionRotationAxis(XMLoadFloat3(&fRight), pitch);
		quatRot = XMQuaternionMultiply(quatRot, quat);

		quat = XMQuaternionRotationAxis(XMLoadFloat3(&fUp), yaw);
		quatRot = XMQuaternionMultiply(quatRot, quat);

		quatCurrentRot = XMQuaternionMultiply(quatCurrentRot, quatRot);

		XMStoreFloat4(&qRot, quatCurrentRot);

		// Convertir le quaternion en une matrice de rotation (magique)
		XMMATRIX matRot;
		matRot = XMMatrixRotationQuaternion(quatRot);
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
		XMMATRIX MatrixPos = XMMatrixTranslation(fPos.x, fPos.y, fPos.z);
		XMStoreFloat4x4(&mPos, MatrixPos);
	}
	void Transform::Update_mSca()
	{
		XMMATRIX MatrixSca = XMMatrixScaling(fSca.x, fSca.y, fSca.z);
		XMStoreFloat4x4(&mSca, MatrixSca);
	}

	void Transform::Update_WorldMatrix()
	{
		XMMATRIX sca = XMLoadFloat4x4(&mSca);
		XMMATRIX rot = XMLoadFloat4x4(&mRot);
		XMMATRIX pos = XMLoadFloat4x4(&mPos);
		
		XMStoreFloat4x4(&matrix, (sca * rot * pos));
	}
