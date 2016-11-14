#pragma once
/******************************************************************************
/*!
@file   Sound.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include <windows.h>


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    class Sound
    {
    public:
        Sound(){}
        virtual ~Sound(){}

        enum SoundFormat
        {
            SF_MONO8,
            SF_MONO16,
            SF_STEREO8,
            SF_STEREO16
        };

        void Release();

        char            FileName[MAX_PATH];

        int             format;
        unsigned char*  pData;
        int             freq;
        int             size;
    };
}


/******************************* �w�b�_�����܂� ******************************/
