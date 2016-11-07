#pragma once
/******************************************************************************
/*!
@file   SkinMeshData.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  構造体定義
******************************************************************************/


namespace Framework
{
    struct SkinMeshDataHeader
    {
        int faceNum;            // 面数
        int vertexNum;          // 頂点数
        int materialNum;        // マテリアル数
        int subsetNum;          // サブセット数
        int boneNum;            // ボーン数
        int motionNum;          // モーション数
        int indexNum;           // インデックス数
    };
}


/******************************* ヘッダここまで ******************************/
