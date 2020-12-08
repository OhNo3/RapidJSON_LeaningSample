#pragma once
class JSONSampler
{
};

/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONSampler.h] RapidJSONサンプラークラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：JSON操作サンプラークラス
=============================================================================*/
#ifndef JSON_SAMPLER_H_
#define	JSON_SAMPLER_H_

/*--- インクルードファイル ---*/

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------
/* RapidJSONサンプラークラス
-------------------------------------*/
class JSONSampler
{
private:
	JSONSampler(void);

public:
	~JSONSampler(void);

	static void LoadJSON(void);
	static void SaveJSON(void);

	//文字列データをDOMに渡して構文解析、読み込み表示する処理
	static void DOMParseSample01(void);
	static void DOMParseSample02(void);

	//メモリからの入出力ストリーム
	static void MemoryIOStreamingSample(void);

	//ファイルからの入出力ストリーム
	static void FileIOStreamingSample(void);


private:

};

#endif //JSON_SAMPLER_H_
/*=============================================================================
/*		End of File
=============================================================================*/