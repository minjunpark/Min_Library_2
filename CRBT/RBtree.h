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
			if (_pNode == &m_NilNode)//���� ��尡 nil�� �ƴҋ�
				return 0;

			//���� ����üũ
			//������ȸ ����带 ��ȸ�ϸ鼭 ���ӵ� �θ� RED �ڽ�RED�� �ִٸ�
			if (_pNode->eNodeColor == NodeColor::RED && _pNode->pParentNode->eNodeColor == NodeColor::RED)
			{
				printf("\_pNode->P->Data %d\n", _pNode->pParentNode->key);
				printf("_pNode->Data %d\n", _pNode->key);
				//printTree(pRoot, nullptr, false);
				throw std::bad_exception{};//���� ���� �߻���Ű��
				return 5;
			}
			RBT_CHECK(_pNode->pLeftNode);
			RBT_CHECK(_pNode->pRightNode);

			//���ܳ�忡�� ���� ��Ʈ������ ���üũ
			if (_pNode->pLeftNode == &m_NilNode && _pNode->pRightNode == &m_NilNode)
			{
				Node* _tmpNode = _pNode;//���� ��������ϰ��
				int BlackCount = 0;
				while (_tmpNode != root)
				{
					if (_tmpNode->eNodeColor == NodeColor::BLACK)
					{
						BlackCount++;
					}
					_tmpNode = _tmpNode->pParentNode;//�θ� Ÿ��ö󰡸鼭 üũ
				}
				if (black_depth == 0)
					black_depth = BlackCount;
				else if (black_depth != BlackCount)
				{
					printf("black_depthError\n");
					printf("_tmpNode->P->Data %d\n", _pNode->pParentNode->key);
					printf("_tmpNode->Data %d\n", _pNode->key);
					//printTree(pRoot, nullptr, false);
					throw std::bad_exception{};//���� ���� �߻���Ű��
					return 2;
				}
			}

			//���ݱ��� ������ Ž���Ǵ� ����� Ȯ��
			//�߰��ѳ�� - �����ȳ�� == ������ ����
			//int _in_outNodeCount = insert_Count - delete_Count;
			//if (_in_outNodeCount != Tree_Count(pRoot))
			//{
			//	throw std::bad_exception{};//���� ���� �߻���Ű��
			//	return 3;
			//}
			//���ప�� �ٸ���
			//�����Ͱ� ���� �����ϴ°��� �ٸ���
			//��尡 ���ǵǰ� �ִ� ��Ȳ


			return 1;//1 true �̸� ���� ��� �����°� �����̶�� ��
		}


	};


#endif // !__RED_BLACK_TREE_HEADER__