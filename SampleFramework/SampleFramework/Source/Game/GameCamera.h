#pragma once
/******************************************************************************
/*!
@file   GameCamera.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  �C���N���[�h
******************************************************************************/


#include "../Framework/Camera.h"


/*  �N���X��`
******************************************************************************/


namespace Game
{
    class GameCamera : public Framework::Camera
    {
    public:
        GameCamera();
        ~GameCamera();

        void Init();
        void Uninit();
        void Update();

        Framework::Vector3 GetRotation(){ return rot; }

        Framework::Vector3 distEyetoModel; // ���_���烂�f���܂ł̋���
        Framework::Vector3 distModeltoAt;  // ���f�����璍���_�܂ł̋���
        
        Framework::Vector3 rot;            // �J�����̌���
        float              fDistance;      // ����
        Framework::Vector3 rotAim;         // �J�����̖ڕW�p�x
        Framework::Vector3 rotVec;         // �J�����̊p�ړ���
        Framework::Vector3 rotIner;        // �J�����̊�����
        Framework::Vector3 rotUnit;        // �J�����̒P�ʉ�]��
        
        Framework::Vector3 traEyeAim;      // ���_�ڕW���W
        Framework::Vector3 traEyeVec;      // ���_�ړ���
        Framework::Vector3 traEyeIner;     // ���_������
        Framework::Vector3 traEyeUnit;     // ���_�P�ʈړ���
        
        Framework::Vector3 traAtAim;       // �����_�ڕW���W
        Framework::Vector3 traAtVec;       // �����_�ړ���
        Framework::Vector3 traAtIner;      // �����_������
        Framework::Vector3 traAtUnit;      // �����_�P�ʈړ���

    };

}


/******************************* �w�b�_�����܂� ******************************/
