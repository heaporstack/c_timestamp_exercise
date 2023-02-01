#include "interface.h"
#include "timestamp.h"

uint8_t main(uint64_t count, char **args) {
    char *time0 = str_time_off(1675289559520, 3600000);
    out("%s\n", time0);
    deallocate(time0);

    char *time1 = str_time(0);
    out("%s\n", time1);
    deallocate(time1);

    char *time2 = str_time_off(0, -3600000);
    out("%s\n", time2);
    deallocate(time2);

    return 0;
}
