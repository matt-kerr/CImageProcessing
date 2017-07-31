// Matthew Kerr
// November 13, 2013

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pgmUtility.h"

void usage( void )
{
	printf("Usage:\n");
	printf("-e edgeWidth < oldImageFile > newImageFile\n");
	printf("-c circleCenterRow circleCenterCol radius < oldImageFile > newImageFile\n");
}


int main(int argc, const char * argv[])
{
	// parsing command line arguments
	char temp[100];
	char *input_filename;
	char *output_filename;
	int circle_center_row = 0;
	int circle_center_col = 0;
	int circle_radius = 0;
	int edge_width = 0;
	int rows = 0;
	int cols = 0;
	int i, j;
	if (argc == 9)
	{
		if (strcmp(argv[1], "-c") == 0 && strcmp(argv[2], "-e") == 0)
		{
			if (sscanf(argv[3], "%d", &circle_center_row) == 1 && sscanf(argv[4], "%d", &circle_center_col) == 1 && sscanf(argv[5], "%d", &circle_radius) == 1 && sscanf(argv[6], "%d", &edge_width) == 1)
			{
				input_filename = (char *)malloc((strlen(argv[7]) + 1) * sizeof(char));
				strcpy(input_filename, argv[7]);
				output_filename = (char *)malloc((strlen(argv[8]) + 1) * sizeof(char));
				strcpy(output_filename, argv[8]);
			}
			else
			{
				usage();
				return 0;
			}
		}
		else
		{
			usage();
			return;
		}
	}
	else if (argc == 8)
	{
		if (strcmp(argv[1], "-ce") == 0)
		{
			if (sscanf(argv[2], "%d", &circle_center_row) == 1 && sscanf(argv[3], "%d", &circle_center_col) == 1 && sscanf(argv[4], "%d", &circle_radius) == 1 && sscanf(argv[5], "%d", &edge_width) == 1)
			{
				input_filename = (char *)malloc((strlen(argv[6]) + 1) * sizeof(char));
				strcpy(input_filename, argv[6]);
				output_filename = (char *)malloc((strlen(argv[7]) + 1) * sizeof(char));
				strcpy(output_filename, argv[7]);
			}
			else
			{
				usage();
				return 0;
			}
		}
		else
		{
			usage();
			return;
		}
	}
	else if (argc == 7)
	{
		if (strcmp(argv[1], "-c") == 0)
		{
			if (sscanf(argv[2], "%d", &circle_center_row) == 1 && sscanf(argv[3], "%d", &circle_center_col) == 1 && sscanf(argv[4], "%d", &circle_radius) == 1)
			{
				input_filename = (char *)malloc((strlen(argv[5]) + 1) * sizeof(char));
				strcpy(input_filename, argv[5]);
				output_filename = (char *)malloc((strlen(argv[6]) + 1) * sizeof(char));
				strcpy(output_filename, argv[6]);
			}
			else
			{
				usage();
				return 0;
			}
		}
		else
		{
			usage();
			return 0;
		}
	}
	else if (argc == 5)
	{
		if (strcmp(argv[1], "-e") == 0)
		{
			if (sscanf(argv[2], "%d", &edge_width) == 1)
			{
				input_filename = (char *)malloc((strlen(argv[3]) + 1) * sizeof(char));
				strcpy(input_filename, argv[3]);
				output_filename = (char *)malloc((strlen(argv[4]) + 1) * sizeof(char));
				strcpy(output_filename, argv[4]);
			}
			else
			{
				usage();
				return 0;
			}
		}
		else
		{
			usage();
			return 0;
		}
	}
	else
	{
		usage();
		return 0;
	}

	// read in pixels
	FILE *in;
	if ((in = fopen(input_filename, "r")) == NULL)
	{
		printf("Error opening input file (%s).  Check that the file exists and try again.\n", input_filename);
		return 0;
	}
    char **header = (char **)malloc(rowsInHeader * sizeof(char *));
    int **pixels = pgmRead(header, &rows, &cols, in);
    if (pixels == NULL)
    {
     printf("Error reading input file\n");
     return 0;

    }
	// draw pixels
    pgmDrawEdge(pixels, rows, cols, edge_width, header);
    pgmDrawCircle(pixels, rows, cols, circle_center_row, circle_center_col, circle_radius, header);

	// write result
	FILE *out;
	if ((out = fopen(output_filename, "w")) == NULL)
	{
		printf("Error opening output file (%s). Check that you have permission to write that file and try again.\n", output_filename);
		return 0;
	}
    if (pgmWrite((const char **)header, (const int **)pixels, rows, cols, out) == -1)
    {
            printf("Error writing output file.\n");
            return 0;
    }
    if (fclose(in) != 0 || fclose(out) != 0)
    {
    	printf("Error closing files.\n");
    }

    return 0;
}

