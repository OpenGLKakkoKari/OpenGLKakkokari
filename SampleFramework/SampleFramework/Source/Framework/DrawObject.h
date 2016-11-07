#pragma once
/******************************************************************************
/*!
@file   DrawObject.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "Object.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class DrawObject : public Object
    {
    public:
        enum Type
        {
            TYPE_MESH = 0,
            TYPE_ALPHAMESH,
            TYPE_SPRITE,

            TYPE_MAX
        };

        DrawObject();
        DrawObject(Type type);
        virtual ~DrawObject();

        virtual void Draw() = 0;
        static void DrawAll();

        void    SetPriority(int priority)       { this->priority = priority; }
        void SetType(Type newType);

    private:
        static void ZSort(int idxL, int idxR, DrawObject** pDrawObjectList);
        static void PrioritySort(int idxL, int idxR, DrawObject** pDrawObjectList);

        void RegisterList();
        void UnregisterList();
        float GetZ();

        static DrawObject*  pFirst[TYPE_MAX];
        static DrawObject*  pLast[TYPE_MAX];
        static int          objectNum[TYPE_MAX];
        static int          allObjectNum;
        static Matrix       viewMatrix;

        int                 priority;
        Type                type;
        DrawObject*         pPrev;
        DrawObject*         pNext;
    };
}


/****************************** ヘッダここまで *******************************/
