/*****************************************************************************/
/*!
@file   Vector3.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  インクルード
******************************************************************************/


#include "Vector3.h"
#include <math.h>
#include "..\Math\Math.h"


using Framework::Vector3;
using Framework::Matrix;
using namespace Framework::Math;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  内積算出
@param  pV1         入力ベクトル1
@param  pV2         入力ベクトル2
@return float       内積
******************************************************************************/

float Vector3::Dot(const Vector3 *pV1, const Vector3 *pV2)
{
    return pV1->x * pV2->x +
           pV1->y * pV2->y +
           pV1->z * pV2->z;

}

/******************************************************************************
@brief  外積算出
@param  pOut        出力先
@param  pV1         入力ベクトル1
@param  pV2         入力ベクトル2
@return Vector3     外積
******************************************************************************/

Vector3* Vector3::Cross(Vector3 *pOut, const Vector3 *pV1, const Vector3 *pV2)
{

    pOut->x = pV1->y * pV2->z - pV1->z * pV2->y;
    pOut->y = pV1->z * pV2->x - pV1->x * pV2->z;
    pOut->z = pV1->x * pV2->y - pV1->y * pV2->x;

    return pOut;
}

/******************************************************************************
@brief  ベクトルの長さ算出
@param  pV          入力ベクトル
@return float       ベクトルの長さ
******************************************************************************/

float Vector3::Length(const Vector3 *pV)
{

    return sqrtf( pV->x * pV->x +
                  pV->y * pV->y +
                  pV->z * pV->z);

}

/******************************************************************************
@brief  距離算出
@param  pV1         入力ベクトル1
@param  pV2         入力ベクトル2
@return float       距離
******************************************************************************/

float Vector3::Distance(const Vector3 *pV1, const Vector3 *pV2)
{
    return Vector3::Length(pV1) - Vector3::Length(pV2);
}

/******************************************************************************
@brief  2つのベクトルがなす角を算出
@param  pV1         入力ベクトル1
@param  pV2         入力ベクトル2
@return float       ラジアン
******************************************************************************/

float Vector3::Radian(const Vector3 *pV1, const Vector3 *pV2)
{
    float lengthA = Vector3::Length(pV1);
    float lengthB = Vector3::Length(pV2);

    float cos = Vector3::Dot(pV1, pV2) / (lengthA * lengthB);

    return acosf(cos);
}

/******************************************************************************
@brief  ベクトルの正規化( 零ベクトルの場合、零ベクトルを返す )
@param  pOut        出力ベクトル
@param  pV          入力ベクトル
******************************************************************************/

Vector3* Vector3::Normalize(Vector3 *pOut, const Vector3 *pV)
{
    (Length(pV) == 0.0f) ?
        (*pOut = Vector3::Zero()) :
        (*pOut = *pV / Length(pV));
    
    return pOut;
}

/******************************************************************************
@brief  3次元ベクトルを行列変換
@param  pOut        出力ベクトル
@param  pV          入力ベクトル
@param  pM          入力行列
@return Vector3*    出力ベクトル
******************************************************************************/

Vector3* Vector3::Transform(Vector3 *pOut, Vector3 *pV, Matrix *pM)
{

    pOut->x = pV->x    * pM->_11
            + pV->y    * pM->_21
            + pV->z    * pM->_31
            + pM->_41;

    pOut->y = pV->x    * pM->_12
            + pV->y    * pM->_22
            + pV->z    * pM->_32
            + pM->_42;

    pOut->z = pV->x    * pM->_13
            + pV->y    * pM->_23
            + pV->z    * pM->_33
            + pM->_43;

    return pOut;
}

/******************************************************************************
@brief  補間
@param  A           始点
@param  B           終点
@param  min         最小時間
@param  max         最大時間
@param  elapsed     経過時間
@param  func        補間関数ポインタ
@return Vector3     座標
******************************************************************************/

Vector3* Vector3::Lerp(
    Vector3* pOut,
    const Vector3 &A,
    const Vector3 &B,
    float min,
    float max,
    float elapsed,
    float(*func)(float))
{

    float t = (elapsed - min) / (max - min);    // 時間を媒介変数に
    bool isOut = false;
    if (t < 0.0f)
    {
        t = 0.0f; isOut = true;
    }
    else if (t > 1.0f)
    {
        t = 1.0f; isOut = true;
    }

    float rate = (*func)(t);                    // 引数の補間値に変換
    *pOut = A * (1.0f - rate) + B * rate;

    return pOut;
}

/******************************************************************************
@brief  エルミート曲線
@param  p0          始点
@param  v0          始点ベクトル
@param  p1          終点
@param  v1          終点ベクトル
@param  s           補間比率(0 ～ 1)
@return Vector3     指定座標
******************************************************************************/

Vector3* Vector3::Hermite(
    Vector3 *pOut,
    Vector3 *p0, Vector3 *v0,
    Vector3 *p1, Vector3 *v1,
    float s)
{

    Vector3 Vec;

    float u1 = s;
    float u2 = u1*u1;
    float u3 = u1*u1*u1;
    float mP0 = 2 * u3 - 3 * u2 + 0 + 1;
    float mV0 = u3 - 2 * u2 + u1;
    float mP1 = -2 * u3 + 3 * u2;
    float mV1 = u3 - u2;

    Vec.x = p0->x*mP0 + v0->x*mV0 + p1->x*mP1 + v1->x*mV1;
    Vec.y = p0->y*mP0 + v0->y*mV0 + p1->y*mP1 + v1->y*mV1;
    Vec.z = p0->z*mP0 + v0->z*mV0 + p1->z*mP1 + v1->z*mV1;

    *pOut = Vec;
    return pOut;
}

/******************************************************************************
@brief  ベジェ曲線
@param  p0          始点
@param  p1          制御点1
@param  p2          制御店2
@param  p3          終点
@param  s           補間比率(0 ～ 1)
@return Vector3     指定座標
******************************************************************************/

Vector3* Vector3::Bezier(
    Vector3 *pOut,
    Vector3 *p0, Vector3 *p1,
    Vector3 *p2, Vector3 *p3,
    float s)
{

    Vector3 Vec;

    float u = s;
    float mP0 = (1 - u)*(1 - u)*(1 - u);
    float mP1 = 3 * u     * (1 - u)*(1 - u);
    float mP2 = 3 * u*u   * (1 - u);
    float mP3 = u*u*u;

    Vec.x = p0->x*mP0 + p1->x*mP1 + p2->x*mP2 + p3->x*mP3;
    Vec.y = p0->y*mP0 + p1->y*mP1 + p2->y*mP2 + p3->y*mP3;
    Vec.z = p0->z*mP0 + p1->z*mP1 + p2->z*mP2 + p3->z*mP3;

    *pOut = Vec;
    return pOut;
}

/******************************************************************************
@brief  Bスプライン曲線
@param  p0          始点
@param  p1          制御点1
@param  p2          制御店2
@param  p3          終点
@param  s           補間比率(0 ～ 1)
@return Vector3     指定座標
******************************************************************************/

Vector3* Vector3::BSpline(
    Vector3 *pOut,
    Vector3 *p0, Vector3 *p1,
    Vector3 *p2, Vector3 *p3,
    float s)
{
    Vector3 Vec;

    float u1 = s;
    float u2 = u1*u1;
    float u3 = u1*u1*u1;
    float mP0 = (-1 * u3 + 3 * u2 - 3 * u1 + 1)*1.0f / 6;
    float mP1 = (3 * u3 - 6 * u2 + 4)*1.0f / 6;
    float mP2 = (-3 * u3 + 3 * u2 + 3 * u1 + 1)*1.0f / 6;
    float mP3 = (1 * u3)*1.0f / 6;

    Vec.x = p0->x*mP0 + p1->x*mP1 + p2->x*mP2 + p3->x*mP3;
    Vec.y = p0->y*mP0 + p1->y*mP1 + p2->y*mP2 + p3->y*mP3;
    Vec.z = p0->z*mP0 + p1->z*mP1 + p2->z*mP2 + p3->z*mP3;

    *pOut = Vec;
    return pOut;
}

/******************************** 実装ここまで *******************************/
