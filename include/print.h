#ifndef PRINT_PYTHON_H
#define PRINT_PYTHON_H
#include <stdint.h>

char* print_sep = ", ";
char* print_end = "\n";

void _print(const char* restrict sep, const char* restrict end, const size_t n, ...);

void default_print(void)
{
    print_sep = ", ";
    print_end = "\n";
}

void set_param_print(char* restrict sep, char* restrict end)
{
    print_sep = sep;
    print_end = end;
}

void type_add_char(void);

void type_add_ui8(void);
void type_add_i8(void);

void type_add_ui16(void);
void type_add_i16(void);

void type_add_ui32(void);
void type_add_i32(void);

void type_add_ui64(void);
void type_add_i64(void);

void type_add_double(void);

void type_add_str(void);
void type_add_void(void);

// clang-format off

#define type_add(x)						\
	_Generic((x),						\
		char*: type_add_str,			\
		char: type_add_char,			\
		short: type_add_i16,			\
		int: type_add_i32,				\
		long: type_add_i64,				\
		float: type_add_double,			\
		double: type_add_double,		\
	default: _Generic((x),				\
		signed char: type_add_i8,		\
		signed short: type_add_i16,		\
		signed int: type_add_i32,		\
		signed long: type_add_i64,		\
		unsigned char: type_add_ui8,	\
		unsigned short: type_add_ui16,	\
		unsigned int: type_add_ui32,	\
		unsigned long: type_add_ui64,	\
	default: _Generic((x),				\
		int8_t: type_add_i8,			\
		int16_t: type_add_i16,			\
		int32_t: type_add_i32,			\
		int64_t: type_add_i64,			\
		uint8_t: type_add_ui8,			\
		uint16_t: type_add_ui16,		\
		uint32_t: type_add_ui32,		\
		uint64_t: type_add_ui64,		\
	default: type_add_void				\
)))()

#include "print_n.h"

#define print(...)  print_(__VA_ARGS__, PRINT_RSEQ_N())
#define print_(...) PRINT_ARG_N(__VA_ARGS__)

/*
 *
 *	The PP_NARG* macro returns the number of arguments that have been
 *	passed to it.
 *
 *  https://groups.google.com/forum/#!msg/comp.std.c/d-6Mj5Lko_s/5R6bMWTEbzQJ
 *
 */

#define PRINT_ARG_N(  \
	_1, _2, _3, _4, _5, _6, _7, _8, _9, \
	_10, _11, _12, _13, _14, _15, _16,  \
	_17, _18, _19, _20, _21, _22, _23,  \
	_24, _25, _26, _27, _28, _29, _30,  \
	_31, _32, _33, _34, _35, _36, _37,  \
	_38, _39, _40, _41, _42, _43, _44,  \
	_45, _46, _47, _48, _49, _50, _51,  \
	_52, _53, _54, _55, _56, _57, _58,  \
	_59, _60, _61, _62, _63, _64, N, ...)	\
										\
	print_##N(	\
		_1, _2, _3, _4, _5, _6, _7, _8, \
		_9, _10, _11, _12, _13, _14, _15, _16, \
		_17, _18, _19, _20, _21, _22, _23, _24, \
		_25, _26, _27, _28, _29, _30, _31, _32, \
		_33, _34, _35, _36, _37, _38, _39, _40, \
		_41, _42, _43, _44, _45, _46, _47, _48, \
		_49, _50, _51, _52, _53, _54, _55, _56, \
		_57, _58, _59, _60, _61, _62, _63, _64	\
	)


#define PRINT_RSEQ_N() \
	64, 63, 62, 61, 60, 59, 58, 57, \
	56, 55, 54, 53, 52, 51, 50, 49, \
	48, 47, 46, 45, 44, 43, 42, 41, \
	40, 39, 38, 37, 36, 35, 34, 33, \
	32, 31, 30, 29, 28, 27, 26, 25, \
	24, 23, 22, 21, 20, 19, 18, 17, \
	16, 15, 14, 13, 12, 11, 10, 9,	\
	8, 7, 6, 5, 4, 3, 2, 1, 0

// clang-format on

#endif  // !PRINT_PYTHON_H
