// cdc.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"




//--------------------------------------------------------------------------------

//cpp_trick.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "cpp_trick.h"

void panic(char *msg) {
        fprintf(stderr, "%s\n", msg);
        exit(EXIT_FAILURE);
}

void *xmalloc(size_t size) {
        void *p;
        
        p = malloc(size);
        if (p == NULL)
                panic("Out of memory");
        return p;
}

void *xstrdup(char *str) {
        char *copy;
        
        copy = xmalloc(strlen(str) + 1);
        strcpy(copy, str);
        return copy;
}

int read_integer(int *p) {
        if (fread(p, sizeof(int), 1, stdin) == 0)
                return 0;
        return 1;
}

char *read_string(void) {
        int len;
        char *str;
        
        if (read_integer(&len) == 0)
                return NULL;
        str = xmalloc(len + 1);
        if (fread(str, len, 1, stdin) != 1)
                return NULL;
        str[len] = '\0';
        return str;
}

void write_integer(int i) {
        if (fwrite(&i, sizeof(i), 1, stdout) != 1)
                panic("Write error.");
}

void write_string(char *str) {
        int len;
        
        len = (int) strlen(str);
        write_integer(len);
        if (fwrite(str, len, 1, stdout) != 1)
                panic("Write error.");
}

typedef enum {
        #define INTEGER(name)
        #define STRING(name)
        #define PACKET(name, fields) name,
        #include "cpp_trick.h"
} PacketType;

char *type_name(PacketType type) {
        #define INTEGER(name)
        #define STRING(name)
        #define PACKET(name, fields) \
                if (type == name) return #name;
        #include "cpp_trick.h"
        return "unknown";
}


typedef struct Packet {
        PacketType type;
        
        #define INTEGER(name) int name;
        #define STRING(name) char *name;
        #define PACKET(name, fields) struct name { fields } name;
        #include "cpp_trick.h"
} Packet;


Packet *packet_create(PacketType type) {
        Packet *packet;
        
        packet = xmalloc(sizeof(Packet));
        packet->type = type;

        #define INTEGER(name) p->name = 0;
        #define STRING(name) p->name = NULL;
        #define PACKET(name, fields) \
                { struct name *p = &packet->name; fields }
        #include "cpp_trick.h"

        return packet;
}


void packet_destroy(Packet *packet) {
        #define INTEGER(name)
        #define STRING(name) free(p->name); p->name = NULL;
        #define PACKET(name, fields) \
                { struct name *p = &packet->name; fields }
        #include "cpp_trick.h"
        free(packet);
}

void packet_dump(Packet *packet) {
        printf("Dumping packet %p:\n", (void *) packet);
        printf("  Type: %s\n", type_name(packet->type));
        #define INTEGER(name) printf("  %s: %d\n", #name, p->name);
        #define STRING(name) printf("  %s: %s\n", #name, p->name);
        #define PACKET(name, fields) \
                if (packet->type == name) \
                        { struct name *p = &packet->name; fields }
        #include "cpp_trick.h"
        printf("End of dump.\n");
}


Packet *packet_read(void) {
        Packet *packet;
        int type;
        
        if (read_integer(&type) == 0)
                return NULL;
        packet = packet_create(type);
        #define INTEGER(name) read_integer(&p->name);
        #define STRING(name) p->name = read_string();
        #define PACKET(name, fields) \
                if (type == name) { struct name *p = &packet->name; fields }
        #include "cpp_trick.h"
        
        return packet;
}


void packet_write(Packet *packet) {
        write_integer(packet->type);
        #define INTEGER(name) write_integer(p->name);
        #define STRING(name) write_string(p->name);
        #define PACKET(name, fields) \
                if (packet->type == name) \
                        { struct name *p = &packet->name; fields }
        #include "cpp_trick.h"
}


int main(int argc, char **argv) {
        Packet *packet;

        if (argc != 2) {
                fprintf(stderr, "Usage: %s [read|write]\n", argv[0]);
                return EXIT_FAILURE;
        }
        
        if (strcmp(argv[1], "read") == 0) {
                while ((packet = packet_read()) != NULL) {
                        packet_dump(packet);
                        packet_destroy(packet);
                }
        } else {
                packet = packet_create(Auth);
                packet->Auth.username = xstrdup("guest");
                packet->Auth.password = xstrdup("demo");
                packet_write(packet);
                packet_destroy(packet);

                packet = packet_create(Ack);
                packet->Ack.status = 123;
                packet->Ack.error_text = xstrdup("Access denied.");
                packet_write(packet);
                packet_destroy(packet);
        }

        return 0;
}



/*
int main(int argc, char* argv[])
{
	printf("Hello World!\n");
	return 0;
}
*/
