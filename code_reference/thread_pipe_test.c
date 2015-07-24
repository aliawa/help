#include <stdio.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>


int fd[2];

void* thread_proc_2(void *arg)
{
	printf ("thread_2 started\n");
	sleep(3);
	write(fd[1], "", 1);
	printf("thread_2 done\n");
}

void* thread_proc_1(void *arg)
{
    int ret;
    char ch;
    int maxFd;
	fd_set readSet;
	
    printf("thread_1 started\n");
	
	if (pipe(fd) <0)
    {
	    printf("error opening pipe\n");
    }

    FD_ZERO(&readSet);
    FD_SET(fd[0], &readSet);
    maxFd = fd[0];
	printf("now entering select\n");
	ret = select(maxFd+1, &readSet, 0, 0, NULL);

	if (FD_ISSET(fd[0], &readSet))
	{
        ret = read(fd[0], &ch, 1);
        printf("received %c\n", ch);
	}
}



int main(int argc, char *argv[])
{
	int result;
	pthread_t thread_id_1;
	pthread_t thread_id_2;

	result = pthread_create(&thread_id_1, NULL, thread_proc_1, NULL);
	result = pthread_create(&thread_id_2, NULL, thread_proc_2, NULL);

    pthread_join (thread_id_2, NULL);
	pthread_join (thread_id_1, NULL);
}


