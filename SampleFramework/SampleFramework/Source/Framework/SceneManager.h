/******************************************************************************
/*!
@file   SceneManager.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Scene.h"


/*  �N���X��`
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


/******************************* �w�b�_�����܂� ******************************/
