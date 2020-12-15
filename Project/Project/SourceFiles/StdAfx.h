/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StdAfx.h] 標準拡張フレームワーク
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：ファイルのインクルードなど
=============================================================================*/
#ifndef STDAFX_H_
#define	STDAFX_H_

#define _CRT_SECURE_NO_WARNINGS

/*--- インクルードファイル ---*/
#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>


/*--- RapidJSONのインクルード ---*/

//RapidJSONそのもの
#include "External/rapidjson/include/document.h"
//書き込み
#include "External/rapidjson/include/writer.h"
#include "External/rapidjson/include/filewritestream.h"	//インデント・改行なし
#include "External/rapidjson/include/prettywriter.h"	//インデント・改行あり
//読み込み
#include "External/rapidjson/include/reader.h"
#include "External/rapidjson/include/filereadstream.h"
//エラーハンドル
#include "External/rapidjson/include/error/error.h"
#include "External/rapidjson/include/error/en.h"		//英語専用


/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/



#endif //STDAFX_H_
/*=============================================================================
/*		End of File
=============================================================================*/