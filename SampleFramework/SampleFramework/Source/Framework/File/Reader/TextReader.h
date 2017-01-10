#pragma once
/******************************************************************************
/*!
@file   TextReader.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Reader.h"
#include "..\..\Mesh\MotionModel.h"
#include "..\..\Stage.h"


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    namespace File
    {
        class TextReader : public Reader
        {
        public:
            static MotionModel* LoadMotionModel(const char *FileName);
            static Stage*       LoadStage(const char *FileName);

		private:
			static Game::Field*		LoadField(const char *binaryFileName, const char *textureFileName);
        };
    }
}


/****************************** �w�b�_�����܂� *******************************/