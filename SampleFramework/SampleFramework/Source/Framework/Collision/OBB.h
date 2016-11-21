#pragma once
/******************************************************************************
/*!
@file   OBB.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "..\Math\Vector3.h"
#include "..\Mesh\Mesh.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Model;
    class OBB
    {
    public:
        OBB();
        ~OBB();

        void Draw();
        void UpdateLength(Vertex* pVertexList, int vertexNum);
        void UpdateLength(Mesh* pMesh) { UpdateLength(pMesh->pVertex, pMesh->vertexNum); }

        Vector3 pos;        // 中心点の座標
        Vector3 dir[3];     // XYZ の各座標軸の傾きを表す方向ベクトル
        Vector3 len;        // OBB の各座標軸に沿った長さの半分（中心点から面までの長さ）
        Model*  pBox;       // 描画用

        static OBB* Create(Mesh* pMesh, Vector3 worldPos, Vector3 rot);
        static OBB* Create(Vector3 scale, Vector3 worldPos, Vector3 rot);
        static bool CheckCollision(OBB *pA, OBB *pB);
        static void ResolveCollision(OBB *pA, OBB *pB);
        static void ResolveCollision(OBB *pA, OBB *pB, Vector3 posOld);

    private:
        static float LenSegOnSeparateAxis(Vector3* v1, Vector3* v2, Vector3* v3, Vector3* v4);
        static float LenSegOnSeparateAxis(Vector3* v1, Vector3* v2, Vector3* v3);
    };
}


/****************************** ヘッダここまで *******************************/
