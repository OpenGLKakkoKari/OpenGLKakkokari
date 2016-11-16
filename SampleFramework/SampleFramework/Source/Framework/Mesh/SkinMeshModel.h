#pragma once
/******************************************************************************
/*!
@file   SkinMeshModel.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Model.h"
#include "Motion.h"
#include "Bone.h"


/*  構造体定義
******************************************************************************/


namespace Framework
{
    class SkinMeshModel : public Model
    {
    public:
        SkinMeshModel();
        virtual ~SkinMeshModel();

        void Update();
        
        static SkinMeshModel* Load(const char *FileName);

        void SetMotion(int index)           { activeMotionIndex = index; SetFrame(0); }
        void SetFrame(int frame)            { pMotionList[activeMotionIndex].SetFrame(frame); }
        void NextFrame(int addFrameCnt = 1) { pMotionList[activeMotionIndex].NextFrame(addFrameCnt); }
        bool IsMotionEnd(int index)         { return pMotionList[index].frame >= pMotionList[index].frameMax - 1; }
        void SetLoop(bool flag)             { pMotionList[activeMotionIndex].loop = flag; }


        int     boneNum;                // ボーン行列総数
        Bone*   pBoneList;              // ボーンリスト

        int**   pBoneIndexList;         // ボーンインデックスリスト
        float** pWeightList;            // ボーンの重みリスト

        Motion* pMotionList;            // モーションリスト
        int     motionNum;              // モーション総数
        int     activeMotionIndex;      // 現在のモーション

        Vertex* pVertexList;            // 元モデルの頂点リスト
        Matrix* pCalcMatrix;            // 座標変換行列と逆BOf行列を掛け算したもの


    protected:
        void CalcMesh();
        void GetBoneMatrix(Matrix* pOut, Bone* pBone, int boneIndex);

    };
}


/******************************* ヘッダここまで ******************************/
