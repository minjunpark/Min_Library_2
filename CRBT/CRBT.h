﻿#pragma once
#include <iostream>
#include <queue>
#define max(a,b) (((a)>(b))?(a):(b))//괄호를 무조건 둘러싸자
#include <map>
using namespace std;

enum Color
{
	RED,
	BLACK
};

enum
{
	e_BLACK = 1,
	e_RED = 0
};

struct Node
{
	int Data;
	char pColor = e_RED;//false 빨강 true 검정
	Node* pParent = nullptr;
	Node* pLeft = nullptr;
	Node* pRight = nullptr;
};
typedef Node* NodePtr;


class CREDBLACKTREE
{
public:
	struct Trunk
	{
		Trunk* prev;
		string str;

		Trunk(Trunk* prev, string str)
		{
			this->prev = prev;
			this->str = str;
		}
	};

	Node* pRoot;
	Node* nil;

	int insert_Count;//넣은개수
	int delete_Count;//삭제한개수
	int black_depth;//현재 트리 블랙의 깊이

public:
	//초기화
	CREDBLACKTREE();
	CREDBLACKTREE(int data);

	bool Delete(int item);
	void DelteFixUp(NodePtr x);
	NodePtr IsKey(int item);

	void Transplant(NodePtr u, NodePtr v);

	Node* GetRootNode() { return pRoot; }//루트노드 가져오기
	virtual ~CREDBLACKTREE();

	void delete_clear(Node* pNode);//모든데이터 정리

	//삽입
	void RedBlack_Insert(int data);//RBT Insert
	void RedBlack_Insert_Refresh(Node* pNode);//insert후 밸런스작업
	//삭제
	bool RedBlack_Delete(int data);
	void RedBlack_Delete_Refresh(Node* _DNode);
	
	bool RedBlack_Search(int data);
	Node* RedBlack_Search_Node(int data);

	//밸런스 작업용 도구
	void Right_Rotation(Node* sNode);//왼쪽회전
	void Right_Delete_Rotation(Node* sNode);//왼쪽회전
	void Right_Rotation_Test(int data);//왼쪽회전 테스트
	void  Left_Rotation(Node* sNode);//오른쪽회전
	void  Left_Delete_Rotation(Node* sNode);//오른쪽회전
	void  Left_Rotation_Test(int data);//오른쪽 회전 테스트
	bool Color_swap(Node* pNode);//색깔 뒤집기
	int Tree_Count(Node* pNode);//트리 개수 가져오기
	int Depth_Count(Node* root);//최대 깊이 확인하기
	
	bool Tree_Delete(int data);//단순 이진삭제

	//검색
	bool Tree_Search(int data);//있다 없다 검증
	Node* Tree_Search_Node(int data);//위치리턴 Nil이면 없다는뜻

	void Black_Insert(int data);//오류 고의발생용
	
	// 출력용함수 모음
	void showTrunks(Trunk* p);
	void printBinaryTree(Node* pNode, bool isLeft, int space = 0, int height = 5);
	void printTree(Node* root, Trunk* prev, bool isLeft);
	void LevelPrint(Node* pNode);
	void All_print(Node* pNode);

	//검증용코드
	int RBT_CHECK(Node* _pNode);
	
	//트리의 모든 데이터를 중위순회하면서 q에 넣는다.
	void All_Q(Node* pNode, queue<int> * q)
	{
		if (pNode == nullptr || pNode == nil)
			return;

		//중위 순회로 모든 데이터 출력
		All_Q(pNode->pLeft,q);
		q->push(pNode->Data);//중위순회로 루트의 모든 노드를 넣는다.
		All_Q(pNode->pRight,q);
	}

	/*x를 중심으로 왼쪽으로 회전*/
	void RotateLeft(NodePtr x)
	{
		NodePtr y;

		y = x->pRight;
		x->pRight = y->pLeft;
		if (y->pLeft != nil)
		{
			y->pLeft->pParent = x;
		}
		y->pParent = x->pParent;

		if (!x->pParent)
		{
			pRoot = y;
		}
		else if (x == x->pParent->pLeft)
		{
			x->pParent->pLeft = y;
		}
		else
		{
			x->pParent->pRight = y;
		}
		x->pParent = y;
		y->pLeft = x;
	}
	/*x를 중심으로 오른쪽으로 회전*/
	void RotateRight(NodePtr y)
	{
		NodePtr x;

		x = y->pLeft;
		y->pLeft = x->pRight;
		if (x->pRight != nil)
		{
			x->pRight->pParent = y;
		}
		x->pParent = y->pParent;

		if (!y->pParent)
		{
			pRoot = x;
		}
		else if (y == y->pParent->pLeft)
		{
			y->pParent->pLeft = x;
		}
		else
		{
			y->pParent->pRight = x;
		}
		y->pParent = x;
		x->pRight = y;
	}

	NodePtr tree_minimum(NodePtr x)
	{
		while (x->pLeft != nil)
		{
			x = x->pLeft;
		}
		return x;
	}
	
	//최댓값 찾기
	NodePtr tree_maximum(NodePtr x)
	{
		while (x->pRight != nil)
		{
			x = x->pRight;
		}
		return x;
	}
};