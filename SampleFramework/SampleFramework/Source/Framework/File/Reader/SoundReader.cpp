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
    else if (strcmp(ext, ".ogg") == 0)
    {
        return LoadOGG(FileName);
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

/******************************************************************************
@brief  OGGファイル読み込み
@param  FileName    ( ファイル名 )
@return Sound       ( サウンド情報 )
******************************************************************************/

Sound SoundReader::LoadOGG(const char *FileName)
{
    FILE *fp;
    if (!(fp = fopen(FileName, "rb")) == NULL)
    {
        Error::Message("ファイル\"%s\"の読み込みに失敗しました。", FileName);
    }

    OggVorbis_File vf;
    ov_open(fp, &vf, NULL, 0);
    vorbis_info *pInfo = ov_info(&vf, -1);

    Sound sound;
    sound.freq = pInfo->rate;
    strcpy(sound.FileName, FileName);
    switch (pInfo->channels)
    {
    case 1: sound.format = Sound::SF_MONO16;  break;
    case 2: sound.format = Sound::SF_STEREO16; break;
    }
    int bitstream;
    int readSize = 0;
    int comSize = 0;
    char* tmp = new char[1024 * 80000]; // 100MB
    char* tmpBuffer = new char[1024 * 80000]; // 100MB

    while (1)
    {
        readSize = ov_read(&vf, (char*)tmpBuffer, 4096, 0, 2, 1, &bitstream);
        if (comSize + readSize >= 1024 * 80000 || readSize == 0)
            break;
        memcpy(tmp + comSize, tmpBuffer, readSize);
        comSize += readSize;
    }

    sound.pData = new unsigned char[comSize];
    sound.size = comSize;
    memcpy(sound.pData, tmp, comSize);

    delete[] tmp;
    delete[] tmpBuffer;

    return sound;
}

/******************************* 関数ここまで ********************************/
