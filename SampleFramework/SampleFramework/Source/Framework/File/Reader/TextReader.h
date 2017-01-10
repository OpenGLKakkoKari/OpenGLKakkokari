#pragma once
/******************************************************************************
/*!
@file   TextReader.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Reader.h"
#include "..\..\Mesh\MotionModel.h"
#include "..\..\Stage.h"


/*  クラス定義
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


/****************************** ヘッダここまで *******************************/