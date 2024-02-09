#include <iso646.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

#include "_date.h"

const int32_t DEF_TIME = 946674000;  // 00-01-100 00:00:00 GMT+0000
const int32_t LEAP_YEAR_SEC = 31622400;  // Total second in leap year: 2000


uint32_t _random(const uint32_t min, const uint32_t max)
{
    uint32_t result = rand() & 0xff;

    result ^= (rand() & 0xff) << 8;
    result ^= (rand() & 0xff) << 16;
    result ^= (rand() & 0xff) << 24;

    result = min + result % (max - min);
    return result;
}


Date* get_date(const int16_t y, const int16_t m, const int16_t d)
{
    Date* result = malloc(sizeof(Date));

    if (result == NULL) {
        perror("Allocate error: internal 'get_date'");
        exit(1);
    }

    result->year = y;
    result->month = m;
    result->day = d;

    return result;
}


Date* get_date_by_second(const int32_t second)
{
    int32_t total_second = DEF_TIME + second;
    time_t total_time = (time_t)total_second;
    struct tm tmp_time_buffer;

    localtime_s(&tmp_time_buffer, &total_time);

    tmp_time_buffer.tm_year += 1900;
    tmp_time_buffer.tm_mon++;

    return get_date(tmp_time_buffer.tm_year, tmp_time_buffer.tm_mon, tmp_time_buffer.tm_mday);
}


Date** get_brithdays(const size_t num_of_brithdays)
{
    Date** brithdays = calloc(num_of_brithdays, sizeof(Date*));

    if (brithdays == NULL) {
        perror("Allocate error: internal 'get_brithdays'");
        exit(1);
    }

    for (size_t i = 0; i < num_of_brithdays; ++i) {
        uint32_t second = _random(0, LEAP_YEAR_SEC);
        brithdays[i] = get_date_by_second(second);
    }

    return brithdays;
}


Date* get_match(Date** brithdays, size_t length)
{
    for (size_t i = 0; i < length - 1; ++i) {
        for (size_t j = i + 1; j < length; ++j) {
            if (brithdays[i]->month == brithdays[j]->month and brithdays[i]->day == brithdays[j]->day) {
                return brithdays[i];
            }
        }
    }
    return NULL;
}


void free_brithdays(Date** brithdays, size_t len)
{
    for (size_t i = 0; i < len; ++i) {
        free(brithdays[i]);
    }
    free(brithdays);
}
