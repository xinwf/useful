#include <stdio.h>
#include <time.h>
#include <sys/time.h>

void sysLocalTime(void)
{
    time_t             timesec;
    struct tm         *t;
    
    
    time(&timesec);
    t = localtime(&timesec);
    
    printf("%d-%d-%d %d:%d:%d\n", 1900+t->tm_year, 1+t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec);
    
}

void sysUsecTime(void)
{
    struct timeval    tv;
    struct timezone tz;
    
    struct tm         *t;
    
    gettimeofday(&tv, &tz);
    printf("tv_sec:%ld\n",tv.tv_sec);
    printf("tv_usec:%ld\n",tv.tv_usec);
    printf("tz_minuteswest:%d\n",tz.tz_minuteswest);
    printf("tz_dsttime:%d\n",tz.tz_dsttime);
    
    t = localtime(&tv.tv_sec);
    printf("time_now:%d-%d-%d %d:%d:%d.%ld\n", 1900+t->tm_year, 1+t->tm_mon, t->tm_mday, t->tm_hour, t->tm_min, t->tm_sec, tv.tv_usec);
}

int main(void)
{
    sysLocalTime();
    
    sysUsecTime();
    
    return 0;
}
