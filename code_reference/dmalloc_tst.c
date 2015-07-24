#include <stdio.h>
#include <stdlib.h>

#include <dmalloc.h>
#include <signal.h>


// ---------------------------------------------------
//  using dmalloc library
//  - compile and link with 
//    libdmalloc.a   (non-threaded application)
//    libdmallocth.a (threaded application)
//
//  - set environment before executing
//    the debug=<value> is obtained by oring the dmalloc tokens
//    export DMALLOC_OPTIONS=debug=0x44a40503,inter=1,log=dmalloc.log
//
//  - create logs
//    killall -SIGUSR1 mytst
//
//  - examin the log
//    dmalloc.log
// ---------------------------------------------------

static void dump_stats (int sig)
{
    printf("dump stats\n");
    dmalloc_log_stats();
    dmalloc_log_unfreed();
}


// this function will produce a memory leak
char* getValue()
{
    char* buff = (char*) malloc(40);
    snprintf(buff, 40, "%lu", time(NULL)); 
	return buff;
}



// Normally dmalloc dumps stats when the program exits
// Our program never exits so we dump stats on signal
void installSigHandlers()
{
    struct sigaction sa;
    
    sa.sa_sigaction = (void *)dump_stats;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);
}



void main()
{
    installSigHandlers();

    while (1) {
        printf ("got: %s\n", getValue());
        getchar();
    }
}

