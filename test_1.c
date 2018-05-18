#include <stdio.h>
#include <string.h>

int main()
{

	int a = 5;
	char buf[10];
	memset(buf, '\0', sizeof(buf));
	sprintf(buf, "%d", a);
	printf(" a= %s\n", buf);
	return 0;
}


