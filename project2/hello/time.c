#include<stdio.h>
#include<time.h>
#include <sys/time.h>

void timestamp();
long long current_timestamp();

int main(){
    long long before = current_timestamp();
    printf("Before time is %lld\n", before);
    int i = 10000000;
    while(i){
        i--;
    }
    long long after = current_timestamp();
    printf("Before time is %lld\n", after);
    printf("Time spent is %lld\n", after-before);
    return 0;
}

long long current_timestamp() {
    struct timeval te;
    gettimeofday(&te, NULL); // get current time
    long long milliseconds = te.tv_sec*1000LL + te.tv_usec/1000; // caculate milliseconds
    // printf("milliseconds: %lld\n", milliseconds);
    return milliseconds;
}

void timestamp() {
    time_t ltime; /* calendar time */
    ltime=time(NULL); /* get current cal time */
    printf("%s",asctime( localtime(&ltime) ) );
}

