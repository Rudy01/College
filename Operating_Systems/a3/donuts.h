/*
    Jason Downing
    Assignment 3
    Operating Systems - COMP.3080
    10/24/2016

    This is a header file for A3
    Parts of this file are originally from this helpfile:
    http://www.cs.uml.edu/~bill/cs308/call_help_assign3.txt

    I have added several includes such as stdio, stdlib, time.h, and unistd.h to
    avoid getting a ton of errors and warnings.
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/signal.h>
#include <sys/time.h>
#include <unistd.h>

#define   SEMKEY      (key_t)549351763
#define   MEMKEY      (key_t)549351763
#define   NUMFLAVORS  4
#define   NUMSLOTS    50
#define   NUMSEMIDS   3
#define   PROD        0
#define   CONSUMER    1
#define   OUTPTR      2

struct  donut_ring {
  int flavor  [NUMFLAVORS]  [NUMSLOTS];
  int outptr  [NUMFLAVORS];
};

extern int p (int, int);
extern int v (int, int);
extern int semsetall (int, int, int);
