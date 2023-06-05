#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int number = 6;
int INF = 1000000000;
vector<pair<int, int>> graph[7];
int d[7];//�������� �ּ� ��밪 ����

void dijkstra(int start)
{
	priority_queue<pair<int, int>>pq; // �Ÿ�, ��� �ε���

	pq.push({ 0,start }); //���� ���� �������� �ִ� ��δ� 0���� �����Ͽ�, ť�� ����.
	d[start] = 0;

	while (!pq.empty())
	{
		int dist = -pq.top().first; //���� �������� ���
		int now = pq.top().second; // ���� ���
		pq.pop();

		if (d[now] < dist) // �̹� �ִܰ�θ� üũ�� ����� ��� �н�
			continue;

		for (int i = 0; i < graph[now].size(); i++)
		{
			int cost = dist + graph[now][i].second; // ���ļ� ���� ����� ����� ���
			// ��������� ��� + ���� ��� ���
			if (cost < d[graph[now][i].first]) // ����� �� �۴ٸ� �ִܰ�� ���̺� ���� ����.
			{
				d[graph[now][i].first] = cost;
				pq.push(make_pair(-cost, graph[now][i].first));
			}
		}
	}
}

int main()
{
	//�⺻������ ������� ���� ��� ����� ����

	for (int i = 1; i <= number; i++)
	{
		d[i] = INF;//��� ����� �켱�� �����̴�.
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
	// ����� ����մϴ�. 
	for (int i = 1; i <= number; i++) {
		printf("%d ", d[i]);
	}
	return 0;
}

