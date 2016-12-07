/*****************************************************************************/
/*!
@file   Field.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include <math.h>
#include "Field.h"
#include "../Game/GameScene.h"
#include "../Game/Character/Player.h"
#include "../Framework/Manager.h"
#include "../Framework/Math/Random.h"
#include "../Framework/Math/Math.h"


using namespace Game;
using namespace Framework;
using namespace Framework::Math;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
@param  widthDiv        横の分割数
@param  heightDiv       縦の分割数
******************************************************************************/

Field::Field(
    const char* fileName,
    int widthDiv,
    int heightDiv,
    const Vector2& size,
    float* pHeightMap)
{
    pField = new MeshField(fileName, widthDiv, heightDiv, size, pHeightMap);
}

/******************************************************************************
@brief  デストラクタ
******************************************************************************/

Field::~Field()
{
    SAFE_DELETE(pField)
}


/******************************************************************************
@brief  更新処理
******************************************************************************/

void Field::Update(void)
{
    ////
    //// 面の法線を算出
    ////
    //Vector3 *pNormal = new Vector3[pMesh->faceNum];
    //for (int i = 0; i < pMesh->faceNum; i++)
    //{
    //    if (i % 2 == 0)
    //    {
    //        Vector3 vec1 = pMesh->pVertex[pMesh->pIndexList[i + 1]].pos - pMesh->pVertex[pMesh->pIndexList[i + 0]].pos;
    //        Vector3 vec2 = pMesh->pVertex[pMesh->pIndexList[i + 2]].pos - pMesh->pVertex[pMesh->pIndexList[i + 0]].pos;
    //        Vector3::Cross(&pNormal[i], &vec1, &vec2);
    //    }
    //    else 
    //    {
    //        Vector3 vec1 = pMesh->pVertex[pMesh->pIndexList[i + 1]].pos - pMesh->pVertex[pMesh->pIndexList[i + 0]].pos;
    //        Vector3 vec2 = pMesh->pVertex[pMesh->pIndexList[i + 2]].pos - pMesh->pVertex[pMesh->pIndexList[i + 0]].pos;
    //        Vector3::Cross(&pNormal[i], &vec2, &vec1);
    //    }
    //    Vector3::Normalize(&pNormal[i], &pNormal[i]);
    //}

    //Vector3 pos = GameScene::GetCharacter(0)->GetPosition();
    //Vector3 P;
    //Vector3 X;
    //Vector3 LineA = Vector3(pos.x, pos.y + 150.0f, pos.z);
    //Vector3 LineB = Vector3(pos.x, pos.y, pos.z);
    //for (int i = 0; i < pMesh->faceNum; i++)
    //{
    //    //平面上の点X
    //    X = pMesh->pVertex[pMesh->pIndexList[i + 0]].pos;

    //    //XA XBベクトル
    //    Vector3 XA = X - LineA;
    //    Vector3 XB = X - LineB;

    //    //XA XBそれぞれを平面法線と内積
    //    float dot_XA = Vector3::Dot(&XA, &pNormal[i]);
    //    float dot_XB = Vector3::Dot(&XB, &pNormal[i]);

    //    if (fabsf(dot_XA) < epsilon) { dot_XA = 0.0; }
    //    if (fabsf(dot_XB) < epsilon) { dot_XB = 0.0; }

    //    //貫通判定
    //    if (dot_XA * dot_XB <= 0.0f)
    //    {
    //        //内積の片方がプラスで片方がマイナスなので、交差している
    //        Vector3 LineAB = LineB - LineA;

    //        //交点とAの距離 : 交点とBの距離 = dot_XA : dot_XB
    //        float hiritu = fabsf(dot_XA) / (abs(dot_XA) + abs(dot_XB));

    //        P.x = LineA.x + (LineAB.x * hiritu);
    //        P.y = LineA.y + (LineAB.y * hiritu);
    //        P.z = LineA.z + (LineAB.z * hiritu);

    //        // ③ポリゴン内部に貫通点が含まれるかをチェック
    //        Vector3 A = pMesh->pVertex[pMesh->pIndexList[i + 0]].pos;
    //        Vector3 B = pMesh->pVertex[pMesh->pIndexList[i + 1]].pos;
    //        Vector3 C = pMesh->pVertex[pMesh->pIndexList[i + 2]].pos;

    //        Vector3 AB = B - A;
    //        Vector3 BP = P - B;

    //        Vector3 BC = C - B;
    //        Vector3 CP = P - C;

    //        Vector3 CA = A - C;
    //        Vector3 AP = P - A;

    //        Vector3 cross[3];

    //        Vector3::Cross(&cross[0], &AB, &BP);
    //        Vector3::Cross(&cross[1], &BC, &CP);
    //        Vector3::Cross(&cross[2], &CA, &AP);

    //        float dot12 = Vector3::Dot(&cross[0], &cross[1]);
    //        float dot13 = Vector3::Dot(&cross[0], &cross[2]);
    //        float dot23 = Vector3::Dot(&cross[1], &cross[2]);

    //        if (fabsf(dot12) < 0.1f) { dot12 = 0.0f; }
    //        if (fabsf(dot13) < 0.1f) { dot13 = 0.0f; }
    //        if (fabsf(dot23) < 0.1f) { dot23 = 0.0f; }


    //        if (dot12 >= 0 && dot13 >= 0 && dot23 >= 0)
    //        {
    //            // プレイヤーの座標を貫通点に設定
    //            GameScene::GetCharacter(0)->SetPosition(Vector3(P.x, P.y, P.z));
    //            Manager::GetDebug()->Print("PP : %.2f %.2f %.2f\n", P.x, P.y, P.z);
    //        }
    //    }
    //}

    ////
    //// 頂点の法線を算出
    ////
    //int blockNumX = widthDiv  + 1;
    //int blockNumZ = heightDiv + 1;
    //for (int i = 0; i < pMesh->vertexNum; i++)
    //{
    //    Vector3 vec;
    //    int cnt = 0;

    //    // 右上部
    //    if (((i % blockNumX) < (blockNumX - 1)) && (i > (blockNumX - 1)))
    //    {// 使用する面ポリゴンを1つ追加
    //        vec += pNormal[(((i / blockNumX) - 1) * (widthDiv * 2 + 4)) + ((i % blockNumX) * 2)];
    //        cnt++;
    //    }
    //    // 左上部
    //    if ((0 < (i % blockNumX)) && (i > (blockNumX - 1)))
    //    {// 使用する面ポリゴンを2つ追加
    //        // 下
    //        vec += pNormal[(((i / blockNumX) - 1) * (widthDiv * 2 + 4)) + ((i % blockNumX) * 2) - 2];
    //        // 上
    //        vec += pNormal[(((i / blockNumX) - 1) * (widthDiv * 2 + 4)) + ((i % blockNumX) * 2) - 1];
    //        cnt += 2;
    //    }
    //    // 右下部
    //    if (((i % blockNumX) < (blockNumX - 1)) && (i < blockNumX*blockNumZ - blockNumX))
    //    {// 使用する面ポリゴンを2つ追加
    //        // 下
    //        vec += pNormal[((i / blockNumX) * (widthDiv * 2 + 4)) + ((i % blockNumX) * 2)];
    //        // 上
    //        vec += pNormal[((i / blockNumX) * (widthDiv * 2 + 4)) + ((i % blockNumX) * 2) + 1];
    //        cnt += 2;
    //    }
    //    // 左下部
    //    if ((0 < (i % blockNumX)) && (i < blockNumX*blockNumZ - blockNumX))
    //    {// 使用する面ポリゴンを1つ追加
    //        vec += pNormal[((i / blockNumX) * (widthDiv * 2 + 4)) + ((i % blockNumX) * 2) - 1];
    //        cnt++;
    //    }

    //    // 面数で割る
    //    vec /= (float)cnt;

    //    // 正規化
    //    Vector3::Normalize(&vec, &vec);
    //    pMesh->pVertex[i].nor = vec;
    //}
    //delete[] pNormal;
}

/******************************** 実装ここまで *******************************/
