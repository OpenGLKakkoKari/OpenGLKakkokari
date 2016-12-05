#pragma once
/******************************************************************************
/*!
@file   Graph.h
@brief  Graph Header

@author Yuki Kogawara
@date   2016/05/31 (Tue) Yuki Kogawara

@copy   Copyright(C) 2016 HAL TOKYO All Rights Reserved.

******************************************************************************/


/*  インクルード
******************************************************************************/


#include "../Vertex.h"
#include "../Sprite.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Graph
    {
    public:
        Graph();
        virtual ~Graph();

        void Init(float min, float max, int pNum, Vector2 size, Vector2 pos);
        void Uninit();
        void Draw();

        void SetRange(float min, float max);
        void SetPointNum(int pNum);
        void SetSize(Vector2 size) { this->size = size; }
        void SetPosition(Vector2 pos) { this->pos = pos; }
        void SetColor(Color color);
        void SetBackgroundEnable(bool isEnable);

        void AddPoint(float point);

    private:
        Sprite* pSprite;
        Vertex* pVtx;

        float min;
        float max;
        int pointNum;
        Vector2 pos;
        Vector2 size;

        bool isBackground;

    };
}


/******************************* ヘッダここまで ******************************/
