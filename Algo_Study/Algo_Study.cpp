//#include <iostream>
//#include <string>
//#include <vector>
//#include <time.h>
//#define MAXSIZE 10
//using namespace std;
//
//void ArrayPrint(int arr[], int arr_size, int a, int b)
//{
//	for (int i = 0; i < arr_size; i++) {
//		if (i >= a && i <= b) {
//			printf(" [%d] ", arr[i]);
//		}
//		else {
//			printf("  %d  ", arr[i]);
//		}
//	}
//	printf("\n");
//};
//
//void swap(int& a, int& b)
//{
//	int temp;
//	temp = a;
//	a = b;
//	b = temp;
//}
//
//int* generateRandomArray(int size) {
//	int* myArray = (int*)calloc(size, sizeof(int));
//	//srand((unsigned)time(NULL));
//	srand(1);
//	for (int i = 0; i < size; i++) {
//		//myArray[i] = rand() % 100;
//		myArray[i] = rand() % 10;
//	}
//	return myArray;
//}
//
//
//string players[5] = { "mumu", "soe", "poe", "kai", "mine" };
//string callings[5] = { "kai", "kai", "mine", "mine" };
////string result[5] = { "mumu", "kai", "mine", "soe", "poe" };
//
//vector<string> solution(vector<string> players, vector<string> callings) {
//	vector<string> answer;
//
//	return answer;
//}
//
////int arr[] = {7,4,5,1,3};
//int arr[] = { 8,5,6,2,4 };
//int arr2[] = { 5, 3, 8, 4, 9, 1, 6, 2, 7 };
//
//
//
//void  quick_sort(int arr[], int left, int right) {
//
//	if (left >= right)//left가 right보다 크거나 같다면 정렬이 완료된 상태이기 때문에 정렬하지 않는다.
//		return;
//
//	int pivot;
//	int low;
//	int high;
//
//	pivot = left;//가장 왼쪽 피봇지점 세팅
//
//	low = left + 1;
//	high = right;
//
//	for (;;) {
//		//low 한칸씩 오른쪽으로 이동
//		for (; low <= right; low++) {
//			//피벗보다 크면정지
//			if (arr[pivot] < arr[low]) {
//				break;
//			}
//		}
//		//high 한칸씩 왼쪽으로 이동
//		for (; left < high; high--) {
//			//피벗값보다 작으면 정지
//			if (arr[pivot] > arr[high]) {
//				break;
//			}
//		}
//
//		if (low >= high)//low>=high면 같은위치이므로 무한 반복문을 탈출한다.
//			break;
//
//		swap(arr[low], arr[high]);//low high가 다른 값이므로 서로 스왑스킨다.
//	}
//
//	swap(arr[pivot], arr[high]);//pivot과 high의 위치값을 전환시킨다.
//
//	//_getch();//경과를 확인 할 수 있게 엔터로체크
//	//ArrayPrint(arr, MAXSIZE, left, right);//출력한다.
//	quick_sort(arr, left, high - 1);//pivot기준 앞부분을 재귀로 정렬
//	quick_sort(arr, high + 1, right);//pivot기준 뒷부분을 재귀로 정렬
//};
//
//void bubble_sort(int arr[], int size)
//{
//	for (int i = 0; i < size; i++)
//	{
//		for (int j = 0; j < size - i; j++)
//		{
//			if (arr[j] > arr[j + 1])
//				swap(arr[j], arr[j + 1]);
//		}
//	}
//}
//
//void select_sort(int arr[], int size)
//{
//	int temp_index;
//	for (int i = 0; i < size; i++)
//	{
//		temp_index = i;
//		for (int j = i + 1; j < size; j++)
//		{
//			if (arr[temp_index] > arr[j])
//				temp_index = j;
//		}
//		if (temp_index != i)
//			swap(arr[i], arr[temp_index]);
//	}
//}
//
//void insert_sort(int arr[], int size)
//{
//	int j;
//	for (int i = 0; i < size - 1; i++)
//	{
//		j = i;
//		while (arr[j] > arr[j + 1])
//		{
//			swap(arr[j], arr[j + 1]);
//			j--;
//		}
//
//	}
//}
//
//int main()
//{
//	ArrayPrint(arr2, 9, 0, 10);
//
//	//bubble_sort(arr,5);
//	//select_sort(arr, 5);
//	//insert_sort(arr, 5);
//	ArrayPrint(arr2, 9, 0, 9);
//	quick_sort(arr2, 0, 8);
//	ArrayPrint(arr2, 9, 0, 9);
//	return 0;
//}
//
//
