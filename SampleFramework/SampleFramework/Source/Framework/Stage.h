#pragma once
/*****************************************************************************/
/*!
@file   Stage.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  インクルード
******************************************************************************/


#include "GameObject.h"


/*  クラス定義
******************************************************************************/


namespace Game
{
    class MeshField;
    class Plant;
}
namespace Framework
{
    class Model;
    class OBB;
    class Stage : public GameObject
    {
    public:
        Stage();
        ~Stage();

        void Init(){}
        void Uninit(){}
        void Update();

        int modelNum;
        int plantNum;
        int obbNum;
        
        Game::MeshField*    pMeshField;
        Model**             pModelList;
        Game::Plant**       pPlantList;
        OBB**               pOBBList;
    };
}


/****************************** ヘッダここまで *******************************/
