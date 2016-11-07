/*****************************************************************************/
/*!
@file   SoundPlayer.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "SoundPlayer.h"
#include "../File/Reader/SoundReader.h"

using Framework::Sound;
using Framework::SoundPlayer;
using Framework::File::SoundReader;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

SoundPlayer::SoundPlayer()
{
    alGenBuffers(1, &buffer);
    alGenSources(1, &source);
    use = false;
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

SoundPlayer::~SoundPlayer()
{
    alDeleteBuffers(1, &buffer);
    alDeleteSources(1, &source);
}

/******************************************************************************
@brief  �t�@�C���ǂݍ���
@param  tag         �^�O
@param  FileName    �t�@�C����
******************************************************************************/

void SoundPlayer::Load(const char* tag, const char* FileName)
{
    strcpy(this->tag, tag);
    sound = File::SoundReader::Load(FileName);

    ALenum format;
    switch (sound.format)
    {
    case Sound::SF_MONO8:    format = AL_FORMAT_MONO8; break;
    case Sound::SF_MONO16:   format = AL_FORMAT_MONO16; break;
    case Sound::SF_STEREO8:  format = AL_FORMAT_STEREO8; break;
    case Sound::SF_STEREO16: format = AL_FORMAT_STEREO16; break;
    }

    alBufferData(buffer, format, sound.pData, sound.size, sound.freq);

    use = true;
}

/******************************************************************************
@brief  �t�@�C���j��
******************************************************************************/

void SoundPlayer::Unload()
{
    sound.Release();

    use = false;
}

/******************************************************************************
@brief  �Đ�
@param  loop        ���[�v���邩�ǂ���
******************************************************************************/

void SoundPlayer::Play(bool loop)
{
    ALfloat SourcePos[] = { 0.0, 0.0, 0.0 };
    ALfloat SourceVel[] = { 0.0, 0.0, 0.0 };
    ALfloat ListenerPos[] = { 0.0, 0.0, 0.0 };
    ALfloat ListenerVel[] = { 0.0, 0.0, 0.0 };
    ALfloat ListenerOri[] = { 0.0, 0.0, -1.0, 0.0, 1.0, 0.0 };

    // Listener
    alListenerfv(AL_POSITION, ListenerPos);
    alListenerfv(AL_VELOCITY, ListenerVel);
    alListenerfv(AL_ORIENTATION, ListenerOri);
    //Source
    alSourcei(source, AL_BUFFER, buffer);
    alSourcef(source, AL_PITCH, 1.0f);
    alSourcef(source, AL_GAIN, 1.0f);
    alSourcefv(source, AL_POSITION, SourcePos);
    alSourcefv(source, AL_VELOCITY, SourceVel);
    (loop) ? (alSourcei(source, AL_LOOPING, AL_TRUE)) : (alSourcei(source, AL_LOOPING, AL_FALSE));
    alSourcePlay(source);

    //// Listener
    //alListenerfv(AL_POSITION, (ALfloat*)&ListenerPos);
    //alListenerfv(AL_VELOCITY, (ALfloat*)&ListenerVel);
    //alListenerfv(AL_ORIENTATION, (ALfloat*)&ListenerOri);
    ////Source
    //alSourcei(source, AL_BUFFER, buffer);
    //alSourcef(source, AL_PITCH, 1.0f);
    //alSourcef(source, AL_GAIN, 1.0f);
    //alSourcefv(source, AL_POSITION, (ALfloat*)&SourcePos);
    //alSourcefv(source, AL_VELOCITY, (ALfloat*)&SourceVel);
    //(loop) ? (alSourcei(source, AL_LOOPING, AL_TRUE)) : (alSourcei(source, AL_LOOPING, AL_FALSE));
    //alSourcePlay(source);
}

/******************************************************************************
@brief  �ꎞ��~
******************************************************************************/

void SoundPlayer::Pause()
{
    alSourcePause(source);
}

/******************************************************************************
@brief  ��~
******************************************************************************/

void SoundPlayer::Stop()
{
    alSourceStop(source);
}

/******************************************************************************
@brief  ��Ԏ擾
@return State       ���
******************************************************************************/

SoundPlayer::State SoundPlayer::GetState()
{
    // ��ԕϐ�
    ALint state;
    State ret;

    // �\�[�X�̏�Ԃ��擾
    alGetSourcei(source, AL_SOURCE_STATE, &state);

    switch (state)
    {
    case AL_PLAYING:    ret = SOUND_PLAYING;    break;
    case AL_PAUSED :    ret = SOUND_PAUSED;     break;
    case AL_STOPPED:    ret = SOUND_STOPPED;    break;
    case AL_INITIAL:    ret = SOUND_INITIAL;    break;
    default        :    ret = SOUND_INITIAL;    break;
    }

    return ret;
}

/******************************* ���������܂� ********************************/
