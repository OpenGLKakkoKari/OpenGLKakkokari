#pragma once
/******************************************************************************
/*!
@file   Mesh.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "..\Vertex.h"
#include "..\Material.h"
#include "..\VertexBuffer.h"
#include "..\IndexBuffer.h"


/*  �N���X��`
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
        bool                    IsReleased()    // �J������钼�O���ǂ���
        {
            return useNum - 1 <= 0;
        }


        static Mesh*            pFirst;         // �e�N�X�`�����X�g�̍őO��
        static Mesh*            pLast;          // �e�N�X�`�����X�g�̍Ō��

        Mesh*                   pNext;
        Mesh*                   pPrev;
        char                    filePath[256];  // ���̃e�N�X�`���̃t�@�C���p�X
        int                     useNum;         // ���̃e�N�X�`���̎Q�Ɛ�
    };
}


/****************************** �w�b�_�����܂� *******************************/
