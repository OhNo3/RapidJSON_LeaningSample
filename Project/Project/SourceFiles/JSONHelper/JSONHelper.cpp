/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONHelper.cpp] RapidJSONヘルパークラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：RapidJSONヘルパークラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "JSONHelper.h"
#include "../JSONSampler/JSONSampler.h"

//RapidJSONはJSONファイルを高速に構文解析するためのAPI

//RapidJSONそのもの
#include "../External/rapidjson/include/document.h"
//書き込み
#include "../External/rapidjson/include/writer.h"
#include "../External/rapidjson/include/filewritestream.h"
//読み込み
#include "../External/rapidjson/include/reader.h"
#include "../External/rapidjson/include/filereadstream.h"
//エラーハンドル
#include "../External/rapidjson/include/error/en.h"

#include "../External/rapidjson/include/prettywriter.h"


using namespace rapidjson;

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
JSONHelper::JSONHelper(void)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
JSONHelper::~JSONHelper(void)
{
}

/*-----------------------------------------------------------------------------
/* 関数サンプル群の呼び出し関数
-----------------------------------------------------------------------------*/
void JSONHelper::RapidJSONSampler(void)
{
	//関数の中身で定義した、サンプルの呼び出し関数
	JSONSampler::LoadSamples();
}

/*-----------------------------------------------------------------------------
/* JSONのInt型メンバプロパティの取得関数
-----------------------------------------------------------------------------*/
bool JSONHelper::GetInt(const rapidjson::Value& inObject, const char* inPropertyName, int& outInt)
{
	//このプロパティが存在するかどうかを確認
	auto itr = inObject.FindMember(inPropertyName);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	//値の型を取得し、整数であることを確認
	auto& property = itr->value;
	if (!property.IsInt())
	{
		return false;
	}

	//プロパティの値を出力
	outInt = property.GetInt();
	return true;
}

/*-----------------------------------------------------------------------------
/* JSONのFloat型メンバプロパティの取得関数
-----------------------------------------------------------------------------*/
bool JSONHelper::GetFloat(const rapidjson::Value& inObject, const char* inPropertyName, float& outFloat)
{
	//このプロパティが存在するかどうかを確認
	auto itr = inObject.FindMember(inPropertyName);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	//値の型を取得し、整数であることを確認
	auto& property = itr->value;
	if (!property.IsDouble())
	{
		return false;
	}

	//プロパティの値を出力
	outFloat = property.GetDouble();
	return true;
}

/*-----------------------------------------------------------------------------
/* JSONのString型メンバプロパティの取得関数
-----------------------------------------------------------------------------*/
bool JSONHelper::GetString(const rapidjson::Value& inObject, const char* inPropertyName, std::string& outStr)
{
	//このプロパティが存在するかどうかを確認
	auto itr = inObject.FindMember(inPropertyName);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	//値の型を取得し、整数であることを確認
	auto& property = itr->value;
	if (!property.IsString())
	{
		return false;
	}

	//プロパティの値を出力
	outStr = property.GetString();
	return true;
}

/*-----------------------------------------------------------------------------
/* JSONのBool型メンバプロパティの取得関数
-----------------------------------------------------------------------------*/
bool JSONHelper::GetBool(const rapidjson::Value& inObject, const char* inPropertyName, bool& outBool)
{
	//このプロパティが存在するかどうかを確認
	auto itr = inObject.FindMember(inPropertyName);
	if (itr == inObject.MemberEnd())
	{
		return false;
	}

	//値の型を取得し、整数であることを確認
	auto& property = itr->value;
	if (!property.IsBool())
	{
		return false;
	}

	//プロパティの値を出力
	outBool = property.GetBool();
	return true;
}

/*-----------------------------------------------------------------------------
/* JSONのInt型メンバプロパティの追加関数
-----------------------------------------------------------------------------*/
void JSONHelper::AddInt(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* inPropertyName, int value)
{
	rapidjson::Value v(value);
	inObject.AddMember(rapidjson::StringRef(inPropertyName), v, alloc);
}

/*-----------------------------------------------------------------------------
/* JSONのFloat型メンバプロパティの追加関数
-----------------------------------------------------------------------------*/
void JSONHelper::AddFloat(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* inPropertyName, float value)
{
	rapidjson::Value v(value);
	inObject.AddMember(rapidjson::StringRef(inPropertyName), v, alloc);
}

/*-----------------------------------------------------------------------------
/* JSONのString型メンバプロパティの追加関数
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
/* JSONのBool型メンバプロパティの追加関数
-----------------------------------------------------------------------------*/
void JSONHelper::AddBool(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject, const char* inPropertyName, bool value)
{
	rapidjson::Value v(value);
	inObject.AddMember(rapidjson::StringRef(inPropertyName), v, alloc);
}

/*=============================================================================
/*		End of File
=============================================================================*/