/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONHelper.cpp] RapidJSON�w���p�[�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FRapidJSON�w���p�[�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"
#include "JSONHelper.h"
#include "../JSONSampler/JSONSampler.h"

//RapidJSON��JSON�t�@�C���������ɍ\����͂��邽�߂�API

//RapidJSON���̂���
#include "../External/rapidjson/include/document.h"
//��������
#include "../External/rapidjson/include/writer.h"
#include "../External/rapidjson/include/filewritestream.h"
//�ǂݍ���
#include "../External/rapidjson/include/reader.h"
#include "../External/rapidjson/include/filereadstream.h"
//�G���[�n���h��
#include "../External/rapidjson/include/error/en.h"

#include "../External/rapidjson/include/prettywriter.h"


using namespace rapidjson;

/*-----------------------------------------------------------------------------
/* �R���X�g���N�^
-----------------------------------------------------------------------------*/
JSONHelper::JSONHelper(void)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
JSONHelper::~JSONHelper(void)
{
}

/*-----------------------------------------------------------------------------
/* �֐��T���v���Q�̌Ăяo���֐�
-----------------------------------------------------------------------------*/
void JSONHelper::RapidJSONSampler(void)
{
	//1.������f�[�^��DOM�ɓn���č\����͂��A�ǂݍ��ݕ\�����鏈��
	//JSONSampler::DOMParseSample01();
	//JSONSampler::DOMParseSample02();

	//2.����������̓��o�͕\�����鏈��
	//JSONSampler::MemoryIOStreamingSample();

	//3.�t�@�C������̓��o�͕\�����鏈��
	JSONSampler::FileIOStreamingSample();
}

/*-----------------------------------------------------------------------------
/* �ǂݍ��݊֐�
-----------------------------------------------------------------------------*/
void JSONHelper::LoadJSON(void)
{
}

/*-----------------------------------------------------------------------------
/* �������݊֐�
-----------------------------------------------------------------------------*/
void JSONHelper::SaveJSON(void)
{
}


/*=============================================================================
/*		End of File
=============================================================================*/