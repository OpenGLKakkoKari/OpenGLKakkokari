/*****************************************************************************/
/*!
@file   NumberSprite.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "NumberSprite.h"
#include "Manager.h"


using namespace Framework;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

NumberSprite::NumberSprite() : number_(0)
{
    SetNumberVertexUV();
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

NumberSprite::~NumberSprite()
{
}

/******************************************************************************
@brief  �ԍ��ݒ�
******************************************************************************/

void NumberSprite::SetNumber(int number)
{
    number_ = number;
    SetNumberVertexUV();
}

/******************************************************************************
@brief �e�N�X�`�����W�ݒ�
******************************************************************************/

void NumberSprite::SetNumberVertexUV()
{
    vtx[0].tex = Vector2(0.1f * number_, 0.0f);
    vtx[1].tex = Vector2(0.1f * number_ + 0.1f, 0.0f);
    vtx[2].tex = Vector2(0.1f * number_, 1.0f);
    vtx[3].tex = Vector2(0.1f * number_ + 0.1f, 1.0f);
}

/******************************************************************************
@brief  �X�v���C�g��������
@param  pos             ���W
@param  size            �T�C�Y
@param  col             �F
@param  FileName        �e�N�X�`���̃t�@�C����
@param  number          ����
@return Sprite*         �X�v���C�g���ւ̃|�C���^
******************************************************************************/

NumberSprite* NumberSprite::Create(const Vector2& pos, const Vector2& size, Color col, const char *FileName, int number)
{
    NumberSprite *pSprite = new NumberSprite;
    pSprite->SetPosition(pos);
    pSprite->SetScale(size);
    pSprite->SetColor(col);
    pSprite->SetTexture(FileName);
    pSprite->SetNumber(number);
    return pSprite;
}
NumberSprite* NumberSprite::Create(const Vector2& pos, const Vector2& size, Color col, int number)
{
    NumberSprite *pSprite = new NumberSprite;
    pSprite->SetPosition(pos);
    pSprite->SetScale(size);
    pSprite->SetColor(col);
    pSprite->SetNumber(number);
    return pSprite;
}

/******************************** ���������܂� *******************************/
