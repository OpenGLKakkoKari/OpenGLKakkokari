/*****************************************************************************/
/*!
@file   BinaryWriter.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "BinaryWriter.h"
#include "../File.h"

using Framework::File::BinaryWriter;
using Framework::File::File;


/*  �ϐ��錾
******************************************************************************/


char BinaryWriter::fileName[MAX_PATH];
char BinaryWriter::ext[16];
int  BinaryWriter::fileSize;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �t�@�C����������
@param  FileName        �t�@�C���p�X
@param  pData           �������ރf�[�^
@param  size            �������ރT�C�Y
******************************************************************************/

void BinaryWriter::Write(const char *FileName, void *pData, int size)
{
    File file;
    if (file.Open(FileName, "wb"))
    {
        printf("%s file open error!!\n", FileName);
    }

    file.Seek(0, SEEK_SET);
    file.Write(pData, size, 1);

    file.Close();
}

/******************************* �֐������܂� ********************************/
