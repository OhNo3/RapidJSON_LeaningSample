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
	//1.文字列データをDOMに渡して構文解析し、読み込み表示する処理
	//JSONSampler::DOMParseSample01();
	//JSONSampler::DOMParseSample02();

	//2.メモリからの入出力表示する処理
	//JSONSampler::MemoryIOStreamingSample();

	//3.ファイルからの入出力表示する処理
	JSONSampler::FileIOStreamingSample();
}

/*-----------------------------------------------------------------------------
/* 読み込み関数
-----------------------------------------------------------------------------*/
void JSONHelper::LoadJSON(void)
{
}

/*-----------------------------------------------------------------------------
/* 書き込み関数
-----------------------------------------------------------------------------*/
void JSONHelper::SaveJSON(void)
{
}


/*=============================================================================
/*		End of File
=============================================================================*/