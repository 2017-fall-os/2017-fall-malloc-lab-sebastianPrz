#include "stdio.h"
#include "stdlib.h"
#include "myAllocator.h"
#include "sys/time.h"
#include <sys/resource.h>
#include <unistd.h>

double diffTimeval(struct timeval *t1, struct timeval *t2) {
  double d = (t1->tv_sec - t2->tv_sec) + (1.0e-6 * (t1->tv_usec - t2->tv_usec));
  return d;
}

void getutime(struct timeval *t)
{
  struct rusage usage;
  getrusage(RUSAGE_SELF, &usage);
  *t = usage.ru_utime;
}

int main() 
{
  void *p1, *p2, *p3, *p4;
  printf("For realloc\n");
  printf("Start %p\n", p1 - 8);
  p1 = malloc(200);
  arenaCheck();
  p2 = malloc(150);
  arenaCheck();
  p3 = malloc(200);
  arenaCheck();
  p4 = malloc(150);
  freeRegion(p2);
  arenaCheck();
  p3 = realloc(p3, 250);
  arenaCheck();
  printf("End %p\n", p1 - 8);
  return 0;
}
