	#include <iostream>
	#include <algorithm>
	using namespace std;

	pair <int, pair<int, int>>vil[1000004];

	int parent[100004];
	int r[100004];
	int ans;

	void make_set(int x)
	{
		for (int i = 1; i <= x; i++)
			parent[i] = i;
	}

	int find_set(int x)
	{
		if (x != parent[x])
			parent[x] = find_set(parent[x]);
		return parent[x];
	}
	void union_set(int x, int y) {
		x = find_set(x), y = find_set(y);
		if (r[x] > r[y])
			parent[y] = x;
		else {
			parent[x] = y;
			if (r[x] == r[y])
				r[y]++;
		}
	}
	int main()
	{
		int house; // 집의 개수
		int load; //길의 개수
		int start, end, weight;

		scanf("%d %d", &house, &load);

		make_set(house);

		for (int i = 1; i <= load; i++)
		{
			scanf("%d %d %d", &start, &end, &weight);

			vil[i].first = weight;
			vil[i].second.first = start;
			vil[i].second.second = end;
		}

		sort(vil, vil + load);

		for (int i = 1; i <= load; i++)
		{
			start = vil[i].second.first;
			end = vil[i].second.second;
			weight = vil[i].first;

			if (find_set(start) != find_set(end))
			{
				ans += weight;
				union_set(start, end);
				house--;
				if (house == 2) // 마을이 2개라면
				{
					printf("%d\n", ans);
					return 0;
				}
			}
		}
	
	}
