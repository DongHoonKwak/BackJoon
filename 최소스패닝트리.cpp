//#include <iostream>
//#include <algorithm>
//#include <vector>
//using namespace std;
//
//int parent[10001];
//int height[10001];
//
//int dot, line; // ����, ����
//int ans = 0; //��
//
//struct node{
//	int start;
//	int end;
//	int weight;
//}edge[100001];
//
//void make_set(int x) //�����
//{
//	parent[x] = x; //�ڱ��ڽ��� �θ�
//	height[x] = 0; //����
//}
//
//int find_set(int x) //�θ�ã��
//{
//	if (x != parent[x])
//	{
//		parent[x] = find_set(parent[x]);
//	}
//
//	return parent[x];
//}
//
//void union_set(int x, int y) //��ġ�� //�θ��� ��尪�� ��
//{
//	x = find_set(x); //�θ� ã�Ƽ�
//	y = find_set(y);
//
//	if (x != y) //�θ� �ٸ���
//	{
//		if (height[x] > height[y]) //�� ���̰� ������
//		{
//			parent[y] = x; //�θ�� �Ѵ�.
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
//		make_set(i); //���� ���μ��� ���·� �����
//
//	for (int i = 0; i < line; i++)
//	{
//		scanf("%d%d%d", &edge[i].start, &edge[i].end, &edge[i].weight);
//	}
//
//	sort(edge, edge + line, compare); //����
//
//	for (int i = 0; i < line; i++)
//	{
//		union_set(edge[i].start, edge[i].end); //��ġ��
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

bool operator< (const Edge& e1, const Edge& e2)  //����ġ��Һ� ������ <
{
	return e1.weight < e2.weight;
}

Edge edge[100001];

int parent[100001];

int find(int x)  //�θ�ã��
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


