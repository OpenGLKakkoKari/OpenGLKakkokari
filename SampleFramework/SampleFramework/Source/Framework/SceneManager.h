/******************************************************************************
/*!
@file   SceneManager.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Scene.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class SceneManager
    {
    public:
        SceneManager();
        virtual ~SceneManager();

        void Update();
        void SetScene(Scene* newScene);

    private:
        Scene*      nowScene;
    };
}


/******************************* ヘッダここまで ******************************/
