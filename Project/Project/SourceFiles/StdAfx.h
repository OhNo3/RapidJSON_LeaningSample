/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[StdAfx.h] �W���g���t���[�����[�N
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����F�t�@�C���̃C���N���[�h�Ȃ�
=============================================================================*/
#ifndef STDAFX_H_
#define	STDAFX_H_

#define _CRT_SECURE_NO_WARNINGS

/*--- �C���N���[�h�t�@�C�� ---*/
#include <iostream>
#include <fstream>
#include <string>
#include <functional>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>


/*--- RapidJSON�̃C���N���[�h ---*/

//RapidJSON���̂���
#include "External/rapidjson/include/document.h"
//��������
#include "External/rapidjson/include/writer.h"
#include "External/rapidjson/include/filewritestream.h"	//�C���f���g�E���s�Ȃ�
#include "External/rapidjson/include/prettywriter.h"	//�C���f���g�E���s����
//�ǂݍ���
#include "External/rapidjson/include/reader.h"
#include "External/rapidjson/include/filereadstream.h"
//�G���[�n���h��
#include "External/rapidjson/include/error/error.h"
#include "External/rapidjson/include/error/en.h"		//�p���p


/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/



#endif //STDAFX_H_
/*=============================================================================
/*		End of File
=============================================================================*/