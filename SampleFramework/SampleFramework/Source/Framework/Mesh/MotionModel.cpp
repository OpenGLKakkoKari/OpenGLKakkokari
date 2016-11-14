/*****************************************************************************/
/*!
@file   MotionModel.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "MotionModel.h"
#include "..\File\Reader\TextReader.h"
#include "..\Manager.h"


using Framework::MotionModel;
using Framework::Manager;
using Framework::File::TextReader;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

MotionModel::MotionModel()
    : modelNum(0), pModelList(NULL),
    partsNum(0), pPartsModelList(NULL),
    pMotionList(NULL), motionNum(NULL), activeMotionIndex(0)
{
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

MotionModel::~MotionModel()
{
}

/******************************************************************************
@brief  モーションモデル描画
******************************************************************************/

void MotionModel::Draw()
{
    Manager::GetRenderer()->SetVertexColorEnable(false);
    for (int i = 0; i < partsNum; i++)
    { // 補間座標、回転を設定
        //PartsModelList[i]->SetPosition(MotionList[ActiveMotionIndex].GetPosition(i));
        //PartsModelList[i]->SetRotation(MotionList[ActiveMotionIndex].GetRotation(i));
    }
    for (int i = 0; i < partsNum; i++)
    { // 描画
        pPartsModelList[i]->Draw();
    }
}

/******************************************************************************
@brief  モーションモデル生成
@param  ScriptFileName      スクリプトファイル名
@return MotionModel*        モーションモデル
******************************************************************************/

MotionModel* MotionModel::Create(const char *ScriptFileName)
{
    MotionModel* motionModel = new MotionModel;
    motionModel = TextReader::LoadMotionModel(ScriptFileName);
    return motionModel;
}

/******************************************************************************
@brief  モーションモデル開放
******************************************************************************/

void MotionModel::Release()
{
    // モデルの開放
    for (int i = 0; i < modelNum; i++)
    {
        delete pModelList[i];
        pModelList[i] = NULL;
    }
    delete[] pModelList;

    // パーツの開放
    for (int i = 0; i < partsNum; i++)
        pPartsModelList[i] = NULL;
    delete[] pPartsModelList;

    // モーション情報の開放
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

/******************************** 実装ここまで *******************************/
