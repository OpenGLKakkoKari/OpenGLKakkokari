#pragma once
/******************************************************************************
/*!
@file   MotionModel.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Motion.h"
#include "Model.h"


/*  �\���̒�`
******************************************************************************/


namespace Framework
{
    class MotionModel : public DrawObject
    {
    public:

        MotionModel();
        virtual ~MotionModel();

        void Init(){}
        void Uninit(){}
        void Update(){}
        void Draw();
        
        static MotionModel* Create(const char *ScriptFileName);
        void Release();

        void SetMotion(int index) { pMotionList[activeMotionIndex].SetFrame(0); activeMotionIndex = index; }
        void SetFrame(int frame)  { pMotionList[activeMotionIndex].SetFrame(frame); }
        void NextFrame(int addFrameCnt = 1){ pMotionList[activeMotionIndex].NextFrame(addFrameCnt); }
        void SetLoop(bool flag){ pMotionList[activeMotionIndex].loop = flag; }


        int     modelNum;               // ���b�V������
        Model** pModelList;             // ���b�V�����X�g

        int     partsNum;               // �p�[�c����
        Model** pPartsModelList;        // �p�[�c�ɑΉ����郁�b�V�����X�g

        Motion* pMotionList;            // ���[�V�������X�g
        int     motionNum;              // ���[�V��������
        int     activeMotionIndex;      // ���݂̃��[�V����

    };
}


/******************************* �w�b�_�����܂� ******************************/
