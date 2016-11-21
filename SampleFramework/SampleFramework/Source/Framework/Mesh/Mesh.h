#pragma once
/******************************************************************************
/*!
@file   Mesh.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "..\Vertex.h"
#include "..\Material.h"
#include "..\VertexBuffer.h"
#include "..\IndexBuffer.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Mesh
    {
    public:
        struct Subset
        {
            int startIndex;
            int count;
            int materialIndex;
        };

        Mesh();
        virtual ~Mesh();

        void Release();
        void SetTexture(int index, const char* FileName)   { pMaterialList[index].pTexture = Texture::Load(FileName); }

        static Mesh* Load(const char *FileName);
        static Mesh* CreateBox(const Vector3& scale);

        unsigned int    faceNum;
        unsigned int    vertexNum;
        
        Vertex          *pVertex;
        int             *pIndexList;

        Material        *pMaterialList;
        int             materialNum;

        Subset          *pSubsetList;
        int             subsetNum;

        VertexBuffer*   pVtxBuf;
        IndexBuffer*    pIdxBuf;


    private:
        bool                    IsReleased()    // 開放される直前かどうか
        {
            return useNum - 1 <= 0;
        }


        static Mesh*            pFirst;         // テクスチャリストの最前列
        static Mesh*            pLast;          // テクスチャリストの最後尾

        Mesh*                   pNext;
        Mesh*                   pPrev;
        char                    filePath[256];  // このテクスチャのファイルパス
        int                     useNum;         // このテクスチャの参照数
    };
}


/****************************** ヘッダここまで *******************************/
