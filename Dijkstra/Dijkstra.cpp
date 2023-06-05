#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int number = 6;
int INF = 1000000000;
vector<pair<int, int>> graph[7];
int d[7];//노드까지의 최소 비용값 세팅

void dijkstra(int start)
{
	priority_queue<pair<int, int>>pq; // 거리, 노드 인덱스

	pq.push({ 0,start }); //시작 노드로 가기위한 최단 경로는 0으로 설정하여, 큐에 삽입.
	d[start] = 0;

	while (!pq.empty())
	{
		int dist = -pq.top().first; //현재 노드까지의 비용
		int now = pq.top().second; // 현재 노드
		pq.pop();

		if (d[now] < dist) // 이미 최단경로를 체크한 노드인 경우 패스
			continue;

		for (int i = 0; i < graph[now].size(); i++)
		{
			int cost = dist + graph[now][i].second; // 거쳐서 가는 노드의 비용을 계산
			// 현재노드까지 비용 + 다음 노드 비용
			if (cost < d[graph[now][i].first]) // 비용이 더 작다면 최단경로 테이블 값을 갱신.
			{
				d[graph[now][i].first] = cost;
				pq.push(make_pair(-cost, graph[now][i].first));
			}
		}
	}
}

int main()
{
	//기본적으로 연결되지 않은 경우 비용은 무한

	for (int i = 1; i <= number; i++)
	{
		d[i] = INF;//모든 비용은 우선은 무한이다.
	}

	graph[1].push_back(make_pair(2, 2));
	graph[1].push_back(make_pair(3, 5));
	graph[1].push_back(make_pair(4, 1));

	graph[2].push_back(make_pair(1, 2));
	graph[2].push_back(make_pair(3, 3));
	graph[2].push_back(make_pair(4, 2));
	
	graph[3].push_back(make_pair(1, 5));
	graph[3].push_back(make_pair(2, 3));
	graph[3].push_back(make_pair(4, 3));
	graph[3].push_back(make_pair(5, 1));
	graph[3].push_back(make_pair(6, 5));
	
	graph[4].push_back(make_pair(1, 1));
	graph[4].push_back(make_pair(2, 2));
	graph[4].push_back(make_pair(3, 3));
	graph[4].push_back(make_pair(5, 1));
	
	graph[5].push_back(make_pair(3, 1));
	graph[5].push_back(make_pair(4, 1));
	graph[5].push_back(make_pair(6, 2));
	
	graph[6].push_back(make_pair(3, 5));
	graph[6].push_back(make_pair(5, 2));

	dijkstra(1);


	for (int i = 65; i < 65 + number; i++) {
		printf("%c ", i);
	}
	printf("\n");
	// 결과를 출력합니다. 
	for (int i = 1; i <= number; i++) {
		printf("%d ", d[i]);
	}
	return 0;
}

