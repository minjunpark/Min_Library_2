#include "CRT2.h"

CREDBLACKTREE2::CREDBLACKTREE2()
{
	nil = new Node;
	nil->pParent = nullptr;
	nil->pColor = e_BLACK;
	nil->pLeft = nullptr;
	nil->pRight = nullptr;
	black_depth = 0;
	insert_Count = 0;
	delete_Count = 0;

	pRoot = nullptr;

};

CREDBLACKTREE2::CREDBLACKTREE2(int data)
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

CREDBLACKTREE2::~CREDBLACKTREE2()
{
	delete_clear(pRoot);

	delete nil;

}

void CREDBLACKTREE2::delete_clear(Node* pNode)
{
	if (pNode == nullptr || pNode == nil)
		return;

	//중위 순회로 모든 데이터 순회
	delete_clear(pNode->pLeft);
	delete_clear(pNode->pRight);
	delete pNode;//모든 할당된 노드제거
};

//삽입
void CREDBLACKTREE2::RedBlack_Insert(int data)
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
		insert_Count++;
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

	insert_Count++;

	if (pNode->Data > data)//부모 노드보다 작다면 왼쪽으로
		pNode->pLeft = insertNode;
	else//부모 노드보다 크다면 오른쪽으로
		pNode->pRight = insertNode;

	///////////////////////////////////////////////////////////
	///여기부터 레드블랙트리 정리//////////////////////////////
	///////////////////////////////////////////////////////////

	RedBlack_Insert_Refresh(insertNode);
}

void CREDBLACKTREE2::RedBlack_Insert_Refresh(Node* pNode)
{
	Node* _MNode = pNode;
	Node* _PNode = _MNode->pParent;
	Node* _GNode = _PNode->pParent;
	Node* _UNode;

	while (1)
	{
		_PNode = _MNode->pParent;
		_GNode = _PNode->pParent;

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
					//1.부모와 할아버지의 색을 뒤집어서 바꾼 후
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
				if (_GNode->pColor == e_BLACK)//할아버지가 블랙이라면 레드로
					Color_swap(_GNode);

				Color_swap(_GNode->pLeft);//할아버지의 왼쪽 자식 레드를 블랙으로->여기오는 조건자체가 시작부터 부모는 레드고
				Color_swap(_GNode->pRight);//할아버지의 왼쪽 자식 레드를 블랙으로->삼촌이 레드트리기 이기때문에

				if (_GNode == pRoot)//만약 할아버지가 루트노드라면 블랙노드로 바꿔준다.
					_GNode->pColor = e_BLACK;

				if (_GNode->pColor == e_RED)//만약 이뒤에 할아버지가 레드로 바뀐상태라면
				{
					//RedBlack_Insert_Refresh(_GNode);//다시 할아버지부터 검증을 들어간다.
					_MNode = _GNode;
				}
			}
		}

		if (_MNode != _GNode)
		{//만약 노드가 같지 않다면 삼촌이 레드트리가 아니며
		 //나의 할아버지가 루트가 아니거나 할아버지가 레드로 바뀐게 아니라 블랙인 상태이기 때문에
			break;
		}

		if (pRoot->pColor == e_RED)//루트노드가 레드라면 블랙으로 바꿔준다.
			pRoot->pColor = e_BLACK;
	}
}

void CREDBLACKTREE2::Right_Rotation(Node* sNode)
{
	//if (sNode == nil || sNode->pLeft == nil)//돌리려는곳이 닐노드면 돌리지 않는다.
	//	return;

	Node* lNode = sNode->pLeft;
	//if (lNode == nil || lNode == nullptr)//회전하려는데 왼쪽노드 데이터가 없으면 회전불가
	//	return;

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

	if (lNode->pParent->pLeft == sNode)
		lNode->pParent->pLeft = lNode;
	else
		lNode->pParent->pRight = lNode;

	sNode->pParent = lNode;

	if (lNode->pParent == nil)//만약 이동하려는 노드가 Root노드라면
	{
		pRoot = lNode;//LNode를 루트로 바꿔준다.
	}
}



void  CREDBLACKTREE2::Left_Rotation(Node* sNode)
{
	//if (sNode == nil || sNode->pRight == nil)//돌리려는곳이 닐노드면 돌리지 않는다.
	//	return;

	Node* lNode = sNode->pRight;

	//if (lNode == nil || lNode == nullptr)//회전하려는데 오른쪽 노드 데이터가 없다면 회전불가
	//	return;

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

	if (lNode->pParent->pLeft == sNode)
		lNode->pParent->pLeft = lNode;
	else
		lNode->pParent->pRight = lNode;

	sNode->pParent = lNode;

	if (lNode->pParent == nil)//만약 이동하려는 노드가 Root노드라면
		pRoot = lNode;//LNode를 루트로 바꿔준다.
}


void CREDBLACKTREE2::Right_Delete_Rotation(Node* sNode)
{
	//if (sNode == nil || sNode->pLeft == nil)//돌리려는곳이 닐노드면 돌리지 않는다.
	//	return;

	Node* lNode = sNode->pLeft;
	//if (lNode == nil || lNode == nullptr)//회전하려는데 왼쪽노드 데이터가 없으면 회전불가
	//	return;

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

	if (lNode->pParent->pLeft == sNode)
		lNode->pParent->pLeft = lNode;
	else
		lNode->pParent->pRight = lNode;

	sNode->pParent = lNode;

	if (lNode->pParent == nil)//만약 이동하려는 노드가 Root노드라면
	{
		pRoot = lNode;//LNode를 루트로 바꿔준다.
	}
}



void  CREDBLACKTREE2::Left_Delete_Rotation(Node* sNode)
{
	//if (sNode == nil || sNode->pRight == nil)//돌리려는곳이 닐노드면 돌리지 않는다.
	//	return;

	Node* lNode = sNode->pRight;

	//if (lNode == nil || lNode == nullptr)//회전하려는데 오른쪽 노드 데이터가 없다면 회전불가
	//	return;

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

	if (lNode->pParent->pLeft == sNode)
		lNode->pParent->pLeft = lNode;
	else
		lNode->pParent->pRight = lNode;

	sNode->pParent = lNode;

	if (lNode->pParent == nil)//만약 이동하려는 노드가 Root노드라면
		pRoot = lNode;//LNode를 루트로 바꿔준다.
}



bool CREDBLACKTREE2::Color_swap(Node* pNode)
{
	if (pNode == nil || pNode == nullptr)
		return false;

	if (pNode->pColor == e_BLACK)
		pNode->pColor = e_RED;
	else
		pNode->pColor = e_BLACK;

	return true;
}

int CREDBLACKTREE2::Tree_Count(Node* pNode)
{
	int count = 0;//개수를 초기화해야 하나씩 카운트된다.안하면 팩토리얼되버림
	if (pNode != nullptr && pNode != nil)
	{
		count = 1 + Tree_Count(pNode->pLeft) + Tree_Count(pNode->pRight);
	}
	return count;
}

int CREDBLACKTREE2::Depth_Count(Node* root)
{
	int height = 0;
	if (root != nullptr && root != nil)
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
bool CREDBLACKTREE2::RedBlack_Delete(int data)
{
	Node* pNode = nil;
	Node* cNode = pRoot;
	Node* sNode = nullptr;
	if (delete_Count == 13)
	{
		printf("delete count %d\n", delete_Count);
	}
	printf("delete count %d\n", delete_Count);

	//우선 삭제해야하는 노드의 위치를 탐색한다.
	while (cNode != nil)
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

	if (cNode == nil)//데이터가 없다는 뜻이므로 삭제하지 않고 무시한다.
		return false;

	//현재 cNode 위치가 삭제해야하는 위치다.
	//삭제할 노드가(1) 단말 노드인 경우
	if (cNode->pColor == e_RED) //삭제되는 노드가 레드노드라면 이진트리방식으로 그냥 삭제해버려도 이상없다.
	{
		if (cNode->pLeft == nil && cNode->pRight == nil)//자식이 없는 노드라면
		{
			if (pNode == nil)//루트 노드일경우
				pRoot = nullptr;//루트 노드를 제거한다.->이반복문 탈출시 cNode로 루트 자동 제거됨
			else if (pNode->pLeft == cNode) //부모노드의 왼쪽노드라면경
			{
				pNode->pLeft = nil;//왼쪽노드 nil변경
			}
			else//부모노드의 오른쪽노드라면
			{
				pNode->pRight = nil;//오른쪽노드 초기화
			}
		}
		//삭제할 노드가(3) 두 개의 서브트리를 가지고 있는 경우
		else if (cNode->pLeft != nil && cNode->pRight != nil)
		{
			Node* nNode = cNode;//원본 위치 저장
			pNode = nil;

			//cNode = cNode->pRight;//오른쪽노드로 한번이동

			cNode = cNode->pLeft;//왼쪽노드로 한번이동

			//왼쪽 서브트리중 가장 큰놈을 찾는다.
			while (cNode->pRight != nil)
			{
				pNode = cNode;//삭제해야하는 노드의 부모노드를 기록한다.
				cNode = cNode->pRight;//노드 오른쪽으로 이동
			}

			nNode->Data = cNode->Data;//삭제한 원본노드 업데이트

			if (pNode != nil)//루트노드가 아닐경우
			{
				pNode->pRight = cNode->pLeft;//부모노드가 루트가되어 삭제되야 하는값을 자식으로 받아야한다.
				cNode->pLeft->pParent = pNode;
			}
			else if (pNode == nil)//루트노드일경우
			{
				nNode->pLeft = cNode->pLeft;//부모가 루트노드라면
				cNode->pLeft->pParent = nNode;
			}

			//바로 오른쪽 노드를 받는것 오른쪽노드의 자식을 받는다 nil이라면 그것대로 상관없다.
		}
		//삭제할 노드가(2) 하나의 서브트리만 가지고 있는 경우
		else if (cNode->pLeft != nil)//왼쪽 노드만 있을경우
		{
			if (pNode == nil) //루트 노드일 경우
			{//오른쪽에 아무 노드도 없다는거니까 루트를 지우고 그냥 한칸 당긴다.
				Node* nNode = pRoot->pLeft;//스왑할 노드 위치저장
				pRoot->Data = cNode->pLeft->Data;//루트 노드 데이터업데이트
				pRoot->pRight = cNode->pLeft->pRight;//루트 노드 데이터 업데이트
				pRoot->pLeft = cNode->pLeft->pLeft;//루트노드 데이터 업데이트
				cNode = nNode;//스왑한 노드를 지운다.
			}
			else if (pNode->Data > cNode->Data)//삭제해야하는 데이터가 부모 노드보다 작다면
			{
				pNode->pLeft = cNode->pLeft;//나의 왼쪽자식은 부모노드의 왼쪽으로 이동시킨다.
				cNode->pLeft->pParent = pNode;
			}
			else
			{
				pNode->pRight = cNode->pLeft;//나의 왼쪽자식을 부모노드의 오른쪽으로 이동시킨다.
				cNode->pLeft->pParent = pNode;
			}
		}
		else if (cNode->pRight != nil)//오른쪽노드만 있을경우
		{
			if (pNode == nil)//루트 노드일 경우
			{//왼쪽에 아무 노드도 없다는거니까 그냥 한칸 당긴다
				Node* nNode = pRoot->pRight;//원본 위치 저장
				pRoot->Data = cNode->pRight->Data;
				pRoot->pLeft = cNode->pRight->pLeft;
				pRoot->pRight = cNode->pRight->pRight;
				cNode = nNode;//삭제를위해 원본 cNode업데이트
			}
			else if (pNode->Data > cNode->Data)//삭제하는 데이터가 부모노드보다 작다면
			{
				pNode->pLeft = cNode->pRight;//나의 오른쪽 자식을 부모노드의 왼쪽으로 이동시킨다.
				cNode->pRight->pParent = pNode;
			}
			else
			{
				pNode->pRight = cNode->pRight;//나의 오른쪽 자식을 부모노드의 오른쪽으로 이동시킨다.
				cNode->pRight->pParent = pNode;
			}
		}
	}
	//블랙이라면
	else if (cNode->pColor == e_BLACK)
	{
		//현재 cNode 위치가 삭제해야하는 위치다.
		//삭제할 노드가(1) 단말 노드인 경우
		if (cNode->pLeft == nil && cNode->pRight == nil)//자식이 없는 노드라면
		{

		}
		//삭제할 노드가(3) 두 개의 서브트리를 가지고 있는 경우
		else if (cNode->pLeft != nil && cNode->pRight != nil)
		{
			Node* nNode = cNode;//원본 위치 저장
			pNode = nil;

			//cNode = cNode->pRight;//오른쪽노드로 한번이동

			cNode = cNode->pLeft;//왼쪽노드로 한번이동

			//왼쪽 서브트리중 가장 큰놈을 찾는다.
			while (cNode->pRight != nil)
			{
				pNode = cNode;//삭제해야하는 노드의 부모노드를 기록한다.
				cNode = cNode->pRight;//노드 오른쪽으로 이동
			}

			nNode->Data = cNode->Data;//삭제한 원본노드 업데이트
			/// <summary>
			/// //////////////////
			/// </summary>
			/// <param name="data"></param>
			/// <returns></returns>
			if (cNode->pColor == e_RED) //삭제되는 노드가 레드노드라면 이진트리방식으로 그냥 삭제해버려도 이상없다.
			{
				if (cNode->pLeft == nil && cNode->pRight == nil)//자식이 없는 노드라면
				{
					if (pNode == nil)//루트 노드일경우
						pRoot = nullptr;//루트 노드를 제거한다.->이반복문 탈출시 cNode로 루트 자동 제거됨
					else if (pNode->pLeft == cNode) //부모노드의 왼쪽노드라면경
					{
						pNode->pLeft = nil;//왼쪽노드 nil변경
					}
					else//부모노드의 오른쪽노드라면
					{
						pNode->pRight = nil;//오른쪽노드 초기화
					}
				}
				//삭제할 노드가(3) 두 개의 서브트리를 가지고 있는 경우
				else if (cNode->pLeft != nil && cNode->pRight != nil)
				{
					Node* nNode = cNode;//원본 위치 저장
					pNode = nil;

					//cNode = cNode->pRight;//오른쪽노드로 한번이동

					cNode = cNode->pLeft;//왼쪽노드로 한번이동

					//왼쪽 서브트리중 가장 큰놈을 찾는다.
					while (cNode->pRight != nil)
					{
						pNode = cNode;//삭제해야하는 노드의 부모노드를 기록한다.
						cNode = cNode->pRight;//노드 오른쪽으로 이동
					}

					nNode->Data = cNode->Data;//삭제한 원본노드 업데이트

					if (pNode != nil)//루트노드가 아닐경우
					{
						pNode->pRight = cNode->pLeft;//부모노드가 루트가되어 삭제되야 하는값을 자식으로 받아야한다.
						cNode->pLeft->pParent = pNode;
					}
					else if (pNode == nil)//루트노드일경우
					{
						nNode->pLeft = cNode->pLeft;//부모가 루트노드라면
						cNode->pLeft->pParent = nNode;
					}

					//바로 오른쪽 노드를 받는것 오른쪽노드의 자식을 받는다 nil이라면 그것대로 상관없다.
				}
				//삭제할 노드가(2) 하나의 서브트리만 가지고 있는 경우
				else if (cNode->pLeft != nil)//왼쪽 노드만 있을경우
				{
					if (pNode == nil) //루트 노드일 경우
					{//오른쪽에 아무 노드도 없다는거니까 루트를 지우고 그냥 한칸 당긴다.
						Node* nNode = pRoot->pLeft;//스왑할 노드 위치저장
						pRoot->Data = cNode->pLeft->Data;//루트 노드 데이터업데이트
						pRoot->pRight = cNode->pLeft->pRight;//루트 노드 데이터 업데이트
						pRoot->pLeft = cNode->pLeft->pLeft;//루트노드 데이터 업데이트
						cNode = nNode;//스왑한 노드를 지운다.
					}
					else if (pNode->Data > cNode->Data)//삭제해야하는 데이터가 부모 노드보다 작다면
					{
						pNode->pLeft = cNode->pLeft;//나의 왼쪽자식은 부모노드의 왼쪽으로 이동시킨다.
						cNode->pLeft->pParent = pNode;
					}
					else
					{
						pNode->pRight = cNode->pLeft;//나의 왼쪽자식을 부모노드의 오른쪽으로 이동시킨다.
						cNode->pLeft->pParent = pNode;
					}
				}
				else if (cNode->pRight != nil)//오른쪽노드만 있을경우
				{
					if (pNode == nil)//루트 노드일 경우
					{//왼쪽에 아무 노드도 없다는거니까 그냥 한칸 당긴다
						Node* nNode = pRoot->pRight;//원본 위치 저장
						pRoot->Data = cNode->pRight->Data;
						pRoot->pLeft = cNode->pRight->pLeft;
						pRoot->pRight = cNode->pRight->pRight;
						cNode = nNode;//삭제를위해 원본 cNode업데이트
					}
					else if (pNode->Data > cNode->Data)//삭제하는 데이터가 부모노드보다 작다면
					{
						pNode->pLeft = cNode->pRight;//나의 오른쪽 자식을 부모노드의 왼쪽으로 이동시킨다.
						cNode->pRight->pParent = pNode;
					}
					else
					{
						pNode->pRight = cNode->pRight;//나의 오른쪽 자식을 부모노드의 오른쪽으로 이동시킨다.
						cNode->pRight->pParent = pNode;
					}
				}
				delete cNode;//노드제거
				delete_Count++;
				return true;//트루 리턴
			}

			/////////////////////////////////////////

			/// <summary>
			/// /////////////////////
			/// </summary>
			/// <param name="data"></param>
			/// <returns></returns>
			if (pNode != nil)//루트노드가 아닐경우
			{
				pNode->pRight = cNode->pLeft;//부모노드가 루트가되어 삭제되야 하는값을 자식으로 받아야한다.
				cNode->pLeft->pParent = pNode;
			}
			else if (pNode == nil)//루트노드일경우
			{
				nNode->pLeft = cNode->pLeft;//부모가 루트노드라면
				cNode->pLeft->pParent = nNode;
			}
			/// <summary>
			/// /////////////////////
			/// </summary>
			/// <param name="data"></param>
			/// <returns></returns>

			RedBlack_Delete_Refresh(cNode);//블랙노드라면 삭제절차를 거치기전에

			if (cNode->pLeft == nil && cNode->pRight == nil)//자식이 없는 노드라면
			{
				if (pNode == nil)//루트 노드일경우
					pRoot = nullptr;//루트 노드를 제거한다.->이반복문 탈출시 cNode로 루트 자동 제거됨
				else if (pNode->pLeft == cNode) //부모노드의 왼쪽노드라면경
				{
					pNode->pLeft = nil;//왼쪽노드 nil변경
				}
				else//부모노드의 오른쪽노드라면
				{
					pNode->pRight = nil;//오른쪽노드 초기화
				}
			}
			//삭제할 노드가(3) 두 개의 서브트리를 가지고 있는 경우
			else if (cNode->pLeft != nil && cNode->pRight != nil)
			{
				Node* nNode = cNode;//원본 위치 저장
				pNode = nil;

				cNode = cNode->pLeft;//왼쪽노드로 한번이동

				//왼쪽 서브트리중 가장 큰놈을 찾는다.
				while (cNode->pRight != nil)
				{
					pNode = cNode;//삭제해야하는 노드의 부모노드를 기록한다.
					cNode = cNode->pRight;//노드 오른쪽으로 이동
				}

				nNode->Data = cNode->Data;//삭제한 원본노드 업데이트

				if (pNode != nil)//루트노드가 아닐경우
				{
					pNode->pRight = cNode->pLeft;//부모노드가 루트가되어 삭제되야 하는값을 자식으로 받아야한다.
					cNode->pLeft->pParent = pNode;
				}
				else if (pNode == nil)//루트노드일경우
				{
					nNode->pLeft = cNode->pLeft;//부모가 루트노드라면
					cNode->pLeft->pParent = nNode;
				}
				//바로 오른쪽 노드를 받는것 오른쪽노드의 자식을 받는다 nil이라면 그것대로 상관없다.
			}
			//삭제할 노드가(2) 하나의 서브트리만 가지고 있는 경우
			else if (cNode->pLeft != nil)//왼쪽 노드만 있을경우
			{
				if (pNode == nil) //루트 노드일 경우
				{//오른쪽에 아무 노드도 없다는거니까 루트를 지우고 그냥 한칸 당긴다.
					Node* nNode = pRoot->pLeft;//스왑할 노드 위치저장
					pRoot->Data = cNode->pLeft->Data;//루트 노드 데이터업데이트
					pRoot->pRight = cNode->pLeft->pRight;//루트 노드 데이터 업데이트
					pRoot->pLeft = cNode->pLeft->pLeft;//루트노드 데이터 업데이트
					cNode = nNode;//스왑한 노드를 지운다.
				}
				else if (pNode->Data > cNode->Data)//삭제해야하는 데이터가 부모 노드보다 작다면
				{
					pNode->pLeft = cNode->pLeft;//나의 왼쪽자식은 부모노드의 왼쪽으로 이동시킨다.
					cNode->pLeft->pParent = pNode;
				}
				else
				{
					pNode->pRight = cNode->pLeft;//나의 왼쪽자식을 부모노드의 오른쪽으로 이동시킨다.
					cNode->pLeft->pParent = pNode;
				}
			}
			else if (cNode->pRight != nil)//오른쪽노드만 있을경우
			{
				if (pNode == nil)//루트 노드일 경우
				{//왼쪽에 아무 노드도 없다는거니까 그냥 한칸 당긴다
					Node* nNode = pRoot->pRight;//원본 위치 저장
					pRoot->Data = cNode->pRight->Data;
					pRoot->pLeft = cNode->pRight->pLeft;
					pRoot->pRight = cNode->pRight->pRight;
					cNode = nNode;//삭제를위해 원본 cNode업데이트
				}
				else if (pNode->Data > cNode->Data)//삭제하는 데이터가 부모노드보다 작다면
				{
					pNode->pLeft = cNode->pRight;//나의 오른쪽 자식을 부모노드의 왼쪽으로 이동시킨다.
					cNode->pRight->pParent = pNode;
				}
				else
				{
					pNode->pRight = cNode->pRight;//나의 오른쪽 자식을 부모노드의 오른쪽으로 이동시킨다.
					cNode->pRight->pParent = pNode;
				}
			}

			delete cNode;//노드제거
			delete_Count++;
			return true;//트루 리턴
		}
		//삭제할 노드가(2) 하나의 서브트리만 가지고 있는 경우
		else if (cNode->pLeft != nil)//왼쪽 노드만 있을경우
		{
			//if (pNode == nil) //루트 노드일 경우
			//{//오른쪽에 아무 노드도 없다는거니까 루트를 지우고 그냥 한칸 당긴다.
			//	Node* nNode = pRoot->pLeft;//스왑할 노드 위치저장
			//	pRoot->Data = cNode->pLeft->Data;//루트 노드 데이터업데이트
			//	pRoot->pRight = cNode->pLeft->pRight;//루트 노드 데이터 업데이트
			//	pRoot->pLeft = cNode->pLeft->pLeft;//루트노드 데이터 업데이트
			//	cNode = nNode;//스왑한 노드를 지운다.
			//}
			//else if (pNode->Data > cNode->Data)//삭제해야하는 데이터가 부모 노드보다 작다면
			//	pNode->pLeft = cNode->pLeft;//나의 왼쪽자식은 부모노드의 왼쪽으로 이동시킨다.
			//else
			//	pNode->pRight = cNode->pLeft;//나의 왼쪽자식을 부모노드의 오른쪽으로 이동시킨다.
		}
		else if (cNode->pRight != nil)//오른쪽노드만 있을경우
		{
			//if (pNode == nil)//루트 노드일 경우
			//{//왼쪽에 아무 노드도 없다는거니까 그냥 한칸 당긴다
			//	Node* nNode = pRoot->pRight;//원본 위치 저장
			//	pRoot->Data = cNode->pRight->Data;
			//	pRoot->pLeft = cNode->pRight->pLeft;
			//	pRoot->pRight = cNode->pRight->pRight;
			//	cNode = nNode;//삭제를위해 원본 cNode업데이트
			//}
			//else if (pNode->Data > cNode->Data)//삭제하는 데이터가 부모노드보다 작다면
			//	pNode->pLeft = cNode->pRight;//나의 오른쪽 자식을 부모노드의 왼쪽으로 이동시킨다.
			//else
			//	pNode->pRight = cNode->pRight;//나의 오른쪽 자식을 부모노드의 오른쪽으로 이동시킨다.
		}

		//먼저 레드블랙트리의 밸런스부터 정리한다.
		RedBlack_Delete_Refresh(cNode);//블랙노드라면 삭제절차를 거치기전에

		//그후 삭제할 노드의 상태를 판별해서 제거한다.
		if (cNode->pLeft == nil && cNode->pRight == nil)//자식이 없는 노드라면
		{
			if (pNode == nil)//루트 노드일경우
				pRoot = nullptr;//루트 노드를 제거한다.->이반복문 탈출시 cNode로 루트 자동 제거됨
			else if (pNode->pLeft == cNode) //부모노드의 왼쪽노드라면경
				pNode->pLeft = nil;//왼쪽노드 nil변경
			else//부모노드의 오른쪽노드라면
				pNode->pRight = nil;//오른쪽노드 초기화
		}
		//삭제할 노드가(3) 두 개의 서브트리를 가지고 있는 경우
		else if (cNode->pLeft != nil && cNode->pRight != nil)
		{
			Node* nNode = cNode;//원본 위치 저장
			pNode = nil;

			cNode = cNode->pLeft;//왼쪽노드로 한번이동

			//왼쪽 서브트리중 가장 큰놈을 찾는다.
			while (cNode->pRight != nil)
			{
				pNode = cNode;//삭제해야하는 노드의 부모노드를 기록한다.
				cNode = cNode->pRight;//노드 오른쪽으로 이동
			}

			nNode->Data = cNode->Data;//삭제한 원본노드 업데이트

			if (pNode != nil)//루트노드가 아닐경우
			{
				pNode->pRight = cNode->pLeft;//부모노드가 루트가되어 삭제되야 하는값을 자식으로 받아야한다.
				cNode->pLeft->pParent = pNode;
			}
			else if (pNode == nil)//루트노드일경우
			{
				nNode->pLeft = cNode->pLeft;//부모가 루트노드라면
				cNode->pLeft->pParent = nNode;
			}
			//바로 오른쪽 노드를 받는것 오른쪽노드의 자식을 받는다 nil이라면 그것대로 상관없다.
		}
		//삭제할 노드가(2) 하나의 서브트리만 가지고 있는 경우
		else if (cNode->pLeft != nil)//왼쪽 노드만 있을경우
		{
			if (pNode == nil) //루트 노드일 경우
			{//오른쪽에 아무 노드도 없다는거니까 루트를 지우고 그냥 한칸 당긴다.
				Node* nNode = pRoot->pLeft;//스왑할 노드 위치저장
				pRoot->Data = cNode->pLeft->Data;//루트 노드 데이터업데이트
				pRoot->pRight = cNode->pLeft->pRight;//루트 노드 데이터 업데이트
				pRoot->pLeft = cNode->pLeft->pLeft;//루트노드 데이터 업데이트
				cNode = nNode;//스왑한 노드를 지운다.
			}
			else if (pNode->Data > cNode->Data)//삭제해야하는 데이터가 부모 노드보다 작다면
			{
				pNode->pLeft = cNode->pLeft;//나의 왼쪽자식은 부모노드의 왼쪽으로 이동시킨다.
				cNode->pLeft->pParent = pNode;
			}
			else
			{
				pNode->pRight = cNode->pLeft;//나의 왼쪽자식을 부모노드의 오른쪽으로 이동시킨다.
				cNode->pLeft->pParent = pNode;
			}
		}
		else if (cNode->pRight != nil)//오른쪽노드만 있을경우
		{
			if (pNode == nil)//루트 노드일 경우
			{//왼쪽에 아무 노드도 없다는거니까 그냥 한칸 당긴다
				Node* nNode = pRoot->pRight;//원본 위치 저장
				pRoot->Data = cNode->pRight->Data;
				pRoot->pLeft = cNode->pRight->pLeft;
				pRoot->pRight = cNode->pRight->pRight;
				cNode = nNode;//삭제를위해 원본 cNode업데이트
			}
			else if (pNode->Data > cNode->Data)//삭제하는 데이터가 부모노드보다 작다면
			{
				pNode->pLeft = cNode->pRight;//나의 오른쪽 자식을 부모노드의 왼쪽으로 이동시킨다.
				cNode->pRight->pParent = pNode;
			}
			else
			{
				pNode->pRight = cNode->pRight;//나의 오른쪽 자식을 부모노드의 오른쪽으로 이동시킨다.
				cNode->pRight->pParent = pNode;
			}
		}

	}

	delete cNode;//노드제거
	delete_Count++;
	return true;//트루 리턴
}

void CREDBLACKTREE2::RedBlack_Delete_Refresh(Node* _DNode)//삭제정리
{
	//printTree(pRoot, nullptr, false);
	Node* _MNode;//나
	Node* _MLNode;//나의 왼족
	Node* _MRNode;//나의 왼족
	Node* _PNode;//나의부모

	Node* _SNode;//나의형제
	Node* _SLNode;//형제 왼쪽자식
	Node* _SRNode;//형제 오른쪽자식

	_MNode = _DNode;//삭제된 나를 넣는다.

	//_PNode = _MNode->pParent;//삭제된 노드의 부모

	//if (_PNode->pLeft == _MNode)//삭제된 노드의 왼쪽이 나라면
	//	_SNode = _PNode->pRight;//형제는 부모의 오른쪽노드
	//else
	//	_SNode = _PNode->pLeft;//형제는 부모의 왼쪽노드

	//_SLNode_ = _SNode->pLeft;//형제의 왼쪽 자식
	//_SRNode_ = _SNode->pRight;//형제의 오른쪽 자식

	//while (1)
	//{

	_MLNode = _MNode->pLeft;
	_MRNode = _MNode->pRight;
	_PNode = _MNode->pParent;//삭제될 노드의 부모

	if (_PNode->pLeft == _MNode)//삭제된 노드의 왼쪽이 나라면
		_SNode = _PNode->pRight;//형제는 부모의 오른쪽노드
	else if (_PNode->pRight == _MNode)
		_SNode = _PNode->pLeft;//형제는 부모의 왼쪽노드
	else if (_PNode->pLeft == nil)
		_SNode = _PNode->pRight;
	else if (_PNode->pRight == nil)
		_SNode = _PNode->pLeft;
	else
		_SNode = nil;

	_SLNode = _SNode->pLeft;//형제의 왼쪽 자식
	_SRNode = _SNode->pRight;//형제의 오른쪽 자식

	//이게 루트노드일 경우를 생각해둬야하네.
	//버전을 2개만들자
	//단말노드 버전하고 단말노드가 아닐때를 생각해야한다.

	if (_PNode->pLeft == _MNode)//내가 부모의 왼쪽자식이라면
	{
		//2.1 삭제 노드의 자식(기준노드)이 레드인 경우
		if (_MNode->pLeft->pColor == e_RED)//nil이 아니면서 왼쪽이 빨강색이라면
		{
			//자식이 레드라면 삭제노드(블랙)이 빠짐으로
			//삭제 노드의 자식(레드) 을 블랙으로 바꾸어줌으로 문제 해결
			//새로 자리한 노드가 레드라면 이를 블랙으로 바꾸는걸로 마무리 됨.
			_MNode->pLeft->pColor = e_BLACK;
			return;
		}

		//2.2 삭제 노드의 형제가 레드
		if (_SNode->pColor == e_RED)
		{
			_SNode->pColor = e_BLACK;//형제를 블랙으로 바꿈
			Left_Rotation(_PNode);//부모를 기준으로 좌회전!!!
			_PNode->pColor = e_RED;//기존 부모를 레드로 바꿈.
			_MNode = _MNode->pLeft;//그리고 현재노드 (삭제 후 들어온노드, 삭제노드의 자식) 기준으로 처음부터 재작업.
			RedBlack_Delete_Refresh(_MNode);
		}

		//2.3 삭제 노드의 형제가 블랙이고 형제의 양쪽 자식이 블랙(부모가 레드인지 아닌지에 따라)

		if (_SNode->pColor == e_BLACK &&
			_SLNode->pColor == e_BLACK &&
			_SRNode->pColor == e_BLACK)
		{
			_SNode->pColor = e_RED;//이때는 형제를 레드로
			//_MNode = _PNode;//그래서 내 부모를 기준으로 처음부터 다시 처리.
			RedBlack_Delete_Refresh(_PNode);
		}

		//2.4 삭제 노드의 형제가 블랙이고 형제의 왼자식이 레드, 오른자식은 블랙

		if (_SNode->pColor == e_BLACK &&
			_SLNode->pColor == e_RED &&
			_SRNode->pColor == e_BLACK)
		{
			_SLNode->pColor = e_BLACK;//형제의 왼자식을 블랙으로
			_SNode->pColor = e_RED;//형제를 레드로
			Right_Rotation(_SNode);//형제 기준으로 우회전
			_SRNode = _SNode;
			_SNode = _SLNode;
		}

		//2.5 삭제 노드의 형제가 블랙이고 형제의 오른자식이 레드

		if (_SNode->pColor == e_BLACK &&
			_SRNode->pColor == e_RED)
		{
			_SNode->pColor = _SNode->pParent->pColor;//형제 컬러를 부모 컬러로.
			_PNode->pColor = e_BLACK;//부모 컬러는 블랙
			_SNode->pRight->pColor = e_BLACK;//형제의 오른자식은 블랙
			Left_Rotation(_PNode);//부모기준 좌회원   
			return;
			//RedBlack_Delete_Refresh(_DNode);
		}
	}
	else//내가 부모의 오른쪽 자식이라면
	{
		//2.1 삭제 노드의 자식(기준노드)이 레드인 경우
		if (_MNode->pLeft->pColor == e_RED)//nil이 아니면서 왼쪽이 빨강색이라면
		{
			//자식이 레드라면 삭제노드(블랙)이 빠짐으로
			//삭제 노드의 자식(레드) 을 블랙으로 바꾸어줌으로 문제 해결
			//새로 자리한 노드가 레드라면 이를 블랙으로 바꾸는걸로 마무리 됨.
			_MNode->pLeft->pColor = e_BLACK;
			return;
		}

		//2.2 삭제 노드의 오른쪽 형제가 레드
		if (_SNode->pColor == e_RED)
		{
			_SNode->pColor = e_BLACK;//형제를 블랙으로 바꿈
			Left_Rotation(_PNode);//부모를 기준으로 좌회전!!!
			_PNode->pColor = e_RED;//기존 부모를 레드로 바꿈.
			_MNode = _MNode->pRight;//그리고 현재노드 (삭제 후 들어온노드, 삭제노드의 자식) 기준으로 처음부터 재작업.
			RedBlack_Delete_Refresh(_MNode);
			//continue;
		}

		//2.3 삭제 노드의 형제가 블랙이고 형제의 양쪽 자식이 블랙(부모가 레드인지 아닌지에 따라)
		if (_SNode->pColor == e_BLACK &&
			_SLNode->pColor == e_BLACK &&
			_SRNode->pColor == e_BLACK)
		{
			_SNode->pColor = e_RED;//이때는 형제를 레드로
			RedBlack_Delete_Refresh(_PNode);//내 부모를 기준으로 다시 리밸런스
			//return;
		}

		//2.4 삭제 노드의 형제가 블랙이고 형제의 왼자식이 레드, 오른자식은 블랙

		if (_SNode->pColor == e_BLACK &&
			_SRNode->pColor == e_RED &&
			_SLNode->pColor == e_BLACK)
		{
			_SRNode->pColor = e_BLACK;//형제의 오른자식을 블랙으로
			_SNode->pColor = e_RED;//형제를 레드로
			Left_Rotation(_SNode);//형제 기준으로 좌회전
			_SLNode = _SNode;
			_SNode = _SRNode;
		}

		//2.5 삭제 노드의 형제가 블랙이고 형제의 오른자식이 레드

		if (_SNode->pColor == e_BLACK &&
			_SLNode->pColor == e_RED)
		{
			_SNode->pColor = _SNode->pParent->pColor;//형제 컬러를 부모 컬러로.
			_PNode->pColor = e_BLACK;//부모 컬러는 블랙
			_SNode->pLeft->pColor = e_BLACK;//형제의 왼자식은 블랙
			Right_Rotation(_PNode);//부모기준 우회전  
			return;
			//RedBlack_Delete_Refresh(_DNode);
		}
	}
	//}
}

//삭제
bool CREDBLACKTREE2::Tree_Delete(int data)
{
	Node* pNode = nullptr;
	Node* cNode = pRoot;

	//우선 삭제해야하는 노드의 위치를 탐색한다.
	while (cNode != nil)
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

	if (cNode == nil)//데이터가 없다는 뜻이므로 삭제하지 않고 무시한다.
		return false;

	//현재 checkNode 위치가 삭제해야하는 위치다.
	//삭제할 노드가(1) 단말 노드인 경우
	if (cNode->pLeft == nil && cNode->pRight == nil)//자식이 없는 노드라면
	{
		if (pNode == nil)//루트 노드일경우
			pRoot = nullptr;//루트 노드를 제거한다.->이반복문 탈출시 cNode로 루트 자동 제거됨

		//return true;//마지막 노드니까 삭제하지 않게하겠다.->이건뭐 정책정하기 나름인듯?
		else if (pNode->pLeft == cNode) //부모노드의 왼쪽노드라면
			pNode->pLeft = nil;//왼쪽노드 초기화
		else//부모노드의 오른쪽노드라면
			pNode->pRight = nil;//오른쪽노드 초기화
	}
	//삭제할 노드가(3) 두 개의 서브트리를 가지고 있는 경우
	else if (cNode->pLeft != nil && cNode->pRight != nil)
	{
		Node* nNode = cNode;//원본 위치 저장
		pNode = nil;

		cNode = cNode->pRight;//오른쪽노드로 한번이동

		//오른쪽 서브트리 중 가장 작은 노드를 찾는다.
		while (cNode->pLeft != nil)
		{
			pNode = cNode;//삭제해야하는 노드의 부모노드를 기록한다.
			cNode = cNode->pLeft;//노드 왼쪽으로 이동
		}

		nNode->Data = cNode->Data;//삭제한 원본노드

		if (pNode != nil)//루트노드가 아닐경우
			pNode->pLeft = cNode->pRight;//부모노드가 루트가되어 삭제되야 하는값을 자식으로 받아야한다.
		else//루트노드일경우
			nNode->pRight = cNode->pRight;//부모가 루트노드라면
		//바로 오른쪽 노드를 받는것 오른쪽노드의 자식을 받는다 nullptr이라면 그것대로 상관없다.
	}
	//삭제할 노드가(2) 하나의 서브트리만 가지고 있는 경우
	else if (cNode->pLeft != nil)//왼쪽 노드만 있을경우
	{
		if (pNode == nil) //루트 노드일 경우
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
	else if (cNode->pRight != nil)//오른쪽노드만 있을경우
	{
		if (pNode == nil)//루트 노드일 경우
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

	//삭제된 노드가 레드노드가 아니라면
	if (cNode->pColor != e_RED)
	{

	}

	delete cNode;//노드제거

	return true;//트루 리턴
}

//검색
bool CREDBLACKTREE2::Tree_Search(int data)
{
	Node* SearchNode = pRoot;//루트 노드부터 시작

	while (SearchNode != nullptr)
	{
		if (SearchNode->Data == data)//데이터가 있다면
			return true;

		if (SearchNode->Data > data) //현재 노드보다 데이터가 작다면 왼쪽으로 가야한다.
		{
			SearchNode = SearchNode->pLeft;
		}
		else//현재 노드보다 데이터가 크다면 오른쪽으로 가야한다.
		{
			SearchNode = SearchNode->pRight;
		}
	}
	return false;
}

CREDBLACKTREE2::Node* CREDBLACKTREE2::Tree_Search_Node(int data)
{
	Node* SearchNode = pRoot;//루트 노드부터 시작

	while (SearchNode != nullptr)
	{
		if (SearchNode->Data == data)//데이터가 있다면
			return SearchNode;

		if (SearchNode->Data > data) //현재 노드보다 데이터가 작다면 왼쪽으로 가야한다.
		{
			SearchNode = SearchNode->pLeft;
		}
		else//현재 노드보다 데이터가 크다면 오른쪽으로 가야한다.
		{
			SearchNode = SearchNode->pRight;
		}
	}
	return nil;//데이터가 없다면 nil리턴
};


//단순 중위순회 출력
void CREDBLACKTREE2::All_print(Node* pNode)
{
	if (pNode == nullptr || pNode == nil)
		return;

	//중위 순회로 모든 데이터 출력
	All_print(pNode->pLeft);

	printf("%d ", pNode->Data);

	All_print(pNode->pRight);
}


// 후위 순회로 간편하게 확인 할 수 있게 한다.
void CREDBLACKTREE2::printBinaryTree(Node* pNode, bool isLeft, int space, int height)
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

// 이진 트리의 분기를 인쇄하는 도우미 함수
void CREDBLACKTREE2::showTrunks(Trunk* p)
{
	if (p == nullptr) {
		return;
	}

	showTrunks(p->prev);
	cout << p->str;
}

void CREDBLACKTREE2::printTree(Node* root, Trunk* prev, bool isLeft)
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

//현재 레드블랙 트리를 체크하는 코드
int CREDBLACKTREE2::RBT_CHECK(Node* _pNode)
{
	if (_pNode == nil)//들어온 노드가 nil이 아닐떄
		return 0;

	//레드 연속체크
	//전위순회 모든노드를 순회하면서 연속된 부모 RED 자식RED가 있다면
	if (_pNode->pColor == e_RED && _pNode->pParent->pColor == e_RED)
	{
		printf("\_pNode->P->Data %d\n", _pNode->pParent->Data);
		printf("_pNode->Data %d\n", _pNode->Data);
		printTree(pRoot, nullptr, false);
		throw std::bad_exception{};//고의 에러 발생시키기
		return 5;
	}
	RBT_CHECK(_pNode->pLeft);
	RBT_CHECK(_pNode->pRight);

	//말단노드에서 부터 루트까지의 노드체크
	if (_pNode->pLeft == nil && _pNode->pRight == nil)
	{
		Node* _tmpNode = _pNode;//말단 리프노드일경우
		int BlackCount = 0;
		while (_tmpNode != pRoot)
		{
			if (_tmpNode->pColor == e_BLACK)
			{
				BlackCount++;
			}
			_tmpNode = _tmpNode->pParent;//부모를 타고올라가면서 체크
		}
		if (black_depth == 0)
			black_depth = BlackCount;
		else if (black_depth != BlackCount)
		{
			printf("black_depthError\n");
			printf("_tmpNode->P->Data %d\n", _pNode->pParent->Data);
			printf("_tmpNode->Data %d\n", _pNode->Data);
			//printTree(pRoot, nullptr, false);
			throw std::bad_exception{};//고의 에러 발생시키기
			return 2;
		}
	}

	//지금까지 모든노드와 탐색되는 노드의 확인
	//추가한노드 - 삭제된노드 == 현재노드 개수
	int _in_outNodeCount = insert_Count - delete_Count;
	if (_in_outNodeCount != Tree_Count(pRoot))
	{
		throw std::bad_exception{};//고의 에러 발생시키기
		return 3;
	}
	//만약값이 다르면
	//넣은것과 현재 존재하는것이 다르다
	//노드가 유실되고 있는 상황


	return 1;//1 true 이면 현재 모든 노드상태가 정상이라는 뜻
}




void CREDBLACKTREE2::LevelPrint(Node* pNode)
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

		if (_qNode != nil)
			printf("%d ", _qNode->Data);
	}
	printf("\n");
}


void CREDBLACKTREE2::Black_Insert(int data)
{
	if (data <= 0) //0이하의 데이터는 처리하지 않겠다.
		return;

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
	insertNode->pColor = e_BLACK;//맨처음 입력시 반드시 빨간색으로 세팅한다.
	insertNode->pParent = pNode;//부모를 넣는다.
	insertNode->pLeft = nil;
	insertNode->pRight = nil;

	insert_Count++;

	if (pNode->Data > data)//부모 노드보다 작다면 왼쪽으로
		pNode->pLeft = insertNode;
	else//부모 노드보다 크다면 오른쪽으로
		pNode->pRight = insertNode;
}


void CREDBLACKTREE2::Right_Rotation_Test(int data)
{
	Node* sNode = pRoot;
	while (sNode != nil)//넣어야하는 위치를 탐색한다.
	{
		if (sNode->Data == data)//중복데이터를 찾았다면 그 노드를 회전
			break;

		if (sNode->Data > data) //현재 노드보다 데이터가 작다면 왼쪽으로 가야한다.
		{
			sNode = sNode->pLeft;
		}
		else//현재 노드보다 데이터가 크다면 오른쪽으로 가야한다.
		{
			sNode = sNode->pRight;
		}
	}

	Node* lNode = sNode->pLeft;
	if (lNode == nil || lNode == nullptr)//회전하려는데 왼쪽노드 데이터가 없으면 회전불가
		return;

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

	if (lNode->pParent->pLeft == sNode)
		lNode->pParent->pLeft = lNode;
	else
		lNode->pParent->pRight = lNode;

	sNode->pParent = lNode;

	if (lNode->pParent == nil)//만약 이동하려는 노드가 Root노드라면
	{
		pRoot = lNode;//LNode를 루트로 바꿔준다.
	}
}

void  CREDBLACKTREE2::Left_Rotation_Test(int data)
{
	//if (sNode == nil || sNode->pRight == nil)
	//return;
	Node* sNode = pRoot;
	while (sNode != nil)//넣어야하는 위치를 탐색한다.
	{
		if (sNode->Data == data)//중복데이터를 찾았다면 그 노드를 회전
			break;

		if (sNode->Data > data) //현재 노드보다 데이터가 작다면 왼쪽으로 가야한다.
		{
			sNode = sNode->pLeft;
		}
		else//현재 노드보다 데이터가 크다면 오른쪽으로 가야한다.
		{
			sNode = sNode->pRight;
		}
	}

	Node* lNode = sNode->pRight;

	if (lNode == nil || lNode == nullptr)//회전하려는데 오른쪽 노드 데이터가 없다면 회전불가
		return;

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

	if (lNode->pParent->pLeft == sNode)
		lNode->pParent->pLeft = lNode;
	else
		lNode->pParent->pRight = lNode;

	sNode->pParent = lNode;

	if (lNode->pParent == nil)//만약 이동하려는 노드가 Root노드라면
		pRoot = lNode;//LNode를 루트로 바꿔준다.
}