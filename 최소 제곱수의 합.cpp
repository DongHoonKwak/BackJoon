#include<stdio.h>

int dp[100000 + 1];

int main()
{
	int n;
	scanf("%d", &n);

	for (int i = 0; i <= n; i++)
	{
		dp[i] = i;
		for (int j = 0; j*j <= i; j++)
		{
			if (dp[i - j*j] + 1 < dp[i])
				dp[i] = dp[i - j*j] + 1;
		}
	}

	printf("%d\n", dp[n]);

}
