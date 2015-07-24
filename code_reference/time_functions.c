#include <time.h>
#include <stdio.h>
#include <strings.h>

int main (int argc, char**argv) {

    time_t cal_tm = time(NULL);

    // time_t or Simple Calendar Time
    printf("time_t(NULL) is: %ld\n", cal_tm);
    // can also use printf("%ju\n", (uintmax_t) cal_tm);

    // -----------------------------------------------
    //                  Conversion
    // -----------------------------------------------

    // time_t --> string
    printf("Current time using \"ctime()\": %s\n", ctime (&cal_tm));
   

    // convert from time_t to tm as UTC
    struct tm* stm1 = gmtime(&cal_tm);
    printf("Current time in UTC using \"gmtime()\": %s\n", asctime (stm1));

    // convert from time_t to tm as Local time
    struct tm* local_tm = localtime(&cal_tm);
    printf("Current time local using \"localtime()\": %s\n", asctime (local_tm));
   
    // Formated output with strftime
    char buff[50];
    strftime(buff, sizeof(buff), "%D", local_tm);
    printf("Today's date: %s\n", buff);

    // -----------------------------------------------
    //                  Struct tm
    // -----------------------------------------------

    // Reference Date.
    struct tm azadi_day;
    bzero(&azadi_day, sizeof(struct tm));
    azadi_day.tm_mday = 14;
    azadi_day.tm_mon  = 7;    // starts from 0
    azadi_day.tm_year = 47;   // Year since 1900
    printf("Independence day: %s\n", asctime (&azadi_day));

    // -----------------------------------------------
    //              Time manipulation
    // -----------------------------------------------

    // tm --> time_t
    time_t azadi_time = mktime(&azadi_day);

    time_t age1 = difftime(cal_tm, azadi_time);
    time_t age2 = cal_tm - azadi_time;

    printf ("Age of Pak with difftime: %ld seconds\n", age1);
    printf ("Age of Pak subtraction  : %ld seconds\n", age2);

    return 0;
}
