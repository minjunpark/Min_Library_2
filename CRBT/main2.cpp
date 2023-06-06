//// CBST.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
////
//
//#include <iostream>
//#include "RBtree.h"
//#include <iostream>
//#include <time.h>
//#include <Windows.h>
//#include <wchar.h>
//#include <locale.h>
//#include <conio.h>
//#include <map>
//#include "Profile.h"
//#include <queue>
//
//#pragma comment(lib, "winmm.lib")
//#include "CTREE.h"
//#define RANDOM(__min__, __max__) \
//	((int)(((double)((rand()<<15) | rand())) / ((RAND_MAX<<15 | RAND_MAX) + 1) \
//		* (((__max__) + 1) - (__min__))) + (__min__))
//
//using namespace std;
//
//void RBT_INSERT_CHECK(int count, bool RBT_CHECk);
//void RBT_DELETE_CHECK(int count, bool RBT_CHECK);
//void Struct_Time_Check_RANDOM(int count, int start, int end, int max_seed);
//int main()
//{
//	timeBeginPeriod(1);
//	QueryPerformanceFrequency(&_P_Freq);//최초 시간대 한번 세팅
//	Struct_Time_Check_RANDOM(10000, 1, 10000, 2000);
//	return 0;
//	
//	return 0;
//}
//
//bool RBT_MAP_CHECK()
//{
//	//map에 같은 정보 넣은후
//	//둘다 중위순회하면서 queue에 같은 데이터를 넣는다.
//	//하나씩 빼면서 비교하다 다르다면 false
//	//버퍼로하는 방식도 가능하겠네
//}
//
////카운트 갯수만큼 넣으면서
////카운트의 2배의 랜덤사이 값을 넣는다
////예:100000을 넣으면 1~200000의 랜덤이 잡히고
////그사이의 값을 중복 제외하고 10만개를 넣게 만들고
////그데이터를 maps과 레드블랙 트리에 넣은후
////레드블랙 트리를 중위순회하면서 q에 데이터를 모두넣고
////masp과 트리에서 하나씩 뽑아내면서 비교한다.
////불일치하면 재현을 위해 timeseed와 문제 생긴 노드
////그리고 강제 에러를 발생시킨다.
////그리고 RBT_CHECK로 레드블랙트리의 오류가 없는지 검사한다.
////레드 연속 여부
////루트마다 블랙의 개수가 같은지
////넣은것과 나온것의 개수가 같은지
//
//
//void Struct_Time_Check_RANDOM(int count, int start, int end, int max_seed) //실제 성능측정
//{
//	//4000
//	//4가지 자료구조세팅
//	RedBlackTree* CRBT;//레드블랙트리
//	CTREE* CBST;//이진트리
//	int timeSeed = 1;
//
//	//map
//	//unmap
//
//	//4개의 자료구조에 카운터크기만큼 랜덤한 데이터를
//	//start부터 end까지의 범위에서 랜덤하게 넣고 뺴고
//	while (1)
//	{
//		srand(timeSeed);
//		if (max_seed == timeSeed)
//			break;
//
//		CRBT = new RedBlackTree;
//		CBST = new CTREE;
//
//		//입력
//		for (int i = 0; i < 10; i++)
//		{
//			int num = RANDOM(1, 100);
//			//레드블랙트리 삽입측정
//			//PRO_BEGIN(L"RedBlack_Insert");
//			CRBT->Insert(num);
//			//PRO_END(L"RedBlack_Insert");
//
//			//이진트리 입력 측정
//			//PRO_BEGIN(L"Tree_Insert");
//			//CBST->Tree_Insert(num);
//			//PRO_END(L"Tree_Insert");
//			
//		}
//		
//		//검색
//		for (int i = 0; i < count; i++)
//		{
//			int num = RANDOM(start, end);
//			//레드블랙트리 삽입측정
//			//PRO_BEGIN(L"RedBlack_Search");
//			CRBT->Remove(num);
//			//PRO_END(L"RedBlack_Search");
//
//			//이진트리 입력 측정
//			//PRO_BEGIN(L"Tree_Search");
//			//CBST->Tree_Search(num);
//			//PRO_END(L"Tree_Search");
//			
//		}
//
//
//		//삭제
//		for (int i = 0; i < count; i++)
//		{
//			int num = RANDOM(start, end);
//			//레드블랙트리 삭제측정
//			//PRO_BEGIN(L"RedBlack_Delete");
//			CRBT->Remove(num);
//			//PRO_END(L"RedBlack_Delete");
//
//			//이진트리 삭제측정
//			//PRO_BEGIN(L"Tree_Delete");
//			//CBST->Tree_Delete(num);
//			//PRO_END(L"Tree_Delete");
//		}
//
//		CRBT->RBT_CHECK(CRBT->GetRootNode());
//
//		//for (map<int, int>::iterator itr = maps2->begin(); itr != maps2->end(); ++itr)
//		//{
//		//	if (itr->first != q->front())
//		//	{
//		//		printf("timeSeed %d\n", timeSeed);//랜덤시드는 무엇인지
//		//		printf("itr->first %d\n", itr->first);//어느 자식에서 문제가 생겼는지
//		//		throw std::bad_exception{};//강제 에러발생
//		//	}
//		//	//rintf("map %d\n", timeSeed);
//		//	q->pop();
//		//}
//
//		printf("timeSeed %d\n", timeSeed);
//		timeSeed++;
//		//ProfileReset();
//		delete CRBT;
//		delete CBST;
//		//ProfilePrint();
//	}
//	ProfileDataOutText(L"CRBT_CBST_CHECK");
//	//같은 데이터를 넣고 검색하고 삭제 하는 시간을 측정
//
//}