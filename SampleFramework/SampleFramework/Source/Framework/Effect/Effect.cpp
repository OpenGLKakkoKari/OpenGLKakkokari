/*****************************************************************************/
/*!
@file   Effect.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Effect.h"
#include "../Manager.h"


using namespace Framework;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Effect::Effect() : 
startTime(0), endTime(120), timer(0),
isPlaying(false), isLoop(false),
emitterNum(0)
{
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Effect::~Effect()
{
    if (pEmitterList)
    {
        for (int i = 0; i < EMITTER_MAX; i++)
        {
            if (pEmitterList[i])
            {
                SAFE_DELETE(pEmitterList[i])
            }
        }
        delete[] pEmitterList;
    }
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void Effect::Update(void)
{
    // �G�t�F�N�g�X�V����
    if (isPlaying)
    {
        for (int i = 0; i < EMITTER_MAX; i++)
        {
            pEmitterList[i]->Update();
        }

        // �^�C�}�[�X�V
        timer++;
        if (isLoop)
        {
            if (timer > endTime)
            {
                timer = startTime;
                for (int i = 0; i < EMITTER_MAX; i++)
                {
                    pEmitterList[i]->Reset();
                }
            }
        }
        else
        {
            if (timer >= endTime)
            {
                timer = endTime - 1;
                isPlaying = false;
            }
        }
    }
}

/******************************** ���������܂� *******************************/
