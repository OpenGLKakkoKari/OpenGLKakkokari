/*****************************************************************************/
/*!
@file   Score.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Score.h"
#include <math.h>
#include "../Framework/Math/Math.h"
#include "../Framework/Manager.h"
#include "../Framework/NumberSprite.h"


using namespace Framework;
using namespace Framework::Math;
using namespace Game;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

Score::Score() : pNumberList(NULL), value_(0), digits_(6)
{
}

/******************************************************************************
@brief  �f�X�g���N�^
******************************************************************************/

Score::~Score()
{
    if (pNumberList)
    {
        for (int i = 0; i < digits_; i++)
        {
            SAFE_DELETE(pNumberList[i])
        }
        SAFE_DELETE(pNumberList)
    }
}

/******************************************************************************
@brief  ����������
******************************************************************************/

void Score::Init(void)
{
    pNumberList = new NumberSprite*[digits_];
    for (int i = 0; i < digits_; i++)
    {
        pNumberList[i] = new NumberSprite;
    }
}

/******************************************************************************
@brief  �`�揈��
******************************************************************************/

void Score::Update(void)
{

    const Vector2 numberSize = Vector2(size.x / pScore->digits_, size.y);
    const Vector2 numberFirstPos = Vector2(size.x, size.x);

    for (int i = 0; i < digits_; i++)
    {
    }
}

/******************************************************************************
@brief  �X�R�A��������
@param  FileName    �e�N�X�`����
@param  pos         ���W
@param  size        �傫��
@param  polygonNum  �`�文��
@return Score       �����
******************************************************************************/

Score* Score::Create(
    const char* FileName,
    const Vector3& pos,
    const Vector2& size,
    int score)
{
    Score* pScore = new Score;

    pScore->SetValue(score);
    pScore->Init();
    
    const Vector2 numberSize = Vector2(size.x / pScore->digits_, size.y);
    const Vector2 numberFirstPos = Vector2(size.x, size.x);

    for (int i = 0; i < digits_; i++)
    {
    }

    pScore->SetPosition(pos);
    pScore->SetScale(Vector2(size.x, size.y));
    pScore->SetTexture(FileName);
    pScore->SetPolygonNum(polygonNum);

    return pScore;
}
Score* Score::Create(
    const char* FileName,
    const Vector3& pos,
    const Vector2& size)
{
    Score* pScore = new Score;

    pScore->SetPosition(pos);
    pScore->SetScale(Vector2(size.x, size.y));
    pScore->SetTexture(FileName);
    pScore->SetPolygonNum(polygonNum);

    return pScore;
}

/******************************** ���������܂� *******************************/
