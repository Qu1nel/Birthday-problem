#ifndef CALENDAR_H
#define CALENDAR_H
#include <stdint.h>

#include "_date.h"


char* MONTHS[12] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

extern Date* get_date(const int16_t y, const int16_t m, const int16_t d);
extern Date* get_date_by_second(const int32_t second);
extern Date** get_brithdays(const size_t num_of_brithdays);
extern Date* get_match(Date** brithdays, size_t length);

extern void free_brithdays(Date** brithdays, size_t len);


#endif  // CALENDAR_H
