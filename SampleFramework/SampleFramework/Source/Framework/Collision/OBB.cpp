/*****************************************************************************/
/*!
@file   OBB.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "OBB.h"
#include "..\Math\Matrix.h"
#include "..\Math\Math.h"
#include "..\Mesh\Mesh.h"
#include "..\Mesh\Model.h"
#include <math.h>


using namespace Framework;
using namespace Framework::Math;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
******************************************************************************/

OBB::OBB() : pBox(NULL)
{
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

OBB::~OBB()
{
    if (pBox)
    {
        delete pBox;
        pBox = NULL;
    }
}

/******************************************************************************
@brief  OBB生成処理
@param  pMesh           メッシュ
@param  scale           大きさ
@param  worldPos        座標
@param  rot             回転
@return OBB*            OBB情報へのポインタ
******************************************************************************/

OBB* OBB::Create(Mesh *pMesh, Vector3 worldPos, Vector3 rot)
{
    OBB *pOBB = new OBB;

    //最大値、最小値の初期値設定
    Vector3 min = Vector3(10000.0f, 10000.0f, 10000.0f);
    Vector3 max = Vector3(-10000.0f, -10000.0f, -10000.0f);

    //メッシュの頂点データ取得
    for (int i = 0; i < (int)pMesh->vertexNum; i++)
    {
        Vector3 pos = pMesh->pVertex[i].pos;
        if (pos.x < min.x) min.x = pos.x;
        if (pos.x > max.x) max.x = pos.x;
        if (pos.y < min.y) min.y = pos.y;
        if (pos.y > max.y) max.y = pos.y;
        if (pos.z < min.z) min.z = pos.z;
        if (pos.z > max.z) max.z = pos.z;
    }

    //中心点取得
    pOBB->pos = (min + max) * 0.5f + worldPos;

    //方向ベクトル取得
    Matrix rotMat;
    Matrix::RotationYXZ(&rotMat, rot.x, rot.y, rot.z);
    pOBB->dir[0] = Vector3(rotMat._11, rotMat._12, rotMat._13);
    pOBB->dir[1] = Vector3(rotMat._21, rotMat._22, rotMat._23);
    pOBB->dir[2] = Vector3(rotMat._31, rotMat._32, rotMat._33);

    //長さ取得
    pOBB->len.x = fabsf(max.x - min.x) * 0.5f;
    pOBB->len.y = fabsf(max.y - min.y) * 0.5f;
    pOBB->len.z = fabsf(max.z - min.z) * 0.5f;

    // 描画用モデル作成
    pOBB->pBox = Model::CreateBox(Vector3(pOBB->len.x * 2, pOBB->len.y * 2, pOBB->len.z * 2));
    pOBB->pBox->SetRotation(Vector3(rot.x, rot.y, rot.z));
    pOBB->pBox->pMesh->pMaterialList[0].diffuse = ColorValue(1.0f, 0.0f, 0.0f, 0.5f);
    pOBB->pBox->SetType(DrawObject::TYPE_ALPHAMESH);
    
    return pOBB;
}
OBB* OBB::Create(Vector3 scale, Vector3 worldPos, Vector3 rot)
{
    OBB *pOBB = new OBB;

    //最大値、最小値の初期値設定
    Vector3 min = Vector3(-scale.x / 2, -scale.y / 2, -scale.z / 2);
    Vector3 max = Vector3(scale.x / 2, scale.y / 2, scale.z / 2);

    //中心点取得
    pOBB->pos = worldPos;

    //方向ベクトル取得
    Matrix rotMat;
    Matrix::RotationYXZ(&rotMat, rot.x, rot.y, rot.z);
    pOBB->dir[0] = Vector3(rotMat._11, rotMat._12, rotMat._13);
    pOBB->dir[1] = Vector3(rotMat._21, rotMat._22, rotMat._23);
    pOBB->dir[2] = Vector3(rotMat._31, rotMat._32, rotMat._33);

    //長さ取得
    pOBB->len.x = fabsf(max.x - min.x) * 0.5f;
    pOBB->len.y = fabsf(max.y - min.y) * 0.5f;
    pOBB->len.z = fabsf(max.z - min.z) * 0.5f;

    // 描画用モデル作成
    pOBB->pBox = Model::CreateBox(Vector3(pOBB->len.x * 2, pOBB->len.y * 2, pOBB->len.z * 2));
    pOBB->pBox->SetPosition(Vector3(worldPos.x, worldPos.y, worldPos.z));
    pOBB->pBox->SetRotation(Vector3(rot.x, rot.y, rot.z));
    pOBB->pBox->pMesh->pMaterialList[0].diffuse = ColorValue(1.0f, 0.0f, 0.0f, 0.5f);
    pOBB->pBox->SetType(DrawObject::TYPE_ALPHAMESH);

    return pOBB;
}

/******************************************************************************
@brief  OBBの長さ更新
@param  pVertexList     メッシュ
@param  vertexNum       頂点数
******************************************************************************/

void OBB::UpdateLength(Vertex *pVertexList, int vertexNum)
{
    //最大値、最小値の初期値設定
    Vector3 min = Vector3(10000.0f, 10000.0f, 10000.0f);
    Vector3 max = Vector3(-10000.0f, -10000.0f, -10000.0f);

    //メッシュの頂点データ取得
    for (int i = 0; i < vertexNum; i++)
    {
        Vector3 pos = pVertexList[i].pos;
        if (pos.x < min.x) min.x = pos.x;
        if (pos.x > max.x) max.x = pos.x;
        if (pos.y < min.y) min.y = pos.y;
        if (pos.y > max.y) max.y = pos.y;
        if (pos.z < min.z) min.z = pos.z;
        if (pos.z > max.z) max.z = pos.z;
    }

    //長さ取得
    len.x = fabsf(max.x - min.x) * 0.5f;
    len.y = fabsf(max.y - min.y) * 0.5f;
    len.z = fabsf(max.z - min.z) * 0.5f;

}

/******************************************************************************
@brief  OBB同士の衝突判定
@param  pA              OBB1
@param  pB              OBB2
@retval true    衝突している
@retval false   衝突していない
******************************************************************************/

bool OBB::CheckCollision(OBB *pA, OBB *pB)
{
    // 各方向ベクトルの確保
    // （N***:標準化方向ベクトル）
    Vector3 NAe1 = pA->dir[0], Ae1 = NAe1 * pA->len.x;
    Vector3 NAe2 = pA->dir[1], Ae2 = NAe2 * pA->len.y;
    Vector3 NAe3 = pA->dir[2], Ae3 = NAe3 * pA->len.z;
    Vector3 NBe1 = pB->dir[0], Be1 = NBe1 * pB->len.x;
    Vector3 NBe2 = pB->dir[1], Be2 = NBe2 * pB->len.y;
    Vector3 NBe3 = pB->dir[2], Be3 = NBe3 * pB->len.z;
    Vector3 Interval = pA->pos - pB->pos;

    // 分離軸 : Ae1
    float rA = Vector3::Length(&Ae1);
    float rB = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
    float L = fabs(Vector3::Dot(&Interval, &NAe1));
    if (L > rA + rB)
        return false; // 衝突していない

    // 分離軸 : Ae2
    rA = Vector3::Length(&Ae2);
    rB = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
    L = fabs(Vector3::Dot(&Interval, &NAe2));
    if (L > rA + rB)
        return false;

    // 分離軸 : Ae3
    rA = Vector3::Length(&Ae3);
    rB = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
    L = fabs(Vector3::Dot(&Interval, &NAe3));
    if (L > rA + rB)
        return false;

    // 分離軸 : Be1
    rA = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
    rB = Vector3::Length(&Be1);
    L = fabs(Vector3::Dot(&Interval, &NBe1));
    if (L > rA + rB)
        return false;

    // 分離軸 : Be2
    rA = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
    rB = Vector3::Length(&Be2);
    L = fabs(Vector3::Dot(&Interval, &NBe2));
    if (L > rA + rB)
        return false;

    // 分離軸 : Be3
    rA = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
    rB = Vector3::Length(&Be3);
    L = fabs(Vector3::Dot(&Interval, &NBe3));
    if (L > rA + rB)
        return false;

    // 分離軸 : C11
    Vector3 Cross;
    Vector3::Cross(&Cross, &NAe1, &NBe1);
    rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    L = fabs(Vector3::Dot(&Interval, &Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C12
    Vector3::Cross(&Cross, &NAe1, &NBe2);
    rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    L = fabs(Vector3::Dot(&Interval, &Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C13
    Vector3::Cross(&Cross, &NAe1, &NBe3);
    rA = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    L = fabs(Vector3::Dot(&Interval, &Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C21
    Vector3::Cross(&Cross, &NAe2, &NBe1);
    rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    L = fabs(Vector3::Dot(&Interval, &Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C22
    Vector3::Cross(&Cross, &NAe2, &NBe2);
    rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    L = fabs(Vector3::Dot(&Interval, &Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C23
    Vector3::Cross(&Cross, &NAe2, &NBe3);
    rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    L = fabs(Vector3::Dot(&Interval, &Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C31
    Vector3::Cross(&Cross, &NAe3, &NBe1);
    rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    L = fabs(Vector3::Dot(&Interval, &Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C32
    Vector3::Cross(&Cross, &NAe3, &NBe2);
    rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    L = fabs(Vector3::Dot(&Interval, &Cross));
    if (L > rA + rB)
        return false;

    // 分離軸 : C33
    Vector3::Cross(&Cross, &NAe3, &NBe3);
    rA = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    L = fabs(Vector3::Dot(&Interval, &Cross));
    if (L > rA + rB)
        return false;

    return true;
}

/******************************************************************************
@brief  OBB同士の衝突を解決する
@param  pA              OBB1
@param  pB              OBB2
@retval true    衝突している
@retval false   衝突していない
******************************************************************************/

void OBB::ResolveCollision(OBB *pA, OBB *pB)
{
    // 各方向ベクトルの確保
    // （N***:標準化方向ベクトル）
    Vector3 NAe1 = pA->dir[0], Ae1 = NAe1 * pA->len.x;
    Vector3 NAe2 = pA->dir[1], Ae2 = NAe2 * pA->len.y;
    Vector3 NAe3 = pA->dir[2], Ae3 = NAe3 * pA->len.z;
    Vector3 NBe1 = pB->dir[0], Be1 = NBe1 * pB->len.x;
    Vector3 NBe2 = pB->dir[1], Be2 = NBe2 * pB->len.y;
    Vector3 NBe3 = pB->dir[2], Be3 = NBe3 * pB->len.z;
    Vector3 Interval = pA->pos - pB->pos;

    float rA[15], rB[15], L[15];
    Vector3 vec[15];

    // 分離軸 : Ae1
    rA[0] = Vector3::Length(&Ae1);
    rB[0] = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
    L[0] = Vector3::Dot(&Interval, &NAe1);
    vec[0] = NAe1;

    // 分離軸 : Ae2
    rA[1] = Vector3::Length(&Ae2);
    rB[1] = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
    L[1] = Vector3::Dot(&Interval, &NAe2);
    vec[1] = NAe2;

    // 分離軸 : Ae3
    rA[2] = Vector3::Length(&Ae3);
    rB[2] = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
    L[2] = Vector3::Dot(&Interval, &NAe3);
    vec[2] = NAe3;

    // 分離軸 : Be1
    rA[3] = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
    rB[3] = Vector3::Length(&Be1);
    L[3] = Vector3::Dot(&Interval, &NBe1);
    vec[3] = NBe1;

    // 分離軸 : Be2
    rA[4] = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
    rB[4] = Vector3::Length(&Be2);
    L[4] = Vector3::Dot(&Interval, &NBe2);
    vec[4] = NBe2;

    // 分離軸 : Be3
    rA[5] = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
    rB[5] = Vector3::Length(&Be3);
    L[5] = Vector3::Dot(&Interval, &NBe3);
    vec[5] = NBe3;

    // 分離軸 : C11
    Vector3 Cross;
    Vector3::Cross(&Cross, &NAe1, &NBe1);
    rA[6] = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB[6] = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    L[6] = Vector3::Dot(&Interval, &Cross);
    vec[6] = Cross;

    // 分離軸 : C12
    Vector3::Cross(&Cross, &NAe1, &NBe2);
    rA[7] = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB[7] = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    L[7] = Vector3::Dot(&Interval, &Cross);
    vec[7] = Cross;

    // 分離軸 : C13
    Vector3::Cross(&Cross, &NAe1, &NBe3);
    rA[8] = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB[8] = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    L[8] = Vector3::Dot(&Interval, &Cross);
    vec[8] = Cross;

    // 分離軸 : C21
    Vector3::Cross(&Cross, &NAe2, &NBe1);
    rA[9] = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB[9] = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    L[9] = Vector3::Dot(&Interval, &Cross);
    vec[9] = Cross;

    // 分離軸 : C22
    Vector3::Cross(&Cross, &NAe2, &NBe2);
    rA[10] = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB[10] = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    L[10] = Vector3::Dot(&Interval, &Cross);
    vec[10] = Cross;

    // 分離軸 : C23
    Vector3::Cross(&Cross, &NAe2, &NBe3);
    rA[11] = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB[11] = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    L[11] = Vector3::Dot(&Interval, &Cross);
    vec[11] = Cross;

    // 分離軸 : C31
    Vector3::Cross(&Cross, &NAe3, &NBe1);
    rA[12] = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB[12] = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    L[12] = Vector3::Dot(&Interval, &Cross);
    vec[12] = Cross;

    // 分離軸 : C32
    Vector3::Cross(&Cross, &NAe3, &NBe2);
    rA[13] = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB[13] = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    L[13] = Vector3::Dot(&Interval, &Cross);
    vec[13] = Cross;

    // 分離軸 : C33
    Vector3::Cross(&Cross, &NAe3, &NBe3);
    rA[14] = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB[14] = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    L[14] = Vector3::Dot(&Interval, &Cross);
    vec[14] = Cross;

    // １番めり込んでいる分離軸を探す
    float min = fabsf(L[5]);
    int id = 5;
    for (int i = 4; i >= 3; i--)
        if (min < fabsf(L[i]))
            id = i;
    
    if (fabsf(L[id]) < epsilon)
        return;

    if (L[id] > 0)
        pA->pos += vec[id] * ((rA[id] + rB[id]) - L[id]);
    else
        pA->pos += -vec[id] * ((rA[id] + rB[id]) + L[id]);


}

/******************************************************************************
@brief  OBB同士の衝突を解決する
@param  pA              OBB1
@param  pB              OBB2
@param  posOld          OBB1の１フレーム前の座標
@retval true    衝突している
@retval false   衝突していない
******************************************************************************/

void OBB::ResolveCollision(OBB *pA, OBB *pB, Vector3 posOld)
{
    // 各方向ベクトルの確保
    // （N***:標準化方向ベクトル）
    Vector3 NAe1 = pA->dir[0], Ae1 = NAe1 * pA->len.x;
    Vector3 NAe2 = pA->dir[1], Ae2 = NAe2 * pA->len.y;
    Vector3 NAe3 = pA->dir[2], Ae3 = NAe3 * pA->len.z;
    Vector3 NBe1 = pB->dir[0], Be1 = NBe1 * pB->len.x;
    Vector3 NBe2 = pB->dir[1], Be2 = NBe2 * pB->len.y;
    Vector3 NBe3 = pB->dir[2], Be3 = NBe3 * pB->len.z;
    Vector3 Interval = pA->pos - pB->pos;

    float rA[15], rB[15], L[15];
    Vector3 vec[15];

    // 分離軸 : Ae1
    rA[0] = Vector3::Length(&Ae1);
    rB[0] = LenSegOnSeparateAxis(&NAe1, &Be1, &Be2, &Be3);
    L[0] = Vector3::Dot(&Interval, &NAe1);
    vec[0] = NAe1;

    // 分離軸 : Ae2
    rA[1] = Vector3::Length(&Ae2);
    rB[1] = LenSegOnSeparateAxis(&NAe2, &Be1, &Be2, &Be3);
    L[1] = Vector3::Dot(&Interval, &NAe2);
    vec[1] = NAe2;

    // 分離軸 : Ae3
    rA[2] = Vector3::Length(&Ae3);
    rB[2] = LenSegOnSeparateAxis(&NAe3, &Be1, &Be2, &Be3);
    L[2] = Vector3::Dot(&Interval, &NAe3);
    vec[2] = NAe3;

    // 分離軸 : Be1
    rA[3] = LenSegOnSeparateAxis(&NBe1, &Ae1, &Ae2, &Ae3);
    rB[3] = Vector3::Length(&Be1);
    L[3] = Vector3::Dot(&Interval, &NBe1);
    vec[3] = NBe1;

    // 分離軸 : Be2
    rA[4] = LenSegOnSeparateAxis(&NBe2, &Ae1, &Ae2, &Ae3);
    rB[4] = Vector3::Length(&Be2);
    L[4] = Vector3::Dot(&Interval, &NBe2);
    vec[4] = NBe2;

    // 分離軸 : Be3
    rA[5] = LenSegOnSeparateAxis(&NBe3, &Ae1, &Ae2, &Ae3);
    rB[5] = Vector3::Length(&Be3);
    L[5] = Vector3::Dot(&Interval, &NBe3);
    vec[5] = NBe3;

    // 分離軸 : C11
    Vector3 Cross;
    Vector3::Cross(&Cross, &NAe1, &NBe1);
    rA[6] = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB[6] = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    L[6] = Vector3::Dot(&Interval, &Cross);
    vec[6] = Cross;

    // 分離軸 : C12
    Vector3::Cross(&Cross, &NAe1, &NBe2);
    rA[7] = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB[7] = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    L[7] = Vector3::Dot(&Interval, &Cross);
    vec[7] = Cross;

    // 分離軸 : C13
    Vector3::Cross(&Cross, &NAe1, &NBe3);
    rA[8] = LenSegOnSeparateAxis(&Cross, &Ae2, &Ae3);
    rB[8] = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    L[8] = Vector3::Dot(&Interval, &Cross);
    vec[8] = Cross;

    // 分離軸 : C21
    Vector3::Cross(&Cross, &NAe2, &NBe1);
    rA[9] = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB[9] = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    L[9] = Vector3::Dot(&Interval, &Cross);
    vec[9] = Cross;

    // 分離軸 : C22
    Vector3::Cross(&Cross, &NAe2, &NBe2);
    rA[10] = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB[10] = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    L[10] = Vector3::Dot(&Interval, &Cross);
    vec[10] = Cross;

    // 分離軸 : C23
    Vector3::Cross(&Cross, &NAe2, &NBe3);
    rA[11] = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae3);
    rB[11] = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    L[11] = Vector3::Dot(&Interval, &Cross);
    vec[11] = Cross;

    // 分離軸 : C31
    Vector3::Cross(&Cross, &NAe3, &NBe1);
    rA[12] = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB[12] = LenSegOnSeparateAxis(&Cross, &Be2, &Be3);
    L[12] = Vector3::Dot(&Interval, &Cross);
    vec[12] = Cross;

    // 分離軸 : C32
    Vector3::Cross(&Cross, &NAe3, &NBe2);
    rA[13] = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB[13] = LenSegOnSeparateAxis(&Cross, &Be1, &Be3);
    L[13] = Vector3::Dot(&Interval, &Cross);
    vec[13] = Cross;

    // 分離軸 : C33
    Vector3::Cross(&Cross, &NAe3, &NBe3);
    rA[14] = LenSegOnSeparateAxis(&Cross, &Ae1, &Ae2);
    rB[14] = LenSegOnSeparateAxis(&Cross, &Be1, &Be2);
    L[14] = Vector3::Dot(&Interval, &Cross);
    vec[14] = Cross;

    //// 方向ベクトルを生成
    Vector3 dirPos = pA->pos - posOld;
    dirPos = Vector3(fabsf(dirPos.x), dirPos.y, fabsf(dirPos.z));
    float min = 0.0f;
    int id = 0;
    
    // min = (rA[0] + rB[0]) - fabsf(L[0]);
    //id = 0;
    //for (int i = 0; i < 6; i++)
    //    if (min > (rA[i] + rB[i]) - fabsf(L[i]))
    //        id = i;

    // x >= z
    //if ((dirPos.x >= dirPos.z))
    //{
    //    min = (rA[4] + rB[4]) - fabsf(L[4]); id = 4;
    //    if (min > (rA[4] + rB[4]) - fabsf(L[4])) { id = 4; }
    //    if (min > (rA[3] + rB[3]) - fabsf(L[3])) { id = 3; }
    //    if (min > (rA[5] + rB[5]) - fabsf(L[5])) { id = 5; }
    //    if (min > (rA[1] + rB[1]) - fabsf(L[1])) { id = 1; }
    //    if (min > (rA[0] + rB[0]) - fabsf(L[0])) { id = 0; }
    //    if (min > (rA[2] + rB[2]) - fabsf(L[2])) { id = 2; }
    //}
    //// z > x
    //if ((dirPos.z > dirPos.x))
    //{
    //    min = (rA[4] + rB[4]) - fabsf(L[4]); id = 4;
    //    if (min > (rA[4] + rB[4]) - fabsf(L[4])) { id = 4; }
    //    if (min > (rA[5] + rB[5]) - fabsf(L[5])) { id = 5; }
    //    if (min > (rA[3] + rB[3]) - fabsf(L[3])) { id = 3; }
    //    if (min > (rA[1] + rB[1]) - fabsf(L[1])) { id = 1; }
    //    if (min > (rA[2] + rB[2]) - fabsf(L[2])) { id = 2; }
    //    if (min > (rA[0] + rB[0]) - fabsf(L[0])) { id = 0; }
    //}


    //// x > y > z
    //if ((dirPos.x >= dirPos.y) && (dirPos.y >= dirPos.z) && (dirPos.x >= dirPos.z))
    //{
    //    min = fabsf(L[3]); id = 3;
    //    if (min < fabsf(L[3])) { id = 3; min = fabsf(L[3]); }
    //    if (min < fabsf(L[4])) { id = 4; min = fabsf(L[4]); }
    //    if (min < fabsf(L[5])) { id = 5; min = fabsf(L[5]); }
    //    if (min < fabsf(L[0])) { id = 0; min = fabsf(L[0]); }
    //    if (min < fabsf(L[1])) { id = 1; min = fabsf(L[1]); }
    //    if (min < fabsf(L[2])) { id = 2; min = fabsf(L[2]); }
    //}
    //// x > z > y
    //if ((dirPos.x >= dirPos.z) && (dirPos.z >= dirPos.y) && (dirPos.x >= dirPos.y))
    //{
    //    min = fabsf(L[3]); id = 3;
    //    if (min < fabsf(L[3])) { id = 3; min = fabsf(L[3]); }
    //    if (min < fabsf(L[5])) { id = 5; min = fabsf(L[5]); }
    //    if (min < fabsf(L[4])) { id = 4; min = fabsf(L[4]); }
    //    if (min < fabsf(L[0])) { id = 0; min = fabsf(L[0]); }
    //    if (min < fabsf(L[2])) { id = 2; min = fabsf(L[2]); }
    //    if (min < fabsf(L[1])) { id = 1; min = fabsf(L[1]); }
    //}
    //// y > x > z
    //if ((dirPos.y >= dirPos.x) && (dirPos.x >= dirPos.z) && (dirPos.y >= dirPos.z))
    //{
    //    min = fabsf(L[4]); id = 4;
    //    if (min < fabsf(L[4])) { id = 4; min = fabsf(L[4]); }
    //    if (min < fabsf(L[3])) { id = 3; min = fabsf(L[3]); }
    //    if (min < fabsf(L[5])) { id = 5; min = fabsf(L[5]); }
    //    if (min < fabsf(L[1])) { id = 1; min = fabsf(L[1]); }
    //    if (min < fabsf(L[0])) { id = 0; min = fabsf(L[0]); }
    //    if (min < fabsf(L[2])) { id = 2; min = fabsf(L[2]); }
    //}
    //// y > z > x
    //if ((dirPos.y >= dirPos.z) && (dirPos.z >= dirPos.x) && (dirPos.y >= dirPos.x))
    //{
    //    min = fabsf(L[4]); id = 4;
    //    if (min < fabsf(L[4])) { id = 4; min = fabsf(L[4]); }
    //    if (min < fabsf(L[5])) { id = 5; min = fabsf(L[5]); }
    //    if (min < fabsf(L[3])) { id = 3; min = fabsf(L[3]); }
    //    if (min < fabsf(L[1])) { id = 1; min = fabsf(L[1]); }
    //    if (min < fabsf(L[2])) { id = 2; min = fabsf(L[2]); }
    //    if (min < fabsf(L[0])) { id = 0; min = fabsf(L[0]); }
    //}
    //// z > x > y
    //if ((dirPos.z >= dirPos.x) && (dirPos.x >= dirPos.y) && (dirPos.z >= dirPos.y))
    //{
    //    min = fabsf(L[5]); id = 5;
    //    if (min < fabsf(L[5])) { id = 5; min = fabsf(L[5]); }
    //    if (min < fabsf(L[3])) { id = 3; min = fabsf(L[3]); }
    //    if (min < fabsf(L[4])) { id = 4; min = fabsf(L[4]); }
    //    if (min < fabsf(L[2])) { id = 2; min = fabsf(L[2]); }
    //    if (min < fabsf(L[0])) { id = 0; min = fabsf(L[0]); }
    //    if (min < fabsf(L[1])) { id = 1; min = fabsf(L[1]); }
    //}
    //// z > y > x
    //if ((dirPos.z >= dirPos.y) && (dirPos.y >= dirPos.x) && (dirPos.z >= dirPos.x))
    //{

    //    min = fabsf(L[5]); id = 5;
    //    if (min < fabsf(L[5])) { id = 5; min = fabsf(L[5]); }
    //    if (min < fabsf(L[4])) { id = 4; min = fabsf(L[4]); }
    //    if (min < fabsf(L[3])) { id = 3; min = fabsf(L[3]); }
    //    if (min < fabsf(L[2])) { id = 2; min = fabsf(L[2]); }
    //    if (min < fabsf(L[1])) { id = 1; min = fabsf(L[1]); }
    //    if (min < fabsf(L[0])) { id = 0; min = fabsf(L[0]); }
    //}

    // １番めり込んでいる分離軸を探す
    //float min = fabsf(L[5]);
    //int id = 5;
    //for (int i = 4; i >= 3; i--)
    //    if (min < fabsf(L[i]))
    //        id = i;
    
    //min = (rA[0] + rB[0]) - fabsf(L[0]);
    //id = 0;
    //for (int i = 0; i < 6; i++)
    //    if (min > (rA[i] + rB[i]) - fabsf(L[i]))
    //        id = i;



    // y >= x && y >= z
    if ((fabsf(dirPos.y) >= dirPos.x) && (fabsf(dirPos.y) >= dirPos.z) )
    {
        min = (rA[1] + rB[1]) - fabsf(L[1]); id = 1;
        if (min > (rA[4] + rB[4]) - fabsf(L[4])) { id = 4; }
    }
    // x >= z
    else if ((dirPos.x >= dirPos.z))
    {
        min = (rA[0] + rB[0]) - fabsf(L[0]); id = 0;
        if (min > (rA[3] + rB[3]) - fabsf(L[3])) { id = 3; }
        if (min > (rA[5] + rB[5]) - fabsf(L[5])) { id = 5; }
        if (min > (rA[0] + rB[0]) - fabsf(L[0])) { id = 0; }
        if (min > (rA[2] + rB[2]) - fabsf(L[2])) { id = 2; }
    }
    // z > x
    else if ((dirPos.z > dirPos.x))
    {
        min = (rA[2] + rB[2]) - fabsf(L[2]); id = 2;
        if (min > (rA[5] + rB[5]) - fabsf(L[5])) { id = 5; }
        if (min > (rA[3] + rB[3]) - fabsf(L[3])) { id = 3; }
        if (min > (rA[2] + rB[2]) - fabsf(L[2])) { id = 2; }
        if (min > (rA[0] + rB[0]) - fabsf(L[0])) { id = 0; }
    }

    if (fabsf(L[id]) < epsilon)
        return;

    if (L[id] > 0)
        pA->pos += vec[id] * ((rA[id] + rB[id]) - L[id]);
    else
        pA->pos += -vec[id] * ((rA[id] + rB[id]) + L[id]);


}

/******************************************************************************
@brief  長さを算出
@param  v1              ベクトル1
@param  v2              ベクトル2
@param  v3              ベクトル3
@param  v4              ベクトル4
@return float           長さ    
******************************************************************************/

float OBB::LenSegOnSeparateAxis(Vector3* v1, Vector3* v2, Vector3* v3, Vector3* v4)
{
    return (fabsf(Vector3::Dot(v2, v1)) +
        fabsf(Vector3::Dot(v3, v1)) +
        fabsf(Vector3::Dot(v4, v1)));
}
float OBB::LenSegOnSeparateAxis(Vector3* v1, Vector3* v2, Vector3* v3)
{
    return (fabsf(Vector3::Dot(v2, v1)) +
        fabsf(Vector3::Dot(v3, v1)));
}

/******************************** 実装ここまで *******************************/
