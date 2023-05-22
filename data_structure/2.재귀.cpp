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
	if (num==1) //이동할 원반의 수가 1개라면
	{
		printf("원반1을 %c에서 %c로 이동!\n",from,to);
	}
	else
	{
		HanoiTowerMove(num - 1, from, to, by);//3단계중 첫번째
		printf("원반%d을 %c에서 %c로 이동! \n",num,from,to);//
		HanoiTowerMove(num - 1, by, from, to);//3단계중 첫번째
	}

}

int main()
{
	HanoiTowerMove(10, 'A', 'B', 'C');
	return 0;
}