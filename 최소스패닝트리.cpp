//#include <iostream>
//#include <algorithm>
//#include <vector>
//using namespace std;
//
//int parent[10001];
//int height[10001];
//
//int dot, line; // 정점, 간선
//int ans = 0; //답
//
//struct node{
//	int start;
//	int end;
//	int weight;
//}edge[100001];
//
//void make_set(int x) //만들기
//{
//	parent[x] = x; //자기자신이 부모
//	height[x] = 0; //높이
//}
//
//int find_set(int x) //부모찾기
//{
//	if (x != parent[x])
//	{
//		parent[x] = find_set(parent[x]);
//	}
//
//	return parent[x];
//}
//
//void union_set(int x, int y) //합치기 //부모의 노드값의 합
//{
//	x = find_set(x); //부모를 찾아서
//	y = find_set(y);
//
//	if (x != y) //부모가 다르면
//	{
//		if (height[x] > height[y]) //더 높이가 높은걸
//		{
//			parent[y] = x; //부모로 한다.
//
//			x += edge[y].weight;
//
//			ans += edge[y].weight;
//		}
//
//		else
//		{
//			parent[x] = y;
//
//			if (height[x] == height[y])
//				height[y]++;
//
//			y += edge[x].weight;
//
//			ans += edge[x].weight;
//		}
//	}
//}
//
//int compare(node a, node b)
//{
//	return a.weight < b.weight;
//}
//
//int main()
//{
//	node temp;
//
//	scanf("%d%d", &dot, &line);
//
//	for (int i = 0; i < dot; i++)
//		make_set(i); //각자 서로소의 형태로 만들기
//
//	for (int i = 0; i < line; i++)
//	{
//		scanf("%d%d%d", &edge[i].start, &edge[i].end, &edge[i].weight);
//	}
//
//	sort(edge, edge + line, compare); //정렬
//
//	for (int i = 0; i < line; i++)
//	{
//		union_set(edge[i].start, edge[i].end); //합치기
//	}
//
//	printf("%d\n", ans);
//}

#include <iostream>
#include <algorithm>
using namespace std;

int dot, line;
int ans;

struct Edge
{
	int weight, start, end;
};

bool operator< (const Edge& e1, const Edge& e2)  //가중치대소비교 재정의 <
{
	return e1.weight < e2.weight;
}

Edge edge[100001];

int parent[100001];

int find(int x)  //부모찾기
{
	if (x == parent[x])
		return x;
	else
		return parent[x] = find(parent[x]);
}

void union_set(int x, int y) 
{
	x = parent[x];
	y = parent[y];

	parent[x] = y;
}

int main() 
{
	scanf("%d %d", &dot, &line);

	for (int i = 0; i < line; i++)
	{
		scanf("%d %d %d", &edge[i].start, &edge[i].end, &edge[i].weight);
	}

	for (int i = 1; i <= dot; i++) //make_set
		parent[i] = i;

	sort(edge, edge + line);

	for (int i = 0; i < dot - 1; i++) 
	{
		if (find(edge[i].start) != find(edge[i].end))
		{
			union_set(edge[i].start, edge[i].end);
			ans += edge[i].weight;
		}
	}

	printf("%d\n", ans);

	return 0;
}


