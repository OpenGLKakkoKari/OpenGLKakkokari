#pragma once
/*****************************************************************************/
/*!
@file   Stage.h
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "GameObject.h"


/*  �N���X��`
******************************************************************************/


namespace Game
{
    class Field;
    class Skybox;
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

        int fieldNum;
        int modelNum;
        int plantNum;
        int obbNum;

        Game::Skybox*       pSkybox;
        Game::Field**       pFieldList;
        Model**             pModelList;
        Game::Plant**       pPlantList;
        OBB**               pOBBList;
    };
}


/****************************** �w�b�_�����܂� *******************************/
