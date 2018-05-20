#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	char a[7] = {'.', };

	for (int y = 0; y < 13; y++)
	{
			scanf("%s", &a[y]);
	}

	for (int y = 0; y < 13; y++)
	{
			printf("%s", &a[y]);
			printf("\n");
	}

}