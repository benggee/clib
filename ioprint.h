#ifndef CLIB_IOPRINT_H_
#define CLIB_IOPRINT_H_

#include <stdio.h>
#include <limits.h>

#define PRINT_METADATA
#ifdef PRINT_METADATA	
#define PRINTLNF(format, ...) printf("("__FILE__": %d) %s: "format"\n", __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
#define PRINTLNF(format, ...) printf(format"\n", ##__VA_ARGS__)
#endif

// printlnf char
#define PRINT_CHAR(char_value) PRINTLNF(#char_value": %c", char_value)

// printlnf wchar
#define PRINT_WCHAR(char_value) PRINTLNF(#char_value": %lc", char_value)

// printlnf int 
#define PRINT_INT(int_value) PRINTLNF(#int_value": %d", int_value)

// printlnf long
#define PRINT_LONG(long_value) PRINTLNF(#long_value": %ld", long_value)

// printlnf llong
#define PRINT_LLONG(llong_value) PRINTLNF(#llong_value": %lld", llong_value)

// printlnf binary
//#define PRINT_BINARY(binary_value) PRINTLNF(#binary_value": %#")

// printlnf hex
#define PRINT_HEX(hex_value) PRINTLNF(#hex_value": %#x", hex_value)

// printlnf bool
#define PRINT_BOOL(bool_value) PRINTLNF(#bool_value": %s", bool_value ? "true": "false")

// printlnf double
#define PRINT_DOUBLE(double_value) PRINTLNF(#double_value": %g", double_value)

// printlnf string 
#define PRINT_STRING(string_value) PRINTLNF(#string_value": %s", string_value)

// printfnf array
#define PRINT_ARRAY(format, array, length) \
{ int array_index; \
for (array_index = 0; array_index < length; ++array_index) { \
	printf(format, array[array_index]); \
}; \
printf("\n"); }

#define PRINT_INT_ARRAY_LN(array, length) \
{ int i; \
for (i = 0; i < length; ++i) { \
	PRINTLNF(#array"[%d]: %d", i, array[i]); \
}}

#define PRINT_INT_ARRAY(array, length) PRINT_ARRAY("%d, ", array, length)
#define PRINT_CHAR_ARRAY(array, length) PRINT_ARRAY("%c, ", array, length)
#define PRINT_DOUBLE_ARRAY(array, length) PRINT_ARRAY("%g, ", array, length)

#endif
