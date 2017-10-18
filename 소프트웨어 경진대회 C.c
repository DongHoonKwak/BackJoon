#include <stdio.h>
#include <string.h>

int main() {
	char a[10] = "NULL";
	char b[10] = "NULL";
	int count = 0;
	size_t size = strlen(a);
	scanf("%s %s", &a, &b);
	for (size_t i = size; i > 0; i--) {
		if (a[i] < b[i]) {
			count++;
			a[i - 1] = a[i - 1] - 1;
		}
	}
	printf("%d\n", count);
	return 0;
}