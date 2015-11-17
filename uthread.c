#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"

#undef NULL
#define NULL ((void*)0)
#define PGSIZE (4096)

void* start;

/*
 * This is where you'll need to implement the user-level functions
 */


void lock_init(lock_t *lock) {
  lock->locked = 0;
  lock->cpu = 0;
}

void lock_acquire(lock_t *lock) {

  while(xchg(&lock->locked, 1) != 0)
    ;
}

void lock_release(lock_t *lock) {
  lock->pcs[0] = 0;
  lock->cpu = 0;
  xchg(&lock->locked, 0);
}

int thread_join(int pid) {
  if (pid > 0){
    if (pid == join(pid)){
      free(start);
      return pid;
    }
  }
  else if (pid == -1){
    return join(pid);
  }
  return -1;
}

int thread_create(void (*start_routine)(void *), void *arg) {
  void *stack = malloc(PGSIZE*2);
  start = stack;
  if(stack == NULL){
    return -1;
  }
  if((uint)stack % PGSIZE)
    stack = stack + (PGSIZE - (uint)stack % PGSIZE);
  return clone(start_routine, arg, stack);
}
