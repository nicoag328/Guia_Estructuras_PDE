// csv_file.c - open and read csv files

#include <errno.h>
#include <stdio.h>

#define MAXIMUM_CSV_FIELD_WIDTH 512

// CSV file struct
struct csv_file_t {
    FILE* fp;
    int field_pos;
    int line_pos;
};

// Seek the file for the required line position
int seek_line(struct csv_file_t* csv_file, int line);

// Seek the file for the required field position
int seek_field(struct csv_file_t* csv_file, int field);

// Initialize csv file to read
int csv_open (struct csv_file_t* csv_file, char* filename)
{
	csv_file->line_pos = 0;
	csv_file->field_pos = 0;

	// Open file
    csv_file->fp = fopen(filename, "rb+");

    // Check if file was opened correctly
    if (csv_file->fp == NULL)
    {
        perror("CSV error");
        return -1;
    }

	return 0;	
}

// Close csv file
void csv_close(struct csv_file_t* csv_file)
{
	// Close file
	fclose(csv_file->fp);
}

// Get content string from a csv field. Both line and field count start at 0
int csv_get_field (struct csv_file_t* csv_file, char* buf, int length, int line, int field)
{
	
	if (line < 0 || field < 0)
	{
		fprintf(stderr, "CSV error: Cannot access negative fields or lines\n");
		return -1;
	}	

	int buf_pos = 0;
	char c = 0;
	int error = 0;
	
	// Set stream cursor to the correct position
	error = seek_line (csv_file, line);
	if(error != 0)
		return -1;

	error = seek_field(csv_file, field);
	if(error != 0)
		return -1;

	// Store content string into buffer
	while(1)
	{
		// Read next character
		c = fgetc(csv_file->fp);
	
		// Handle EOF
		if (feof(csv_file->fp) || c == '\n' || c == ',')
		{
			rewind(csv_file->fp);
			break;
		}

		// Handle newline
		if (c == '\n')
		{
			csv_file->line_pos++;
			break;
		}
		
		// Handle comma
		if (c == ',')
		{
			csv_file->field_pos++;
			break;
		}
		
		// Handle overflow
		if (buf_pos >= length + 1)
			return -1;

		// Write read character to buffer
		buf[buf_pos] = c;
		buf_pos++;
	}
	
	// Write trailing zero
	buf_pos++;
	buf[buf_pos] = 0;	

	return 0;
}

// Seek the file for the required line position
int seek_line(struct csv_file_t* csv_file, int line)
{

	int c = 0;

	// Check if positioned after correct line
	if(csv_file->line_pos > line)
	{
		rewind(csv_file->fp);
		csv_file->line_pos = 0;
		csv_file->field_pos = 0;
	}

	// Check if positioned before correct line
	if(csv_file->line_pos < line)
	{		
		while (csv_file->line_pos < line)
		{
			// Get next character
			c = fgetc(csv_file->fp);

			// Handle EOF
			if(feof(csv_file->fp))
			{
				fprintf(stderr, "CSV error: Line %d not found\n", line);
				return -1;
			}
			
			// Handle newline
			if(c == '\n')
			{
				csv_file->line_pos++;
				csv_file->field_pos = 0;
			}
		}
	}

/*	// Check if positioned after correct line
	if(csv_file->line_pos > line)
	{
		printf("Going back\n");
		while (csv_file->line_pos > line)
		{
			printf("Rewind one %ld\n", ftell(csv_file->fp));
			int error = 0;
			// Rewind file one character
			error = fseek(csv_file->fp, -1, SEEK_CUR);
			if(error != 0)
			{
				perror("fseek:");
				clearerr(csv_file->fp);
			}

			fseek(csv_file->fp, 0L, SEEK_CUR);	

			// Read next character
			c = fgetc(csv_file->fp);
			printf("Got char %c", c);
			
			// Handle newline
			if(c == '\n')
			{
				printf("Newline found going backwards");
				csv_file->line_pos--;
			}
			
			// Rewind file one character
			fseek(csv_file->fp, -1, SEEK_CUR);
		}

		// Go to line beginning
		while(1)
		{
			// Rewind file one character
			fseek(csv_file->fp, -1, SEEK_CUR);
		
			// Read next character
			c = fgetc(csv_file->fp);

			// Handle newline or start of file
			if(c == '\n' || ftell(csv_file->fp) == SEEK_SET)
			{
				printf("Line beginning found\n");
				csv_file->field_pos = 0;
				break;
			}

			// Rewind file one character
			fseek(csv_file->fp, -1, SEEK_CUR);
		}
	} */

	return 0;
}

// Seek the file for the required field position
int seek_field(struct csv_file_t* csv_file, int field)
{	
	char c = 0;

	// Check if positioned after correct line
	if(csv_file->field_pos > field)
	{
		rewind(csv_file->fp);
		csv_file->line_pos = 0;
		csv_file->field_pos = 0;
	}

	// Check if positioned in correct field
	if (csv_file->field_pos < field)
	{
		while (csv_file->field_pos < field)
		{
			// Read next character
			c = fgetc(csv_file->fp);
		
			// Handle EOF
			if(feof(csv_file->fp))
			{
				fprintf(stderr, "CSV error: Field %d not found\n", field);
				return -1;
			}
			
			// Handle newline
			if(c == '\n')
			{
				fprintf(stderr, "CSV error: Field %d not found\n", field);
				csv_file->line_pos++;
				csv_file->field_pos = 0;
				return -1;
			}
			
			// Handle comma
			if(c == ',')
			{
				csv_file->field_pos++;
			}
		}
	}

/*	if (csv_file->field_pos > field)
	{
		while (csv_file->field_pos > field)
		{
			// Rewind file one character
			fseek(csv_file->fp, -1, SEEK_CUR);

			// Read next character
			c = fgetc(csv_file->fp);
			
*			// Handle newline
			if(c == '\n')
			{
				printf("Newline found going backwards\n");
				return -1;
			}
*			
			// Handle comma
			if(c == ',')
			{
				printf("Field found going backwards\n");
				csv_file->field_pos--;
				break;
			}

			//go back
			fseek(csv_file->fp, -1, SEEK_CUR);
		}

		// Go to field beginning	
		while(1)
		{
			// Rewind file one character
			fseek(csv_file->fp, -1, SEEK_CUR);
		
			// Go to next character
			c = fgetc(csv_file->fp);

			// Handle newline or start of file
			if(c == '\n' || ftell(csv_file->fp) == SEEK_SET)
			{
				printf("Field beginning found\n");
				break;
			}

			// Handle comma
			if(c == ',')
			{
				printf("Field beginning found\n");
				break;
			}
			
			// Rewind file one character
			fseek(csv_file->fp, -1, SEEK_CUR);
		}
	}*/

	return 0;	
}



