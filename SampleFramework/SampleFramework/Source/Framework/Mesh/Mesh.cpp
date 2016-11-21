/*****************************************************************************/
/*!
@file   Mesh.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Mesh.h"
#include "../Manager.h"
#include "../File/Reader/ModelReader.h"


using namespace Framework;
using namespace Framework::File;


/*  �ϐ��錾
******************************************************************************/


Mesh*           Mesh::pFirst = NULL;
Mesh*           Mesh::pLast = NULL;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Mesh::Mesh() : 
faceNum(0), vertexNum(0),
pVertex(NULL), pIndexList(NULL),
pMaterialList(NULL), materialNum(0),
pSubsetList(NULL), subsetNum(0),
pVtxBuf(NULL), pIdxBuf(NULL),

pNext(NULL), pPrev(NULL), useNum(0)
{
    // ������̏�����
    strcpy_s(filePath, 256, "");

    // ���X�g�̍őO��ɓo�^
    if (!pFirst)
    {
        pFirst = this;
        pLast = this;
    }
    // ���X�g�̍Ō���ɓo�^
    else
    {
        pLast->pNext = this;
        pPrev = pLast;
        pLast = this;
    }

    // �o�^��g�p�J�E���^�𑝂₷
    useNum++;
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Mesh::~Mesh()
{
    // ���X�g�̍őO��̏ꍇ
    if (pFirst == this)
    {
        pFirst = pNext;
        // ����ȏ�e�N�X�`���͂Ȃ��ꍇ
        if (!pFirst)
        {
            pLast = NULL;
        }
        // ���ɂ��e�N�X�`���͎c���Ă���ꍇ
        else
        {
            pFirst->pPrev = NULL;
        }
    }
    // �����̏ꍇ
    else if (pLast == this)
    {
        // ����ȏ�e�N�X�`���͂Ȃ��ꍇ��
        // pFirst == pLast == this�ɂȂ邽��
        // �����ɂ͗��Ȃ�
        pLast = pPrev;
        pLast->pNext = NULL;
    }
    // ���Ԃ̏ꍇ
    else
    {
        pNext->pPrev = pPrev;
        pPrev->pNext = pNext;
    }
}

/******************************************************************************
@brief  ���b�V���ǂݍ���
@param  FileName    �t�@�C����
@return Mesh*       ���b�V�����
******************************************************************************/

Mesh* Mesh::Load(const char *FileName)
{
    // �t�@�C�������Ȃ��ꍇNULL��Ԃ�
    if (strcmp(FileName, "") == 0)
    {
        return NULL;
    }
    // ���łɐ�������Ă���΂����Ԃ�
    for (Mesh* p = pFirst; p != NULL; p = p->pNext)
    {
        if (!strcmp(p->filePath, FileName))
        {
            p->useNum++;    // �g�p�I�u�W�F�N�g���̑���
            return p;
        }
    }

    Mesh* pMesh = ModelReader::Load(FileName);
    strcpy_s(pMesh->filePath, 256, FileName);
    return pMesh;
}

/******************************************************************************
@brief  ���^���b�V���쐬
@param  
@return Mesh*       ���b�V�����
******************************************************************************/

Mesh* Mesh::CreateBox(const Vector3& scale)
{
    // ���^���b�V�����

    Mesh* pMesh = new Mesh;

    const int faceNum = 12;
    const int vertexNum = 24;
    
    pMesh->faceNum          = faceNum;
    pMesh->vertexNum        = vertexNum;
    pMesh->materialNum      = 1;
    pMesh->subsetNum        = 1;

    pMesh->pVertex          = new Vertex[pMesh->vertexNum];
    pMesh->pIndexList       = new int[pMesh->faceNum*3];
    pMesh->pMaterialList    = new Material[1];
    pMesh->pSubsetList      = new Subset[1];

    pMesh->pVtxBuf          = Manager::GetRenderer()->CreateVertexBuffer(pMesh->vertexNum);
    pMesh->pIdxBuf          = Manager::GetRenderer()->CreateIndexBuffer(pMesh->faceNum*3);

    const Vertex vertexList[vertexNum] =
    {
        // �O��
        { Vector3(-scale.x/2,  scale.y/2, -scale.z/2), Vector3(0.0f, 0.0f, -1.0f), Color(255, 255, 255, 255), Vector2(0.0f, 0.0f), },
        { Vector3( scale.x/2,  scale.y/2, -scale.z/2), Vector3( 0.0f,  0.0f, -1.0f), Color(255, 255, 255, 255), Vector2(1.0f, 0.0f), },
        { Vector3(-scale.x/2, -scale.y/2, -scale.z/2), Vector3( 0.0f,  0.0f, -1.0f), Color(255, 255, 255, 255), Vector2(0.0f, 1.0f), },
        { Vector3( scale.x/2, -scale.y/2, -scale.z/2), Vector3( 0.0f,  0.0f, -1.0f), Color(255, 255, 255, 255), Vector2(1.0f, 1.0f), },
        // ����
        { Vector3(-scale.x/2, -scale.y/2, -scale.z/2), Vector3( 0.0f, -1.0f,  0.0f), Color(255, 255, 255, 255), Vector2(0.0f, 0.0f), },
        { Vector3( scale.x/2, -scale.y/2, -scale.z/2), Vector3( 0.0f, -1.0f,  0.0f), Color(255, 255, 255, 255), Vector2(1.0f, 0.0f), },
        { Vector3(-scale.x/2, -scale.y/2,  scale.z/2), Vector3( 0.0f, -1.0f,  0.0f), Color(255, 255, 255, 255), Vector2(0.0f, 1.0f), },
        { Vector3( scale.x/2, -scale.y/2,  scale.z/2), Vector3( 0.0f, -1.0f,  0.0f), Color(255, 255, 255, 255), Vector2(1.0f, 1.0f), },
        // �w��
        { Vector3(-scale.x/2, -scale.y/2,  scale.z/2), Vector3( 0.0f,  0.0f,  1.0f), Color(255, 255, 255, 255), Vector2(0.0f, 0.0f), },
        { Vector3( scale.x/2, -scale.y/2,  scale.z/2), Vector3( 0.0f,  0.0f,  1.0f), Color(255, 255, 255, 255), Vector2(1.0f, 0.0f), },
        { Vector3(-scale.x/2,  scale.y/2,  scale.z/2), Vector3( 0.0f,  0.0f,  1.0f), Color(255, 255, 255, 255), Vector2(0.0f, 1.0f), },
        { Vector3( scale.x/2,  scale.y/2,  scale.z/2), Vector3( 0.0f,  0.0f,  1.0f), Color(255, 255, 255, 255), Vector2(1.0f, 1.0f), },
        // ���
        { Vector3(-scale.x/2,  scale.y/2,  scale.z/2), Vector3( 0.0f,  1.0f,  0.0f), Color(255, 255, 255, 255), Vector2(0.0f, 0.0f), },
        { Vector3( scale.x/2,  scale.y/2,  scale.z/2), Vector3( 0.0f,  1.0f,  0.0f), Color(255, 255, 255, 255), Vector2(1.0f, 0.0f), },
        { Vector3(-scale.x/2,  scale.y/2, -scale.z/2), Vector3( 0.0f,  1.0f,  0.0f), Color(255, 255, 255, 255), Vector2(0.0f, 1.0f), },
        { Vector3( scale.x/2,  scale.y/2, -scale.z/2), Vector3( 0.0f,  1.0f,  0.0f), Color(255, 255, 255, 255), Vector2(1.0f, 1.0f), },
        // �E��
        { Vector3( scale.x/2,  scale.y/2, -scale.z/2), Vector3(-1.0f,  0.0f,  0.0f), Color(255, 255, 255, 255), Vector2(0.0f, 0.0f), },
        { Vector3( scale.x/2,  scale.y/2,  scale.z/2), Vector3(-1.0f,  0.0f,  0.0f), Color(255, 255, 255, 255), Vector2(1.0f, 0.0f), },
        { Vector3( scale.x/2, -scale.y/2, -scale.z/2), Vector3(-1.0f,  0.0f,  0.0f), Color(255, 255, 255, 255), Vector2(0.0f, 1.0f), },
        { Vector3( scale.x/2, -scale.y/2,  scale.z/2), Vector3(-1.0f,  0.0f,  0.0f), Color(255, 255, 255, 255), Vector2(1.0f, 1.0f), },
        // ����
        { Vector3(-scale.x/2,  scale.y/2,  scale.z/2), Vector3(-1.0f,  0.0f,  0.0f), Color(255, 255, 255, 255), Vector2(0.0f, 0.0f), },
        { Vector3(-scale.x/2,  scale.y/2, -scale.z/2), Vector3(-1.0f,  0.0f,  0.0f), Color(255, 255, 255, 255), Vector2(1.0f, 0.0f), },
        { Vector3(-scale.x/2, -scale.y/2,  scale.z/2), Vector3(-1.0f,  0.0f,  0.0f), Color(255, 255, 255, 255), Vector2(0.0f, 1.0f), },
        { Vector3(-scale.x/2, -scale.y/2, -scale.z/2), Vector3(-1.0f,  0.0f,  0.0f), Color(255, 255, 255, 255), Vector2(1.0f, 1.0f), },

    };

    const int indexList[faceNum*3] =
    {
        0, 1, 2,
        1, 3, 2,

        4, 5, 6,
        5, 7, 6,

        8, 9, 10,
        9, 11, 10,

        12, 13, 14,
        13, 15, 14,

        16, 17, 18,
        17, 19, 18,

        20, 21, 22,
        21, 23, 22,
    };

    for (int i = 0; i < (int)pMesh->vertexNum; i++)
    {
        pMesh->pVertex[i] = vertexList[i];
    }
    for (int i = 0; i < (int)pMesh->faceNum * 3; i++)
    {
        pMesh->pIndexList[i] = indexList[i];
    }


    Vertex* pVtx = pMesh->pVtxBuf->Lock();
    for (int i = 0; i < (int)pMesh->vertexNum; i++)
    {
        *pVtx = vertexList[i];
        pVtx++;
    }
    pMesh->pVtxBuf->Unlock();

    int* pIdx = pMesh->pIdxBuf->Lock();
    for (int i = 0; i < (int)pMesh->faceNum*3; i++)
    {
        *pIdx = indexList[i];
        pIdx++;
    }
    pMesh->pIdxBuf->Unlock();

    
    pMesh->pSubsetList[0].startIndex    = 0;
    pMesh->pSubsetList[0].count         = faceNum*3;
    pMesh->pSubsetList[0].materialIndex = 0;

    pMesh->pMaterialList[0].diffuse     = ColorValue(1.0f, 1.0f, 1.0f, 1.0f);
    pMesh->pMaterialList[0].ambient     = ColorValue(1.0f, 1.0f, 1.0f, 1.0f);
    pMesh->pMaterialList[0].emissive    = ColorValue(0.0f, 0.0f, 0.0f, 1.0f);
    pMesh->pMaterialList[0].specular    = ColorValue(0.0f, 0.0f, 0.0f, 1.0f);
    pMesh->pMaterialList[0].power       = 0.0f;
    pMesh->pMaterialList[0].pTexture    = NULL;

    return pMesh;
}

/******************************************************************************
@brief  ���b�V���J��
******************************************************************************/

void Mesh::Release()
{
    useNum--;

    if (useNum <= 0)
    {
        if (pVertex)
        {
            delete[] pVertex;
            pVertex = NULL;
        }
        if (pIndexList)
        {
            delete[] pIndexList;
            pIndexList = NULL;
        }
        if (pMaterialList)
        {
            for (int i = 0; i < materialNum; i++)
            {
                if (pMaterialList[i].pTexture)
                {
                    pMaterialList[i].pTexture->Release();
                    pMaterialList[i].pTexture = NULL;
                }
            }
            delete[] pMaterialList;
            pMaterialList = NULL;
        }
        if (pSubsetList)
        {
            delete[] pSubsetList;
            pSubsetList = NULL;
        }
        if (pVtxBuf)
        {
            pVtxBuf->Release();
            pVtxBuf = NULL;
        }
        if (pIdxBuf)
        {
            pIdxBuf->Release();
            pIdxBuf = NULL;
        }
        delete this;
    }
}

/******************************** ���������܂� *******************************/
