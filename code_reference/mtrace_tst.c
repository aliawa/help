#include <stdio.h>
#include <stdlib.h>

#include <mcheck.h>
#include <signal.h>


// ---------------------------------------------------
//  using glibc mtrace
//  - set environment before executing
//    export MALLOC_TRACE=mtrace.log
//
//  - examin the log
//    mtrace mytesprog mtrace.log
// ---------------------------------------------------

static void mtrace_enable (int sig)
{
    printf("mtrace_enable\n");
    mtrace ();
}

static void mtrace_disable (int sig)
{
    printf("mtrace_disable\n");
    muntrace ();
}

// this function will produce a memory leak
char* getValue()
{
    char* buff = (char*) malloc(40);
    snprintf(buff, 40, "%lu", time(NULL)); 
	return buff;
}


// install signal handlres to be able to turn
// mtrace loggin on and off at runtime.
void installSigHandlers()
{
    struct sigaction sa;
    
    sa.sa_sigaction = (void *)mtrace_enable;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_SIGINFO;
    sigaction(SIGUSR1, &sa, NULL);

    sa.sa_sigaction = (void *)mtrace_disable;
    sigaction(SIGUSR2, &sa, NULL);
}



void main()
{
    installSigHandlers();

    while (1) {
        printf ("got: %s\n", getValue());
        getchar();
    }
}

