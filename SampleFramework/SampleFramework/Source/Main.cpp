/*****************************************************************************/
/*!
@file    Main.cpp
@author  Yuki Kogawara
@copy    Copyright(C) 2016 Yuki Kogawara

******************************************************************************/


/*  �C���N���[�h
******************************************************************************/


#include "Main.h"
#include "Framework\Manager.h"
#include <crtdbg.h>


using Framework::Manager;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  ���C���֐�
@param  hInstance       �C���X�^���X�n���h��
@param  hPrevInstance   �ߋ���Windows�p
@param  lpCmdLine       �R�}���h���C������󂯎���������ւ̃|�C���^
@param  nCmdShow        �A�v���P�[�V�����̏����E�B���h�E�\�����@��ݒ�
@retval 0               ����I��
@retval ����ȊO        �ُ�I��
******************************************************************************/

int WINAPI WinMain
    (HINSTANCE hInstance, HINSTANCE hPrevInstance,
     LPSTR lpCmdLine, int nCmdShow)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
/**
 * ������
 */

    Manager::Init(hInstance);


/**
 * ���C�����[�v
 */

    Manager::Loop();

    
/**
 * �I������
 */

    Manager::Uninit();
    
    return 0;
}

/******************************* ���������܂� ********************************/
