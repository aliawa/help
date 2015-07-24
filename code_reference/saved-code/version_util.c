/**
 * @file libewn/version_util.c
 *
 * Copyright (C) 2005 Edgewater Networks.
 */

#define _GNU_SOURCE
#include <time.h>

#include "version_util.h"
#include "cfg_util.h"
#include "../cgi/src/defines.h"

static char   s_versionBuff[DEFAULT_STR_LEN]  = {0};
static char * s_versionDate                   = NULL;
static int    g_first_run                     = 0;

// --------------------------------------------------------------------------

void loadVersionStr(void) {
    FILE *fp;
    memset(s_versionBuff, 0, sizeof(s_versionBuff));
    fp = fopen(VERSION_FILE, "r");
    if (fp != NULL) {
        char* str_ptr = fgets(s_versionBuff, sizeof(s_versionBuff), fp);
        if(str_ptr != NULL) {
            str_ptr = index(s_versionBuff, (int)'-');
            if(str_ptr != NULL) {
                *(str_ptr - 1) = '\0';
                s_versionDate = str_ptr + 3;
            }
        }
        fclose(fp);
    }
}

// --------------------------------------------------------------------------

char *versionString(void){
    return s_versionBuff;
}

// --------------------------------------------------------------------------

char *versionDateString(void){
    return s_versionDate;
}

// --------------------------------------------------------------------------

int firstRun() {
    return g_first_run;
}

// --------------------------------------------------------------------------

int chkVersionChange() {
    char keySaved[14]   = {0};
    char keyNew[14]     = {0};
    struct tm tm        = {0};
    char* verTime       = versionDateString();

    if (verTime) {
        strptime(verTime, "%a %b %d %T PDT %Y", &tm);
        strftime(keyNew, sizeof(keyNew), "%s", &tm);

        load_str(MAND_CONF,  "MAGIC_KEY", keySaved, sizeof(keySaved), NULL);
        g_first_run = strcmp(keySaved, keyNew);
        if (g_first_run != 0)
            save_str(MAND_CONF, "MAGIC_KEY", keyNew);
    } else {
        g_first_run = 0;
    }
    return g_first_run;
}


