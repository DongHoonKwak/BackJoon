#include <iostream>
#include <algorithm>
using namespace std;

pair <int, pair<int, int>>network[100004]; //가중치, 시작, 끝

int com; //컴퓨터의 수(1~1000)
int line; //선의 수(1~100000)

int level[1001];
int parent[1001];
int ans = 0; //답

void make_set()
{
	for (int i = 0; i < 1001; i++)
		parent[i] = i;
}

int find_set(int x)
{
	if (parent[x] != x)
		parent[x] = find_set(parent[x]);
	return parent[x];
}

void union_set(int x, int y)
{
	x = find_set(x);
	y = find_set(y);

	if (level[x] > level[y])
		parent[y] = x;
	else
	{
		parent[x] = y;
		if (level[x] == level[y])
			level[y]++;
	}
}

int main()
{
	int start, end, weight; //시작 끝 가중치

	scanf("%d", &com);
	scanf("%d", &line);

	make_set(); //com개의 노드 생성

	for (int i = 0; i < line; i++) //라인 수 만큼 입력받음
	{
		scanf("%d %d %d", &start, &end, &weight);
		network[i].first = weight;
		network[i].second.first = start;
		network[i].second.second = end;
	}

	sort(network, network + line); //가중치 순서대로 정렬

	for (int i = 0; i < line; i++)
	{
		start = network[i].second.first;
		end = network[i].second.second;
		weight = network[i].first;

		if ((find_set(start)) != (find_set(end)))
		{
			ans += weight;
			union_set(start, end);
		}
	}

	printf("%d", ans);
}