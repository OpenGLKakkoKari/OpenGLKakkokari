/*****************************************************************************/
/*!
@file   MotionModel.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "MotionModel.h"
#include "..\File\Reader\TextReader.h"
#include "..\Manager.h"


using Framework::MotionModel;
using Framework::Manager;
using Framework::File::TextReader;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

MotionModel::MotionModel()
    : modelNum(0), pModelList(NULL),
    partsNum(0), pPartsModelList(NULL),
    pMotionList(NULL), motionNum(NULL), activeMotionIndex(0)
{
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

MotionModel::~MotionModel()
{
}

/******************************************************************************
@brief  ���[�V�������f���`��
******************************************************************************/

void MotionModel::Draw()
{
    Manager::GetRenderer()->SetVertexColorEnable(false);
    for (int i = 0; i < partsNum; i++)
    { // ��ԍ��W�A��]��ݒ�
        //PartsModelList[i]->SetPosition(MotionList[ActiveMotionIndex].GetPosition(i));
        //PartsModelList[i]->SetRotation(MotionList[ActiveMotionIndex].GetRotation(i));
    }
    for (int i = 0; i < partsNum; i++)
    { // �`��
        pPartsModelList[i]->Draw();
    }
}

/******************************************************************************
@brief  ���[�V�������f������
@param  ScriptFileName      �X�N���v�g�t�@�C����
@return MotionModel*        ���[�V�������f��
******************************************************************************/

MotionModel* MotionModel::Create(const char *ScriptFileName)
{
    MotionModel* motionModel = new MotionModel;
    motionModel = TextReader::LoadMotionModel(ScriptFileName);
    return motionModel;
}

/******************************************************************************
@brief  ���[�V�������f���J��
******************************************************************************/

void MotionModel::Release()
{
    // ���f���̊J��
    for (int i = 0; i < modelNum; i++)
    {
        delete pModelList[i];
        pModelList[i] = NULL;
    }
    delete[] pModelList;

    // �p�[�c�̊J��
    for (int i = 0; i < partsNum; i++)
        pPartsModelList[i] = NULL;
    delete[] pPartsModelList;

    // ���[�V�������̊J��
    for (int i = 0; i < motionNum; i++)
    {
        for (int j = 0; j < pMotionList[i].keyframeNum; j++)
        {
            delete[] pMotionList[i].keyframeList[j].keyList;
        }
        delete[] pMotionList[i].keyframeList;
    }
    delete[] pMotionList;
}

/******************************** ���������܂� *******************************/
