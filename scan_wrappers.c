// scan_wrappers.c - provide safe wrappers to scan common data types from stdin

#include <stdio.h>

// Safe wrapper to scan integer values from stdin
int scan_int()
{
    int value;
    char buf[20] = {0};
    int error_code;

    do {
        fgets(buf, 20, stdin);
        error_code = sscanf(buf, "%d", &value);

        if (error_code != 1)
            printf("Ingrese un numero entero\n");

    } while (error_code != 1);

    return value;
}

// Safe wrapper to scan floating-point values from stdin
float scan_float()
{
    float value;
    char buf[20] = {0};
    int error_code;

    do {
        fgets(buf, 20, stdin);
        error_code = sscanf(buf, "%f", &value);

        if (error_code != 1)
            printf("Ingrese un numero flotante\n");

    } while (error_code != 1);

    return value;
}
