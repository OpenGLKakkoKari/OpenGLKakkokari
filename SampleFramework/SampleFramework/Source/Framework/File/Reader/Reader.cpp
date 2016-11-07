/*****************************************************************************/
/*!
@file   Reader.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "Reader.h"
using namespace Framework::File;


/*  �ϐ��錾
******************************************************************************/


char Reader::fileName[MAX_PATH];
char Reader::dir[MAX_PATH];
char Reader::ext[16];
int  Reader::fileSize;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �g���q�擾
@param  FilePath        �t�@�C���p�X
******************************************************************************/

void Reader::GetExtension(const char *FilePath)
{
    char ext[256];

    int iterator = 0;
    int extCnt = 0;
    while (FilePath[iterator] != '\0')
    {
        if (FilePath[iterator] == '.')
        {
            extCnt = 0;
            ext[extCnt] = FilePath[iterator];
            iterator++;
            extCnt++;

            while (FilePath[iterator] != '\0' &&
                FilePath[iterator] != '.' &&
                FilePath[iterator] != ' '
                )
            {
                ext[extCnt] = FilePath[iterator];

                extCnt++;
                iterator++;
            }
        }
        iterator++;
    }
    ext[extCnt] = '\0';

    strcpy(Reader::ext, ext);
}

/******************************************************************************
@brief  �J�����g�f�B���N�g���擾
@param  FilePath        �t�@�C���p�X
******************************************************************************/

void Reader::CurrentDirectory(const char *FilePath)
{
    char tmp[MAX_PATH];
    char dir[MAX_PATH];

    int iterator = 0;
    int dirCnt = 0;
    int tmpCnt = 0;

    while (FilePath[iterator] != '\0')
    {
        //dir[dirCnt] = FilePath[iterator];
        //dirCnt++;

        while (FilePath[iterator] != '\0' &&
            FilePath[iterator] != '/' &&
            FilePath[iterator] != '\\'
            )
        {
            tmp[tmpCnt] = FilePath[iterator];
            tmpCnt++;
            iterator++;
        }
        if (FilePath[iterator] != '\0')
        {
            for (int i = 0; i < tmpCnt; i++)
            {
                dir[dirCnt + i] = FilePath[dirCnt + i];
            }
            dirCnt += tmpCnt;
            tmpCnt = 0;
            memset(tmp, 0, MAX_PATH);
        }
        dir[dirCnt] = FilePath[iterator];
        dirCnt++;

        iterator++;
    }
    dir[dirCnt] = '\0';

    strcpy(Reader::dir, dir);
}

/******************************* �֐������܂� ********************************/
