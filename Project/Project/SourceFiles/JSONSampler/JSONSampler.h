#pragma once
class JSONSampler
{
};

/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONSampler.h] RapidJSON�T���v���[�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FJSON����T���v���[�N���X
=============================================================================*/
#ifndef JSON_SAMPLER_H_
#define	JSON_SAMPLER_H_

/*--- �C���N���[�h�t�@�C�� ---*/

/*--- �\���̒�` ---*/

/*--- �N���X�̑O���錾 ---*/


/*-------------------------------------
/* RapidJSON�T���v���[�N���X
-------------------------------------*/
class JSONSampler
{
private:
	JSONSampler(void);

public:
	~JSONSampler(void);

	static void LoadJSON(void);
	static void SaveJSON(void);

	//������f�[�^��DOM�ɓn���č\����́A�ǂݍ��ݕ\�����鏈��
	static void DOMParseSample01(void);
	static void DOMParseSample02(void);

	//����������̓��o�̓X�g���[��
	static void MemoryIOStreamingSample(void);

	//�t�@�C������̓��o�̓X�g���[��
	static void FileIOStreamingSample(void);


private:

};

#endif //JSON_SAMPLER_H_
/*=============================================================================
/*		End of File
=============================================================================*/