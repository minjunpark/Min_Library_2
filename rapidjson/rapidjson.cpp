#include <iostream>
#include <Windows.h>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
using namespace rapidjson;



//void JsonLoad(void)
//{
//	const char* pJson = "{ \"Account\": [{\"AccountNo\":1,\"Nickname\" : \"테스트계정1\"}, {\"AccountNo\":2, \"Nickname\" : \"테스트계쩡2\"}] ,\"Friend\" : [] ,\"FriendRequest\" : [{\"RequestNo\":1,\"FromAccountNo\" : 1,\"ToAccountNo\" : 2,\"Time\" : 1437344611},{\"RequestNo\":2,\"FromAccountNo\" : 1,\"ToAccountNo\" : 3,\"Time\" : 1437344611}]}";
//
//	Document Doc;
//	Doc.Parse(pJson);	// Document 로 Json 텍스트 파싱.
//
//	UINT64 AccountNo;
//	const char* pNickname;
//
//	Value& AccountArray = Doc["Account"];	// 첫번에 Account 객체 접근
//	// rapidjson::Value  로 받아서 사용
//
//	for (SizeType i = 0; i < AccountArray.Size(); i++)
//	{
//		Value& AccountObject = AccountArray[i];
//		AccountNo = AccountObject["AccountNo"].GetUint64();
//		pNickname = AccountObject["Nickname"].GetString();
//		// 읽혀진 데이터 사용
//		printf("AccountNo %d\n", AccountNo);
//		printf("AccountNo %s\n", pNickname);
//	}
//
//	//Value& FriendArray = Doc["Friend"];
//	//for (SizeType i = 0; i < FriendArray.Size(); i++)
//	//{
//	//	Value& FriendObject = FriendArray[i];
//	//	UINT64 FriendNo = FriendObject["FriendNo"].GetUint64();
//	//	UINT64 FromAccountNo = FriendObject["FromAccountNo"].GetUint64();
//	//	UINT64 ToAccountNo = FriendObject["ToAccountNo"].GetUint64();
//	//	// 읽혀진 데이터 사용
//	//	
//	//}
//}
struct pF 
{
	UINT64 No;
	UINT64 FromAccountNo;
	UINT64 ToAccountNo;
};

typedef GenericStringBuffer<UTF16<>> UTF16StringBuffer;
typedef GenericValue<UTF16<>> UTF16Value;
typedef GenericDocument<UTF16<>> UTF16Document;

void JSON_UTF16()
{
	pF* pFriend;
	UTF16StringBuffer StringJSON;
	Writer<UTF16StringBuffer, UTF16<>, UTF16<>> writer(StringJSON);

	UTF16Document Doc;

	UTF16Value& AccountArray = Doc[L"Account"];

	writer.StartObject();			// { 
	writer.String(L"Account");		// { “Account” 
	writer.StartArray();			// { “Account”:[  
	{ // 반복문 돌면서 Account 정보 저장
		writer.StartObject();		// { “Account”:[{  
		writer.String(L"AccountNo");	// { “Account”:[{“AccountNo”: 
		writer.Uint64(1111); 		// { “Account”:[{“AccountNo”:1111 
		writer.String(L"Nickname");	// { “Account”:[{“AccountNo”:1111, “Nickname”:
		writer.String(L"닉네임"); 	// { “Account”:[{“AccountNo”:1111, “Nickname”:  “닉네임”
		writer.EndObject();		// { “Account”:[{“AccountNo”:1111, “Nickname”: “닉네임”},

	}
	writer.EndArray();			// ] 추가

	//writer.String(L"Friend");			// ……
	//writer.StartArray();
	//while(1)
	//{ // 반복문 돌면서 친구정보 저장
	//	writer.StartObject();
	//	writer.String(L"FriendNo");
	//	writer.Uint64(pFriend->No);
	//	writer.String(L"FromAccountNo");
	//	writer.Uint64(pFriend->FromAccountNo);
	//	writer.String(L"ToAccountNo");
	//	writer.Uint64(pFriend->ToAccountNo);
	//	writer.EndObject();
	//}
	//writer.EndArray();
	//writer.String(L"FriendRequest");
	//writer.StartArray();

	//{ // 반복문 돌면서 저장
	//	writer.StartObject();
	//	writer.String(L"RequestNo");
	//	writer.Uint64(pFriend->No);
	//	writer.String(L"FromAccountNo");
	//	writer.Uint64(pFriend->FromAccountNo);
	//	writer.String(L"ToAccountNo");
	//	writer.Uint64(pFriend->ToAccountNo);
	//	writer.EndObject();
	//}
	//writer.EndArray();
	//writer.EndObject();

	//const char* pJson = StringJSON.GetString();	// 이 문자열을 저장하거나 패킷을 쏨
	const WCHAR* pJson = StringJSON.GetString();	// 이 문자열을 저장하거나 패킷을 쏨
}
int main()
{
	rapidjson::GenericStringBuffer< rapidjson::UTF16<> > buf;
	const WCHAR* pStr = buf.GetString();
	//JsonLoad();
}
