#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */

#define MAX_COUNT 5

int main(int c, char*argv[])
{
	char ptr[5][200];
	FILE *fp = NULL;
	int i = 0, stat, a;
	int flag = 1;
	pid_t g_pid[5];
	pid_t pid[5];
	int count = 0;
	char buf[100];
	char buf_1[100];
	char buf_2[] = "cd ..";
	fp = fopen(argv[1], "r+");
	if (NULL == fp) {
		perror("Error : ");
	}
	memset(buf, '\0', sizeof(buf));
	strcpy(buf, "mkdir -p ");
	strcat(buf, argv[1]);
	strcat(buf, " cd $_");
	system(buf); 

	while(flag) {
		a = count / MAX_COUNT;
		memset(buf, '\0', sizeof(buf));
		strcpy(buf, "mkdir -p ");
		memset(buf_1, '\0', sizeof(buf_1));
		sprintf(buf_1, "%d", a);
		strcat(buf, buf_1);
		strcat(buf, " cd $_");
		system(buf); 


		for (i =0; i < MAX_COUNT && flag; i++) {


			if( count < 103){
				count++;
				printf("count = %d\n", count);
			}
			else
			{
				flag = 0;	
			}
		}
		system(buf_2);
	}
	printf("\n\nTotal count = %d\n", count);
	return 0;
}
