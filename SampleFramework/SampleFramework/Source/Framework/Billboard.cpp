/*****************************************************************************/
/*!
@file   Billboard.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Billboard.h"
#include "Manager.h"
#include "Math\Math.h"


using namespace Framework;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Billboard::Billboard() : type(BILLBOARD_DEFAULT)
{
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Billboard::~Billboard()
{
}

/******************************************************************************
@brief  �`�揈��
******************************************************************************/

void Billboard::Draw(void)
{

    Matrix WorldMatrix, transMat, rotMat, scaMat;
    Matrix viewMat, viewInvMat;

    Matrix::Identity(&WorldMatrix);
    Matrix::Scale(&scaMat, scale_.x, scale_.y, scale_.z);
    Matrix::Multiply(&WorldMatrix, &WorldMatrix, &scaMat);

    viewMat = Manager::GetRenderer()->GetViewMatrix();
    Matrix::Identity(&viewInvMat);

    switch (type)
    {
    case BILLBOARD_DEFAULT:
        Matrix::Inverse(&rotMat, &viewMat);
        Matrix::Multiply(&WorldMatrix, &WorldMatrix, &rotMat);
        break;
    case BILLBOARD_YENABLE:
        viewInvMat._11 = viewMat._11;
        viewInvMat._13 = viewMat._31;

        viewInvMat._22 = viewMat._22;

        viewInvMat._31 = viewMat._13;
        viewInvMat._33 = viewMat._33;
        Matrix::Multiply(&WorldMatrix, &WorldMatrix, &viewInvMat);
        break;

    case BILLBOARD_ZROTATION:
        Matrix::RotationYXZ(&rotMat, 0.0f, 0.0f, rot_.z);
        Matrix::Multiply(&WorldMatrix, &WorldMatrix, &rotMat);
        Matrix::Inverse(&viewInvMat, &viewMat);
        Matrix::Multiply(&WorldMatrix, &WorldMatrix, &viewInvMat);
        break;

    case BILLBOARD_NONE:
        Matrix::RotationYXZ(&rotMat, rot_.x, rot_.y, rot_.z);
        Matrix::Multiply(&WorldMatrix, &WorldMatrix, &rotMat);
        break;
    }

    Matrix::Translation(&transMat, pos_.x, pos_.y, pos_.z);
    WorldMatrix._41 = 0.0f;
    WorldMatrix._42 = 0.0f;
    WorldMatrix._43 = 0.0f;
    Matrix::Multiply(&WorldMatrix, &WorldMatrix, &transMat);

    Manager::GetRenderer()->SetTranslationMode(true);
    Manager::GetRenderer()->SetTexture(texture_);
    Manager::GetRenderer()->SetMaterial(NULL);
    Manager::GetRenderer()->SetLightEnable(false);
    Manager::GetRenderer()->SetWorldMatrix(&WorldMatrix);
    Manager::GetRenderer()->DrawPrimitiveUP(Framework::Renderer::PRIMITIVE_TYPE_TRIANGLE_STRIP, vtx, 2);
}

/******************************************************************************
@brief  �r���{�[�h��������
@param  pos             ���W
@param  size            �T�C�Y
@param  col             �F
@param  type            �r���{�[�h�̎��
@param  FileName        �e�N�X�`���̃t�@�C����
@return Billboard*      �r���{�[�h���ւ̃|�C���^
******************************************************************************/

Framework::Billboard* Billboard::Create(const Vector3& pos, const Vector2& size, Color col, TYPE type, const char *FileName)
{
    Billboard *pBillboard = new Billboard;
    pBillboard->SetBillboardType(type);
    pBillboard->SetPosition(pos);
    pBillboard->SetScale(Vector2(size.x, size.y));
    pBillboard->SetColor(col);
    if (FileName)
        pBillboard->SetTexture(FileName);
    return pBillboard;
}

/******************************** ���������܂� *******************************/
