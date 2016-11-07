#pragma once
/******************************************************************************
/*!
@file   Fps.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include <windows.h>


/*  ���C�u���������N
******************************************************************************/


#pragma comment( lib, "winmm.lib" )


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    class Fps
    {
    public:
        static bool IsNextFrame();
        static void Calc(unsigned int DrawIntervalms);
        static void SetFPS(unsigned int fps);

        static float GetAverageFPS();
        static float GetFPS();

    private:
        static unsigned int     FPS;                // �ݒ�FPS
        static float            cntFPS;             // FPS�J�E���^
        static float            avgFPS;             // ���݂̕���FPS
        static float            avgFPSOld;          // 1�t���[���O�̕���FPS
        static unsigned int     cntCalcFPS;         // FPS���v�Z�����݌v��
        static unsigned int     cntFrame;           // �t���[����
        static unsigned int     currentTime;        // ���݂̎���
        static unsigned int     execLastTime;       // �Ō�Ɏ��s��������
        static unsigned int     showLastTime;       // FPS���Ō�ɕ\����������
    };
}


/****************************** �w�b�_�����܂� *******************************/