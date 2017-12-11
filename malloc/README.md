# os-malloc
This directory contains:

myAllocator.c: a first-fit, best-fit allocator
myAllocator.h: its header file

myAllocatorTest1.c: a test program that uses the first fit and best fit as a replacement for malloc 
myAllocatorTest2.c: a test program for my allocator using the best fit method 

myMalloc.c: a replacement for malloc that uses my allocator
test1.c: a test program that uses this replacement malloc
allocTest.c: a test program that uses the first fit and best fit as a replacement for malloc

There are two different testers as some implementations of printf
call malloc to allocate buffer space. This causes test1 to behave
improperly as it uses myAllocator as a malloc replacement. In this
case myAllocatorTest1 will function correctly. The only difference
between the programs is that test1 uses myAllocator as a malloc
replacement and myAllocatorTest1 uses myAllocator directly.

Makefile: a fairly portable "makefile", targets "all" and "clean"

To compile: 
 $ make 
To clean:
 $ make clean

The cygwin runtime uses malloc() and brk() extensively.  It is
interesting to compare the output of test1 & myAllocatorTest1.  All
those extra allocated regions are being used by cygwin's libraries!

I created the best fit allocator and also the resizeRegion method to resize an already allocated region.

The best fit allocator at first works like the first fit allocator, however a size_t variable is used to determine is the amount to allocate is the smallest one possible that satisfies the request, if it is then that is the best one. First I check if the region is not already allocated to then proceed check the size. If by any chance it turns out to be the same size then that is the best fit. Otherwise, it will look if the next prefix is enough to satisfy the request, and if a better block is found then that will be our best one, this will be done until there are no more blocks to check, meaning that if one was found that will be the best one.

For the resizeRegion method, in case the region is not big enough it will arrange the rest to make sure it is enough. This is done by first checking if the next block contains enough space for the request, and if it does I then check for the difference between the request and the space available on that prefix, making sure that they are smaller than the next block. If and only if they are smaller or equal the resizing can be performed.

I used as reference the provided code as well as the book chapters on memory. I got more background on the topic by reading the content on this website which describes a possible implementation for malloc and realloc in general. "https://danluu.com/malloc-tutorial/"
I also watched this video with the same purpose of getting another explanation on the topic: "https://youtu.be/xDVC3wKjS64"