#pragma once
#include <iostream>
#include <queue>
#define max(a,b) (((a)>(b))?(a):(b))//괄호를 무조건 둘러싸자
using namespace std;
class CREDBLACKTREE
{
public:
	enum
	{
		e_BLACK = 1,
		e_RED = 0
	};

	struct Node
	{
		int Data;
		char pColor= e_RED;//false 빨강 true 검정
		Node* pParent = nullptr;
		Node* pLeft = nullptr;
		Node* pRight = nullptr;
	};
	Node* pRoot;
	Node* nil;

public:
	//초기화
	CREDBLACKTREE()
	{
		nil = new Node;
		nil->pParent = nullptr;
		nil->pColor = e_BLACK;
		nil->pLeft = nullptr;
		nil->pRight = nullptr;

		pRoot = nullptr;

	};
	CREDBLACKTREE(int data)
	{
		nil = new Node;
		nil->pParent = nullptr;
		nil->pColor = e_BLACK;
		nil->pLeft = nullptr;
		nil->pRight = nullptr;

		//트리초기화
		pRoot = new Node;
		if (pRoot == nullptr)
			return;
		pRoot->pColor = e_BLACK;
		pRoot->Data = data;
		pRoot->pParent = nil;
		pRoot->pLeft = nil;
		pRoot->pRight = nil;
	}

	virtual ~CREDBLACKTREE()
	{
		delete_clear(pRoot);
	}

	void delete_clear(Node* pNode)
	{
		if (pNode == nullptr)
			return;

		//중위 순회로 모든 데이터 순회
		delete_clear(pNode->pLeft);
		delete_clear(pNode->pRight);
		delete pNode;//모든 할당된 노드제거
	};

	//삽입
	void RedBlack_Insert(int data)
	{
		if (data <= 0) //0이하의 데이터는 처리하지 않겠다.
			return;

		if (pRoot == nullptr)//루트노드가 없다면
		{
			pRoot = new Node;
			pRoot->pColor = e_BLACK;//블랙
			pRoot->Data = data;
			pRoot->pParent = nil;//루트노드 부모는 없다.
			pRoot->pLeft = nil;
			pRoot->pRight = nil;
			return;//루트노드 생성하고 종료
		}

		//루트노드가 있는 상태에서의 데이터 입력
		Node* pNode = nullptr;
		Node* cNode = pRoot;//루트 노드부터 시작
		Node* insertNode = nullptr;
		
		while (cNode != nil)//넣어야하는 위치를 탐색한다.
		{
			if (cNode->Data == data)//중복데이터는 절대없도록한다.
				return;

			pNode = cNode;//부모 노드를 저장한다.

			if (cNode->Data > data) //현재 노드보다 데이터가 작다면 왼쪽으로 가야한다.
			{
				cNode = cNode->pLeft;
			}
			else//현재 노드보다 데이터가 크다면 오른쪽으로 가야한다.
			{
				cNode = cNode->pRight;
			}
		}

		//빠져나왔다는건 리프노드에 도달했다는 뜻
		//데이터 노드를 만들고
		insertNode = new Node;
		insertNode->Data = data;
		insertNode->pColor = e_RED;//맨처음 입력시 반드시 빨간색으로 세팅한다.
		insertNode->pParent = pNode;//부모를 넣는다.
		insertNode->pLeft = nil;
		insertNode->pRight = nil;

		if (pNode->Data > data)//부모 노드보다 작다면 왼쪽으로
			pNode->pLeft = insertNode;
		else//부모 노드보다 크다면 오른쪽으로
			pNode->pRight = insertNode;



		///////////////////////////////////////////////////////////
		///여기부터 레드블랙트리 정리//////////////////////////////
		///////////////////////////////////////////////////////////

		RedBlack_Insert_Refresh(insertNode);

	}

	void RedBlack_Insert_Refresh(Node* pNode)
	{

		if (pRoot->pColor == e_RED)//루트노드가 레드라면 블랙으로 바꿔준다.
			pRoot->pColor = e_BLACK;

		Node* _MNode = pNode;
		Node* _PNode = _MNode->pParent;
		Node* _GNode = _PNode->pParent;
		Node* _UNode;



		if (_GNode->pLeft == _PNode)
			_UNode = _GNode->pRight;
		else
			_UNode = _GNode->pLeft;
		
		if (_PNode->pColor == e_RED)//현재 나의 부모가 RED 노드라면?
		{
			if (_UNode->pColor == e_BLACK)//삼촌이 검정트리일떄
			{
				if (_GNode->pLeft == _PNode//부모가 할아버지 왼쪽자식
					&& _PNode->pLeft == _MNode)//내가 부모의 왼쪽자식
				{
					//1.부모와 할아버지의 뒤집어서 바꾼 후
					Color_swap(_PNode);
					Color_swap(_GNode);

					//2.할아버지 기준으로 오른쪽으로 회전
					Right_Rotation(_GNode);
				}
				else if (_GNode->pRight == _PNode//부모가 할아버지의 오른쪽 자식
					&& _PNode->pRight == _MNode)//내가 부모의 오른쪽자식
				{
					//1.부모와 할아버지의 뒤집어서 바꾼 후
					Color_swap(_PNode);
					Color_swap(_GNode);
					//2.할아버지 기준으로 오른쪽으로 회전
					Left_Rotation(_GNode);
				}
				else if (_GNode->pLeft == _PNode//부모가 할아버지 왼쪽자식
					&& _PNode->pRight == _MNode)//내가 부모의 오른쪽자식
				{
					Left_Rotation(_PNode);

					Color_swap(_MNode);
					Color_swap(_GNode);

					Right_Rotation(_GNode);
				}
				else if (_GNode->pRight == _PNode//부모가 할아버지 오른쪽
					&& _PNode->pLeft == _MNode)//내가 부모의 왼쪽자식
				{
					Right_Rotation(_PNode);

					Color_swap(_MNode);
					Color_swap(_GNode);

					Left_Rotation(_GNode);
				}
			}
			else//삼촌이 레드트리일때
			{
				if (_GNode->pColor == e_BLACK)//블랙이라면 레드로
					Color_swap(_GNode);

				Color_swap(_GNode->pLeft);//레드를 블랙으로
				Color_swap(_GNode->pRight);//레드를 블랙으로

				if (_GNode == pRoot)
					_GNode->pColor = e_BLACK;

				if(_GNode->pColor==e_RED)//만약 바꾼 할아버지가 빨간색이라면
					RedBlack_Insert_Refresh(_GNode);//다시 할아버지부터 검증을 들어간다.
			}
		}
	}

	void Right_Rotation(Node* sNode)
	{
		if (sNode == nil || sNode->pLeft == nil)
			return;

		Node* lNode = sNode->pLeft;
		if (lNode->pRight != nil)
		{
			sNode->pLeft = lNode->pRight;
			sNode->pLeft->pParent = sNode;
		}
		else
		{
			sNode->pLeft = nil;
		}
		lNode->pRight = sNode;

		lNode->pParent = sNode->pParent;
		sNode->pParent = lNode;
		lNode->pParent->pRight = lNode;
		
		if (lNode->pParent == nil)//만약 이동하려는 노드가 Root노드라면
		{
			pRoot = lNode;//LNode를 루트로 바꿔준다.
		}
	}

	void  Left_Rotation(Node* sNode)
	{
		if (sNode == nil || sNode->pRight == nil)
			return;

		Node* lNode = sNode->pRight;
		if (lNode->pLeft != nil)
		{
			sNode->pRight = lNode->pLeft;
			sNode->pRight->pParent = sNode;
		}
		else
		{
			sNode->pRight = nil;
		}
		lNode->pLeft = sNode;

		lNode->pParent = sNode->pParent;
		sNode->pParent = lNode;
		lNode->pParent->pLeft = lNode;

		if (lNode->pParent == nil)//만약 이동하려는 노드가 Root노드라면
			pRoot = lNode;//LNode를 루트로 바꿔준다.
	}

	bool Color_swap(Node* pNode)
	{
		if (pNode == nil || pNode == nullptr)
			return false;

		if (pNode->pColor == e_BLACK)
			pNode->pColor = e_RED;
		else
			pNode->pColor = e_BLACK;

		return true;
	}

	void Tree_black_Insert(int data)
	{
		if (data <= 0) //0이하의 데이터는 처리하지 않겠다.
			return;

		if (pRoot == nullptr)//루트 노드가 없다면
		{
			pRoot = new Node;
			if (pRoot == nullptr)
				return;
			pRoot->pColor = e_BLACK;//루트노드는 반드시 검정
			pRoot->Data = data;
			pRoot->pParent = nullptr;//루트노드 부모는 없다.
			pRoot->pLeft = nullptr;
			pRoot->pRight = nullptr;
			//루트 노드 생성하고 함수를 종료한다.
			return;
		}

		Node* pNode = nullptr;
		Node* cNode = pRoot;//루트 노드부터 시작
		Node* insertNode = nullptr;

		while (cNode != nullptr)//넣어야하는 위치를 탐색한다.
		{
			if (cNode->Data == data)//중복데이터는 절대없도록한다.
				return;

			pNode = cNode;//부모 노드를 저장한다.

			if (cNode->Data > data) //현재 노드보다 데이터가 작다면 왼쪽으로 가야한다.
			{
				cNode = cNode->pLeft;
			}
			else//현재 노드보다 데이터가 크다면 오른쪽으로 가야한다.
			{
				cNode = cNode->pRight;
			}
		}

		//빠져나왔다는건 리프노드에 도달했다는 뜻
		//데이터 노드를 만들고
		insertNode = new Node;
		insertNode->Data = data;
		insertNode->pColor = e_BLACK;//맨처음 입력시 반드시 빨간색으로 세팅한다.
		insertNode->pParent = pNode;//부모를 넣는다.
		insertNode->pLeft = nullptr;
		insertNode->pRight = nullptr;

		if (pNode->Data > data)//부모 노드보다 작다면 왼쪽으로
			pNode->pLeft = insertNode;
		else//부모 노드보다 크다면 오른쪽으로
			pNode->pRight = insertNode;

		///////////////////////////////////////////////////////////
		///여기부터 레드블랙트리 정리//////////////////////////////
		//////////////////////////////////////////////////////////

		if (insertNode == pRoot)
			pRoot->pColor = e_BLACK;

	}

	int Tree_Count(Node* root)
	{
		int count = 0;//개수를 초기화해야 하나씩 카운트된다.안하면 팩토리얼되버림
		if (root != nullptr)
		{
			count = 1 + Tree_Count(root->pLeft) + Tree_Count(root->pRight);
		}
		return count;
	}

	int Depth_Count(Node* root)
	{
		int height = 0;
		if (root != nullptr)
		{
			int left = Depth_Count(root->pLeft);//왼쪽노드 다확인하고 리턴
			int right = Depth_Count(root->pRight);//오른쪽노드 다 확인하고 리턴

			//루트 노드는 반드시 들어가니까 1카운트하고
			height = 1;
			if (left > right)
				height += left;
			else
				height += right;
		}
		return height;

	}

	//삭제
	bool Tree_Delete(int data)
	{
		Node* pNode = nullptr;
		Node* cNode = pRoot;

		bool delete_color;

		//우선 삭제해야하는 노드의 위치를 탐색한다.
		while (cNode != nullptr)
		{
			if (cNode->Data == data)//삭제해야하는 노드에 도달했다면
				break;//반복문을 탈출한다.

			pNode = cNode;//삭제해야하는 노드의 부모노드를 기록한다.

			if (cNode->Data > data) //현재 노드보다 데이터가 작다면 왼쪽으로 가야한다.
			{
				cNode = cNode->pLeft;
			}
			else//현재 노드보다 데이터가 크다면 오른쪽으로 가야한다.
			{
				cNode = cNode->pRight;
			}
		}

		if (cNode == nullptr)//데이터가 없다는 뜻이므로 삭제하지 않고 무시한다.
			return false;

		//현재 checkNode 위치가 삭제해야하는 위치다.
		//삭제할 노드가(1) 단말 노드인 경우
		if (cNode->pLeft == nullptr && cNode->pRight == nullptr)//자식이 없는 노드라면
		{
			if (pNode == nullptr)//루트 노드일경우
				pRoot = nullptr;//루트 노드를 제거한다.->이반복문 탈출시 cNode로 루트 자동 제거됨
			//return true;//마지막 노드니까 삭제하지 않게하겠다.->이건뭐 정책정하기 나름인듯?
			else if (pNode->pLeft == cNode) //부모노드의 왼쪽노드라면
				pNode->pLeft = nullptr;//왼쪽노드 초기화
			else//부모노드의 오른쪽노드라면
				pNode->pRight = nullptr;//오른쪽노드 초기화
		}
		//삭제할 노드가(3) 두 개의 서브트리를 가지고 있는 경우
		else if (cNode->pLeft != nullptr && cNode->pRight != nullptr)
		{
			Node* nNode = cNode;//원본 위치 저장
			pNode = nullptr;

			cNode = cNode->pRight;//오른쪽노드로 한번이동

			//오른쪽 서브트리 중 가장 작은 노드를 찾는다.
			while (cNode->pLeft != nullptr)
			{
				pNode = cNode;//삭제해야하는 노드의 부모노드를 기록한다.
				cNode = cNode->pLeft;//노드 왼쪽으로 이동
			}

			nNode->Data = cNode->Data;//삭제한 원본노드

			if (pNode != nullptr)//루트노드가 아닐경우
				pNode->pLeft = cNode->pRight;//부모노드가 루트가되어 삭제되야 하는값을 자식으로 받아야한다.
			else//루트노드일경우
				nNode->pRight = cNode->pRight;//부모가 루트노드라면
			//바로 오른쪽 노드를 받는것 오른쪽노드의 자식을 받는다 nullptr이라면 그것대로 상관없다.
		}
		//삭제할 노드가(2) 하나의 서브트리만 가지고 있는 경우
		else if (cNode->pLeft != nullptr)//왼쪽 노드만 있을경우
		{
			if (pNode == nullptr) //루트 노드일 경우
			{//오른쪽에 아무 노드도 없다는거니까 루트를 지우고 그냥 한칸 당긴다.
				Node* nNode = pRoot->pLeft;//스왑할 노드 위치저장
				pRoot->Data = cNode->pLeft->Data;//루트 노드 데이터업데이트
				pRoot->pRight = cNode->pLeft->pRight;//루트 노드 데이터 업데이트
				pRoot->pLeft = cNode->pLeft->pLeft;//루트노드 데이터 업데이트
				cNode = nNode;//스왑한 노드를 지운다.
			}
			else if (pNode->Data > cNode->Data)//삭제해야하는 데이터가 부모 노드보다 작다면
				pNode->pLeft = cNode->pLeft;//나의 왼쪽자식은 부모노드의 왼쪽으로 이동시킨다.
			else
				pNode->pRight = cNode->pLeft;//나의 왼쪽자식을 부모노드의 오른쪽으로 이동시킨다.
		}
		else if (cNode->pRight != nullptr)//오른쪽노드만 있을경우
		{
			if (pNode == nullptr)//루트 노드일 경우
			{//왼쪽에 아무 노드도 없다는거니까 그냥 한칸 당긴다
				Node* nNode = pRoot->pRight;//원본 위치 저장
				pRoot->Data = cNode->pRight->Data;
				pRoot->pLeft = cNode->pRight->pLeft;
				pRoot->pRight = cNode->pRight->pRight;
				cNode = nNode;//삭제를위해 원본 cNode업데이트
			}
			else if (pNode->Data > cNode->Data)//삭제하는 데이터가 부모노드보다 작다면
				pNode->pLeft = cNode->pRight;//나의 오른쪽 자식을 부모노드의 왼쪽으로 이동시킨다.
			else
				pNode->pRight = cNode->pRight;//나의 오른쪽 자식을 부모노드의 오른쪽으로 이동시킨다.
		}


		cNode->pColor;

		delete cNode;//노드제거

		return true;//트루 리턴
	}

	//검색
	bool Tree_Search(int data)
	{
		Node* checkNode = pRoot;//루트 노드부터 시작

		while (checkNode != nullptr)
		{
			if (checkNode->Data == data)//데이터가 있다면
				return true;

			if (checkNode->Data > data) //현재 노드보다 데이터가 작다면 왼쪽으로 가야한다.
			{
				checkNode = checkNode->pLeft;
			}
			else//현재 노드보다 데이터가 크다면 오른쪽으로 가야한다.
			{
				checkNode = checkNode->pRight;
			}
		}
		return false;
	}

	//단순 중위순회 출력
	void All_print(Node* pNode)
	{
		if (pNode == nullptr)
			return;

		//중위 순회로 모든 데이터 출력
		All_print(pNode->pLeft);

		printf("%d ", pNode->Data);

		All_print(pNode->pRight);
	}


	// 후위 순회로 간편하게 확인 할 수 있게 한다.
	void printBinaryTree(Node* pNode, bool isLeft, int space = 0, int height = 5)
	{
		// 기본 케이스
		if (pNode == nullptr || pNode == nil) {
			return;
		}

		// 레벨 사이의 거리 증가
		space += height;

		// 오른쪽 자식을 먼저 출력
		printBinaryTree(pNode->pRight, true, space);
		cout << endl;

		// 공백으로 채운 후 현재 노드를 인쇄합니다.
		for (int i = height; i < space - 1; i++) {
			cout << ' ';
		}
		if (pNode == pRoot)//루트 노드일때
		{
			cout << "-" << pNode->Data;
		}
		else if (isLeft)//자식노드일때
		{
			cout << "┏  " << pNode->Data;
		}
		else {

			cout << "┗  " << pNode->Data;
		}

		// 왼쪽 자식 출력
		cout << endl;
		printBinaryTree(pNode->pLeft, false, space);

	}

	Node* GetRootNode() { return pRoot; }

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

	// 이진 트리의 분기를 인쇄하는 도우미 함수
	void showTrunks(Trunk* p)
	{
		if (p == nullptr) {
			return;
		}

		showTrunks(p->prev);
		cout << p->str;
	}

	void printTree(Node* root, Trunk* prev, bool isLeft)
	{
		if (root == nullptr || root == nil) {
			return;
		}

		string prev_str = "    ";
		Trunk* trunk = new Trunk(prev, prev_str);

		printTree(root->pRight, trunk, true);

		if (!prev) {
			trunk->str = "---";
		}
		else if (isLeft)
		{
			trunk->str = ".---";
			prev_str = "   |";
		}
		else {
			trunk->str = "`---";
			prev->str = prev_str;
		}

		showTrunks(trunk);
		if (root->pColor == e_BLACK)//true 검정 B출력
			cout << " " << root->Data << "B" << endl;
		else
			cout << " " << root->Data << "R" << endl;
		if (prev) {
			prev->str = prev_str;
		}
		trunk->str = "   |";

		printTree(root->pLeft, trunk, false);
	}

	bool BSTCHECK(Node* pNode)
	{
		//BST트리인지 검증
		queue<Node*>q;
		q.push(pRoot);

		while (!q.empty())//큐가 빌때까지
		{
			Node* _qNode = q.front();
			q.pop();

			//왼쪽노드가 나보다 크다면 이진트리일수가 없다.
			if (_qNode->pLeft->Data > _qNode->Data
				&& _qNode->pLeft != nullptr)
				return false;
			else
				q.push(_qNode->pLeft);
			//오른쪽 노드가 나보다 작다면
			if (_qNode->pRight->Data < _qNode->Data
				&& _qNode->pRight != nullptr)
				return false;
			else
				q.push(_qNode->pRight);

			//printf("%d ", _qNode->Data);
		}
		printf("\n");
		return true;
		//오른쪽노드가 나보다 작지 않다면 fasle

	}

	void LevelPrint(Node* pNode)
	{
		if (pNode == nullptr)
			return;

		queue<Node*>q;
		q.push(pNode);

		while (!q.empty())//큐가 빌때까지
		{
			Node* _qNode = q.front();
			q.pop();
			
			if (_qNode->pLeft != nullptr && _qNode != nil)
				q.push(_qNode->pLeft);

			if (_qNode->pRight != nullptr && _qNode != nil)
				q.push(_qNode->pRight);

			if(_qNode != nil)
				printf("%d ", _qNode->Data);
		}
		printf("\n");
	}

	void BST_Insert(int data)
	{
		if (data <= 0) //0이하의 데이터는 처리하지 않겠다.
			return;

		if (pRoot == nullptr)//루트노드가 없다면
		{
			pRoot = new Node;
			pRoot->pColor = e_BLACK;//블랙
			pRoot->Data = data;
			pRoot->pParent = nil;//루트노드 부모는 없다.
			pRoot->pLeft = nil;
			pRoot->pRight = nil;
			return;//루트노드 생성하고 종료
		}

		//루트노드가 있는 상태에서의 데이터 입력
		Node* pNode = nullptr;
		Node* cNode = pRoot;//루트 노드부터 시작
		Node* insertNode = nullptr;

		while (cNode != nil)//넣어야하는 위치를 탐색한다.
		{
			if (cNode->Data == data)//중복데이터는 절대없도록한다.
				return;

			pNode = cNode;//부모 노드를 저장한다.

			if (cNode->Data > data) //현재 노드보다 데이터가 작다면 왼쪽으로 가야한다.
			{
				cNode = cNode->pLeft;
			}
			else//현재 노드보다 데이터가 크다면 오른쪽으로 가야한다.
			{
				cNode = cNode->pRight;
			}
		}

		//빠져나왔다는건 리프노드에 도달했다는 뜻
		//데이터 노드를 만들고
		insertNode = new Node;
		insertNode->Data = data;
		insertNode->pColor = e_RED;//맨처음 입력시 반드시 빨간색으로 세팅한다.
		insertNode->pParent = pNode;//부모를 넣는다.
		insertNode->pLeft = nil;
		insertNode->pRight = nil;

		if (pNode->Data > data)//부모 노드보다 작다면 왼쪽으로
			pNode->pLeft = insertNode;
		else//부모 노드보다 크다면 오른쪽으로
			pNode->pRight = insertNode;


	}
};