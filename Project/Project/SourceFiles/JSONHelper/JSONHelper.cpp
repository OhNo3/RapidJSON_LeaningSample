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
	//�֐��̒��g�Œ�`�����A�T���v���̌Ăяo���֐�
	JSONSampler::LoadSamples();
}

/*-----------------------------------------------------------------------------
/* JSON��Int�^�����o�v���p�e�B�̎擾�֐�
-----------------------------------------------------------------------------*/
bool JSONHelper::GetInt(const rapidjson::Value& inObject, const char* inPropertyName, int& outInt)
{
	//���̃v���p�e�B�����݂��邩�ǂ������m�F
	auto itr = inObject.FindMember(inPropertyName);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	//�l�̌^���擾���A�����ł��邱�Ƃ��m�F
	auto& property = itr->value;
	if (!property.IsInt())
	{
		return false;
	}

	//�v���p�e�B�̒l���o��
	outInt = property.GetInt();
	return true;
}

/*-----------------------------------------------------------------------------
/* JSON��Float�^�����o�v���p�e�B�̎擾�֐�
-----------------------------------------------------------------------------*/
bool JSONHelper::GetFloat(const rapidjson::Value& inObject, const char* inPropertyName, float& outFloat)
{
	//���̃v���p�e�B�����݂��邩�ǂ������m�F
	auto itr = inObject.FindMember(inPropertyName);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	//�l�̌^���擾���A�����ł��邱�Ƃ��m�F
	auto& property = itr->value;
	if (!property.IsDouble())
	{
		return false;
	}

	//�v���p�e�B�̒l���o��
	outFloat = property.GetDouble();
	return true;
}

/*-----------------------------------------------------------------------------
/* JSON��String�^�����o�v���p�e�B�̎擾�֐�
-----------------------------------------------------------------------------*/
bool JSONHelper::GetString(const rapidjson::Value& inObject, const char* inPropertyName, std::string& outStr)
{
	//���̃v���p�e�B�����݂��邩�ǂ������m�F
	auto itr = inObject.FindMember(inPropertyName);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	//�l�̌^���擾���A�����ł��邱�Ƃ��m�F
	auto& property = itr->value;
	if (!property.IsString())
	{
		return false;
	}

	//�v���p�e�B�̒l���o��
	outStr = property.GetString();
	return true;
}

/*-----------------------------------------------------------------------------
/* JSON��Bool�^�����o�v���p�e�B�̎擾�֐�
-----------------------------------------------------------------------------*/
bool JSONHelper::GetBool(const rapidjson::Value& inObject, const char* inPropertyName, bool& outBool)
{
	//���̃v���p�e�B�����݂��邩�ǂ������m�F
	auto itr = inObject.FindMember(inPropertyName);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	//�l�̌^���擾���A�����ł��邱�Ƃ��m�F
	auto& property = itr->value;
	if (!property.IsBool())
	{
		return false;
	}

	//�v���p�e�B�̒l���o��
	outBool = property.GetBool();
	return true;
}

/*-----------------------------------------------------------------------------
/* JSON��Int�^�����o�v���p�e�B�̒ǉ��֐�
-----------------------------------------------------------------------------*/
void JSONHelper::AddInt(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* inPropertyName, int value)
{
	rapidjson::Value v(value);
	inObject.AddMember(rapidjson::StringRef(inPropertyName), v, alloc);
}

/*-----------------------------------------------------------------------------
/* JSON��Float�^�����o�v���p�e�B�̒ǉ��֐�
-----------------------------------------------------------------------------*/
void JSONHelper::AddFloat(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* inPropertyName, float value)
{
	rapidjson::Value v(value);
	inObject.AddMember(rapidjson::StringRef(inPropertyName), v, alloc);
}

/*-----------------------------------------------------------------------------
/* JSON��String�^�����o�v���p�e�B�̒ǉ��֐�
-----------------------------------------------------------------------------*/
void JSONHelper::AddString(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* inPropertyName, const std::string& value)
{
	rapidjson::Value v;
	v.SetString(value.c_str()
				, static_cast<rapidjson::SizeType>(value.length())
				, alloc);
	inObject.AddMember(rapidjson::StringRef(inPropertyName), v, alloc);
}

/*-----------------------------------------------------------------------------
/* JSON��Bool�^�����o�v���p�e�B�̒ǉ��֐�
-----------------------------------------------------------------------------*/
void JSONHelper::AddBool(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* inPropertyName, bool value)
{
	rapidjson::Value v(value);
	inObject.AddMember(rapidjson::StringRef(inPropertyName), v, alloc);
}

/*=============================================================================
/*		End of File
=============================================================================*/