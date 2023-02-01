#include "interface.h"
#include "timestamp.h"

static uint8_t integer_length(uint64_t value) {
    uint8_t ret = 0;
    while (value > 0) {
        value /= 10;
        ++ret;
    }
    return ret;
}

char *str_time_off(uint64_t ms, int32_t off) {
    ms += off;
    uint8_t off_pos = off >= 0;
    off = abs(off);

    uint8_t _ms = 0 + ms % 1000;
    ms /= 1000;
    uint8_t s = 0 + ms % 60;
    ms /= 60;
    uint8_t min = 0 + ms % 60;
    ms /= 60;
    uint8_t h = 0 + ms % 24;
    ms /= 24;
    uint8_t d = 0;
    uint8_t m = 0;
    uint64_t y = 1970;
    uint8_t days_per_month[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    while (ms > days_per_month[m]) {
        if ((y % 400 == 0) || (y % 4 == 0) && (y % 100 != 0)) {
            days_per_month[1] = 29;
        } else {
            days_per_month[1] = 28;
        }
        if (m == 12) {
            m = 0;
            ++y;
        }
        ms -= days_per_month[m++];
    }
    ++d;
    ++m;

    uint8_t off_ms = 0 + off % 1000;
    off /= 1000;
    uint8_t off_s = 0 + off % 60;
    off /= 60;
    uint8_t off_min = 0 + off % 60;
    off /= 60;
    uint8_t off_h = 0 + off % 24;
    off /= 24;

    // special characters such as <space>, :, or -
    uint16_t reserve = 12 + integer_length(_ms) + integer_length(y);
    reserve += s > 10 ? 2 : 1;
    reserve += min > 10 ? 2 : 1;
    reserve += h > 10 ? 2 : 1;
    reserve += d > 10 ? 2 : 1;
    reserve += m > 10 ? 2 : 1;
    char *str = allocate(reserve * sizeof(char));
    char str_m[3], str_d[3], str_h[3], str_min[3], str_s[3], str_off_h[3], str_off_min[3], str_off_s[3];
    m > 10 ? string(str_m, "%i", m) : string(str_m, "0%i", m);
    d > 10 ? string(str_d, "%i", d) : string(str_d, "0%i", d);
    h > 10 ? string(str_h, "%i", h) : string(str_h, "0%i", h);
    min > 10 ? string(str_min, "%i", min) : string(str_min, "0%i", min);
    s > 10 ? string(str_s, "%i", s) : string(str_s, "0%i", s);
    off_h > 10 ? string(str_off_h, "%i", off_h) : string(str_off_h, "0%i", off_h);
    off_min > 10 ? string(str_off_min, "%i", off_min) : string(str_off_min, "0%i", off_min);
    off_s > 10 ? string(str_off_s, "%i", off_s) : string(str_off_s, "0%i", off_s);
    char sign = off_pos ? '+' : '-';
    string(str, "%li-%s-%s %s:%s:%s.%i %c(%s:%s:%s.%i)", y, str_m, str_d, str_h, str_min, str_s, _ms, sign, str_off_h, str_off_min, str_off_s, off_ms);
    return str;
}
