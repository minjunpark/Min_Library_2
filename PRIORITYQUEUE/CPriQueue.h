#pragma once
#include <iostream>


template <class DATA>
class CPriQueue
{
public:
	enum {
		MAX_SIZE = 100000
	};

	struct HeapNode
	{
		int Priority;
		DATA Data;
	};

	struct tagHeap
	{
		HeapNode* MainHeap;
		int Size;
		int UseSize;
	};

	tagHeap* pMainHeap;

public:

	CPriQueue()
	{
		pMainHeap = new tagHeap;
		pMainHeap->MainHeap = new HeapNode[100000];
		pMainHeap->Size = 100000;
		pMainHeap->UseSize = 0;//사용중인사이즈
	};

	CPriQueue(int size, DATA data)
	{
		pMainHeap = new tagHeap;
		pMainHeap->MainHeap = new HeapNode[size];
		pMainHeap->Size = size;
		pMainHeap->MainHeap[0].Data = data;//처음 루트 세팅
		pMainHeap->UseSize++;//사용중인사이즈
	}

	~CPriQueue()
	{
		//delete_clear(pRoot);
		delete[] pMainHeap->MainHeap;
		delete pMainHeap;
	}

	//void delete_clear(Node* pNode)
	//{
	//	//if (pNode == nullptr || pNode == nil)
	//	//	return;

	//	////중위 순회로 모든 데이터 순회
	//	//delete_clear(pNode->pLeft);
	//	//delete_clear(pNode->pRight);
	//	//delete pNode;//모든 할당된 노드제거
	//};

	void PQ_Enqueue(DATA _data)
	{
		//for (int i = 0; i < pMainHeap->UseSize; i++)
		//{
		//	if (pMainHeap->MainHeap[i].Data == _data)
		//		return;//중복데이터가 있다면 실행하지 않는다.
		//}

		if (pMainHeap->UseSize == pMainHeap->Size)
			return;//더이상 더하지 않는다.

		int cur_position = pMainHeap->UseSize;
		int parent_position = Heap_GetParent(cur_position);

		pMainHeap->MainHeap[cur_position].Data = _data;

		while (cur_position > 0
			&& pMainHeap->MainHeap[cur_position].Priority
			< pMainHeap->MainHeap[parent_position].Priority)
		{
			Heap_Swap(cur_position, parent_position);

			cur_position = parent_position;
			parent_position = Heap_GetParent(cur_position);
		}
		pMainHeap->UseSize++;
	}

	void PQ_Dequeue()//최소힙을 삭제한다.
	{
		if (pMainHeap->UseSize < 0)
			return;//더이상 더하지 않는다.

		int cur_position = pMainHeap->UseSize;
		int parent_position = 0;

		//HeapNode *Root;
		//memcpy(Root, &pMainHeap->MainHeap[0], sizeof(HeapNode));

		pMainHeap->UseSize--;
		Heap_Swap(0, pMainHeap->UseSize);

		int LeftPosition = Heap_Left_Position(0);
		int RightPosition = LeftPosition + 1;

		while (1)
		{
			int Select_Position = 0;

			if (LeftPosition >= pMainHeap->UseSize)
				break;

			if (RightPosition >= pMainHeap->UseSize)
				Select_Position = LeftPosition;
			else
			{
				if (pMainHeap->MainHeap[LeftPosition].Priority >
					pMainHeap->MainHeap[RightPosition].Priority)
					Select_Position = RightPosition;
				else
					Select_Position = LeftPosition;
			}

			if (pMainHeap->MainHeap[Select_Position].Priority <
				pMainHeap->MainHeap[parent_position].Priority)
			{
				Heap_Swap(LeftPosition, parent_position);
				parent_position = Select_Position;
			}
			else
				break;

			LeftPosition = Heap_Left_Position(parent_position);
			RightPosition = LeftPosition + 1;
		}

	}

	int Heap_GetParent(int _position)
	{
		return (_position - 1) / 2;
	}

	void Heap_Print()
	{
		if (pMainHeap->UseSize <= 0)
			return;//더이상 더하지 않는다.

		for (int i = 0; i < pMainHeap->UseSize; i++)
		{
			printf("%d ", pMainHeap->MainHeap[i].Data);
		}
		printf("\n");
	}

	int Heap_Left_Position(int _position)
	{
		//2k+1;
		return  (2 * _position) + 1;
	}

	void Heap_Swap(int _cur, int _pcur)
	{
		int tmp_Cur = pMainHeap->MainHeap[_cur].Data;
		int tmp_pCur = pMainHeap->MainHeap[_pcur].Data;

		pMainHeap->MainHeap[_cur].Data = tmp_pCur;
		pMainHeap->MainHeap[_pcur].Data = tmp_Cur;
	}

};