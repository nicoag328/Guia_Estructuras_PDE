// csv_file.h - 

#include <stdio.h>
#include "csv_file.c"

// CSV file struct
struct csv_file_t {
    FILE* fp;
    int field_pos;
    int line_pos;
};

// Initialize csv file to read
int csv_open(struct csv_file_t* csv_file, char* filename);

// Close csv file
void csv_close(struct csv_file_t* csv_file);

// Get content string from a csv field. Both line and field count start at 0
int csv_get_field(struct csv_file_t* csv_file, char* buf, int length, int line, int field);

// Seek the file for the required line position
int seek_line(struct csv_file_t* csv_file, int line);

// Seek the file for the required field position
int seek_field(struct csv_file_t* csv_file, int field);


