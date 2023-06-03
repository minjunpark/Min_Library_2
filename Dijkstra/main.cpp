//#include <iostream>
//
//
//int number = 6;
//
//int INF = 100000000;
//
//int a[6][6] = {
//	{0, 2, 5, 1, INF, INF},
//	{2, 0, 3, 2, INF, INF},
//	{5, 3, 0, 3, 1, 5},
//	{1, 2, 3, 0, 1, INF},
//	{INF, INF, 1, 1, 0, 2},
//};
//
//bool v[6];//방문여부
//int d[6];//최단거리
//
//
//
//int getSmall_Index()
//{
//	int min = INF;
//	int index = 0;
//	for (int i = 0; i < number; i++)
//	{
//		if (d[i] < min && v[i] == false) 
//		{
//			min = d[i];
//			index = i;
//		}
//	}
//	return index;
//}
//
////다익스트라를 수행하는 함수
//void dijkstra(int start)
//{
//	for (int i = 0; i < number; i++)
//	{
//		d[i] = a[start][i];//들어온 시작점으로 부터의 최소값 상태를 넣는다.
//	}// 0 2 5 1 INF INF
//
//	v[start] = true;//시작지점은 방문했으니까 제외한다.
//
//	for (int i = 0; i < number - 2; i++) //나자신을 제외하고 인덱스값도 제외한다
//	{
//		int current = getSmall_Index();//방문하지 않은 노드중 최소값을 찾는다. 1이 가장 작음므로 4번 정점으로간다.
//		v[current] = true;//이동한 정점을 방문처리한ㄷ.
//		for (int j = 0; j < 6; j++)//모든 정점을 하나하나 확인하면서
//		{
//			if (v[j]==false)//해당노드가 방문처리 되지 않은곳이라면
//			{
//				if (d[current] + a[current][j] < d[j])//현재 노드 방문값 + 그노드의 방문값이 그 노드 방문값보다 작다면 이건 경로가 단축된것이다.
//				{
//					d[j] = d[current] + a[current][j];//단축된경로값을 넣는다.
//				}
//			}
//		}
//	}
//	
//}
//
//int main()
//{
//	dijkstra(0);
//	for (int i = 0; i < number; i++)
//	{
//		printf("%d ", d[i]);
//	}
//}
//
