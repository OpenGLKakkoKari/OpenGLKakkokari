#pragma once
/******************************************************************************
/*!
@file   EffectReader.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Reader.h"
#include "../../Effect/Effect.h"


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    namespace File
    {
        class EffectReader : public Reader
        {
        public:
            static Effect* LoadEffect(const char *FileName);
        };
    }
}


/****************************** �w�b�_�����܂� *******************************/