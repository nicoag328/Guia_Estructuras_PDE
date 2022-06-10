// csv_file.c - open and read csv files fields

#include <errno.h>
#include <stdio.h>

#define MAXIMUM_CSV_FIELD_WIDTH 512

// CSV file struct
struct csv_file_t {
	FILE* fp;
	int columns = 0;
	int field_pos = 0;
};

// Initialize csv file to read
int csv_open (struct csv_file_t* csv_file, char* filename, int columns_count)
{
	// Initialize column count
	if (columns_count < 0)
	{
		printf("CSV error: The csv file should have at least 1 column\n");
		return -1;
	}
	
	csv_file->columns = columns_count;
	
	// Open file
    csv_file->fp = fopen(filename, "r");

    // Check if file was opened correctly
    if (csv_file->fp = NULL)
    {
        perror("CSV error: ");
        return -1;
    }
	
}

// Get content string from a csv field. Both line and field count start at 0
char* csv_get_field (struct csv_file_t* csv_file, int line, int field)
{
	int buf_pos = 0;
	char buf[MAXIMUM_CSV_FIELD_WIDTH];

	// Set stream cursor to the correct position
	seek_field(fp, line, field);

	// Store content string into buffer until a comma or EOF is read

}

void seek_field(struct csv_file_t* csv_file, int line, int field)
{

	int line_pos = field_pos / columns;

	// Check if positioned in correct line, else go to correct line
	if((field_pos / columns) != line)
	{		
		while ( < line)
		{
			//seek till eol
			//if eof print error, clear error 
			//increase linepos
		}
	}
	
	// Check if positioned in correct field
	if ()


	

}



}

