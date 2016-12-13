/*****************************************************************************/
/*!
@file   AnimationBillboard.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "AnimationBillboard.h"
#include "Manager.h"
#include "Math\Math.h"


using namespace Framework;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

AnimationBillboard::AnimationBillboard()
{
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

AnimationBillboard::~AnimationBillboard()
{
}

/******************************************************************************
@brief  �r���{�[�h��������
@param  pos                     ���W
@param  size                    �T�C�Y
@param  col                     �F
@param  type                    �r���{�[�h�̎��
@param  FileName                �e�N�X�`���̃t�@�C����
@return AnimationBillboard*     �r���{�[�h���ւ̃|�C���^
******************************************************************************/

Framework::AnimationBillboard* AnimationBillboard::Create(const Vector3& pos, const Vector2& size, Color col, TYPE type, AnimationData animData, const char *FileName)
{
    AnimationBillboard *pBillboard = new AnimationBillboard;
    pBillboard->SetBillboardType(type);
    pBillboard->SetPosition(pos);
    pBillboard->SetScale(Vector2(size.x, size.y));
    pBillboard->SetColor(col);
    pBillboard->SetAnimationData(animData);
    pBillboard->SetPattern(0);
    if (FileName)
        pBillboard->SetTexture(FileName);
    return pBillboard;
}

/******************************************************************************
@brief  �p�^�[���ݒ�
******************************************************************************/

void AnimationBillboard::SetPattern(int index)
{
    anim_.pattern = index;

    Vector2 imageSize = Vector2(1.0f / anim_.wDiv, 1.0f / anim_.hDiv);

    vtx[0].tex = Vector2(imageSize.x * (anim_.pattern % anim_.wDiv)              , imageSize.y * (anim_.pattern / anim_.wDiv));
    vtx[1].tex = Vector2(imageSize.x * (anim_.pattern % anim_.wDiv) + imageSize.x, imageSize.y * (anim_.pattern / anim_.wDiv));
    vtx[2].tex = Vector2(imageSize.x * (anim_.pattern % anim_.wDiv)              , imageSize.y * (anim_.pattern / anim_.wDiv) + imageSize.y);
    vtx[3].tex = Vector2(imageSize.x * (anim_.pattern % anim_.wDiv) + imageSize.x, imageSize.y * (anim_.pattern / anim_.wDiv) + imageSize.y);
}

/******************************************************************************
@brief  ���̃p�^�[���ɕω�
******************************************************************************/

void AnimationBillboard::NextPattern()
{
    anim_.pattern++;
    if (anim_.pattern >= anim_.patternMax)
    {
        anim_.pattern = 0;
    }

    Vector2 imageSize = Vector2(1.0f / anim_.wDiv, 1.0f / anim_.hDiv);

    vtx[0].tex = Vector2(imageSize.x * (anim_.pattern % anim_.wDiv), imageSize.y * (anim_.pattern / anim_.wDiv));
    vtx[1].tex = Vector2(imageSize.x * (anim_.pattern % anim_.wDiv) + imageSize.x, imageSize.y * (anim_.pattern / anim_.wDiv));
    vtx[2].tex = Vector2(imageSize.x * (anim_.pattern % anim_.wDiv), imageSize.y * (anim_.pattern / anim_.wDiv) + imageSize.y);
    vtx[3].tex = Vector2(imageSize.x * (anim_.pattern % anim_.wDiv) + imageSize.x, imageSize.y * (anim_.pattern / anim_.wDiv) + imageSize.y);

}

/******************************** ���������܂� *******************************/
