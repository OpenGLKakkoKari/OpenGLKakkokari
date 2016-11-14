/*****************************************************************************/
/*!
@file   Sprite.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Sprite.h"
#include "Manager.h"


using namespace Framework;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Sprite::Sprite()
{
    SetType(TYPE_SPRITE);
    SetUse(true);

    vtx[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
    vtx[0].nor = Vector3(0.0f, 0.0f, 0.0f);
    vtx[0].col = Color(255, 255, 255, 255);
    vtx[0].tex = Vector2(0.0f, 0.0f);

    vtx[1].pos = Vector3(0.5f, 0.5f, 0.0f);
    vtx[1].nor = Vector3(0.0f, 0.0f, 0.0f);
    vtx[1].col = Color(255, 255, 255, 255);
    vtx[1].tex = Vector2(1.0f, 0.0f);

    vtx[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
    vtx[2].nor = Vector3(0.0f, 0.0f, 0.0f);
    vtx[2].col = Color(255, 255, 255, 255);
    vtx[2].tex = Vector2(0.0f, 1.0f);

    vtx[3].pos = Vector3(0.5f, -0.5f, 0.0f);
    vtx[3].nor = Vector3(0.0f, 0.0f, 0.0f);
    vtx[3].col = Color(255, 255, 255, 255);
    vtx[3].tex = Vector2(1.0f, 1.0f);
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Sprite::~Sprite()
{
}

/******************************************************************************
@brief  �`�揈��
******************************************************************************/

void Sprite::Draw(void)
{
    Matrix WorldMatrix, transMat, rotMat, scaMat;

    Matrix::Identity(&WorldMatrix);
    Matrix::Scale(&scaMat, scale_.x, scale_.y, 1.0f);
    Matrix::RotationZ(&rotMat, rot_.z);
    Matrix::Translation(&transMat, pos_.x - Manager::GetWindow()->GetWidth() / 2, Manager::GetWindow()->GetHeight() / 2 - pos_.y, 0.0f);

    Matrix::Multiply(&WorldMatrix, &WorldMatrix, &scaMat);
    Matrix::Multiply(&WorldMatrix, &WorldMatrix, &rotMat);
    Matrix::Multiply(&WorldMatrix, &WorldMatrix, &transMat);

    Manager::GetRenderer()->SetTranslationMode(false);
    Manager::GetRenderer()->SetTexture(texture_);
    Manager::GetRenderer()->SetLightEnable(false);
    Manager::GetRenderer()->SetWorldMatrix(&WorldMatrix);
    Manager::GetRenderer()->DrawPrimitiveUP(Framework::Renderer::PRIMITIVE_TYPE_TRIANGLE_STRIP, vtx, 2);
}

/******************************************************************************
@brief  �X�v���C�g��������
@param  pos             ���W
@param  size            �T�C�Y
@param  col             �F
@param  FileName        �e�N�X�`���̃t�@�C����
@return Sprite*         �X�v���C�g���ւ̃|�C���^
******************************************************************************/

Sprite* Sprite::Create(const Vector2& pos, const Vector2& size, Color col, const char *FileName)
{
    Sprite *pSprite = new Sprite;
    pSprite->SetPosition(pos);
    pSprite->SetScale(size);
    pSprite->SetColor(col);
    pSprite->SetTexture(FileName);
    return pSprite;
}
Sprite* Sprite::Create(const Vector2& pos, const Vector2& size, Color col)
{
    Sprite *pSprite = new Sprite;
    pSprite->SetPosition(pos);
    pSprite->SetScale(size);
    pSprite->SetColor(col);
    return pSprite;
}

/******************************** ���������܂� *******************************/
