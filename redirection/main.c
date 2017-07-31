// Matthew Kerr
// November 13, 2013

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pgmUtility.h"

void usage( void )
{
	fprintf(stderr, "Usage:\n");
	fprintf(stderr, "-e edgeWidth < oldImageFile > newImageFile\n");
	fprintf(stderr, "-c circleCenterRow circleCenterCol radius < oldImageFile > newImageFile\n");
}


int main(int argc, const char * argv[])
{
	// parsing command line arguments
	int circle_center_row = 0;
	int circle_center_col = 0;
	int circle_radius = 0;
	int edge_width = 0;
	int rows = 0;
	int cols = 0;
	int i, j;

	if (argc == 7)
	{
		if (strcmp(argv[1], "-c") == 0 && strcmp(argv[2], "-e") == 0)
		{
			if (sscanf(argv[3], "%d", &circle_center_row) == 0 || sscanf(argv[4], "%d", &circle_center_col) == 0 || sscanf(argv[5], "%d", &circle_radius) == 0 || sscanf(argv[6], "%d", &edge_width) == 0)
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
	else if (argc == 6)
	{
		if (strcmp(argv[1], "-ce") == 0)
		{
			if (sscanf(argv[2], "%d", &circle_center_row) == 0 || sscanf(argv[3], "%d", &circle_center_col) == 0 || sscanf(argv[4], "%d", &circle_radius) == 0 || sscanf(argv[5], "%d", &edge_width) == 0)
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
	else if (argc == 5)
	{
		if (strcmp(argv[1], "-c") == 0)
		{
			if (sscanf(argv[2], "%d", &circle_center_row) == 0 || sscanf(argv[3], "%d", &circle_center_col) == 0 || sscanf(argv[4], "%d", &circle_radius) == 0)
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
	else if (argc == 3)
	{
		if (strcmp(argv[1], "-e") == 0)
		{
			if (sscanf(argv[2], "%d", &edge_width) == 0)
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
    	char **header = (char **)malloc(rowsInHeader * sizeof(char *));
    	int **pixels = pgmRead(header, &rows, &cols);

	// draw pixels
    	pgmDrawEdge(pixels, rows, cols, edge_width, header);
    	pgmDrawCircle(pixels, rows, cols, circle_center_row, circle_center_col, circle_radius, header);

	// write result
    	pgmWrite((const char **)header, (const int **)pixels, rows, cols);

    return 0;
}

