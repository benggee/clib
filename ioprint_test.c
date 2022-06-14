#include <stdio.h>
#include "ioprint.h"
#include <stdbool.h>
#include <stdlib.h>

int main(void) {
	PRINTLNF("a:%d, b:%d, c:%c", 1, 2, 'c');

	char c = 'a';
	PRINT_CHAR( c);

	wchar_t c2 = 'b';
	PRINT_WCHAR(c2);

	int i = 1;
	PRINT_INT(i);

	long i2 = 2;
	PRINT_LONG(i2);

	long long i3 = 3;
	PRINT_LLONG(i3);

	int hex = 0x55;
	PRINT_HEX(hex);

	bool bl = true;
	PRINT_BOOL(bl);

	double dd = 0.42;
	PRINT_DOUBLE(dd);

	char s[] = "Hello World!";
	PRINT_STRING(s);

	int arr1[] = {1, 2, 3, 4, 5};
	PRINT_INT_ARRAY(arr1, 5);

	char arr2[] = {'a', 'b', 'c', 'd', 'e'};
	PRINT_CHAR_ARRAY(arr2, 5);
	
	double arr3[] = {0.1, 1.2, 2.3, 3.4, 4.5, 5.6};
	PRINT_DOUBLE_ARRAY(arr3, 6);

	return 0;
}
