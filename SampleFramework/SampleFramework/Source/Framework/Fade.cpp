/*****************************************************************************/
/*!
@file   Fade.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Fade.h"
#include "../Game/GameScene.h"
#include "Manager.h"
#include "Math\Math.h"
#include <math.h>


using namespace Game;
using namespace Framework;
using namespace Framework::Math;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Fade::Fade() : nowFade(FADE_IN), nextScene_(NULL)
{
    SetFrame(30);
    SetPriority(-1);

    color = Color(0, 0, 0, 255);
    SetPosition(Vector2((float)Manager::GetWindow()->GetWidth() / 2, (float)Manager::GetWindow()->GetHeight() / 2));
    SetScale(Vector2((float)Manager::GetWindow()->GetWidth(), (float)Manager::GetWindow()->GetHeight()));
    SetColor(color);
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Fade::~Fade()
{
}

/******************************************************************************
@brief  �t�F�[�h�X�V����
******************************************************************************/

void Fade::Update(void)
{

    // �t�F�[�h�C��
    if (nowFade == FADE_IN)
    {
        color.a -= unit;

        if (color.a <= 0 + unit)
        {
            color.a = 0;
            nowFade = FADE_NONE;
        }
    }
    // �t�F�[�h�A�E�g
    else if (nowFade == FADE_OUT)
    {
        color.a += unit;

        if (color.a >= 255 - unit)
        {
            color.a = 255;
            nowFade = FADE_IN;

            Manager::SetScene(nextScene_);
        }
    }

    SetColor(color);
}

/******************************************************************************
@brief  �t�F�[�h�ݒ菈��
@param  fadeType    �t�F�[�h�̎��
@param  nextState   �ڍs����X�e�[�g
******************************************************************************/

void Fade::SetFade(Type fadeType, Scene* nextScene)
{
    nowFade = fadeType;
    nextScene_ = nextScene;
}

/******************************** ���������܂� *******************************/
