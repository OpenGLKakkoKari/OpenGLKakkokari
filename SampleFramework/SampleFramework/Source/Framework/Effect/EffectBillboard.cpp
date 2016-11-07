/*****************************************************************************/
/*!
@file   EffectBillboard.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "EffectBillboard.h"
#include "../Manager.h"
#include "../Math/Math.h"
#include "Emitter.h"


using namespace Framework;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

EffectBillboard::EffectBillboard() : 
blendType(0), canDepthWrite(false), canDepthTest(false)
{

}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

EffectBillboard::~EffectBillboard()
{
}

/******************************************************************************
@brief  �`�揈��
******************************************************************************/

void EffectBillboard::Draw(void)
{

    Manager::GetRenderer()->SetCullingEnable(false);
    switch (blendType)
    {
    case 0: Manager::GetRenderer()->SetBlend(Renderer::BLEND_SRC_ALPHA, Renderer::BLEND_ONE); break;
    case 1: break;
    }
    switch (canDepthWrite)
    {
    case 0: Manager::GetRenderer()->SetZWriteEnable(false); break;
    case 1: Manager::GetRenderer()->SetZWriteEnable(true); break;
    }
    switch (canDepthTest)
    {
    case 0: Manager::GetRenderer()->SetZTestEnable(false); break;
    case 1: Manager::GetRenderer()->SetZTestEnable(true); break;
    }

    Billboard::Draw();

    Manager::GetRenderer()->SetCullingEnable(true);
    Manager::GetRenderer()->SetZWriteEnable(true);
    Manager::GetRenderer()->SetZTestEnable(true);
    Manager::GetRenderer()->SetBlend(Renderer::BLEND_SRC_ALPHA, Renderer::BLEND_SRC_INVALPHA);
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

EffectBillboard* EffectBillboard::Create(const Vector3& pos, const Vector2& size, Color col, TYPE type, const char *FileName)
{
    EffectBillboard *pBillboard = new EffectBillboard;
    pBillboard->SetBillboardType(type);
    pBillboard->SetPosition(pos);
    pBillboard->SetScale(Vector2(size.x, size.y));
    pBillboard->SetColor(col);
    if (FileName)
        pBillboard->SetTexture(FileName);
    return pBillboard;
}

/******************************** ���������܂� *******************************/
