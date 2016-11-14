/*****************************************************************************/
/*!
@file   SoundReader.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "SoundReader.h"
#include "../File.h"
#include "../../Error.h"

using Framework::File::File;
using Framework::File::SoundReader;
using Framework::Sound;
using Framework::Error;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �t�@�C���ǂݍ���
@param  FileName    ( �t�@�C���� )
@param  reverse     ( ���]�t���O )
@return Texture     ( �e�N�X�`����� )
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
@brief  WAV�t�@�C���ǂݍ���
@param  FileName    ( �t�@�C���� )
@return Sound       ( �T�E���h��� )
******************************************************************************/

Sound SoundReader::LoadWAV(const char *FileName)
{
    File file;
    if (!file.Open(FileName, "rb"))
    {
        Error::Message("�t�@�C��\"%s\"�̓ǂݍ��݂Ɏ��s���܂����B", FileName);
    }
    Sound sound;

    // Riff�̓ǂݍ���
    RiffHeader riff;
    file.Read(&riff, sizeof(RiffHeader), 1);
    if (riff.riff != 'FFIR' || riff.type != 'EVAW')
    {
        return sound;
    }

    // Format Chunk�̓ǂݍ���
    FormatChunk fmtChunk;
    file.Read(&fmtChunk, sizeof(FormatChunk), 1);
    if (fmtChunk.id != ' tmf')
    {
        return sound;
    }

    // data chunk�̓ǂݍ���
    DataChunk dataChunk;
    file.Read(&dataChunk, sizeof(dataChunk.id) + sizeof(dataChunk.size), 1);
    if (dataChunk.id != 'atad')
    {
        return sound;
    }

    sound.pData = new unsigned char[dataChunk.size];
    file.Read(sound.pData, dataChunk.size, 1);
    // �T�E���h�̑S�̃T�C�Y�擾
    sound.size = dataChunk.size;
    strcpy(sound.FileName, FileName);
    if (fmtChunk.format != 1)
    {// ��Ή��t�H�[�}�b�g
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

/******************************* �֐������܂� ********************************/
