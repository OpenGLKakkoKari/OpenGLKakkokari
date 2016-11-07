/*****************************************************************************/
/*!
@file   TextureReader.cpp
@author Yuki Kogawara
@copy   Copyright(C) 2016 Yuki Kogawara

******************************************************************************/

/*  �C���N���[�h
******************************************************************************/


#include "TextureReader.h"
#include "../File.h"
#include "../../Error.h"

using Framework::File::File;
using Framework::File::TextureReader;
using Framework::Texture;
using Framework::Error;


/*  �ÓI�ϐ��錾
******************************************************************************/


bool TextureReader::reverse;


/*  ����
******************************************************************************/

/******************************************************************************
@brief  �t�@�C���ǂݍ���
@param  FileName    �t�@�C����
@param  reverse     ���]�t���O
@return Texture*    �e�N�X�`�����
******************************************************************************/

Texture* TextureReader::Load(const char *FileName, bool reverse)
{

    TextureReader::reverse = reverse;
    strcpy(fileName, FileName);
    GetExtension(FileName);

    if (strcmp(ext, ".bmp") == 0)
    {
        return LoadBMP(FileName);
    }
    else if (strcmp(ext, ".jpg") == 0 ||
        strcmp(ext, ".jpeg") == 0)
    {
        return LoadJPG(FileName);
    }
    else if (strcmp(ext, ".png") == 0)
    {
        return LoadPNG(FileName);
    }
    else if (strcmp(ext, ".tga") == 0)
    {
        return LoadTGA(FileName);
    }

    return NULL;
}

/******************************************************************************
@brief  BMP�t�@�C���ǂݍ���
@param  FileName    �t�@�C����
@return Texture*    �e�N�X�`��
******************************************************************************/

Texture* TextureReader::LoadBMP(const char *FileName)
{
    Texture* pTex;
    BITMAPFILEHEADER bmpFileHeader;
    BITMAPINFOHEADER bmpInfoHeader;
    BITMAPCOREHEADER bmpCoreHeader;

    // �t�@�C���ǂݍ���
    File file;
    if (!file.Open(FileName, "rb"))
    {
        Error::Message("�t�@�C��\"%s\"�̓ǂݍ��݂Ɏ��s���܂����B", FileName);
        return NULL;
    }
    pTex = new Texture;

    // �t�@�C���w�b�_�[�ǂݍ���
    file.Read(&bmpFileHeader, sizeof(BITMAPFILEHEADER), 1);

    // ���w�b�_�[�̃T�C�Y��ǂݍ���
    unsigned long biSize;
    file.Read(&biSize, sizeof(unsigned long), 1);
    // ���w�b�_�[�̐擪�Ɉړ�
    file.Seek(sizeof(BITMAPFILEHEADER), SEEK_SET);

    // ���w�b�_�[�ǂݍ���
    if (biSize == sizeof(BITMAPINFOHEADER))
    {
        file.Read(&bmpInfoHeader, sizeof(BITMAPINFOHEADER), 1);
        // �e�N�X�`�����ݒ�
        pTex->SetInfo(
            (bmpInfoHeader.biBitCount == 32) ? (Texture::RGBA8888) : (Texture::RGBX8888),
            bmpInfoHeader.biWidth,
            bmpInfoHeader.biHeight,
            32);
    }
    else if (biSize == sizeof(BITMAPCOREHEADER))
    {
        file.Read(&bmpCoreHeader, sizeof(BITMAPCOREHEADER), 1);
        // �e�N�X�`�����ݒ�
        pTex->SetInfo(
            (bmpCoreHeader.bcBitCount == 32) ? (Texture::RGBA8888) : (Texture::RGBX8888),
            bmpCoreHeader.bcWidth,
            bmpCoreHeader.bcHeight,
            32);
    }
    else
        return pTex;


    // �o�b�t�@�m��
    unsigned char *pNewBuf = new unsigned char[pTex->info.bufferSize];
    file.Seek(bmpFileHeader.bfOffBits, SEEK_SET);

    // �f�[�^�ǂݍ���
    switch (pTex->info.format)
    {
    case Texture::RGBA8888:
        for (unsigned int y = 0; y < pTex->info.height; y++)
        {
            for (unsigned int x = 0; x < pTex->info.width; x++)
            {
                pNewBuf[pTex->info.pitch*y + 4 * x + 2] = file.GetByte(); // B
                pNewBuf[pTex->info.pitch*y + 4 * x + 1] = file.GetByte(); // G
                pNewBuf[pTex->info.pitch*y + 4 * x + 0] = file.GetByte(); // R
                pNewBuf[pTex->info.pitch*y + 4 * x + 3] = file.GetByte(); // A
            }
        }
        break;

    case Texture::RGBX8888:
        for (unsigned int y = 0; y < pTex->info.height; y++)
        {
            for (unsigned int x = 0; x < pTex->info.width; x++)
            {
                pNewBuf[pTex->info.pitch*y + 4 * x + 2] = file.GetByte(); // R
                pNewBuf[pTex->info.pitch*y + 4 * x + 1] = file.GetByte(); // G
                pNewBuf[pTex->info.pitch*y + 4 * x + 0] = file.GetByte(); // B
                pNewBuf[pTex->info.pitch*y + 4 * x + 3] = 255;            // A
            }
        }
        break;
    }
    pTex->pData = pNewBuf;

    // �㉺���]
    ReverseDataUV(pTex);

    // �F���]
    if (reverse)
        ReverseDataColor(pTex);

    file.Close();

    return pTex;
}

/******************************************************************************
@brief  TGA�t�@�C���ǂݍ���
@param  FileName    �t�@�C����
@return Texture*    �e�N�X�`��
******************************************************************************/

Texture* TextureReader::LoadTGA(const char *FileName)
{
    Texture* pTex;
    TGAHeader tga;

    // �t�@�C���ǂݍ���
    File file;
    if (!file.Open(FileName, "rb"))
    {
        Error::Message("�t�@�C��\"%s\"�̓ǂݍ��݂Ɏ��s���܂����B", FileName);
        return NULL;
    }
    pTex = new Texture;

    // �w�b�_�[�ǂݍ���
    file.Read(&tga, sizeof(TGAHeader), 1);

    // �e�N�X�`�����ݒ�
    pTex->SetInfo(
        (tga.bbp == 32) ? (Texture::RGBA8888) : (Texture::RGBX8888),
        tga.imageWidth,
        tga.imageHeight,
        32);

    // �o�b�t�@�m��
    unsigned char *pNewBuf = new unsigned char[pTex->info.bufferSize];
    file.Read(pNewBuf, sizeof(unsigned char)*pTex->info.bufferSize, 1);
    file.Seek(sizeof(TGAHeader), SEEK_SET);

    // �f�[�^�ǂݍ���
    switch (pTex->info.format)
    {
    case Texture::RGBA8888:
        for (unsigned int y = 0; y < pTex->info.height; y++)
        {
            for (unsigned int x = 0; x < pTex->info.width; x++)
            {
                pNewBuf[pTex->info.pitch*y + 4 * x + 2] = file.GetByte(); // B
                pNewBuf[pTex->info.pitch*y + 4 * x + 1] = file.GetByte(); // G
                pNewBuf[pTex->info.pitch*y + 4 * x + 0] = file.GetByte(); // R
                pNewBuf[pTex->info.pitch*y + 4 * x + 3] = file.GetByte(); // A
            }
        }
        break;

    case Texture::RGBX8888:
        for (unsigned int y = 0; y < pTex->info.height; y++)
        {
            for (unsigned int x = 0; x < pTex->info.width; x++)
            {
                pNewBuf[pTex->info.pitch*y + 4 * x + 2] = file.GetByte(); // B
                pNewBuf[pTex->info.pitch*y + 4 * x + 1] = file.GetByte(); // G
                pNewBuf[pTex->info.pitch*y + 4 * x + 0] = file.GetByte(); // R
                pNewBuf[pTex->info.pitch*y + 4 * x + 3] = 255;            // A
            }
        }
        break;
    }
    pTex->pData = pNewBuf;

    // �㉺���]
    ReverseDataUV(pTex);

    // �F���]
    if (reverse)
        ReverseDataColor(pTex);

    file.Close();

    return pTex;
}

/******************************************************************************
@brief  JPG�t�@�C���ǂݍ���
@param  FileName    �t�@�C����
@return Texture*    �e�N�X�`��
******************************************************************************/

Texture* TextureReader::LoadJPG(const char *FileName)
{
    FILE *fp;
    Texture* pTex;
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    // �t�@�C���ǂݍ���
    if ((fp = fopen(FileName, "rb")) == NULL)
    {
        Error::Message("�t�@�C��\"%s\"�̓ǂݍ��݂Ɏ��s���܂����B", FileName);
        return NULL;
    }
    pTex = new Texture;

    // JPEG�I�u�W�F�N�g�̏�����
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);
    // JPEG�t�@�C�����J��
    jpeg_stdio_src(&cinfo, fp);
    // JPEG�w�b�_�̓ǂݍ���
    jpeg_read_header(&cinfo, TRUE);

    // �e�N�X�`�����ݒ�
    pTex->SetInfo(
        Texture::RGBX8888,
        cinfo.image_width,
        cinfo.image_height,
        32);

    jpeg_start_decompress(&cinfo);

    // �C���[�W��ێ����郁�����̈�̊m�ۂƏ�����
    unsigned char* pNewBuf = new unsigned char[pTex->info.bufferSize / 4 * 3];
    unsigned char * rowptr[1];
    while (cinfo.output_scanline < cinfo.output_height) // loop
    {
        // Enable jpeg_read_scanlines() to fill our jdata array
        rowptr[0] = (unsigned char *)pNewBuf +  // secret to method
            3 * cinfo.output_width * cinfo.output_scanline;
        jpeg_read_scanlines(&cinfo, rowptr, 1);
    }

    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);
    
    unsigned char *pBuf = new unsigned char[pTex->info.bufferSize];
    for (unsigned int y = 0; y < pTex->info.height; y++)
    {
        for (unsigned int x = 0; x < pTex->info.width; x++)
        {
            pBuf[pTex->info.pitch*y + 4 * x + 2] = pNewBuf[pTex->info.width * 3 * y + 3 * x + 2]; // B
            pBuf[pTex->info.pitch*y + 4 * x + 1] = pNewBuf[pTex->info.width * 3 * y + 3 * x + 1]; // G
            pBuf[pTex->info.pitch*y + 4 * x + 0] = pNewBuf[pTex->info.width*3*y + 3 * x + 0]; // R
            pBuf[pTex->info.pitch*y + 4 * x + 3] = 255; // A
        }
    }

    delete[] pNewBuf;
    fclose(fp);
    pTex->pData = pBuf;

    // �F���]
    if (reverse)
        ReverseDataColor(pTex);

    return pTex;

}

/******************************************************************************
@brief  PNG�t�@�C���ǂݍ���
@param  FileName    �t�@�C����
@return Texture*    �e�N�X�`��
******************************************************************************/

Texture* TextureReader::LoadPNG(const char *FileName)
{
    FILE *fp;
    Texture* pTex;
    if ((fp = fopen(FileName, "rb")) == NULL)
    {
        Error::Message("�t�@�C��\"%s\"�̓ǂݍ��݂Ɏ��s���܂����B", FileName);
        return NULL;
    }
    pTex = new Texture;

    const unsigned int headerSize = 8;

    png_structp pPng;
    png_infop pInfo;
    png_uint_32 Width, Height;
    int nBitDepth, nColorType, nInterlaceType;

    // png_struct �\���̂̏�����
    pPng = png_create_read_struct(
        PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    // png_info �\���̂̏������i�摜�f�[�^�̑O�ɂ���`�����N�p�j
    pInfo = png_create_info_struct(pPng);
    png_init_io(pPng, fp);
    png_read_info(pPng, pInfo);
    png_get_IHDR(pPng, pInfo, &Width, &Height,
        &nBitDepth, &nColorType, &nInterlaceType,
        NULL, NULL);

    pTex->info.width = Width;
    pTex->info.height = Height;
    pTex->info.format = (nBitDepth == 8) ? (Texture::RGBA8888) : (Texture::RGBX8888);
    pTex->info.bufferSize = (nBitDepth == 8) ? (Width*Height * 4) : (Width*Height * 3);
    pTex->info.pitch = (nBitDepth == 8) ? (Width * 4) : (Width * 3);
    pTex->info.bit = nBitDepth * 4;

    // �������̈�m��
    int rb = png_get_rowbytes(pPng, pInfo);
    unsigned char *pNewBuf = new unsigned char[Height * rb];
    unsigned char **recv = new unsigned char*[Height];
    for (unsigned int i = 0; i < Height; i++)
        recv[i] = &pNewBuf[i * rb];
    png_read_image(pPng, recv);
    png_read_end(pPng, pInfo);
    png_destroy_read_struct(&pPng, &pInfo, NULL);
    delete[] recv;

    fclose(fp);
    pTex->pData = pNewBuf;

    // �F���]
    if (reverse)
        ReverseDataColor(pTex);

    return pTex;
}

/******************************************************************************
@brief  �f�[�^���㉺���΂ɂ���
@param  tex         �e�N�X�`��
@return Texture     �㉺���]�����e�N�X�`��
******************************************************************************/

void TextureReader::ReverseDataUV(Texture *pTex)
{
    // �㉺���]
    for (unsigned int y = 0; y < pTex->info.height / 2; y++)
    {
        for (unsigned int x = 0; x < pTex->info.width; x++)
        {
            unsigned char *pNewBuf = (unsigned char*)pTex->pData;

            unsigned char b = pNewBuf[pTex->info.pitch*y + 4 * x + 2];
            unsigned char g = pNewBuf[pTex->info.pitch*y + 4 * x + 1];
            unsigned char r = pNewBuf[pTex->info.pitch*y + 4 * x + 0];
            unsigned char a = pNewBuf[pTex->info.pitch*y + 4 * x + 3];

            pNewBuf[pTex->info.pitch*y + 4 * x + 2] = pNewBuf[pTex->info.pitch*(pTex->info.height - y - 1) + 4 * x + 2];
            pNewBuf[pTex->info.pitch*y + 4 * x + 1] = pNewBuf[pTex->info.pitch*(pTex->info.height - y - 1) + 4 * x + 1];
            pNewBuf[pTex->info.pitch*y + 4 * x + 0] = pNewBuf[pTex->info.pitch*(pTex->info.height - y - 1) + 4 * x + 0];
            pNewBuf[pTex->info.pitch*y + 4 * x + 3] = pNewBuf[pTex->info.pitch*(pTex->info.height - y - 1) + 4 * x + 3];

            pNewBuf[pTex->info.pitch*(pTex->info.height - y - 1) + 4 * x + 2] = b;
            pNewBuf[pTex->info.pitch*(pTex->info.height - y - 1) + 4 * x + 1] = g;
            pNewBuf[pTex->info.pitch*(pTex->info.height - y - 1) + 4 * x + 0] = r;
            pNewBuf[pTex->info.pitch*(pTex->info.height - y - 1) + 4 * x + 3] = a;
        }
    }
}

/******************************************************************************
@brief  �f�[�^�̐F��R��B�𔽑΂ɂ���
@param  tex         �e�N�X�`��
@return Texture     �㉺���]�����e�N�X�`��
******************************************************************************/

void TextureReader::ReverseDataColor(Texture *pTex)
{
    // �F���]
    for (unsigned int y = 0; y < pTex->info.height; y++)
    {
        for (unsigned int x = 0; x < pTex->info.width; x++)
        {
            unsigned char *pNewBuf = (unsigned char*)pTex->pData;

            unsigned char b = pNewBuf[pTex->info.pitch*y + 4 * x + 2];
            unsigned char r = pNewBuf[pTex->info.pitch*y + 4 * x + 0];

            pNewBuf[pTex->info.pitch*y + 4 * x + 2] = r;
            pNewBuf[pTex->info.pitch*y + 4 * x + 0] = b;
        }
    }
}

/******************************* �֐������܂� ********************************/
