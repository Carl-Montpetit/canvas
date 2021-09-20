// Provides many standard library functions for file input and output
#include <stdio.h>
// Provides various functions for manipulating arrays of characters
#include <string.h>
// Declaration of constants
#define MAX_HEIGHT 40
#define MAX_WIDTH 80
#define ERROR_MSG_01 "⚠️Error, the number of argument is not valid!❌"
#define ERROR_MSG_02 "⚠️Error, some argument(s) are not valid!❌"
#define USAGE                                                                  \
  "\
Usage: ./canvascii [-n HEIGHT,WIDTH] [-s] [-k] [-p CHAR]\n\
          [-h ROW] [-v COL] [-r ROW,COL,HEIGHT,WIDTH]\n\
          [-l ROW1,COL1,ROW2,COL2] [-c ROW,COL,RADIUS]\n\
Draws on an ASCII canvas. The canvas is provided on stdin and\n\
the result is printed on stdout. The dimensions of the canvas\n\
are limited to at most 40 rows and at most 80 columns.\n\
\n\
If no argument is provided, the program prints this help and exit.\n\
\n\
Canvas options:\n\
  -n HEIGHT,WIDTH           Creates a new empty canvas of HEIGHT rows and\n\
                            WIDTH columns. Should be used as first option,\n\
                            otherwise, the behavior is undefined.\n\
                            Ignores stdin.\n\
  -s                        Shows the canvas and exit.\n\
  -k                        Enables colored output. Replaces characters\n\
                            between 0 and 9 by their corresponding ANSI\n\
                            colors:\n\
                              0: black  1: red      2: green  3: yellow\n\
                              4: blue   5: magenta  6: cyan   7: white\n\
\n\
Drawing options:\n\
  -p CHAR                   Sets the pen to CHAR. Allowed pens are\n\
                            0, 1, 2, 3, 4, 5, 6 or 7. Default pen\n\
                            is 7.\n\
  -h ROW                    Draws an horizontal line on row ROW.\n\
  -v COL                    Draws a vertical line on column COL.\n\
  -r ROW,COL,HEIGHT,WIDTH   Draws a rectangle of dimension HEIGHTxWIDTH\n\
                            with top left corner at (ROW,COL).\n\
  -l ROW1,COL1,ROW2,COL2    Draws a discrete segment from (ROW1,COL1) to\n\
                            (ROW2,COL2) with Bresenham's algorithm.\n\
  -c ROW,COL,RADIUS         Draws a circle centered at (ROW,COL) of\n\
                            radius RADIUS with the midpoint algorithm.\n\
"

// Definition of a canvas
struct canvas {
	char pixels[MAX_HEIGHT][MAX_WIDTH]; // A matrix of pixels
	unsigned int width;                 // Its width
	unsigned int height;                // Its height
	char pen;                           // The character we are drawing with
};

// Declaration of a list of code errors
enum error {
	OK = 0,                         // Everything is ok
	ERR_WRONG_PIXEL = 1,            // Wrong pixel value in canvas
	ERR_CANVAS_TOO_HIGH = 2,        // Canvas is too high
	ERR_CANVAS_TOO_WIDE = 3,        // Canvas is too wide
	ERR_CANVAS_NON_RECTANGULAR = 4, // Canvas is non rectangular
	ERR_UNRECOGNIZED_OPTION = 5,    // Unrecognized option
	ERR_MISSING_VALUE = 6,          // Option with missing value
	ERR_WITH_VALUE = 7              // Problem with value
};

// Declaration of a list of pixels
enum pixels {
	EMPTY = '.',   // empty pixel
	BLACK = '0',   // black pixel
	RED = '1',     // red pixel
	GREEN = '2',   // green pixel
	YELLOW = '3',  // yellow pixel
	BLUE = '4',    // blue pixel
	MAGENTA = '5', // magenta pixel
	CYAN = '6',    // cyan pixel
	WHITE = '7',   // white pixel
};

/**
 * Print the number of arguments and the arguments names to the console
 * @param argc
 * @param argv
 */
void printArguments(int argc, char *argv[]) {
	printf("argc = %d\n", argc);
	for (unsigned int i = 0; i < argc; ++i) {
		printf("argv[%d] = %s\n", i, argv[i]);
	}
}

/**
 * Print the usage documentation to the console
 */
void printUsage() { printf("%s", USAGE); }

/**
 * Print error message for invalid argument number to stderr
 */
void printErrorArgNumber() { fprintf(stderr, ERROR_MSG_01); }

/**
 * Print error message for invalid argument(s) to stderr
 */
void printErrorArgInvalid() { fprintf(stderr, ERROR_MSG_02); }

//----------------------------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
	printArguments(argc, argv);

	// If there's no explicit arguments other than the name of the program
	if (argc == 1) {
		printUsage();
		// If there's explicit arguments
	} else if (argc >= 2) {
		for (int i = 0; i < argc; i++) {
			if (strcmp(argv[i], "-n") == 0) {
				printf("this is -n");
			} else if (strcmp(argv[i], "-s") == 0) {
				printf("this is -s");
			} else if (strcmp(argv[i], "-h") == 0) {
				printf("this is -h");
			} else if (strcmp(argv[i], "-v") == 0) {
				printf("this is -v");
			} else if (strcmp(argv[i], "-r") == 0) {
				printf("this is -r");
			} else if (strcmp(argv[i], "-l") == 0) {
				printf("this is -l");
			} else if (strcmp(argv[i], "-c") == 0) {
				printf("this is -c");
			} else if (strcmp(argv[i], "-p") == 0) {
				printf("this is -p");
			} else if (strcmp(argv[i], "-k") == 0) {
				printf("this is -k");
			} else {
				printErrorArgInvalid();
			}
		}
	} else {
		printErrorArgNumber();
	}

	return 0;
}
