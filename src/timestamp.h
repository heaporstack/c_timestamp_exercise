#ifndef timestamp_timestamp
#define timestamp_timestamp

char* str_time_off(uint64_t, int32_t);
#define str_time(ms) str_time_off(ms, 0)

#endif
