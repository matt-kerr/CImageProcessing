// Matthew Kerr
// November 13, 2013

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "pgmUtility.h"

int ** pgmRead( char **header, int *numRows, int *numCols )
{

	int i, j;
	// initialize 2d pointer array

	char curr[maxSizeHeadRow];
    	char last = '\0';
	for (i = 0; i < rowsInHeader; i++)
    	{
    		fgets(curr, maxSizeHeadRow, stdin);
    		if ((*(header + i) = (char *)malloc(strlen(curr) * sizeof(char))) == 0)
            {
                printf("Error reading header information\n");
                return NULL;
            }
    		strcpy(header[i], curr);
    	}

    	sscanf(*(header + 2), "%d %d", numCols, numRows);
    	int **pixels;
    	if ((pixels = (int **)malloc(*numRows * sizeof(int *))) == NULL)
        {
            printf("Error reading header information\n");
            return NULL;
        }
	for (i = 0; i < *numRows; i++)
	{
        if ((*(pixels + i) = (int *)malloc(*numCols * sizeof(int))) == NULL)
        {
            printf("Error reading header information\n");
            return NULL;
        }
	}
	for (i = 0; i < *numRows; i++)
	{
		for (j = 0; j < *numCols; j++)
		{
			if ((scanf("%d ", (*(pixels + i) + j))) == 0)
            {
                printf("Error reading header information\n");
                return NULL;
            }
		}
	}
	return pixels;

}

int pgmDrawCircle( int **pixels, int numRows, int numCols, int centerRow,
                  int centerCol, int radius, char **header )
{
	if (radius == 0)
	{
		return 0;
	}
	int i, j;
	// p1 is center row/col
	// p2 is current pixel
	int p1[2] = {centerRow, centerCol};
	int p2[2] = {0, 0};
	int new_highest = 0;

	for (i = 0; i < numRows; i++)
	{
		for (j = 0; j < numCols; j++)
		{
			p2[0] = i;
			p2[1] = j;
			if (distance(p1, p2) <= (double) radius)
			{
				*(*(pixels + i) + j) = 0;
			}
		}
	}

	// check if max intensity changed
	for (i = 0; i < numRows; i++)
	{
		for (j = 0; j < numCols; j++)
		{
			if (*(*(pixels + i) + j) > new_highest)
			{
				new_highest = *(*(pixels + i) + j);
			}
		}
	}

	if (new_highest < atoi(*(header + 3)))
	{
		sprintf((*(header + 3)), "%d", new_highest);
		return 1;
	}
	return 0;
}

int pgmDrawEdge( int **pixels, int numRows, int numCols, int edgeWidth, char **header )
{
	if (edgeWidth == 0)
	{
		return 0;
	}
	int i, j;
	int new_highest = 0;

    for (i = 0; i < numRows; i++)
	{
		for (j = 0; j < numCols; j++)
		{
            if (i < edgeWidth || j < edgeWidth || i >= numRows - edgeWidth || j >= numCols - edgeWidth)
            {
                    *(*(pixels + i) + j) = 0;
            }
			if (*(*(pixels + i) + j) > new_highest)
			{
				new_highest = *(*(pixels + i) + j);
			}
		}
	}

	if (new_highest < atoi(*(header + 3)))
	{
		sprintf((*(header + 3)), "%d", new_highest);
		return 1;
	}
	return 0;
}

int pgmWrite( const char **header, const int **pixels, int numRows, int numCols )
{
	int i, j, count = 0;
	for (i = 0; i < rowsInHeader; i++)
    {
        if (printf("%s", *(header + i)) == 0)
        {
            return -1;
        }
    }
    printf("\n");
	for (i = 0; i < numRows; i++)
	{
		for (j = 0; j < numCols; j++)
		{
			if (count == 12)
			{
				printf("\n");
				count = 0;
			}
			if (printf("%d ", *(*(pixels + i) + j)) == 0)
            {
                    return -1;
            }
			count++;
		}
	}
	return 0;
}

double distance( int p1[], int p2[] )
{
	return sqrt((pow((p2[0] - p1[0]), 2) + pow((p2[1] - p1[1]), 2)));
}
