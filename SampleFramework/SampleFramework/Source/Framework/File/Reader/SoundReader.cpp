/*****************************************************************************/
/*!
@file   SoundReader.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "SoundReader.h"
#include "../File.h"
#include "../../Error.h"

using Framework::File::File;
using Framework::File::SoundReader;
using Framework::Sound;
using Framework::Error;


/*  実装
******************************************************************************/

/******************************************************************************
@brief  ファイル読み込み
@param  FileName    ( ファイル名 )
@param  reverse     ( 反転フラグ )
@return Texture     ( テクスチャ情報 )
******************************************************************************/

Sound SoundReader::Load(const char *FileName, bool reverse)
{

    strcpy(fileName, FileName);
    GetExtension(FileName);

    if      (strcmp(ext, ".wav") == 0)
    {
        return LoadWAV(FileName);
    }

    Sound sound;
    return sound;

}

/******************************************************************************
@brief  WAVファイル読み込み
@param  FileName    ( ファイル名 )
@return Sound       ( サウンド情報 )
******************************************************************************/

Sound SoundReader::LoadWAV(const char *FileName)
{
    File file;
    if (!file.Open(FileName, "rb"))
    {
        Error::Message("ファイル\"%s\"の読み込みに失敗しました。", FileName);
    }
    Sound sound;

    // Riffの読み込み
    RiffHeader riff;
    file.Read(&riff, sizeof(RiffHeader), 1);
    if (riff.riff != 'FFIR' || riff.type != 'EVAW')
    {
        return sound;
    }

    // Format Chunkの読み込み
    FormatChunk fmtChunk;
    file.Read(&fmtChunk, sizeof(FormatChunk), 1);
    if (fmtChunk.id != ' tmf')
    {
        return sound;
    }

    // data chunkの読み込み
    DataChunk dataChunk;
    file.Read(&dataChunk, sizeof(dataChunk.id) + sizeof(dataChunk.size), 1);
    if (dataChunk.id != 'atad')
    {
        return sound;
    }

    sound.pData = new unsigned char[dataChunk.size];
    file.Read(sound.pData, dataChunk.size, 1);
    // サウンドの全体サイズ取得
    sound.size = dataChunk.size;
    strcpy(sound.FileName, FileName);
    if (fmtChunk.format != 1)
    {// 非対応フォーマット
        return sound;
    }
    sound.freq = fmtChunk.samplerate;
    switch (fmtChunk.channels)
    {
    case 1:
        sound.format = (fmtChunk.bitswidth == 8) ?
            (Sound::SF_MONO8) : (Sound::SF_MONO16);
        break;
    case 2:
        sound.format = (fmtChunk.bitswidth == 8) ?
            (Sound::SF_STEREO8) : (Sound::SF_STEREO16);
        break;
    }

    file.Close();

    return sound;
}

/******************************* 関数ここまで ********************************/
