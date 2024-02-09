#include <errno.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>


#define FORMAT_SEP(i, N, SEP)        (((i) == (N)-1) ? "" : SEP)
#define SET_DATA(x)                  va_arg(argptr, x), FORMAT_SEP(i, n, sep)
#define write_stdout(_format, value) printf(_format "%s", SET_DATA(value))


typedef enum types { CHAR, UI8, I8, UI16, I16, UI32, I32, UI64, I64, DOUBLE, STRING, VOID } _Type;


static void append_type(_Type type);

static struct {
    size_t head;
    int hidden_types_stack[64];
    void (*append)(_Type type);
} _TypeStack = {.head = 0, .append = &append_type};

static void append_type(_Type type)
{
    size_t idx = _TypeStack.head++;
    _TypeStack.hidden_types_stack[idx] = type;
}

void type_add_char(void)
{
    _TypeStack.append(CHAR);
}

void type_add_ui8(void)
{
    _TypeStack.append(UI8);
}

void type_add_i8(void)
{
    _TypeStack.append(I8);
}

void type_add_ui16(void)
{
    _TypeStack.append(UI16);
}

void type_add_i16(void)
{
    _TypeStack.append(I16);
}

void type_add_ui32(void)
{
    _TypeStack.append(UI32);
}

void type_add_i32(void)
{
    _TypeStack.append(I32);
}

void type_add_ui64(void)
{
    _TypeStack.append(UI64);
}

void type_add_i64(void)
{
    _TypeStack.append(I64);
}

void type_add_double(void)
{
    _TypeStack.append(DOUBLE);
}

void type_add_str(void)
{
    _TypeStack.append(STRING);
}

void type_add_void(void)
{
    _TypeStack.append(VOID);
}


void _print(const char* restrict sep, const char* restrict end, const size_t n, ...)
{
    va_list argptr;
    char msg[1024] = {0};
    va_start(argptr, n);

    for (size_t i = 0; i < n; ++i) {
        switch (_TypeStack.hidden_types_stack[i]) {
            case UI8:
                write_stdout("%" PRIu8, int);
                break;
            case I8:
                write_stdout("%" PRIi8, int);
                break;
            case UI16:
                write_stdout("%" PRIu16, int);
                break;
            case I16:
                write_stdout("%" PRIi16, int);
                break;
            case UI32:
                write_stdout("%" PRIu32, uint32_t);
                break;
            case I32:
                write_stdout("%" PRIi32, int32_t);
                break;
            case UI64:
                write_stdout("%lu", unsigned long);
                break;
            case I64:
                write_stdout("%li", long);
                break;
            case DOUBLE:
                write_stdout("%f", double);
                break;
            case CHAR:
                write_stdout("%c", int);
                break;
            case STRING:
                write_stdout("%s", char*);
                break;
            case VOID:
                write_stdout("0x%p", void*);
                break;
            default:
                snprintf(msg, 1024, "Internal '_print' error line: %d in %s\n", __LINE__, __FILE__);
                perror(msg);
                abort();
        }
    }

    printf("%s", end);
    va_end(argptr);
    _TypeStack.head = 0;
}
