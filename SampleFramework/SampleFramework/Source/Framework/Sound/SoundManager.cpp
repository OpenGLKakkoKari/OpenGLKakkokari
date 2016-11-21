/*****************************************************************************/
/*!
@file   SoundManager.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  インクルード
******************************************************************************/


#include "SoundManager.h"
#include "../File/Reader/SoundReader.h"

using Framework::Sound;
using Framework::SoundManager;
using Framework::SoundPlayer;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  コンストラクタ
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
@brief  サウンド管理初期化
******************************************************************************/

void SoundManager::Init()
{
    // デバイスを開く
    pDevice = alcOpenDevice(NULL);
    if (!pDevice)
        return;
    // コンテキストを作成
    pContext = alcCreateContext(pDevice, NULL);
    // コンテキストを設定
    alcMakeContextCurrent(pContext);
    if (!pContext)
        return;

    // プレイヤー作成
    for (int i = 0; i < SOUNDPLAYER_NUM; i++)
    {
        pSoundPlayer[i] = new SoundPlayer;
    }
}

/******************************************************************************
@brief  サウンド管理終了処理
******************************************************************************/

void SoundManager::Uninit()
{

    // プレイヤー削除
    for (int i = 0; i < SOUNDPLAYER_NUM; i++)
    {
        if (pSoundPlayer[i] != NULL)
        {
            pSoundPlayer[i]->Unload();
            delete pSoundPlayer[i];
        }
    }

    // コンテキストをNULLに設定
    alcMakeContextCurrent(NULL);

    // コンテキストを削除
    alcDestroyContext(pContext);

    // デバイスを閉じる
    alcCloseDevice(pDevice);

}

/******************************************************************************
@brief  サウンド管理読み込み処理
@param  tag         タグ
@param  FileName    ファイル名
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
@brief  サウンド管理演奏処理
@param  tag         タグ
@param  loop        ループするかどうか
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
@brief  サウンド管理停止処理
@param  tag         タグ
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
@brief  サウンド管理一時停止処理
@param  tag         タグ
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
@brief  サウンド状態取得
@param  tag         タグ
@return State       状態
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

/******************************* 実装ここまで ********************************/
