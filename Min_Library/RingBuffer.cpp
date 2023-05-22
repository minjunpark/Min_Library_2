#include "RingBuffer.h"
#include <iostream>

RingBuffer::RingBuffer() :_RingBufferSize(10000)
{
	_Start = (char*)malloc(_RingBufferSize);
	_End = _Start + _RingBufferSize;
	_Front = _Rear = _Start;
}

RingBuffer::RingBuffer(int bufferSize) :_RingBufferSize(bufferSize)
{
	_Start = (char*)malloc(bufferSize);
	_End = _Start + _RingBufferSize;
	_Front = _Rear = _Start;
}

int RingBuffer::GetBufferSize()
{
	return _End - _Start - 1;
}

int RingBuffer::GetUseSize()
{
	if (_Rear >= _Front)
		return _Rear - _Front;
	return (_Rear - _Start) + (_End - _Front - 1);
}

int RingBuffer::GetFreeSize()
{
	if (_Rear >= _Front)
		return (_End - _Rear) + (_Front - _Start - 1);
	return _Front - _Rear - 1;
}

int RingBuffer::DirectEnqeueSize()
{
	if (_Rear >= _Front)
		return _End - _Rear - 1;
	return _Front - _Rear - 1;
}


int RingBuffer::DirectDeqeueSize()
{
	if (_Rear >= _Front)
		return _Rear - _Front;
	return _End - _Front - 1;
}


int RingBuffer::Enqueue(const char* buffer, int size)
{
	if (GetFreeSize() < size)
	{
		return 0;
	}
	if (DirectEnqeueSize() >= size)
	{
		memcpy_s(_Rear, size, buffer, size);
		MoveRear(size);
		return size;
	}
	const char* temp = buffer;

	int directEnqueueSize = DirectEnqeueSize();
	memcpy_s(_Rear, directEnqueueSize, temp, directEnqueueSize);
	temp += directEnqueueSize;
	MoveRear(directEnqueueSize);

	int remainSize = size - directEnqueueSize;
	memcpy_s(_Rear, remainSize, temp, remainSize);
	MoveRear(remainSize);
	return size;
}

int RingBuffer::Dequeue(char* pDest, int size)
{
	if (GetUseSize() < size)return 0;
	if (DirectDeqeueSize() >= size)
	{
		memcpy_s(pDest, size, _Front, size);
		MoveFront(size);
		return size;
	}
	char* pDestTemp = pDest;
	int directDequeueSize = DirectDeqeueSize();

	memcpy_s(pDestTemp, directDequeueSize, _Front, directDequeueSize);
	MoveFront(directDequeueSize);
	int remainSize = size - directDequeueSize;
	pDestTemp += directDequeueSize;
	memcpy_s(pDestTemp, remainSize, _Front, remainSize);
	MoveFront(remainSize);

	return size;
}

int RingBuffer::Peek(char* pDest, int size)
{
	if (GetFreeSize() < size)return 0;
	if (DirectDeqeueSize() >= size)
	{
		memcpy_s(pDest, size, _Front, size);
		return size;
	}
	char* pFrontTemp = _Front;
	char* pDestTemp = pDest;
	int directDequeueSize = DirectDeqeueSize();

	memcpy_s(pDestTemp, directDequeueSize, _Front, directDequeueSize);
	MoveFront(directDequeueSize);
	int remainSize = size - directDequeueSize;
	pDestTemp += directDequeueSize;
	memcpy_s(pDestTemp, remainSize, _Front, remainSize);
	_Front = pFrontTemp;

	return size;
}

void RingBuffer::MoveRear(int size)
{
	_Rear += size;
	if (_Rear >= _End - 1)
	{
		int overFlow = _Rear - _End;
		_Rear = _Start + overFlow;
	}
}

void RingBuffer::MoveFront(int size)
{
	_Front += size;//����Ʈ�� �� �����ŭ �̵���Ű��
	if (_Front >= _End - 1)//���� �������� �Ѿ�ٸ�
	{
		int overFlow = _Front - _End;//�Ѿ�°���ŭ �����
		_Front = _Start + overFlow;//���ۺ��� ����Ʈ�� ���ϰ� �̵���Ų��.
	}
}


void RingBuffer::ClearBuffeR()
{
	//Rear�� Start�� ���� ��ġ�� �̵���Ų��.
	_Rear = _Start;
	_Front = _Start;
};

char* RingBuffer::GetReadPtr()
{
	return _Front;//�б������� ��������
};
char* RingBuffer::GetWritePtr()
{
	return _Rear;//���������� ��������
};