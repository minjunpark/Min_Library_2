#include <iostream>

int fac(int value) 
{
	if (value == 1)
		return 1;

	return value * fac(value - 1);
}

int Fibo(int n)
{
	if (n == 1)
		return 0;
	if (n == 2)
		return 1;

	return Fibo(n - 1) + Fibo(n - 2);
}

int BSearch(int arr[],int first,int last,int target)
{
	int mid;
	if (first > last) 
		return -1;
	mid = (first + last) / 2;

	if (arr[mid] == target)
		return mid;
	else if (target < arr[mid])
		return BSearch(arr, first, mid - 1, target);
	else
		return BSearch(arr, mid + 1, last, target);

}

void HanoiTowerMove(int num, char from, char by, char to)
{
	if (num==1) //�̵��� ������ ���� 1�����
	{
		printf("����1�� %c���� %c�� �̵�!\n",from,to);
	}
	else
	{
		HanoiTowerMove(num - 1, from, to, by);//3�ܰ��� ù��°
		printf("����%d�� %c���� %c�� �̵�! \n",num,from,to);//
		HanoiTowerMove(num - 1, by, from, to);//3�ܰ��� ù��°
	}

}

int main()
{
	HanoiTowerMove(10, 'A', 'B', 'C');
	return 0;
}