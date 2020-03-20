#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(void) {
	srand(time(0));
	int i, n;
	char s[100];
	
	n = (rand() % 10) + 1;
	printf("Enter your name: ");
	scanf("%99s", s);

	if (n % 2 == 0) {
		for (i = 0; i < n; i++) {
			printf("%d: hello, %s!\n", n, s);
		}
	} else {
		for (i = 0; i < n; i++) {
			printf("%d: hi there, %s!\n", n, s);
		}
	}
	return 0;
}
