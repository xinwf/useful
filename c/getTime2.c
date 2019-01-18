#include <stdio.h>
#include <time.h>
#include <sys/time.h>

int main(void)
{   
    struct timeval    tv;
    struct timezone tz;
    struct tm         *t;
    gettimeofday(&tv, &tz);
    t = localtime(&tv.tv_sec);
    printf("time_now:%d-%d-%d %d:%d:%d.%ld\n", 1900+t->tm_year, 1+t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, tv.tv_usec);    
    return 0;
}
