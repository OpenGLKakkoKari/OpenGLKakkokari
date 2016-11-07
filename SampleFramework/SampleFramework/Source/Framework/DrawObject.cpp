/*****************************************************************************/
/*!
@file   DrawObject.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "DrawObject.h"
#include "Manager.h"


using namespace Framework;


/*  �ÓI�ϐ��錾
******************************************************************************/


DrawObject*     DrawObject::pFirst[TYPE_MAX];
DrawObject*     DrawObject::pLast[TYPE_MAX];
int             DrawObject::objectNum[TYPE_MAX];
int             DrawObject::allObjectNum;
Matrix          DrawObject::viewMatrix;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

DrawObject::DrawObject() :
type(TYPE_MESH),
priority(0)
{
    RegisterList();
}
DrawObject::DrawObject(Type type) :
type(type),
priority(0)
{
    RegisterList();
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

DrawObject::~DrawObject()
{
    UnregisterList();
}

/******************************************************************************
@brief  �S�`�揈��
******************************************************************************/

void DrawObject::DrawAll()
{
    DrawObject** pObjectListTop[TYPE_MAX];
    for (int i = 0; i < TYPE_MAX; i++)
        pObjectListTop[i] = new DrawObject*[objectNum[i]];

    DrawObject** pObjectList[TYPE_MAX];
    for (int i = 0; i < TYPE_MAX; i++)
        pObjectList[i] = pObjectListTop[i];

    DrawObject* p;

    // ���X�g�ɑS�I�u�W�F�N�g�̃|�C���^����
    for (int i = 0; i < TYPE_MAX; i++)
    {
        for (p = pFirst[i]; p != NULL; p = p->pNext)
        {
            *pObjectList[i] = p;
            pObjectList[i]++;
        }
    }

    // �r���[�s����擾
    Manager::GetRenderer()->SetTranslationMode(true);
    viewMatrix = Manager::GetRenderer()->GetViewMatrix();

    // Z�\�[�g(�N�C�b�N�\�[�g)
    if (objectNum[TYPE_MESH])
        ZSort(0, objectNum[TYPE_MESH] - 1, pObjectListTop[TYPE_MESH]);
    if (objectNum[TYPE_ALPHAMESH])
        ZSort(0, objectNum[TYPE_ALPHAMESH] - 1, pObjectListTop[TYPE_ALPHAMESH]);
    if (objectNum[TYPE_SPRITE])
        PrioritySort(0, objectNum[TYPE_SPRITE] - 1, pObjectListTop[TYPE_SPRITE]);

    // �`��
    for (int i = 0; i < TYPE_MAX; i++)
        pObjectList[i] = pObjectListTop[i];

    for (int i = 0; i < TYPE_MAX; i++)
    {
        for (int j = 0; j < objectNum[i]; j++, pObjectList[i]++)
        {
            if ((*pObjectList[i])->isUsed_)
                (*pObjectList[i])->Draw();
        }
    }

    for (int i = 0; i < TYPE_MAX; i++)
        delete[] pObjectListTop[i];
}

/******************************************************************************
@brief  Z�\�[�g(�N�C�b�N�\�[�g)
@param  indexL              ����Ώۂ̍��[�v�f�ԍ�
@param  indexR              ����Ώۂ̉E�[�v�f�ԍ�
@param  pDrawObjectList     ����Ώ�
******************************************************************************/

void DrawObject::ZSort(int idxL, int idxR, DrawObject** pDrawObjectList)
{
    unsigned int Base = (idxL + idxR) >> 1;		// ��l�̗v�f�ԍ�
    DrawObject* pSwapWork;						// �f�[�^����ւ����̍�Ɨp

    int i = idxL;
    int j = idxR;

    while (1){
        /*** ��l��菬�����l���݂��� ***/
        while (pDrawObjectList[i]->GetZ() > pDrawObjectList[Base]->GetZ()){
            ++i;
        }

        /*** ��l���傫���l�������� ***/
        while (pDrawObjectList[j]->GetZ() < pDrawObjectList[Base]->GetZ()){
            --j;
        }

        /*** �Փ˂�����I�� ***/
        if (i >= j){
            break;
        }

        /*** �v�f�̓���ւ� ***/
        pSwapWork = pDrawObjectList[i];
        pDrawObjectList[i] = pDrawObjectList[j];
        pDrawObjectList[j] = pSwapWork;

        ++i;
        --j;
    }

    /*** �ċA�Ăяo�� ***/
    if (idxL < i - 1){
        ZSort(idxL, (unsigned int)(i - 1), pDrawObjectList);
    }

    /*** �ċA�Ăяo�� ***/
    if (j + 1 < idxR){
        ZSort((unsigned int)(j + 1), idxR, pDrawObjectList);
    }
}

/******************************************************************************
@brief  �D��x�\�[�g(�N�C�b�N�\�[�g)
@param  indexL              ����Ώۂ̍��[�v�f�ԍ�
@param  indexR              ����Ώۂ̉E�[�v�f�ԍ�
@param  pDrawObjectList     ����Ώ�
******************************************************************************/

void DrawObject::PrioritySort(int idxL, int idxR, DrawObject** pDrawObjectList)
{
    unsigned int Base = (idxL + idxR) >> 1;		// ��l�̗v�f�ԍ�
    DrawObject* pSwapWork;						// �f�[�^����ւ����̍�Ɨp

    int i = idxL;
    int j = idxR;

    while (1){
        /*** ��l��菬�����l���݂��� ***/
        while (pDrawObjectList[i]->priority > pDrawObjectList[Base]->priority){
            ++i;
        }

        /*** ��l���傫���l�������� ***/
        while (pDrawObjectList[j]->priority < pDrawObjectList[Base]->priority){
            --j;
        }

        /*** �Փ˂�����I�� ***/
        if (i >= j){
            break;
        }

        /*** �v�f�̓���ւ� ***/
        pSwapWork = pDrawObjectList[i];
        pDrawObjectList[i] = pDrawObjectList[j];
        pDrawObjectList[j] = pSwapWork;

        ++i;
        --j;
    }

    /*** �ċA�Ăяo�� ***/
    if (idxL < i - 1){
        PrioritySort(idxL, (unsigned int)(i - 1), pDrawObjectList);
    }

    /*** �ċA�Ăяo�� ***/
    if (j + 1 < idxR){
        PrioritySort((unsigned int)(j + 1), idxR, pDrawObjectList);
    }
}

/******************************************************************************
@brief  Z�\�[�g�ɕK�v��Z�l(�r���[�ϊ���̃I�u�W�F�N�g��Z�l)���Z�o
@param  void
@return float       Z�l
******************************************************************************/

float DrawObject::GetZ()
{
    Vector3 vecLook;
    Matrix worldMatrix;
    GetMatrix(&worldMatrix);
    Vector3::Transform(&vecLook, &pos_, &worldMatrix);
    Vector3::Transform(&vecLook, &pos_, &viewMatrix);
    return vecLook.z;
}

/******************************************************************************
@brief  �`�惊�X�g�ɓo�^
******************************************************************************/

void DrawObject::RegisterList()
{
    // �C���X�^���X������
    allObjectNum++;
    objectNum[type]++;

    // �擪�ւ̗v�f�ǉ�
    if (pFirst[type] == NULL)
    {
        pFirst[type] = this;
        pLast[type] = this;
        pPrev = NULL;
        pNext = NULL;
    }
    // �����ւ̗v�f�ǉ�
    else
    {
        pPrev = pLast[type];
        pPrev->pNext = this;
        pLast[type] = this;
    }
}

/******************************************************************************
@brief  �`�惊�X�g�������
******************************************************************************/

void DrawObject::UnregisterList()
{
    // �C���X�^���X������
    allObjectNum--;
    objectNum[type]--;

    // �擪�̗v�f�폜
    if (pFirst[type] == this)
    {
        pFirst[type] = pNext;

        // ���X�g���̗v�f���c��P��
        if (pLast[type] == this)
            pLast[type] = NULL;
        else
            pNext->pPrev = NULL;
    }
    // �����̗v�f�폜
    else if (pLast[type] == this)
    {
        pLast[type] = pPrev;
        pPrev->pNext = NULL;
    }
    // ���Ԃ̗v�f�폜
    else
    {
        pPrev->pNext = pNext;
        pNext->pPrev = pPrev;
    }
}

/******************************************************************************
@brief  �V�����^�C�v�ōēo�^
@param  newType     �V�����^�C�v
******************************************************************************/

void DrawObject::SetType(Type newType)
{
    UnregisterList();

    type = newType;

    RegisterList();
}

/******************************** ���������܂� *******************************/
