/******************************************************************************
/*!
@file   SceneManager.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �N���X��`
******************************************************************************/


namespace Framework
{
    class Scene;
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
