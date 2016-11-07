/*****************************************************************************/
/*!
@file   GameObject.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "GameObject.h"
#include "Manager.h"


using namespace Framework;


/*  �ÓI�ϐ��錾
******************************************************************************/


GameObject*     GameObject::pFirst;
GameObject*     GameObject::pLast;
int             GameObject::allObjectNum;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

GameObject::GameObject()
{
    RegisterList();
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

GameObject::~GameObject()
{
    UnregisterList();
}

/******************************************************************************
@brief  �S�Q�[���I�u�W�F�N�g�X�V
******************************************************************************/

void GameObject::UpdateAll()
{
    // �Q�[���I�u�W�F�N�g�����ׂčX�V
    for (GameObject* p = pFirst; p != NULL; p = p->pNext)
    {
        if (p->isUsed_)
            p->Update();
    }
}

/******************************************************************************
@brief  �`�惊�X�g�ɓo�^
******************************************************************************/

void GameObject::RegisterList()
{
    // �C���X�^���X������
    allObjectNum++;

    // �擪�ւ̗v�f�ǉ�
    if (pFirst == NULL)
    {
        pFirst = this;
        pLast = this;
        pPrev = NULL;
        pNext = NULL;
    }
    // �����ւ̗v�f�ǉ�
    else
    {
        pPrev = pLast;
        pPrev->pNext = this;
        pLast = this;
    }
}

/******************************************************************************
@brief  �`�惊�X�g�������
******************************************************************************/

void GameObject::UnregisterList()
{
    // �C���X�^���X������
    allObjectNum--;

    // �擪�̗v�f�폜
    if (pFirst == this)
    {
        pFirst = pNext;

        // ���X�g���̗v�f���c��P��
        if (pLast == this)
            pLast = NULL;
        else
            pNext->pPrev = NULL;
    }
    // �����̗v�f�폜
    else if (pLast == this)
    {
        pLast = pPrev;
        pPrev->pNext = NULL;
    }
    // ���Ԃ̗v�f�폜
    else
    {
        pPrev->pNext = pNext;
        pNext->pPrev = pPrev;
    }
}

/******************************** ���������܂� *******************************/
