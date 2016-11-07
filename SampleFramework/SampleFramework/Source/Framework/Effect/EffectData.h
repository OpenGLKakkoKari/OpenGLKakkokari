#pragma once
/*****************************************************************************/
/*!
@file   EffectData.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "..\Math\Vector3.h"
#include "..\Color.h"


/*  �N���X��`
******************************************************************************/


namespace Framework
{

    struct EffectDataHeader
    {
        int             majorVer;           // ���W���[�o�[�W����
        int             minorVer;           // �}�C�i�[�o�[�W����
        int             dataSize;           // �f�[�^���̃T�C�Y
        int             nodeNum;            // �m�[�h��
        int             frameStart;         // �J�n�t���[��
        int             frameEnd;           // �I���t���[��
    };
    struct EffectData
    {
        int             siblingIndex;       // ���K�w�̃C���f�b�N�X
        int             childIndex;         // �q���̃C���f�b�N�X

        bool            draw;               // �`�悷�邩�ǂ���
        bool            lifeDelete;         // �����ō폜

        int             createNum;          // ������
        int             lifeMin;            // �ŏ�����
        int             lifeMax;            // �ő����
        int             createIntervalMin;  // �ŏ������Ԋu
        int             createIntervalMax;  // �ő吶���Ԋu
        int             createStartMin;     // �ŏ������J�n����
        int             createStartMax;     // �ő吶���J�n����

        Vector3         posMin;             // �ŏ����W
        Vector3         posMax;             // �ő���W
        Vector3         posVelMin;          // �ŏ��ړ����x
        Vector3         posVelMax;          // �ő�ړ����x
        Vector3         posAccelMin;        // �ŏ��ړ������x
        Vector3         posAccelMax;        // �ő�ړ������x

        Vector3         rotMin;             // �ŏ��p�x
        Vector3         rotMax;             // �ő�p�x
        Vector3         rotVelMin;          // �ŏ���]���x
        Vector3         rotVelMax;          // �ő��]���x
        Vector3         rotAccelMin;        // �ŏ���]�����x
        Vector3         rotAccelMax;        // �ő��]�����x


        Vector3         sclMin;             // �ŏ��X�P�[��
        Vector3         sclMax;             // �ő�X�P�[��
        Vector3         sclVelMin;          // �ŏ��g�k���x
        Vector3         sclVelMax;          // �ő�g�k���x
        Vector3         sclAccelMin;        // �ŏ��g�k�����x
        Vector3         sclAccelMax;        // �ő�g�k�����x

        Color           startColorMin;      // �J�n�ŏ��F
        Color           startColorMax;      // �J�n�ő�F
        Color           endColorMin;        // �I���ŏ��F
        Color           endColorMax;        // �I���ő�F

        //Particle::TYPE  particleType;       // �p�[�e�B�N���̎��
        int             optionType;         // �I�v�V�����̎��
        char            fileName[256];      // �t�@�C����

        int             blendType;          // �u�����h���@
        bool            depthWrite;         // �[�x�o�b�t�@����
        bool            depthTest;          // �[�x�e�X�g

        EffectData() :
            siblingIndex(0), childIndex(0), draw(true), createNum(1), lifeMin(100), lifeMax(100),
            createIntervalMin(1), createIntervalMax(1), createStartMin(0), createStartMax(0),
            sclMin(Vector3(10.0f, 10.0f, 10.0f)), sclMax(Vector3(10.0f, 10.0f, 10.0f)),
            startColorMin(Color(255, 255, 255, 255)), startColorMax(Color(255, 255, 255, 255)),
            endColorMin(Color(255, 255, 255, 255)), endColorMax(Color(255, 255, 255, 255)),
            optionType(0), blendType(0), depthWrite(0), depthTest(0)
        {}

    };
}


/****************************** �w�b�_�����܂� *******************************/
