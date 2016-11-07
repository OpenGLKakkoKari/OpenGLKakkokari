/*****************************************************************************/
/*!
@file   Mesh.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Mesh.h"
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
pSubsetList(NULL), subsetNum(0)
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
