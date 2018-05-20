#include <iostream>
#include <algorithm>

using namespace std;

pair<int, pair<int, int>>info[200004];

int level[200004];
int parent[200004];
long long ans = 0; //답 : total-cost

void make_set(int x)
{
	
	for (int i = 0; i <= x; i++)
	{
		level[i] = 0;
		parent[i] = i;
	}
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
	long long total = 0; //총 전력 길이
	long long cost = 0;; // 최소연결비용 

	int house; //집의 수
	int load; //길의 수

	int s_house, e_house;
	long long meter;

	while (1)
	{
		total = 0;
		cost = 0;
		ans = 0;

		scanf("%d %d", &house, &load);

		if (house == 0 && load == 0)
			break;

		if (house >= 1 && house <= 200000)
		{
			if ((load >= house - 1) && (load <= 200000))
			{
				make_set(house);

				for (int i = 1; i <= load; i++)
				{
					scanf("%d %d %lld", &s_house, &e_house, &meter);

					total += meter;

					info[i].first = meter;
					info[i].second.first = s_house;
					info[i].second.second = e_house;
				}

				sort(info, info + load + 1);

				for (int i = 1; i <= load; i++)
				{
					s_house = info[i].second.first;
					e_house = info[i].second.second;
					meter = info[i].first;

					if ((find_set(s_house)) != (find_set(e_house)))
					{
						cost += meter;

						union_set(s_house, e_house);
					}
				}

				ans = total - cost;

				printf("%lld\n", ans);
			}
		}
	}
}

