#include <iostream>
#include <Windows.h>
#include "Profile.h"
#pragma comment(lib, "winmm.lib")
struct PROFILE_INFO
{
	long			lFlag = 0;				// ���������� ��� ����. (�迭�ÿ���)
	WCHAR			szName[64];			// �������� ���� �̸�.

	LARGE_INTEGER	lStartTime;			// �������� ���� ���� �ð�.

	__int64			iTotalTime;			// ��ü ���ð� ī���� Time.	(��½� ȣ��ȸ���� ������ ��� ����)
	__int64			iMin[2];			// �ּ� ���ð� ī���� Time.	(�ʴ����� ����Ͽ� ���� / [0] �����ּ� [1] ���� �ּ� [2])
	__int64			iMax[2];			// �ִ� ���ð� ī���� Time.	(�ʴ����� ����Ͽ� ���� / [0] �����ִ� [1] ���� �ִ� [2])

	__int64			iCall;				// ���� ȣ�� Ƚ��.
};

enum {
	PROFILE_SIZE = 50//�ִ� �������� ����
};

const char* _tag;//�±� �̸�
WCHAR _P_FILENAME[128];//���� �̸�
PROFILE_INFO _P_ARR[PROFILE_SIZE];//ARRAY LIST �ִ�ũ�� 50
LARGE_INTEGER _P_Start;//���۽ð�
LARGE_INTEGER _P_End;//�����ð�
LARGE_INTEGER _P_Freq;//���ؽð�
LONGLONG _P_RealTime;//����ð�
FILE* _P_FILE;
errno_t _P_error;

void ProfileBegin(const WCHAR* szName)
{
	//������ �ִٸ�
	for (int iPA = 0; iPA < PROFILE_SIZE; iPA++)
	{
		if (0 == wcscmp(_P_ARR[iPA].szName, szName))
		{
			QueryPerformanceCounter(&_P_Start);
			_P_ARR[iPA].lStartTime = _P_Start;
			return;
		}
	}
	//������ ���ٸ�
	for (int iPA = 0; iPA < PROFILE_SIZE; iPA++)
	{
		if (_P_ARR[iPA].lFlag == 0)
		{
			_P_ARR[iPA].lFlag = 1;
			wcscpy_s(_P_ARR[iPA].szName, szName);
			_P_ARR[iPA].iTotalTime = 0;//��Ƚ�� �ʱ�ȭ
			_P_ARR[iPA].iMin[0] = 10000000;//�ּҽ���ð� 
			_P_ARR[iPA].iMax[0] = 0;//�ִ� ����ð�
			QueryPerformanceCounter(&_P_Start);
			_P_ARR[iPA].lStartTime = _P_Start;
			return;
		}
	}
};

void ProfileEnd(const WCHAR* szName)
{
	QueryPerformanceCounter(&_P_End);//���� ��ܿ��� �ð�����
	for (int iPA = 0; iPA < PROFILE_SIZE; iPA++)
	{
		if (_P_ARR[iPA].lFlag != 0)
		{
			if (0 == wcscmp(_P_ARR[iPA].szName, szName))
			{//�±װ��� �ִٸ�
				++_P_ARR[iPA].iCall;//���� ��Ƚ������
				_P_ARR[iPA].iTotalTime = _P_ARR[iPA].iTotalTime + (_P_End.QuadPart - _P_ARR[iPA].lStartTime.QuadPart);//��Ż �ð�����

				if (_P_ARR[iPA].iMin[0] > _P_End.QuadPart - _P_ARR[iPA].lStartTime.QuadPart)
				{//�ּ� ����ð�
					_P_ARR[iPA].iMin[0] = _P_End.QuadPart - _P_ARR[iPA].lStartTime.QuadPart;//�ּ� ����ð� �Է�
				}

				if (_P_ARR[iPA].iMax[0] < _P_End.QuadPart - _P_ARR[iPA].lStartTime.QuadPart)
				{//�ּ� ����ð�
					_P_ARR[iPA].iMax[0] = _P_End.QuadPart - _P_ARR[iPA].lStartTime.QuadPart;//�ּ� ����ð� �Է�
				}
				break;
			}
			//else
			//{//�±װ��� ������
			//	printf("TAG NOT %s %d\n", __FILE__, __LINE__);//���� ��ġ�� ����Ȯ���Ѵ�
			//	throw std::bad_exception{};//���� ���� �߻���Ű��
			//}
		}
	}
};

void ProfileDataOutText(const WCHAR* szFileName)
{
	time_t curTime = time(NULL);
	struct tm tmCurTime;

	_P_error = localtime_s(&tmCurTime, &curTime);
	if (_P_error != 0)
	{
		printf("����ð��� ����������\n");
		return;
	}

	WCHAR _P_TIME_FORMAT[64];

	wcscpy_s(_P_FILENAME, sizeof(_P_FILENAME), szFileName);//�����̸� ����
	wcsftime(_P_TIME_FORMAT, sizeof(_P_FILENAME), L"_%Y%m%d_%I%M%S.txt", &tmCurTime);//Ÿ�� ���� ����
	wcscat_s(_P_FILENAME, _P_TIME_FORMAT);//Ÿ�� ���� ���̱�

	_P_error = _wfopen_s(&_P_FILE, _P_FILENAME, L"wb");
	if (_P_error != 0)
	{
		printf("������ ���� �� �� �����ϴ�.\n");
		return;
	}
	if (_P_FILE == nullptr) {
		printf("������ �������� ���߽��ϴ�..\n");
		return;
	}

	fwprintf(_P_FILE, L"-------------------------------------------------------------------------------\n");
	fwprintf(_P_FILE, L"\n");
	fwprintf(_P_FILE, L"           Name  |     Average  |        Min   |        Max   |       Call |\n");
	fwprintf(_P_FILE, L"---------------------------------------------------------------------------\n");
	for (int iPA = 0; iPA < PROFILE_SIZE; iPA++)
	{
		if (_P_ARR[iPA].lFlag)//�÷��װ� �ִٸ�
		{
			__int64 iTotal = _P_ARR[iPA].iTotalTime - (_P_ARR[iPA].iMax[0] + _P_ARR[iPA].iMin[0]);//�ּҰ� �ִ밪 ��������ؼ� ���ϱ�
			__int64 iAverage = (double) iTotal / (_P_ARR[iPA].iCall - 2);//��սð� ���ϱ� -2�� �ּ� �ִ밪 ����
			
			double dftTotalDu = (double)iAverage * 1000.0 / (double)_P_Freq.QuadPart;         //��չи������� ���
			double dftMinDu = (double)_P_ARR[iPA].iMin[0] * 1000.0 / (double)_P_Freq.QuadPart;//�ּҰ� �и������� ���
			double dftMaxDu = (double)_P_ARR[iPA].iMax[0] * 1000.0 / (double)_P_Freq.QuadPart;//�ִ밪 �и������� ���

			//double dftTotalDu = (double)iAverage * 1000.0 / (double)_P_Freq.QuadPart;         //��չи������� ���
			//double dftMinDu = (double)_P_ARR[iPA].iMin[0] * 1000.0 / (double)_P_Freq.QuadPart;//�ּҰ� �и������� ���
			//double dftMaxDu = (double)_P_ARR[iPA].iMax[0] * 1000.0 / (double)_P_Freq.QuadPart;//�ִ밪 �и������� ���


			//fprintf(file, "%s,%u,%.10llf,%.10llf,%.10llf,%.10llf,%.10llf,%.10llf,%.10lld\n",
			//	samples[i].profileSample[j].profileName,
			//	samples[i].threadID, totalTime, (double)(totalTime / (double)callCountsExceptMinMax),
			//	min0, min1 / freq.QuadPart, max0 / freq.QuadPart, max1 / freq.QuadPart,
			//	callCountsExceptMinMax);
			//printf("%lld : %lld \n",iTotal , (_P_ARR[iPA].iCall - 2));
			//fwprintf(_P_FILE, L"%16s | %10.4lf�� | %10.4lf�� | %10.4lf�� | %10lld |\n",
			//	_P_ARR[iPA].szName, dftTotalDu, dftMinDu, dftMaxDu, _P_ARR[iPA].iCall);//����ȭ ���Ѽ� �Է�
			//% s, % u, % .10llf, % .10llf, % .10llf, % .10llf, % .10llf, % .10llf, % .10lld\n
			fwprintf(_P_FILE, L"%16s | %.10llf�� | %.10llf�� | %.10llf�� | %10lld |\n",
				_P_ARR[iPA].szName, dftTotalDu, dftMinDu, dftMaxDu, _P_ARR[iPA].iCall);//����ȭ ���Ѽ� �Է�
		}
	}
	fwprintf(_P_FILE, L"\n");
	fwprintf(_P_FILE, L"-------------------------------------------------------------------------------\n");
	fclose(_P_FILE);
};

void ProfilePrint(void)
{
	for (int iPA = 0; iPA < PROFILE_SIZE; iPA++)
	{
		if (_P_ARR[iPA].lFlag)
		{
			__int64 iTotal = _P_ARR[iPA].iTotalTime - (_P_ARR[iPA].iMax[0] + _P_ARR[iPA].iMin[0]);//�ִ�ð� ���ϱ�
			__int64 iAverage = _P_ARR[iPA].iTotalTime / _P_ARR[iPA].iCall;//��սð� ���ϱ�
			wprintf(L"%lld %lld", iTotal, iAverage);
		}
	}
}

void ProfileReset(void)
{
	for (int i = 0; i < PROFILE_SIZE; i++)
	{
		memset(&_P_ARR[i].lFlag, 0, sizeof(struct PROFILE_INFO));//��絥���� NULL�� �о������
		memset(&_P_ARR[i].lStartTime, NULL, sizeof(struct PROFILE_INFO));//��絥���� NULL�� �о������
		memset(&_P_ARR[i].iTotalTime, NULL, sizeof(struct PROFILE_INFO));//��絥���� NULL�� �о������
		memset(&_P_ARR[i].iMin, NULL, sizeof(struct PROFILE_INFO));//��絥���� NULL�� �о������
		memset(&_P_ARR[i].iMax, NULL, sizeof(struct PROFILE_INFO));//��絥���� NULL�� �о������
		memset(&_P_ARR[i].iCall, NULL, sizeof(struct PROFILE_INFO));//��絥���� NULL�� �о������
	}
};

