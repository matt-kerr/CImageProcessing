#ifndef cscd240pgm_pgmUtility_h
#define cscd240pgm_pgmUtility_h

#include <math.h>

#define rowsInHeader 4      // number of rows in image header
#define maxSizeHeadRow 200  // maximal number characters in one row in the header

#endif

int ** pgmRead( char **header, int *numRows, int *numCols );
int pgmDrawCircle( int **pixels, int numRows, int numCols, int centerRow,
                  int centerCol, int radius, char **header );
int pgmDrawEdge( int **pixels, int numRows, int numCols, int edgeWidth, char **header );
int pgmWrite( const char **header, const int **pixels, int numRows, int numCols );
double distance( int p1[], int p2[] );


