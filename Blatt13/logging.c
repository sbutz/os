#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <time.h>

#include <sys/time.h>
#define THREADS 5
#define STEPS_PER_ACTIVITY 5

pthread_mutex_t lock;  // access to log is exclusive
struct timestamp {
   int id, value;
} *logData[THREADS * STEPS_PER_ACTIVITY];
int lineCount;

int timeCmp(const void *v1, const void *v2)  {
    struct timestamp *ts1 = (struct timestamp *)v1,
                     *ts2 = (struct timestamp *)v2;
    return ts1->value - ts2->value;
}

void *task(void *data)  {
   int i, nr = *((int *)data);
   for (i = 0;  i < STEPS_PER_ACTIVITY;  ++i)  {
      struct timestamp *stamp = (struct timestamp *)
                       malloc(sizeof(struct timestamp));
      struct timespec value;
      pthread_mutex_lock(&lock);
      clock_gettime(CLOCK_REALTIME, &value);
      stamp->id = nr;
      stamp->value = value.tv_nsec;
      logData[lineCount++] = stamp;
      pthread_mutex_unlock(&lock);
   }
}

void analyzeScheduling(pthread_attr_t *ap)  {
   int i, n[THREADS]; pthread_t t[THREADS];
   lineCount = 0;
   for (i = 0;  i < THREADS;  ++i)  {
      int errno; n[i] = i; 
      if (errno = pthread_create(&t[i], ap, task, &n[i]))  {
        exit(-1);
      }
   }
   for (i = 0;  i < THREADS;  ++i)
      pthread_join(t[i], NULL);
   qsort(logData, lineCount, sizeof(struct timestamp *), timeCmp);
   for (i = 0;  i < lineCount;  ++i)
      printf("%2d: Thread #%d performed an activity\n", i + 1, logData[i]->id); 
}

int main(int argc, char **argv)  {

   return 0;
}
