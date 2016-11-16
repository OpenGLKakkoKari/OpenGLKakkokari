#pragma once
/******************************************************************************
/*!
@file   GameScene.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  インクルード
******************************************************************************/


#include "../Framework/Scene.h"


/*  クラス定義
******************************************************************************/


namespace Framework
{
    class Polygon;
    class Sprite;
    class Model;
    class Effect;
    class Stage;
    class OBB;
}
namespace Game
{
    class GameCamera;
    class Character;
    class MeshField;
    class GameScene : public Framework::Scene
    {
    public:
        enum { CHARACTER_MAX = 4 };

        GameScene();
        ~GameScene();

        void Init();
        void Uninit();
        void Update();

        static GameCamera* GetCamera() { return pCamera; }
        static Character* GetCharacter(int index) { return pCharacter[index]; }

    private:
        static GameCamera*              pCamera;
        static Character**              pCharacter;
        static MeshField*              pMeshField;
        static Framework::Stage*        pStage;
        static Framework::Sprite*       pBackground;
        static Framework::Polygon*      pPolygon;
        static Framework::Model*        pModel;
        static Framework::OBB*          pOBB;
        static Framework::Effect*       pEffect;
    };
}


/******************************* ヘッダここまで ******************************/
