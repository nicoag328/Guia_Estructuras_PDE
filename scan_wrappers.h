// scan_wrappers.h - provide safe wrappers to scan common data types from stdin

#include <stdio.h>
#include "scan_wrappers.c"

// Safe wrapper to scan integer values from stdin
int scan_int();

// Safe wrapper to scan floating-point values from stdin
float scan_float();
