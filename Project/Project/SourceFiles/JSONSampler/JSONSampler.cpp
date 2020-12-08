/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONSampler.cpp] RapidJSONヘルパークラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：RapidJSONヘルパークラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "../StdAfx.h"
#include "JSONSampler.h"

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
JSONSampler::JSONSampler(void)
{
}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
JSONSampler::~JSONSampler(void)
{
}

/*-----------------------------------------------------------------------------
/* 読み込み関数
-----------------------------------------------------------------------------*/
void JSONSampler::LoadJSON(void)
{
    //文字列データをDOMに渡して解析し、読み込み表示する処理
    //JSONSampler::DOMParseSample01();
    //JSONSampler::DOMParseSample02();

    //メモリからの入出力表示する処理
    //JSONSampler::MemoryIOStreamingSample();

    //ファイルからの入出力表示する処理
    JSONSampler::FileIOStreamingSample();
}

/*-----------------------------------------------------------------------------
/* 書き込み関数
-----------------------------------------------------------------------------*/
void JSONSampler::SaveJSON(void)
{
}

/*-----------------------------------------------------------------------------
/* サンプル関数_DOMパース01
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
/* サンプル関数_DOMパース02
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

    //DOM(DocumentObjectModel)へ渡したデータの構文解析エラーハンドリング
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
/* サンプル関数_メモリからの入出力ストリーミング
-----------------------------------------------------------------------------*/
void JSONSampler::MemoryIOStreamingSample(void)
{
    const char* json = R"({"name":"value"})";
    Document doc;

    //このifの分岐は、どちらも同じくメモリからDOMへのパース意味を意味する
    if (true)
    {
        //メモリへの読み込み
        StringStream rs(json);

        doc.ParseStream(rs); //メモリからDOMへパース
    }
    else
    {
        doc.Parse(json);  //メモリからDOMへパース
    }

    // 書き込み処理
    StringBuffer ws;
    Writer<StringBuffer> writer(ws); //バッファを登録

    doc.Accept(writer);//DOMからバッファへパース

    const char* result = ws.GetString(); //出力
    printf("%s\n", result);

}

/*-----------------------------------------------------------------------------
/* サンプル関数_ファイルからの入出力ストリーミング
-----------------------------------------------------------------------------*/
void JSONSampler::FileIOStreamingSample(void)
{
    FILE* fp;
    char buf[512];
    Document doc;

    // 読み込み
    fp = fopen("json.txt", "rb");
    FileReadStream rs(fp, buf, sizeof(buf));    //読み込み専用

    doc.ParseStream(rs);

    fclose(fp);

    // 書き込み
    fp = fopen("tmp.txt", "wb");
    FileWriteStream ws(fp, buf, sizeof(buf));   //書き込み専用
    Writer<FileWriteStream> writer(ws);         //インデントなし

    //PrettyWriter<FileWriteStream> writer(ws);   //インデントあり

    doc.Accept(writer);

    fclose(fp);
}

/*=============================================================================
/*		End of File
=============================================================================*/