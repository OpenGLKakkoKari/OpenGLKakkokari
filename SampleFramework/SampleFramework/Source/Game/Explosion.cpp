/*****************************************************************************/
/*!
@file   Explosion.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Explosion.h"
#include <math.h>
#include "../Framework/Math/Math.h"
#include "../Framework/Manager.h"
#include "../Framework/AnimationBillboard.h"


using namespace Framework;
using namespace Framework::Math;
using namespace Game;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Explosion::Explosion() : frameMax(10)
{
    for (int i = 0; i < BILLBOARD_NUM; i++)
    {
        frameCount[i] = 0;
        pBillboard[i] = NULL;
    }
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Explosion::~Explosion()
{
    for (int i = 0; i < BILLBOARD_NUM; i++)
    {
        SAFE_DELETE(pBillboard[i])
    }
}

/******************************************************************************
@brief  ����������
******************************************************************************/

void Explosion::Init(void)
{
    for (int i = 0; i < BILLBOARD_NUM; i++)
    {
        pBillboard[i] = AnimationBillboard::Create(
            // ���W
            Vector3(300.0f, 100.0f, 0.0f),
            // �T�C�Y
            Vector2(200.0f, 200.0f),
            // �F
            Color(255, 255, 255, 255),
            // �r���{�[�h�̎��
            Billboard::BILLBOARD_DEFAULT,
            // �A�j���[�V�����f�[�^
            AnimationData(8, 1, 8),
            // �t�@�C����
            "data/TEXTURE/explosion000.png"
            );
        pBillboard[i]->SetUse(false);
    }
}

/******************************************************************************
@brief  �`�揈��
******************************************************************************/

void Explosion::Update(void)
{
    for (int i = 0; i < BILLBOARD_NUM; i++)
    {
        if (pBillboard[i]->IsUsed())
        {
            frameCount[i]++;
            if (frameCount[i] > frameMax)
            {
                frameCount[i] = 0;
                pBillboard[i]->NextPattern();
            }

            if (pBillboard[i]->IsAnimationEnd())
            {
                pBillboard[i]->SetUse(false);
                pBillboard[i]->SetPattern(0);
            }

        }
    }


}
/******************************************************************************
@brief  �`�揈��
@param  pos             ���W
******************************************************************************/

void Explosion::Create(const Vector3& pos)
{
    for (int i = 0; i < BILLBOARD_NUM; i++)
    {
        if (!pBillboard[i]->IsUsed())
        {
            pBillboard[i]->SetUse(true);
            pBillboard[i]->SetPosition(pos);
            break;
        }
    }
}

/******************************** ���������܂� *******************************/
