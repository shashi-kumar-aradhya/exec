#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> /* for fork */
#include <sys/types.h> /* for pid_t */
#include <sys/wait.h> /* for wait */

int main(int c, char*argv[])
{
	char ptr[5][200];
	FILE *fp = NULL;
	int i = 0, stat;
	int flag = 1;
	pid_t g_pid[5];
	pid_t pid[5];
	int count = 0;
	fp = fopen(argv[1], "r+");
	if (NULL == fp) {
		perror("Error : ");
	}

	while(flag) {
		for (i =0; i < 5; i++) {
			memset(ptr[i], '\0', sizeof(ptr[i]));
			if(NULL != fgets(ptr[i], sizeof(ptr[i])-1, fp)) {
				count++;
				if (*(ptr[i] + strlen(ptr[i]) - 1) == '\n')
					*(ptr[i] + strlen(ptr[i]) - 1) = '\0';;				
				printf("count = %d, link = %s\n", count, ptr[i]);

				pid[i]=fork();
				if (pid[i]==0)
				{ /* child process */
					g_pid[i] = getpid();
					printf("pid of process = %d, pid = %d\n", g_pid[i], pid[i]);
					//      static char *argv[]={"echo","Foo is my name.",NULL};
					static char *argv[3];
					argv[0] = "youtube-dl";
					argv[1] = ptr[i];
					argv[2] = NULL;
					execv("/usr/bin/youtube-dl", argv);
					exit(127); /* only if execv fails */
				}
			}
			else
			{
				flag = 0;	
			}
		}
		for (i=0; i<5; i++)
		{
			pid_t cpid = waitpid(pid[i], &stat, 0);
			if (WIFEXITED(stat))
				printf("Child %d terminated with status: %d\n",	cpid, WEXITSTATUS(stat));
		}
	}
	printf("\n\nTotal count = %d\n", count);
	return 0;
}
