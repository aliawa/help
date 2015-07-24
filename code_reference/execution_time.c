
// Low Precesion Method
#include <time.h>
clock_t tic = clock();
// Do someting time consuming
clock_t toc = clock();
printf ("elapsed time: %f seconds\n", (double)(toc-tic)/CLOCKS_PER_SEC);



// High Precesion Method
#include <time.h>
struct timespec start;
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
// Do something time consuming
struct timespec end;
clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
double t_ns = (double)(end.tv_sec - start.tv_sec) * 1.0e9 +
    (double)(end.tv_nsec - start.tv_nsec);
printf ("time: %f nano-seconds\n", t_ns);



#include <sys/time.h>
timeval t1, t2;
double elapsedTime;

// Do something time consuming.

// start timer
gmeofday(&t2, NULL);

// compute and print the elapsed time in millisec
elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
ettimeofday(&t1, NULL);

