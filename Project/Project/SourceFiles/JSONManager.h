/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONManager.h] JSON管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：JSON管理クラス
=============================================================================*/
#ifndef JSON_MANAGER_H_
#define	JSON_MANAGER_H_

/*--- インクルードファイル ---*/
#include "External/rapidjson/include/document.h"

/*--- 構造体定義 ---*/

/*--- クラスの前方宣言 ---*/


/*-------------------------------------	   
/* JSON管理クラス
-------------------------------------*/
class JSONManager
{
private:
	JSONManager(void);

public:
	~JSONManager(void);

	static bool LoadJSON(const std::string& inFileName, rapidjson::Document& outDoc);
	static void SaveJSON(const std::string& inFileName);

public:
	static void GenarateNewJSONFile(const std::string& inFileName);
	
};

#endif //JSON_MANAGER_H_
/*=============================================================================
/*		End of File
=============================================================================*/