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
    class Stage;
    class OBB;
}
namespace Game
{
    class GameCamera;
    class Player;
    class MeshField;
    class Timer;
    class Explosion;
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
		static Player* GetPlayer (int index) { return pPlayer[index]; }

    private:
        static GameCamera*              pCamera;
        static Player**                 pPlayer;
        static MeshField*               pMeshField;
        static Timer*                   pTimer;
        static Framework::Stage*        pStage;
        static Framework::Sprite*       pBackground;
        static Framework::Polygon*      pPolygon;
        static Framework::Model*        pModel;
        static Framework::OBB*          pOBB;
        static Explosion*               pExplosion;
    };
}


/******************************* ヘッダここまで ******************************/
