/******************************************************************************
/*!
@file   TokenAnalyzer.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "TokenAnalyzer.h"
#include <string.h>
#include <stdlib.h>


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �R���X�g���N�^
******************************************************************************/

TokenAnalyzer::TokenAnalyzer(const char* string) : str(string), pos(0)
{
    strcpy_s(token, TOKEN_SIZE, "");
    strcpy_s(skipChars, SKIPCHAR_SIZE, " \t\n\r,;\"");
}

/******************************************************************************
@brief  �X�L�b�v���镶�����ݒ�
@param  skipChars   �X�L�b�v����P��̕�����
******************************************************************************/

void TokenAnalyzer::SetSkipChars(const char* skipChars)
{
    strcpy_s(this->skipChars, SKIPCHAR_SIZE, skipChars);
}

/******************************************************************************
@brief  �g�[�N���̎擾
@return char*   �擾�����g�[�N��
******************************************************************************/

char* TokenAnalyzer::GetToken()
{
    // �g�[�N����������
    memset(token, '\0', TOKEN_SIZE);

    char *q = token;

    // ���݂̕������X�L�b�v�����łȂ�����g�[�N���Ɋi�[
    while (!IsScriptEnd() && !strchr(skipChars, str[pos]))
    {
        // �������g�[�N�����Ɋi�[
        *q = str[pos];
        if (*q == '#')
        {
            while (str[pos] != '\n')
            {
                *q = str[pos];
                q++;
                pos++;
            }
            break;
        }
        q++;
        // ���̕����𒲂ׂ�
        pos++;
    }
    // ���݂̕������X�L�b�v�����̏ꍇ�i��
    while (!IsScriptEnd() && strchr(skipChars, str[pos]))
    {
        // ���̕����𒲂ׂ�
        pos++;
    }

    return token;
}

/******************************************************************************
@brief  ���������_�^�̒l�𕶎��񂩂�擾
@return float   �擾�������������_�^�̒l
******************************************************************************/

float TokenAnalyzer::GetFloatToken()
{
    GetToken();
    return (float)atof(token);
}

/******************************************************************************
@brief  ��������̐����^�̒l�𕶎��񂩂�擾
@return float   �擾������������̐����^�̒l
******************************************************************************/

int TokenAnalyzer::GetIntToken()
{
    GetToken();
    return (int)atoi(token);
}

/******************************************************************************
@brief  �g�[�N���ƕ�������r
@param  cmpStr      ��r������
@retval true        �g�[�N���Ɣ�r�����񂪈�v
@retval false       �g�[�N���Ɣ�r�����񂪕s��v
******************************************************************************/

bool TokenAnalyzer::CheckToken(const char* cmpStr)
{
    if (strcmp(token, cmpStr) == 0)
        return true;
    else
        return false;
}

/******************************************************************************
@brief  �g���ʂ̃u���b�N���΂�
******************************************************************************/

void TokenAnalyzer::SkipBracket()
{
    while (!IsScriptEnd())
    {
        GetToken();
        if (strchr(token, '{')) break;
    }
    // ���݂̊K�w�J�E���^�[
    // �[���Ȃ�x��+1
    // ������x��  -1

    int count = 1;
    while (!IsScriptEnd() && count > 0)
    {
        GetToken();
        if (strchr(token, '{')) count++;
        else if (strchr(token, '}')) count--;
    }
    if (count > 0)
    {
        return;
    }
}

/******************************** ���������܂� *******************************/
