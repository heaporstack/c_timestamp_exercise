#ifndef timestamp_interface
#define timestamp_interface

#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"

#define out(args...) fprintf(stdout, args)
#define err(args...) fprintf(stderr, args)
#define string(buf, str, args...) sprintf(buf, str, args)
#define allocate malloc
#define deallocate free

#endif
