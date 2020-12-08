/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONSampler.cpp] RapidJSON�w���p�[�N���X
/*	Author�FKousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	�����FRapidJSON�w���p�[�N���X
=============================================================================*/

/*--- �C���N���[�h�t�@�C�� ---*/
#include "../StdAfx.h"
#include "JSONSampler.h"

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
JSONSampler::JSONSampler(void)
{
}

/*-----------------------------------------------------------------------------
/* �f�X�g���N�^
-----------------------------------------------------------------------------*/
JSONSampler::~JSONSampler(void)
{
}

/*-----------------------------------------------------------------------------
/* �ǂݍ��݊֐�
-----------------------------------------------------------------------------*/
void JSONSampler::LoadJSON(void)
{
    //������f�[�^��DOM�ɓn���ĉ�͂��A�ǂݍ��ݕ\�����鏈��
    //JSONSampler::DOMParseSample01();
    //JSONSampler::DOMParseSample02();

    //����������̓��o�͕\�����鏈��
    //JSONSampler::MemoryIOStreamingSample();

    //�t�@�C������̓��o�͕\�����鏈��
    JSONSampler::FileIOStreamingSample();
}

/*-----------------------------------------------------------------------------
/* �������݊֐�
-----------------------------------------------------------------------------*/
void JSONSampler::SaveJSON(void)
{
}

/*-----------------------------------------------------------------------------
/* �T���v���֐�_DOM�p�[�X01
-----------------------------------------------------------------------------*/
void JSONSampler::DOMParseSample01(void)
{
    // 1. Parse a JSON string into DOM.
    const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    Document d;
    d.Parse(json);

    // 2. Modify it by DOM.
    Value& s = d["stars"];
    s.SetInt(s.GetInt() + 1);

    // 3. Stringify the DOM
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    d.Accept(writer);

    // Output {"project":"rapidjson","stars":11}
    std::cout << buffer.GetString() << std::endl;
}

/*-----------------------------------------------------------------------------
/* �T���v���֐�_DOM�p�[�X02
-----------------------------------------------------------------------------*/
void JSONSampler::DOMParseSample02(void)
{
    const char* s_json = R"(
    {
        "string" : "foo",
        "number" : 123,
        "array" : [
            0,
            1,
            2,
            3
        ],
        "object" : {
            "v0" : "bar",
            "v1" : 456,
            "v2" : 0.123
        }
    }
    )";

    Document doc;

    //DOM(DocumentObjectModel)�֓n�����f�[�^�̍\����̓G���[�n���h�����O
    doc.Parse(s_json);
    bool error = doc.HasParseError();
    if (error) {
        printf("parse error\n");
        return;
    }

    // string
    {
        const char* v = doc["string"].GetString();
        printf("string = %s\n", v);
    }

    // number
    {
        int v = doc["number"].GetInt();
        printf("number = %d\n", v);
    }

    // array
    {
        const Value& a = doc["array"];
        SizeType num = a.Size();

        for (SizeType i = 0; i < num; i++) {
            int v = a[i].GetInt();
            printf("array[%d] = %d\n", i, v);
        }
    }

    // object
    {
        const Value& o = doc["object"];

        // enumerate members in object
        for (Value::ConstMemberIterator itr = o.MemberBegin();
            itr != o.MemberEnd(); itr++)
        {
            const char* name = itr->name.GetString();
            const Value& value = itr->value;
            Type type = value.GetType();

            printf("%s = ", name);
            switch (type) {
            case kStringType:
                printf("%s", value.GetString());
                break;

            case kNumberType:
                if (value.IsDouble())
                    printf("%f", value.GetDouble());
                else
                    printf("%d", value.GetInt());
                break;

            default:
                printf("(unknown type)");
                break;
            }
            printf("\n");
        }
    }
}

/*-----------------------------------------------------------------------------
/* �T���v���֐�_����������̓��o�̓X�g���[�~���O
-----------------------------------------------------------------------------*/
void JSONSampler::MemoryIOStreamingSample(void)
{
    const char* json = R"({"name":"value"})";
    Document doc;

    //����if�̕���́A�ǂ��������������������DOM�ւ̃p�[�X�Ӗ����Ӗ�����
    if (true)
    {
        //�������ւ̓ǂݍ���
        StringStream rs(json);

        doc.ParseStream(rs); //����������DOM�փp�[�X
    }
    else
    {
        doc.Parse(json);  //����������DOM�փp�[�X
    }

    // �������ݏ���
    StringBuffer ws;
    Writer<StringBuffer> writer(ws); //�o�b�t�@��o�^

    doc.Accept(writer);//DOM����o�b�t�@�փp�[�X

    const char* result = ws.GetString(); //�o��
    printf("%s\n", result);

}

/*-----------------------------------------------------------------------------
/* �T���v���֐�_�t�@�C������̓��o�̓X�g���[�~���O
-----------------------------------------------------------------------------*/
void JSONSampler::FileIOStreamingSample(void)
{
    FILE* fp;
    char buf[512];
    Document doc;

    // �ǂݍ���
    fp = fopen("json.txt", "rb");
    FileReadStream rs(fp, buf, sizeof(buf));    //�ǂݍ��ݐ�p

    doc.ParseStream(rs);

    fclose(fp);

    // ��������
    fp = fopen("tmp.txt", "wb");
    FileWriteStream ws(fp, buf, sizeof(buf));   //�������ݐ�p
    Writer<FileWriteStream> writer(ws);         //�C���f���g�Ȃ�

    //PrettyWriter<FileWriteStream> writer(ws);   //�C���f���g����

    doc.Accept(writer);

    fclose(fp);
}

/*=============================================================================
/*		End of File
=============================================================================*/