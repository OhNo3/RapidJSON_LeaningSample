/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONManager.h] JSON�Ǘ��N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FJSON�Ǘ��N���X
=============================================================================*/
#ifndef JSON_MANAGER_H_
#define	JSON_MANAGER_H_

/*--- �C���N���[�h�t�@�C�� ---*/
#include "External/rapidjson/include/document.h"

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------	   
/* JSON�Ǘ��N���X
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