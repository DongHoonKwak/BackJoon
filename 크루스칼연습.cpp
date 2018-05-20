#include <stdio.h>

#define MAX_VER     15
#define MAX_EDGE    30

typedef struct edge {
	int start, end;
	int weight;
}EDGE;

struct vertices {
	int p;
	int rank;
}vt[MAX_VER];

EDGE e[MAX_EDGE];

void mst_kruskal(int, int);
void make_set(int);
void union_set(int, int);
int find_set(int);
void sort_edge(int);
void max_heapify(int, int);
void build_max_heap(int);

int main(void)
{
	int dot, line;
	int start, end;

		// input the number of vertices and edges.
		scanf("%d%d", &dot, &line);

		for (int i = 0; i < line; i++)
		{
			scanf("%d%d", &start, &end);

			e[i].start = start - 1;
			e[i].end = end - 1;

			scanf("%d", &e[i].weight);
		}

		mst_kruskal(dot, line);

	return 0;
}

/*
make_set()
create a linew set whose only member is itself.
*/
void make_set(int x)
{
	vt[x].p = x;
	vt[x].rank = 0;
}

/*
find_set()
returns a pointer to the representative of the set.
*/
int find_set(int x)
{
	if (vt[x].p != x)
	{
		vt[x].p = find_set(vt[x].p);
	}

	return vt[x].p;
}

/*
union_set()
unites the dynamic sets that contain two elements.
*/
void union_set(int x, int y)
{
	x = find_set(x);
	y = find_set(y);

	// compare V with U.
	if (vt[x].rank > vt[y].rank)
	{
		vt[y].p = x;
	}
	else
	{
		vt[x].p = y;

		// if v has the equal number of vertices with u.
		if (vt[x].rank == vt[y].rank)
			vt[y].rank++;

	}
}

/*
mst_kruskal()
it uses disjoint-set and finds a safe edge.
*/
void mst_kruskal(int dot, int line)
{
	int i;
	int total = 0;

	for (i = 0; i < dot; i++)
	{
		// create a linew set whose only member is itself.
		make_set(i);
	}

	// sort the edges.
	sort_edge(line);

	for (i = 0; i < line; i++)
	{
		// examiline whether two representative is not similar each other.
		if (find_set(e[i].start) != find_set(e[i].end))
		{
			// unites the dynamic sets that contain two elements.
			union_set(e[i].start, e[i].end);

			total = total + e[i].weight;
		}
	}

	printf(" %d\n", total);
}

/*
sort_edge()
sort the edges by heap sort
*/
void sort_edge(int line)
{
	EDGE temp;
	int i;

	build_max_heap(--line);

	for (i = line; i > 0; i--)
	{
		temp = e[i];
		e[i] = e[0];
		e[0] = temp;

		max_heapify(0, i);
	}
}

/*
max_heapify()
maintain the characteristic of the heap.
*/
void max_heapify(int index, int size)
{
	EDGE temp;
	int left = index * 2 + 1;
	int right = index * 2 + 2;
	int largest = index;

	if (left < size && e[left].weight > e[largest].weight)
	{
		largest = left;
	}

	if (right < size && e[right].weight > e[largest].weight)
	{
		largest = right;
	}

	if (largest != index)
	{
		temp = e[largest];
		e[largest] = e[index];
		e[index] = temp;

		max_heapify(largest, size);
	}
}

/*
build_max_heap()
make the max heap
*/
void build_max_heap(int line)
{
	int i;

	for (i = line / 2; i >= 0; i--)
	{
		max_heapify(i, line);
	}
}
