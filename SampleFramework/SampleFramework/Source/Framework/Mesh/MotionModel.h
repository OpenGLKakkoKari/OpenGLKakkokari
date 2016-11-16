#pragma once
/******************************************************************************
/*!
@file   MotionModel.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Motion.h"
#include "Model.h"


/*  構造体定義
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


        int     modelNum;               // メッシュ総数
        Model** pModelList;             // メッシュリスト

        int     partsNum;               // パーツ総数
        Model** pPartsModelList;        // パーツに対応するメッシュリスト

        Motion* pMotionList;            // モーションリスト
        int     motionNum;              // モーション総数
        int     activeMotionIndex;      // 現在のモーション

    };
}


/******************************* ヘッダここまで ******************************/
