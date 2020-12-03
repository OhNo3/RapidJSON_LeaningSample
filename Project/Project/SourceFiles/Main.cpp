#define _CRT_SECURE_NO_WARNINGS

//ファイルの入出力管理
#include <fstream>
#include <vector>   
#include <iostream>

#include "External/rapidjson/include/document.h"

#include "External/rapidjson/include/writer.h"
#include "External/rapidjson/include/filewritestream.h"

#include "External/rapidjson/include/reader.h"
#include "External/rapidjson/include/filereadstream.h"


#include "External/rapidjson/include/error/en.h"

//rapidjsonはjsonを高速で構文解析するためのツール
using namespace rapidjson;

bool FileOpen(std::string& fileName, rapidjson::Document& srcDoc);
bool ReadJson(rapidjson::Document& srcDoc);
bool WriteJson(rapidjson::Document& srcDoc);
void GenerateFile(std::string& fileName, rapidjson::Document& srcDoc);
void StringView(rapidjson::Document& srcDoc);


static const char* s_json = R"(
{
    "string" : "foo",
    "number" : 123,
    "array" : [
        0, 0, 0, 0
    ],
    "object" : {
        "v0" : "bar",
        "v1" : 456,
        "v2" : 0.123
    }
}
)";


void StringView(rapidjson::Document& srcDoc)
{
    // write
    StringBuffer ws;
    Writer<StringBuffer> writer(ws);

    srcDoc.Accept(writer);

    const char* result = ws.GetString();
    printf("%s\n", result);
}

bool FileOpen(std::string& fileName, rapidjson::Document& srcDoc)
{
    //読み込み専用でファイルを開く
    std::ifstream ifs(fileName.c_str()
        , std::ios::in      //読み取り専用モードで起動
        | std::ios::binary  //バイナリモードで
        | std::ios::ate);   //ファイル(内容の)サイズを知るためにシークをファイル内のデータ末尾へ

    //ファイルが開けたか(存在しているか？)
    if (!ifs.is_open())
    {
        //ファイルを開けなかった
        printf("ファイルがなかった\n");
        return false;
    }

    //シークの現在位置（末尾の座標）からファイルに内臓されたデータサイズを取得。
    std::ifstream::pos_type fileSize = ifs.tellg();


    //シークの読み取り座標の変更
    //ファイル（内容）の先頭を基準に読み込みを開始するように指定する。
    ifs.seekg(0, std::ios::beg);

    //配列の宣言。ファイルのデータサイズ+末尾にNULL文字分の余裕を与える
    std::vector<char> bytes(static_cast<size_t>(fileSize) + 1);

    //ファイルの情報を配列にコピー
    ifs.read(bytes.data(), static_cast<size_t>(fileSize));

    //rapidjsonのルートのメモリに構文をコピー、展開する。
    srcDoc.Parse(bytes.data());

    bool error = srcDoc.HasParseError();

    if (!srcDoc.IsObject() || error)
    {
        {   //エラーコードの表示
            size_t offset = srcDoc.GetErrorOffset();
            ParseErrorCode code = srcDoc.GetParseError();
            const char* msg = GetParseError_En(code);
            printf("%d:%d(%s)\n", offset, code, msg);
        }

        printf("有効なJsonドキュメントではなかった\n");

        return false;
    }

    return true;
}

bool ReadJson(rapidjson::Document& srcDoc)
{
    // string
    {
        const char* v = srcDoc["string"].GetString();
        printf("string = %s\n", v);
    }

    // number
    {
        int v = srcDoc["number"].GetInt();
        printf("number = %d\n", v);
    }

    // array
    {
        const Value& a = srcDoc["array"];
        SizeType num = a.Size();

        for (SizeType i = 0; i < num; i++) {
            int v = a[i].GetInt();
            printf("array[%d] = %d\n", i, v);
        }
    }

    // object
    {
        const Value& o = srcDoc["object"];

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


    return true;
}

bool WriteJson(rapidjson::Document& srcDoc)
{


    // string
    {
        srcDoc["string"].SetString("ohno");
        const char* v = srcDoc["string"].GetString();
        printf("string = %s\n", v);
    }

    // number
    {
        srcDoc["number"].SetInt(123581);
        int v = srcDoc["number"].GetInt();
        printf("number = %d\n", v);
    }

    // array
    {
        const Value& a = srcDoc["array"];
        SizeType num = a.Size();
        for (SizeType i = 0; i < num; i++) {
            int v = a[i].GetInt();
            printf("array[%d] = %d\n", i, v);
        }



    //    Value val(kArrayType);
    //val.



    }

    // object
    {
        const Value& o = srcDoc["object"];

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

    return true;
}

void GenerateFile(std::string& fileName, rapidjson::Document& srcDoc)
{
    //StringStream rs();

    //srcDoc.ParseStream(rs);

    StringBuffer ws;
    Writer<StringBuffer> writer(ws);

    srcDoc.Accept(writer);


    ////シークの現在位置（末尾の座標）からファイルに内臓されたデータサイズを取得。
    //std::ifstream::pos_type fileSize = ifs.tellg();


    ////シークの読み取り座標の変更
    ////ファイル（内容）の先頭を基準に読み込みを開始するように指定する。
    //ifs.seekg(0, std::ios::beg);

    ////配列の宣言。ファイルのデータサイズ+末尾にNULL文字分の余裕を与える
    //std::vector<char> bytes(static_cast<size_t>(fileSize) + 1);

    ////ファイルの情報を配列にコピー
    //ifs.read(bytes.data(), static_cast<size_t>(fileSize));

    ////rapidjsonのルートのメモリに構文をコピー、展開する。
    //srcDoc.Parse(bytes.data());


    const char* data_string = ws.GetString();


    //ofstreamでもstd::ios::ateが使用可能
    //どちらの書き込みの場合でもファイルの末尾にNULL文字を入力することで
    //正しく書き込みされていることを保証する

    //書き込みモード
    std::ofstream ofs(fileName.c_str()
                    , std::ios::out);

    ////上書きモード
    ////std::ofstream ofs(fileName.c_str()
    ////                , std::ios::trunc);
 
    ofs << data_string;
    ofs.close();

}


int main()
{
    std::string file_name = "test.json";

    rapidjson::Document Doc;//最も重要な部分、DOMのルート部分

    //ファイルを開く
    if (!FileOpen(file_name, Doc))
    {
        //jsonをロードできなかった。
        printf("jsonファイルを開けなかった\n");
    }

    //読み込み
    std::cout << "//***書き込み前****************************//\n";
    ReadJson(Doc);
    StringView(Doc);

    //書き込み
    std::cout << "//***書き込み後****************************//\n";
    WriteJson(Doc);
    StringView(Doc);
    std::cout << "//*****************************************//\n";


    GenerateFile(file_name, Doc);

    ReadJson(Doc);




    // read
    //StringStream rs(json);

    //doc.ParseStream(rs);



   // Doc.Accept();

   //// const char* result = ws.GetString();
   // printf("%s\n", result);






    return 0;
}

