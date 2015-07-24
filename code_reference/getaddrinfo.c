#include <stdio.h>
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netdb.h> 
#include <strings.h> 


const char* ipFamily_str(int f, char b[]) {
    switch(f){
        case AF_INET: return "AF_INET";
        case AF_INET6: return "AF_INET6";
        case AF_UNSPEC: return "AF_UNSPEC";
        default: snprintf(b, 15, "unknown:%d", f);return b;
    }
}
            

const char* ipSockType_str(int s, char b[]) {
    switch(s){
        case SOCK_STREAM: return "SOCK_STREAM";
        case SOCK_DGRAM: return "SOCK_DGRAM";
        case SOCK_RAW: return "SOCK_RAW";
        case 0: return "SOCK_ANY";
        default: snprintf(b, 15, "unknown:%d", s);return b;
    }
}
            
const char* ipProtocolType_str(int p, char b[]) {
    switch(p){
        case IPPROTO_IP: return "IPPROTO_IP";
        case IPPROTO_UDP: return "IPPROTO_UDP";
        case IPPROTO_TCP: return "IPPROTO_TCP";
        default: snprintf(b, 15, "unknown:%d", p);return b;
    }
}


// convert sockadd* to string
const char* ipAddr_str(struct sockaddr* addr, char addrBuf[], int sz) {
    int family = ((struct sockaddr*)addr)->sa_family;
    if (family == AF_INET) {
        char buf[INET_ADDRSTRLEN];
        struct sockaddr_in* sa = (struct sockaddr_in*) addr;
        inet_ntop(family, (void*)&sa->sin_addr, buf, sizeof(buf));
        snprintf(addrBuf, sz, "%s:%d", buf, sa->sin_port);
    } else if (family == AF_INET6) {
        char buf[INET6_ADDRSTRLEN];
        struct sockaddr_in6* sa = (struct sockaddr_in6*) addr;
        inet_ntop(family, (void*)&sa->sin6_addr, buf, sizeof(buf));
        snprintf(addrBuf, sz, "[%s]:%d", buf, sa->sin6_port);
    } else {
        bzero(addrBuf, sz);
        // Unkonwn family
    }
    return addrBuf;
}



int main (int argc, char* argv[]) {
    struct addrinfo hints, *servinfo, *p;
    int rv, i;
    char buff[255];

    bzero(&hints, sizeof hints);
    hints.ai_family = AF_UNSPEC; //AF_INET6;
    hints.ai_protocol = IPPROTO_UDP;

    if ((rv = getaddrinfo(argv[1], NULL, &hints, &servinfo)) != 0) {
        fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
    } else {
            printf("%3s%6s%15s%15s%15s%6s%10s%20s\n", "No", "flags", "family", "socktype", 
                    "protocol",
                    "len",
                    "cname",
                    "addr");

            // loop through all the results 
            for(p = servinfo, i=0; p != NULL; p = p->ai_next, ++i) {
                printf("%3d%6d%15s%15s%15s%6d%10s%20s\n",
                        i,
                        p->ai_flags,
                        ipFamily_str(p->ai_family, buff),
                        ipSockType_str(p->ai_socktype, buff),
                        ipProtocolType_str(p->ai_protocol, buff),
                        p->ai_addrlen,
                        (p->ai_canonname)? p->ai_canonname:"",
                        ipAddr_str(p->ai_addr, buff, sizeof(buff)));
            }
            freeaddrinfo(servinfo);
    }
    return 0;
}
