#pragma once
#ifndef __RED_BLACK_TREE_HEADER__
#define __RED_BLACK_TREE_HEADER__
#define __UNIV_DEVELOPER_

#include <Windows.h>
#include <iostream>
	class RedBlackTree
	{
	private:
		enum class NodeColor { BLACK, RED };
		struct Node
		{
			Node* pParentNode;
			Node* pLeftNode;
			Node* pRightNode;
			NodeColor eNodeColor;
			int key;
		};
	public:
		Node* GetRootNode() { return root; };
#ifdef __PRINT_WITH_WINAPI
		void Print(HDC hdc);
#endif
		RedBlackTree();
		~RedBlackTree();
		bool Insert(int data);
		bool Remove(int data);
		void Release();
		int GetNodeCount() { return nodeCount; }
	private:
		void Print(Node* root, int& depth, int& x, HDC hdc);
		bool Insert(Node* root, int key);
		int NumOfChild(Node* root);
		int GetRightChildCount(Node* root);
		int GetLeftChildCount(Node* root);
		bool Remove(Node* root, int key);
		void Release(Node* root);
		void RotateRight(Node* root);
		void RotateLeft(Node* root);
		void BalanceTree(Node* root);
		void ReBalanceTree(Node* root);
	
	private:
		Node m_NilNode;
		Node* root;
		int nodeCount;
		int black_depth;

	public:
		int RBT_CHECK(Node* _pNode)
		{
			if (_pNode == &m_NilNode)//들어온 노드가 nil이 아닐떄
				return 0;

			//레드 연속체크
			//전위순회 모든노드를 순회하면서 연속된 부모 RED 자식RED가 있다면
			if (_pNode->eNodeColor == NodeColor::RED && _pNode->pParentNode->eNodeColor == NodeColor::RED)
			{
				printf("\_pNode->P->Data %d\n", _pNode->pParentNode->key);
				printf("_pNode->Data %d\n", _pNode->key);
				//printTree(pRoot, nullptr, false);
				throw std::bad_exception{};//고의 에러 발생시키기
				return 5;
			}
			RBT_CHECK(_pNode->pLeftNode);
			RBT_CHECK(_pNode->pRightNode);

			//말단노드에서 부터 루트까지의 노드체크
			if (_pNode->pLeftNode == &m_NilNode && _pNode->pRightNode == &m_NilNode)
			{
				Node* _tmpNode = _pNode;//말단 리프노드일경우
				int BlackCount = 0;
				while (_tmpNode != root)
				{
					if (_tmpNode->eNodeColor == NodeColor::BLACK)
					{
						BlackCount++;
					}
					_tmpNode = _tmpNode->pParentNode;//부모를 타고올라가면서 체크
				}
				if (black_depth == 0)
					black_depth = BlackCount;
				else if (black_depth != BlackCount)
				{
					printf("black_depthError\n");
					printf("_tmpNode->P->Data %d\n", _pNode->pParentNode->key);
					printf("_tmpNode->Data %d\n", _pNode->key);
					//printTree(pRoot, nullptr, false);
					throw std::bad_exception{};//고의 에러 발생시키기
					return 2;
				}
			}

			//지금까지 모든노드와 탐색되는 노드의 확인
			//추가한노드 - 삭제된노드 == 현재노드 개수
			//int _in_outNodeCount = insert_Count - delete_Count;
			//if (_in_outNodeCount != Tree_Count(pRoot))
			//{
			//	throw std::bad_exception{};//고의 에러 발생시키기
			//	return 3;
			//}
			//만약값이 다르면
			//넣은것과 현재 존재하는것이 다르다
			//노드가 유실되고 있는 상황


			return 1;//1 true 이면 현재 모든 노드상태가 정상이라는 뜻
		}


	};


#endif // !__RED_BLACK_TREE_HEADER__