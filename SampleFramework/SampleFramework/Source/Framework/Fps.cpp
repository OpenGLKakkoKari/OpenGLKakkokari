/*****************************************************************************/
/*!
@file   Fps.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Fps.h"
using Framework::Fps;


/*  �ÓI�ϐ��錾
******************************************************************************/


unsigned int    Fps::FPS;               // �ݒ�FPS
float           Fps::cntFPS;            // FPS�J�E���^
float           Fps::avgFPS;            // ���݂̕���FPS
float           Fps::avgFPSOld;         // 1�t���[���O�̕���FPS
unsigned int    Fps::cntCalcFPS;        // FPS���v�Z�����݌v��
unsigned int    Fps::cntFrame;          // �t���[����
unsigned int    Fps::currentTime;       // ���݂̎���
unsigned int    Fps::execLastTime;      // �Ō�Ɏ��s��������
unsigned int    Fps::showLastTime;      // FPS���Ō�ɕ\����������


/*  ����
******************************************************************************/

/******************************************************************************
@brief  ���̃t���[���̏������ԂɈڍs�������`�F�b�N
@retval true            �\
@retval false           �s�\
******************************************************************************/

bool Fps::IsNextFrame()
{
    // ���݂̎������擾
    currentTime = timeGetTime();

    // 1�t���[�����̏���
    if ((currentTime - execLastTime) >= (1000 / FPS))
    {
        execLastTime = currentTime;             // �Ō�̎��s�������X�V
        cntFrame++;                             // �t���[���J�E���g��i�߂�
        return true;
    }
    else
    {
        return false;
    }
}

/******************************************************************************
@brief  ���ς��v�Z
@param  DrawIntervalms          �`��Ԋu(ms)
******************************************************************************/

void Fps::Calc(unsigned int DrawIntervalms)
{
    // ���ԊԊu����FPS���Z�o
    if ((currentTime - showLastTime) >= DrawIntervalms)
    {
        // FPS�Z�o
        cntFPS = (cntFrame * 1000.0f) / (currentTime - showLastTime);

        // FPS��\�������������X�V
        showLastTime = currentTime;
        // FPS��\�������̂ŏ�����
        cntFrame = 0;

        // ���ς̎Z�o
        if (cntCalcFPS == 0)
        {
            avgFPSOld = (float)FPS;
            avgFPS    = (float)FPS;
        }
        else
        {
            avgFPS = ((avgFPSOld * cntCalcFPS) + cntFPS) / (cntCalcFPS + 1);
            avgFPSOld = avgFPS;
        }
        cntCalcFPS++;
    }
}

/******************************************************************************
@brief  FPS��ݒ�
@param  fps         �ݒ肷��FPS
******************************************************************************/

void Fps::SetFPS(unsigned int fps)
{
    FPS = fps;
}

/******************************************************************************
@brief  ����FPS���擾
@return float       ����FPS
******************************************************************************/

float Fps::GetAverageFPS()
{
    return avgFPS;
}

/******************************************************************************
@brief  FPS���擾
@return int         FPS
******************************************************************************/

float Fps::GetFPS()
{
    return cntFPS;
}

/******************************* �֐������܂� ********************************/
