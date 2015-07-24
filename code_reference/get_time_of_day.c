#include <stdio.h>
#include <sys/time.h>


int main (int argc, char** argv)
{
    struct timeval startTime;
    struct timeval timeDiff;
    struct timeval now;
    
    // read time in timeval structure
    gettimeofday(&startTime, NULL);

    // printing timeval
    printf("time now:%ld.%.6ld sec\n", startTime.tv_sec, startTime.tv_usec);

    sleep (8);

    gettimeofday(&now, NULL);
   
    // get the difference
    timersub(&now, &startTime, &timeDiff);


    // checking for non-zero timeval
    if (timerisset(&timeDiff) ){
        printf("Process time:%ld.%.6ld sec\n", timeDiff.tv_sec, timeDiff.tv_usec);
    }else{
        printf("no time elaplsed\n");
    }
}

