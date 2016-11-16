/*****************************************************************************/
/*!
@file   Texture.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  �C���N���[�h
******************************************************************************/


#include "Texture.h"
#include "TextureFactory.h"


using Framework::Texture;
using Framework::TextureFactory;


/*  �ϐ��錾
******************************************************************************/


TextureFactory* Texture::pFactory = NULL;
Texture*        Texture::pFirst = NULL;
Texture*        Texture::pLast = NULL;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Texture::Texture() : pData(NULL), useNum(0), pNext(NULL), pPrev(NULL)
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

Texture::~Texture()
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
@brief  �e�N�X�`���쐬
@param  pInfo       �e�N�X�`�����
@param  pBuffer     ���
@return Texture*    �e�N�X�`���ւ̃|�C���^
******************************************************************************/

Texture* Texture::Create(const Info *pInfo, void *pBuffer)
{
    // �����ł��Ȃ��ꍇNULL��Ԃ�
    if (!pFactory)
    {
        return NULL;
    }

    return pFactory->Create(pInfo, pBuffer);
}

/******************************************************************************
@brief  �e�N�X�`���ǂݍ���
@param  FileName    �t�@�C����
******************************************************************************/

Texture* Texture::Load(const char *FileName)
{
    // �����ł��Ȃ��ꍇNULL��Ԃ�
    if (!pFactory)
    {
        return NULL;
    }
    // �t�@�C�������Ȃ��ꍇNULL��Ԃ�
    if (strcmp(FileName, "") == 0)
    {
        return NULL;
    }
    // ���łɐ�������Ă���΂����Ԃ�
    for (Texture* p = pFirst; p != NULL; p = p->pNext)
    {
        if (!strcmp(p->filePath, FileName))
        {
            p->useNum++;    // �g�p�I�u�W�F�N�g���̑���
            return p;
        }
    }

    Texture* pTex = pFactory->Load(FileName);
    strcpy_s(pTex->filePath, 256, FileName);
    return pTex;
}

/******************************************************************************
@brief  �e�N�X�`���J��
******************************************************************************/

void Texture::Release()
{
    useNum--;

    if (useNum <= 0)
    {
        if (pData != NULL)
        {
            delete[] pData;
            pData = NULL;
        }
        delete this;
    }
}

/******************************************************************************
@brief  �e�N�X�`�����ݒ�
@param  format      �t�H�[�}�b�g
@param  width       ����
@param  height      �c��
@param  bit         �r�b�g��
@return Texture     �e�N�X�`�����ݒ�
******************************************************************************/

void Texture::SetInfo
(
Texture::Format format,
unsigned int    width,
unsigned int    height,
unsigned int    bit
)
{
    info.format     = format;
    info.width      = width;
    info.height     = height;
    info.bit        = bit;
    info.pitch      = width * 4;
    info.bufferSize = width * height * 4;
}

/******************************* ���������܂� ********************************/
