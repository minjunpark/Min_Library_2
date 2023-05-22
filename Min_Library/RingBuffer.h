#pragma once
class RingBuffer
{
public:
	RingBuffer();
	RingBuffer(int bufferSize);

	bool ReSize(int size);
	int GetBufferSize();

	int GetUseSize();
	int GetFreeSize();
	
	int DirectEnqeueSize();
	int DirectDeqeueSize();

	int Enqueue(const char* buffer, int size);
	int Dequeue(char* pDest, int size);
	int Peek(char* pDest, int size);

	void MoveRear(int size);
	void MoveFront(int size);

	void ClearBuffeR();

	char* GetReadPtr();
	char* GetWritePtr();

private:
	char* _Start;
	char* _End;
	char* _Rear;//����������
	char* _Front;//�б�������

	int _RingBufferSize;
};