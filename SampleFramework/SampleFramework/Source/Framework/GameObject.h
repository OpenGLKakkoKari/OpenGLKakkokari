#pragma once
/******************************************************************************
/*!
@file   GameObject.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Object.h"


/*  �N���X��`
******************************************************************************/


namespace Framework
{
    class GameObject : public Object
    {
    public:
        GameObject();
        virtual ~GameObject();

        virtual void Init() = 0;
        virtual void Uninit() = 0;

        virtual void Update() = 0;
        static void UpdateAll();
    
    private:
        void RegisterList();
        void UnregisterList();

        static GameObject*  pFirst;
        static GameObject*  pLast;
        static int          allObjectNum;

        GameObject*         pPrev;
        GameObject*         pNext;
    };
}


/****************************** �w�b�_�����܂� *******************************/
