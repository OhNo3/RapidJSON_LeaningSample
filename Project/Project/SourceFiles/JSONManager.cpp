/*=============================================================================
/*-----------------------------------------------------------------------------
/*	[JSONManager.cpp] JSON管理クラス
/*	Author：Kousuke,Ohno.
/*-----------------------------------------------------------------------------
/*	説明：JSON管理クラス
=============================================================================*/

/*--- インクルードファイル ---*/
#include "StdAfx.h"
#include "JSONManager.h"

//RapidJSONを簡易利用するためのヘルパー関数群
#include "JSONHelper/JSONHelper.h"

//デバッグ用
#include "DebugSystem.h"

//エラーメッセージの日本語翻訳データ
static const char* jp_error_msg[] = {

    "エラーはありません"                                             //!< kParseErrorNone

    , "ドキュメントは空です。"                                       //!< kParseErrorDocumentEmpty
    , "ドキュメントルートは、複数定義されています。"                 //!< kParseErrorDocumentRootNotSingular                  

    , "無効な値です。"                                               //!< kParseErrorValueInvalid
                                                                          
    , "オブジェクトメンバーの名前がありません。"                     //!< kParseErrorObjectMissName                 
    , "オブジェクト・メンバ名の後にコロンがありません。"             //!< kParseErrorObjectMissColon
    , "オブジェクトメンバーの後にカンマまたは'}'がありません。"      //!< kParseErrorObjectMissCommaOrCurlyBracket  
                                                                          
    , "配列要素の後にカンマまたは']'がない。"                        //!< kParseErrorArrayMissCommaOrSquareBracket  
                                                                                     
    , "文字列の後の16進数が正しくありません。"                       //!< kParseErrorStringUnicodeEscapeInvalidHex  
    , "文字列中のサロゲート・ペアが無効です。"                       //!< kParseErrorStringUnicodeSurrogateInvalid 
    , "文字列内のエスケープ文字が無効です。"                         //!< kParseErrorStringEscapeInvalid            
    , "文字列内に引用符がありません。"                               //!< kParseErrorStringMissQuotationMark        
    , "文字列のエンコーディングが無効です。"                         //!< kParseErrorStringInvalidEncoding          
                                                                          
    , "数値が大きすぎてdoubleに格納できません。"                     //!< kParseErrorNumberTooBig        
    , "数値中の端数部分が正しくありません。"                         //!< kParseErrorNumberMissFraction 
    , "数値に指数がありませんでした。"                               //!< kParseErrorNumberMissExponent  
                                                                          
    , "解析が終了しました。"                                         //!< kParseErrorTermination                  
    , "構文エラーです。"                                             //!< kParseErrorUnspecificSyntaxError
};

static constexpr float data_version = 1.00f;

/*-----------------------------------------------------------------------------
/* コンストラクタ
-----------------------------------------------------------------------------*/
JSONManager::JSONManager(void)
{

}

/*-----------------------------------------------------------------------------
/* デストラクタ
-----------------------------------------------------------------------------*/
JSONManager::~JSONManager(void)
{
}

/*-----------------------------------------------------------------------------
/* JSONファイルへのロード処理
-----------------------------------------------------------------------------*/
bool JSONManager::LoadJSON(const std::string& inFileName, rapidjson::Document& outDoc)
{
	//読み込み専用でファイルを開く
	std::ifstream ifs(inFileName.c_str()
				   	 , std::ios::in      //読み取り専用モードで起動
				   	 | std::ios::binary  //バイナリモードで
				   	 | std::ios::ate);   //ファイルサイズを知るためにシークをファイルの末尾へ移動
	
	//ファイルが開けたか(存在しているか？)
	if (!ifs.is_open())
	{
		std::cout << OUTPUT_ERROR_MSG("ファイルが開けませんでした。:" + inFileName);
		return false;
	}

    //シークの現在位置（末尾の座標）から、読み込んだファイルの最大データサイズを取得。
    std::ifstream::pos_type fileSize = ifs.tellg();

    //シークの読み取り座標の変更
    //ファイル（内容）の先頭を基準に、読み込みを開始するように指定する。
    ifs.seekg(0, std::ios::beg);

    //配列の宣言。ファイルの最大データサイズ+末尾にNULL文字分の余裕を与える
    std::vector<char> bytes(static_cast<size_t>(fileSize) + 1);

    //読み込んだファイルの情報を配列にコピー
    ifs.read(bytes.data(), static_cast<size_t>(fileSize));

    //RapidJSONのDocumentにデータ配列を渡して、配列の情報をDOMとして高速解析。
    outDoc.Parse(bytes.data());

    //解析結果にエラーがあるか？
    bool parse_error = outDoc.HasParseError();
    if (!outDoc.IsObject() || parse_error)
    {
        //エラーコードの表示
        {
          //メモリに読み込んだファイルの情報の中で、解析エラーの原因。byte(バイト)オフセット座標の取得
          size_t offset = outDoc.GetErrorOffset();                       
         
          //エラーコードの定数と言語設定
          JSONManager::LanguageSetting  lang = LanguageSetting::Jp;
          rapidjson::ParseErrorCode     code = outDoc.GetParseError();

          //エラーコードの定数と言語設定をもとに、エラーメッセージを返す
          const char* error_msg = JSONManager::GetParseErrorMsg(code, lang);

          //エラーメッセージの出力
          std::string error_code = "RapidJSON::ParseErrorCode:(" + std::to_string(code) + ")" + std::string(error_msg) + "/";
          std::string error_pos  = "エラー対象のオフセット座標:byte[" + std::to_string(offset) + "]\n";
          std::cout << OUTPUT_ERROR_MSG("ファイルの破損を検知。" + error_code + error_pos);
        }
        return false;
    }
    return true;
}

/*-----------------------------------------------------------------------------
/* JSONファイルのドキュメントのロード処理
-----------------------------------------------------------------------------*/
bool JSONManager::LoadData(const std::string& inFileName)
{
    //DocumentとしてのRoot
    rapidjson::Document doc(rapidjson::kObjectType);

    //ファイルのロードが
    const bool is_file_load_failed = JSONManager::LoadJSON(inFileName, doc);
    {
        if (is_file_load_failed == false)
        {
            std::cout << OUTPUT_ERROR_MSG("データのロードに失敗しましたが、このままシステムを実行します。\n");
            return false;
        }

        //データの読み込みなど....
        {
            float version = 0.f;
            if (!JSONHelper::GetFloat(doc, "version", version)
                || version != data_version)
            {
                std::cout << OUTPUT_ERROR_MSG("データのversionが違いますが、このままシステムを実行します。\n");
                return false;
            }

            // プロパティの読み込み
            const rapidjson::Value& property = doc["Properties"];
            if (property.IsObject())
            {
                LoadProperties(property);
            }
        }
    }
    return true;
}

/*-----------------------------------------------------------------------------
/* JSONファイルへのセーブ処理
-----------------------------------------------------------------------------*/
void JSONManager::SaveData(const std::string& inFileName)
{
    //DocumnetのRootを宣言
    rapidjson::Document doc(rapidjson::kObjectType);
    {
        //Versionの記録
        const float version = data_version;
        JSONHelper::AddFloat(doc.GetAllocator(), doc, "version", version);

        //プロパティの記録
        rapidjson::Value property(rapidjson::kObjectType);
        SaveProperties(doc.GetAllocator(), property);
        doc.AddMember("Properties", property, doc.GetAllocator());
    }

    //JSONを文字列バッファに保存
    rapidjson::StringBuffer buffer;
    //PrettyWriterを使用して、人間が確認しやすいフォーマットへ
    rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);

    //バッファへ転送
    doc.Accept(writer);
    const char* output = buffer.GetString();

    // JSONファイルとして出力
    std::ofstream outFile(inFileName);
    if (outFile.is_open())
    {
        outFile << output;
    }

}

/*-----------------------------------------------------------------------------
/* JSONファイルへのプロパティのロード処理
-----------------------------------------------------------------------------*/
void JSONManager::LoadProperties(const rapidjson::Value& inObject)
{
    std::string name = "";
    int today = 0;

    JSONHelper::GetString(inObject, "name", name);
    JSONHelper::GetInt(inObject, "today", today);

    std::cout << "name：" << name << std::endl;
    std::cout << "today：" << std::to_string(today) << std::endl;
}

/*-----------------------------------------------------------------------------
/* JSONファイルへのプロパティのセーブ処理
-----------------------------------------------------------------------------*/
void JSONManager::SaveProperties(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObject)
{
    //プロパティ(kObjectType)にメンバを追加
    JSONHelper::AddString(alloc, inObject, "name", "dog");
    JSONHelper::AddInt(alloc, inObject, "today", int(20201216));
}

/*-----------------------------------------------------------------------------
/* JSONの構文解析エラーメッセージの取得関数
-----------------------------------------------------------------------------*/
const char* JSONManager::GetParseErrorMsg(rapidjson::ParseErrorCode inParseErrorCode, const LanguageSetting inSelectLanguage)
{
    //言語設定によりスイッチ
    switch (inSelectLanguage)
    {
    case LanguageSetting::Jp: 
        return JSONManager::GetParseError_Jp(inParseErrorCode);
        
    case LanguageSetting::En:
        return rapidjson::GetParseError_En(inParseErrorCode);

    default:
        assert("JSONManager::GetParseErrorMsg()に、適切な言語設定がされていません。");
        break;
    }

    return nullptr;
}

/*-----------------------------------------------------------------------------
/* 日本語のエラーメッセージ取得関数
-----------------------------------------------------------------------------*/
const char* JSONManager::GetParseError_Jp(rapidjson::ParseErrorCode inParseErrorCode)
{
    return  jp_error_msg[static_cast<int>(inParseErrorCode)];
}

/*=============================================================================
/*		End of File
=============================================================================*/