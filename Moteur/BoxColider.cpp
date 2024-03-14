#include "BoxColider.h"
#include "Entity.h"
#include "Mesh.h"

void BoxColider::Init(Mesh* pMesh)
{
	for (int i = 0; i < pMesh->_iVertexCount; i++)
	{
		if (pMesh->_pVertices[i].Pos.x < _pBoxGeo.fLeftSide)//LeftSide
		{
			_pBoxGeo.fLeftSide = pMesh->_pVertices[i].Pos.x;
		}
		if (pMesh->_pVertices[i].Pos.x > _pBoxGeo.fRightSide)//RightSide
		{
			_pBoxGeo.fRightSide = pMesh->_pVertices[i].Pos.x;
		}
		if (pMesh->_pVertices[i].Pos.y > _pBoxGeo.fTopSide)//TopSide
		{
			_pBoxGeo.fTopSide = pMesh->_pVertices[i].Pos.y;
		}
		if (pMesh->_pVertices[i].Pos.y < _pBoxGeo.fBotSide)//BotSide
		{
			_pBoxGeo.fBotSide = pMesh->_pVertices[i].Pos.y;
		}
		if (pMesh->_pVertices[i].Pos.z < _pBoxGeo.fFrontSide)//FrontSide
		{
			_pBoxGeo.fFrontSide = pMesh->_pVertices[i].Pos.z;
		}
		if (pMesh->_pVertices[i].Pos.z > _pBoxGeo.fBackSide)//BackSide
		{
			_pBoxGeo.fBackSide = pMesh->_pVertices[i].Pos.z;
		}
	}

}

void BoxColider::Init(float fHight, float fDepth, float fWidth)
{
	_pBoxGeo.fFrontSide = -(fDepth / 2);
	_pBoxGeo.fBackSide = (fDepth / 2);
	_pBoxGeo.fBotSide = -(fHight / 2);
	_pBoxGeo.fTopSide = (fHight / 2);
	_pBoxGeo.fLeftSide = -(fWidth / 2);
	_pBoxGeo.fRightSide = (fWidth / 2);
}

bool BoxColider::IsColidWith(BoxGeo* pBoxGeo, Entity* pEntity)
{
	bool bColidX = false;
	bool bColidY = false;
	bool bColidZ = false;

	BoxGeo CurrBox;
	XMFLOAT3 CurrPos = this->GetEntity()->GetTransform()->fPos;
	XMFLOAT3 CurrSca = this->GetEntity()->GetTransform()->fSca;
	CurrBox.fLeftSide = CurrPos.x + _pBoxGeo.fLeftSide * CurrSca.x;
	CurrBox.fRightSide = CurrPos.x + _pBoxGeo.fRightSide * CurrSca.x;
	CurrBox.fTopSide = CurrPos.y + _pBoxGeo.fTopSide * CurrSca.y;
	CurrBox.fBotSide = CurrPos.y + _pBoxGeo.fBotSide * CurrSca.y;
	CurrBox.fFrontSide = CurrPos.z + _pBoxGeo.fFrontSide * CurrSca.z;
	CurrBox.fBackSide = CurrPos.z + _pBoxGeo.fBackSide * CurrSca.z;

	BoxGeo CurrBoxColid;
	XMFLOAT3 CurrPosColid = pEntity->GetTransform()->fPos;
	XMFLOAT3 CurrScaColid = pEntity->GetTransform()->fSca;
	CurrBoxColid.fLeftSide = CurrPosColid.x + pBoxGeo->fLeftSide * CurrScaColid.x;
	CurrBoxColid.fRightSide = CurrPosColid.x + pBoxGeo->fRightSide * CurrScaColid.x;
	CurrBoxColid.fTopSide = CurrPosColid.y + pBoxGeo->fTopSide * CurrScaColid.y;
	CurrBoxColid.fBotSide = CurrPosColid.y + pBoxGeo->fBotSide * CurrScaColid.y;
	CurrBoxColid.fFrontSide = CurrPosColid.z + pBoxGeo->fFrontSide * CurrScaColid.z;
	CurrBoxColid.fBackSide = CurrPosColid.z + pBoxGeo->fBackSide * CurrScaColid.z;

	if ((CurrBox.fLeftSide > CurrBoxColid.fLeftSide)&&(CurrBox.fLeftSide < CurrBoxColid.fRightSide))
	{
		bColidX = true;
	}
	else if ((CurrBox.fRightSide > CurrBoxColid.fLeftSide) && (CurrBox.fRightSide < CurrBoxColid.fRightSide))
	{
		bColidX = true;
	}

	if ((CurrBox.fTopSide > CurrBoxColid.fBotSide) && (CurrBox.fTopSide < CurrBoxColid.fTopSide))
	{
		bColidY = true;
	}
	else if ((CurrBox.fBotSide > CurrBoxColid.fBotSide) && (CurrBox.fBotSide < CurrBoxColid.fTopSide))
	{
		bColidY = true;
	}

	if ((CurrBox.fBackSide > CurrBoxColid.fFrontSide) && (CurrBox.fBackSide < CurrBoxColid.fBackSide))
	{
		bColidZ = true;
	}
	else if ((CurrBox.fFrontSide > CurrBoxColid.fFrontSide) && (CurrBox.fFrontSide < CurrBoxColid.fBackSide))
	{
		bColidZ = true;
	}

	if (bColidX && bColidY && bColidZ)
	{
		return true;
	}
	return false;
}
BoxGeo* BoxColider::GetBoxGeo()
{
	return &_pBoxGeo;
}