/*****************************************************************************/
/*!
@file   SkinMeshModel.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "SkinMeshModel.h"
#include "..\File\Reader\SkinMeshModelReader.h"
#include "..\Manager.h"
#include "..\Math\Vector4.h"


using namespace Framework;
using namespace Framework::File;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

SkinMeshModel::SkinMeshModel()
{
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

SkinMeshModel::~SkinMeshModel()
{
    for (int i = 0; i < (int)pMesh->vertexNum; i++)
    {
        delete[] pBoneIndexList[i];
        delete[] pWeightList[i];
    }
    delete[] pBoneIndexList;
    delete[] pWeightList;
    delete[] pBoneList;
    delete[] pVertexList;

    for (int i = 0; i < motionNum; i++)
    {
        for (int j = 0; j < pMotionList[i].keyframeNum; j++)
        {
            delete[] pMotionList[i].keyframeList[j].keyList;
        }
        delete[] pMotionList[i].keyframeList;
    }
    delete[] pMotionList;


    delete[] pCalcMatrix;
}

/******************************************************************************
@brief  モーションモデル更新
******************************************************************************/

void SkinMeshModel::Update()
{
    static int idx = -1;
    static int frame = -1;

    if (idx != activeMotionIndex || frame != pMotionList[activeMotionIndex].frame)
    {// メッシュを更新
        CalcMesh();
    }

    idx = activeMotionIndex;
    frame = pMotionList[activeMotionIndex].frame;
}

/******************************************************************************
@brief  モーションモデル生成
@param  ScriptFileName      スクリプトファイル名
@return SkinMeshModel*        モーションモデル
******************************************************************************/

SkinMeshModel* SkinMeshModel::Load(const char *FileName)
{
    SkinMeshModel* motionModel = SkinMeshModelReader::Load(FileName);

    motionModel->pVertexList = new Vertex[motionModel->pMesh->vertexNum];
    memcpy_s(motionModel->pVertexList, sizeof(Vertex)*motionModel->pMesh->vertexNum, motionModel->pMesh->pVertex, sizeof(Vertex)*motionModel->pMesh->vertexNum);
    motionModel->pCalcMatrix = new Matrix[motionModel->boneNum];

    return motionModel;
}

/******************************************************************************
@brief  メッシュの頂点をボーン情報に合わせて変換
@brief  BOf行列×座標変換行列×逆BOf行列×影響度
******************************************************************************/

void SkinMeshModel::CalcMesh()
{
    // 座標変換行列と逆BOf行列を掛け算したものを予め算出
    for (int i = 0; i < boneNum; i++)
        GetBoneMatrix(&pCalcMatrix[i], &pBoneList[i], i);

    Vertex* vtx = pMesh->pVtxBuf->Lock();
    for (int i = 0; i < (int)pMesh->vertexNum; i++)
    {
        // 計算済み行列、BOf行列を用意
        Matrix calc[4], boneOff[4];

        for (int j = 0; j < 4; j++)
        {
            // BOfを入れておく
            boneOff[j] = pBoneList[pBoneIndexList[i][j]].offset;
            // BOfと計算済み行列を掛け算
            Matrix::Multiply(&calc[j], &boneOff[j], &pCalcMatrix[pBoneIndexList[i][j]]);
            // 影響度を掛け算
            calc[j] = calc[j] * pWeightList[i][j];
        }

        // 各ボーンの計算結果を足し合わせる
        Matrix sum = calc[0] + calc[1] + calc[2] + calc[3];

        // 計算結果の行列で頂点を変形
        Vector3::Transform(&vtx->pos, &pVertexList[i].pos, &sum);
        vtx++;
    }
    pMesh->pVtxBuf->Unlock();
}

/******************************************************************************
@brief  ボーンから行列を計算
@param  pOut        出力行列
@param  pBone       ボーン
@param  pTransform  座標変換行列
******************************************************************************/

void SkinMeshModel::GetBoneMatrix(Matrix* pOut, Bone* pBone, int boneIndex)
{
    Matrix transform, calc, parent;

    for (int i = 0; i < pMotionList[activeMotionIndex].keyframeNum - 1; i++)
    {
        if (pMotionList[activeMotionIndex].keyframeList[i].interval <= pMotionList[activeMotionIndex].frame &&
            pMotionList[activeMotionIndex].frame < pMotionList[activeMotionIndex].keyframeList[i + 1].interval)
        {
            // 補間時刻を更新
            int t_frame_diff = pMotionList[activeMotionIndex].keyframeList[i + 1].interval - pMotionList[activeMotionIndex].keyframeList[i].interval;
            float t = (float)(pMotionList[activeMotionIndex].frame - pMotionList[activeMotionIndex].keyframeList[i].interval) / (float)t_frame_diff;

            // 線形補間で拡縮、回転、移動の現在の値を算出
            Vector3 scale, trans, scale_diff, trans_diff;
            Quaternion rot;

            // 拡縮、回転、移動の値を現在のフレームに合わせて補間
            scale_diff = pMotionList[activeMotionIndex].keyframeList[i + 1].keyList[boneIndex].scale - pMotionList[activeMotionIndex].keyframeList[i].keyList[boneIndex].scale;
            trans_diff = pMotionList[activeMotionIndex].keyframeList[i + 1].keyList[boneIndex].trans - pMotionList[activeMotionIndex].keyframeList[i].keyList[boneIndex].trans;

            scale = pMotionList[activeMotionIndex].keyframeList[i].keyList[boneIndex].scale + (scale_diff * t);
            trans = pMotionList[activeMotionIndex].keyframeList[i].keyList[boneIndex].trans + (trans_diff * t);

            Quaternion::Slerp(&rot,
                &pMotionList[activeMotionIndex].keyframeList[i].keyList[boneIndex].rot,
                &pMotionList[activeMotionIndex].keyframeList[i + 1].keyList[boneIndex].rot,
                t);

            // 現在の座標変換行列を掛け合わせる
            Matrix::GetCalcMatrix(&transform, &scale, &rot, &trans);
            Matrix::Multiply(&calc, &calc, &transform);
        }
    }

    if (pBone->parent != -1)
    {
        // 計算した行列を使用して親の行列を調べる
        GetBoneMatrix(&parent, &pBoneList[pBone->parent], pBone->parent);
        Matrix::Multiply(pOut, &calc, &parent);
    }
}


/******************************** 実装ここまで *******************************/
