#include"RingBuf.h"
#include <cstdio>
#include <Windows.h>
#include <iostream>

RingBuf::RingBuf(void)
{
	readPos = 0;
	writePos = 0;
}

RingBuf::RingBuf(int iBufferSize)
{
	readPos = 0;
	writePos = 0;
}


int RingBuf::Enqueue(char* chpData, int iSize)
{
	int count = 0;

	while (iSize != 0)
	{
		//�迭�� ������ �� ��
		if ((writePos + 1) % BUFFER_SIZE == readPos)
		{
			//printf("�迭�� �� á���ϴ� \n");
			return count;
		}

		arr[writePos] = *chpData;
		writePos = (writePos + 1) % BUFFER_SIZE;

		count++;
		chpData++;
		iSize--;

	}

	return count;
}

int RingBuf::Dequeue(char* chpData, int iSize)
{
	int count = 0;
	int pos = readPos;

	bool isOneCircle = false;
	int afterCount = 0;

	char* cmpCopy = (char*)malloc(DATA_SIZE);
	ZeroMemory(cmpCopy, sizeof(cmpCopy));

	//������ �� ����������
	while (iSize != 0)
	{
		//������ ���� �迭�� �������
		if (pos == writePos)
		{
			//���⼭ ������ �ɰ����� ��Ȳ�� ����. (readPos�� �迭 ������ �������� �Ѿ����)
			if (isOneCircle == true)
			{
				memcpy(cmpCopy, arr + readPos, count - afterCount);
				memcpy(cmpCopy + (count - afterCount), arr, afterCount);
			}
			else
				memcpy(cmpCopy, arr + readPos, count);

			//���� �ߴ� peek�� ����� ��
			if (memcmp(cmpCopy, chpData, strlen(chpData)) == 0)
			{
				readPos = pos;
				delete cmpCopy;
				return count;
			}
			else
			{
				delete cmpCopy;
				return 0;
			}
		}

		pos = (pos + 1) % BUFFER_SIZE;

		if (isOneCircle == true)
			afterCount++;

		if (pos == 0)
			isOneCircle = true;

		count++;
		iSize--;
	}

	if (isOneCircle == true)
	{
		memcpy(cmpCopy, arr + readPos, count - afterCount);
		memcpy(cmpCopy + (count - afterCount), arr, afterCount);
	}
	else
		memcpy(cmpCopy, arr + readPos, count);

	//�̺κ��� �׽�Ʈ�� �� peek�� ����� deq�� ����� �������� ��¥ deq�� �ϱ� ���� ���� �ڵ�. 
	//�ݵ�� peek�� ���� �߾�� ������ �񱳰� �����ϰ�, ���� �����Ÿ� 	readPos = pos;	return count; �� ����� ������ ��.
	if (memcmp(cmpCopy, chpData, strlen(chpData)) == 0)
	{
		readPos = pos;
		delete cmpCopy;
		return count;
	}
	else
	{
		delete cmpCopy;
		return 0;
	}
}

int RingBuf::Peek(char* chpData, int iSize)
{
	int count = 0;
	int pos = readPos;

	bool isOneCircle = false;
	int afterCount = 0;

	//������ �� ����������
	while (iSize != 0)
	{
		//������ ���� �迭�� �������
		if (pos == writePos)
		{
			//���⼭ ������ �ɰ����� ��Ȳ�� ����. (readPos�� �迭 ������ �������� �Ѿ����)
			if (isOneCircle == true)
			{
				memcpy(chpData, arr + readPos, count - afterCount);
				memcpy(chpData + (count - afterCount), arr, afterCount);
			}
			else
				memcpy(chpData, arr + readPos, count);

			return count;
		}

		pos = (pos + 1) % BUFFER_SIZE;

		if (isOneCircle == true)
			afterCount++;

		if (pos == 0)
			isOneCircle = true;

		count++;
		iSize--;
	}

	if (isOneCircle == true)
	{
		memcpy(chpData, arr + readPos, count - afterCount);
		memcpy(chpData + (count - afterCount), arr, afterCount);
	}
	else
		memcpy(chpData, arr + readPos, count);

	return count;
}

int RingBuf::MoveRear(int iSize)
{
	writePos = (writePos + iSize) % BUFFER_SIZE;
	return writePos;
}

int RingBuf::MoveFront(int iSize)
{
	readPos = (readPos + iSize) % BUFFER_SIZE;
	return readPos;
}