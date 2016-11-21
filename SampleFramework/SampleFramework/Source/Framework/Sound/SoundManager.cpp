/*****************************************************************************/
/*!
@file   SoundManager.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  �C���N���[�h
******************************************************************************/


#include "SoundManager.h"
#include "../File/Reader/SoundReader.h"

using Framework::Sound;
using Framework::SoundManager;
using Framework::SoundPlayer;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

SoundManager::SoundManager()
    : pDevice(NULL), pContext(NULL)
{
    for (int i = 0; i < SOUNDPLAYER_NUM; i++)
    {
        pSoundPlayer[i] = NULL;
    }
}

/******************************************************************************
@brief  �T�E���h�Ǘ�������
******************************************************************************/

void SoundManager::Init()
{
    // �f�o�C�X���J��
    pDevice = alcOpenDevice(NULL);
    if (!pDevice)
        return;
    // �R���e�L�X�g���쐬
    pContext = alcCreateContext(pDevice, NULL);
    // �R���e�L�X�g��ݒ�
    alcMakeContextCurrent(pContext);
    if (!pContext)
        return;

    // �v���C���[�쐬
    for (int i = 0; i < SOUNDPLAYER_NUM; i++)
    {
        pSoundPlayer[i] = new SoundPlayer;
    }
}

/******************************************************************************
@brief  �T�E���h�Ǘ��I������
******************************************************************************/

void SoundManager::Uninit()
{

    // �v���C���[�폜
    for (int i = 0; i < SOUNDPLAYER_NUM; i++)
    {
        if (pSoundPlayer[i] != NULL)
        {
            pSoundPlayer[i]->Unload();
            delete pSoundPlayer[i];
        }
    }

    // �R���e�L�X�g��NULL�ɐݒ�
    alcMakeContextCurrent(NULL);

    // �R���e�L�X�g���폜
    alcDestroyContext(pContext);

    // �f�o�C�X�����
    alcCloseDevice(pDevice);

}

/******************************************************************************
@brief  �T�E���h�Ǘ��ǂݍ��ݏ���
@param  tag         �^�O
@param  FileName    �t�@�C����
******************************************************************************/

void SoundManager::Load(const char* tag, const char* FileName)
{
    for (int i = 0; i < SOUNDPLAYER_NUM; i++)
    {
        if (strcmp(pSoundPlayer[i]->GetFileName(), FileName) == 0)
            return;
    }
    for (int i = 0; i < SOUNDPLAYER_NUM; i++)
    {
        if (!pSoundPlayer[i]->Use())
        {
            pSoundPlayer[i]->Load(tag, FileName);
            break;
        }
    }
}

/******************************************************************************
@brief  �T�E���h�Ǘ����t����
@param  tag         �^�O
@param  loop        ���[�v���邩�ǂ���
******************************************************************************/

void SoundManager::Play(const char* tag, bool loop)
{
    for (int i = 0; i < SOUNDPLAYER_NUM; i++)
    {
        if (strcmp(pSoundPlayer[i]->GetTag(), tag) == 0)
        {
            pSoundPlayer[i]->Play(loop);
            break;
        }
    }
}

/******************************************************************************
@brief  �T�E���h�Ǘ���~����
@param  tag         �^�O
******************************************************************************/

void SoundManager::Stop(const char* tag)
{
    for (int i = 0; i < SOUNDPLAYER_NUM; i++)
    {
        if (strcmp(pSoundPlayer[i]->GetTag(), tag) == 0)
        {
            pSoundPlayer[i]->Stop();
            break;
        }
    }
}
void SoundManager::Stop()
{
    for (int i = 0; i < SOUNDPLAYER_NUM; i++)
    {
        if (pSoundPlayer[i]->Use())
        {
            pSoundPlayer[i]->Stop();
        }
    }
}

/******************************************************************************
@brief  �T�E���h�Ǘ��ꎞ��~����
@param  tag         �^�O
******************************************************************************/

void SoundManager::Pause(const char* tag)
{
    for (int i = 0; i < SOUNDPLAYER_NUM; i++)
    {
        if (strcmp(pSoundPlayer[i]->GetTag(), tag) == 0)
        {
            pSoundPlayer[i]->Pause();
            break;
        }
    }
}
void SoundManager::Pause()
{
    for (int i = 0; i < SOUNDPLAYER_NUM; i++)
    {
        if (pSoundPlayer[i]->Use())
        {
            pSoundPlayer[i]->Pause();
        }
    }
}

/******************************************************************************
@brief  �T�E���h��Ԏ擾
@param  tag         �^�O
@return State       ���
******************************************************************************/

SoundPlayer::State SoundManager::GetState(const char* tag)
{
    SoundPlayer::State state = SoundPlayer::SOUND_INITIAL;
    for (int i = 0; i < SOUNDPLAYER_NUM; i++)
    {
        if (strcmp(pSoundPlayer[i]->GetTag(), tag) == 0)
        {
            state = pSoundPlayer[i]->GetState();
            break;
        }
    }
    return state;
}

/******************************* ���������܂� ********************************/
