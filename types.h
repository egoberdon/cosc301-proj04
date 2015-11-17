typedef unsigned int   uint;
typedef unsigned short ushort;
typedef unsigned char  uchar;
typedef uint pde_t;
// Mutual exclusion lock.
typedef struct lock {
  uint locked;       // Is the lock held?
} lock_t;

extern void* start;
