/**
 * @file sipTls.cpp
 *
 * @brief SIP TLS implementation
 *
 */

#include <signal.h>
#include <stdio.h>  // printf
#include <stdlib.h> // exit
#include <errno.h>

static void sigpipe_handler(int sig, siginfo_t *si, void *unused)
{
    printf("Got SIGPIPE at address: 0x%lx\n", (long) si->si_addr);
    exit(EXIT_FAILURE);
}

#define perror_exit(msg) \
    do { printf("Error: %s: %d:%s", msg, errno, strerror(errno));} while (0)


int main (int argc, char** argv) {

    // Set up a SIGPIPE handler
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags     = SA_SIGINFO;
    sa.sa_sigaction = sigpipe_handler;

    if (sigaction(SIGPIPE, &sa, NULL) == -1) {
        perror_exit("sigaction");
        return 1;
    }

    return 0;
}
