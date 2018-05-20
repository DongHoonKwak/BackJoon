#include <iostream>>
#include <queue>
using namespace std;

struct water {
	int a, b, c;
};

int main() 
{
	queue <water> wt;
	int a_size, b_size, c_size;
	bool check[1001][1001] = {false, };

	int i = 0; //답 인덱스
	int wt_arr[1001] = { 0, };



	scanf("%d%d%d", &a_size, &b_size, &c_size);

	wt.push({ 0,0,c_size });

	while (!wt.empty())
	{
		water now = wt.front();
		wt.pop();

		if (check[now.a][now.b]) //중복체크
			continue;


		check[now.a][now.b] = true;
		
		if (now.a == 0)
		{
			wt_arr[i++] = now.c;
			if(now.c != c_size)
				wt_arr[i++] = c_size - now.c;
		}

		// ab ac ba bc ca cb
		if (now.a + now.b > b_size) //a에서 b로 부을때
			wt.push({ (now.a + now.b) - b_size,b_size,now.c });
		else
			wt.push({ 0,now.a + now.b,now.c });

		if (now.a + now.c > c_size) //a에서 c로 부을때
			wt.push({ (now.a + now.c) - c_size, now.b, c_size });
		else
			wt.push({ 0,now.b, now.a+now.c });

		if (now.b + now.a > a_size) //b에서 a로 부을때
			wt.push({ a_size ,now.b+now.a - a_size,c_size });
		else
			wt.push({ now.b + now.a,0, now.c });

		if (now.b + now.c > c_size) //b에서 c로 부을때
			wt.push({ now.a ,(now.b + now.c) - c_size,c_size });
		else
			wt.push({ now.c + now.a,now.b,0 });

		if (now.c + now.a > a_size) //c에서 a로 부을때
			wt.push({ a_size,now.b,(now.c + now.a)-a_size });
		else
			wt.push({ now.c + now.a,now.b,0 });

		if (now.c + now.b > b_size) //c에서 b로 부을때
			wt.push({ now.a,b_size,(now.c + now.b) - b_size });
		else
			wt.push({ now.a,now.c + now.b,0 });
	}

	for (int j = 0; j < i; j++)
	{
		printf("%d ", wt_arr[j]);
		if (wt_arr[j] != c_size)
			printf("%d ", c_size - wt_arr[j]);
	}
}