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
  void *p1, *p2, *p3, *p4, *p5;
  printf("For best fit\n");
  arenaCheck();
  p1 = bestFitAllocRegion(254); 
  p2 = bestFitAllocRegion(25400); 
  p3 = bestFitAllocRegion(50800);
  p4 = bestFitAllocRegion(254); 
  p5 = bestFitAllocRegion(6350);

  freeRegion(p2);
  freeRegion(p4);
  arenaCheck();
  p4 = bestFitAllocRegion(254);
  arenaCheck();
  
  printf("%8zx %8zx %8zx\n", p1, p2, p3);
  
  freeRegion(p1);
  arenaCheck();
  freeRegion(p2);
  arenaCheck();
  freeRegion(p3);
  arenaCheck();
  freeRegion(p4);
  arenaCheck();
  freeRegion(p5);
  arenaCheck();

  {				/* measure time for 10000 mallocs */
    struct timeval t1, t2;
    int i;
    getutime(&t1);
    for(i = 0; i < 10000; i++)
      if (bestFitAllocRegion(4) == 0) 
	break;
    getutime(&t2);
    printf("%d bestFitAllocRegion(4) required %f seconds\n", i, diffTimeval(&t2, &t1));
  }
  return 0;
}



