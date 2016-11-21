/*****************************************************************************/
/*!
@file   Stage.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Stage.h"
#include "Collision\OBB.h"
#include "Mesh/Model.h"
#include "../Framework/Manager.h"
#include "../Game/GameScene.h"
#include "../Game/Field.h"
#include "../Game/Skybox.h"
#include "../Game/Plant.h"


using namespace Framework;
using namespace Game;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Stage::Stage() 
    : fieldNum(0), modelNum(0), plantNum(0), obbNum(0),
    pSkybox(NULL), pFieldList(NULL), pModelList(NULL),
    pPlantList(NULL), pOBBList(NULL)
{
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Stage::~Stage()
{
    SAFE_UNINIT(pSkybox);

    if (fieldNum > 0)
    {
        for (int i = 0; i < fieldNum; i++)
            SAFE_DELETE(pFieldList[i]);
        delete[] pFieldList;
    }

    if (modelNum > 0)
    {
        for (int i = 0; i < modelNum; i++)
            SAFE_DELETE(pModelList[i]);
        delete[] pModelList;
    }

    if (plantNum > 0)
    {
        for (int i = 0; i < plantNum; i++)
            SAFE_DELETE(pPlantList[i]);
        delete[] pPlantList;
    }

    if (obbNum > 0)
    {
        for (int i = 0; i < obbNum; i++)
            SAFE_DELETE(pOBBList[i]);
        delete[] pOBBList;
    }
}

/******************************************************************************
@brief  �X�V����
******************************************************************************/

void Stage::Update(void)
{
    pSkybox->Update();
}

/******************************** ���������܂� *******************************/
