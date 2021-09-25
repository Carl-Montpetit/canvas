// Provides many standard library functions for file input and output
#include <stdio.h>
// Provides functions involving memory allocation, process control, conversions
// and others
#include <stdlib.h>
// Provides the boolean type
#include <stdbool.h>
// Provides various functions for manipulating characters
#include <ctype.h>
// Provides various functions for manipulating arrays of characters
#include <string.h>
// Provides regex functions involving regex
#include <regex.h>
// Declaration of constants
#define MAX_HEIGHT 40
#define MAX_WIDTH 80
#define OKAY_MSG "✔︎ Everything is okay!\n"
#define ERR_MSG_01 "✗ Error, wrong pixel value in canvas!\n"
#define ERR_MSG_02 "✗ Error, canvas is too high!\n"
#define ERR_MSG_03 "✗ Error, canvas is too wide!\n"
#define ERR_MSG_04 "✗ Error, canvas is non rectangular!\n"
#define ERR_MSG_05 "✗ Error, Unrecognized option!\n"
#define ERR_MSG_06 "✗ Error, Option with missing value!\n"
#define ERR_MSG_07 "✗ Error, Problem with value!\n"
#define EXECUTABLE argv[0]
#define OPTION_01 argv[1]
#define OPTION_02 argv[2]
#define OPTION_03 argv[3]
#define OPTION_04 argv[4]
#define OPTION_05 argv[5]
#define OPTION_06 argv[6]
#define OPTION_07 argv[7]
#define OPTION_08 argv[8]
#define OPTION_09 argv[9]
#define OPTION_N "-n"
#define OPTION_S "-s"
#define OPTION_H "-h"
#define OPTION_V "-v"
#define OPTION_R "-r"
#define OPTION_L "-l"
#define OPTION_C "-c"
#define OPTION_P "-p"
#define OPTION_K "-k"
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
  ERR_WITH_VALUE = 7,             // Problem with value
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
 * Print the number of arguments and the arguments names to stdout
 * @param argc : number of arguments
 * @param argv : the list of arguments
 */
void printArguments(unsigned int argc, char *argv[]) {
  fprintf(stdout, "Nombre d'arguments = %d\n", argc);
  for (unsigned int position = 0; position < argc; ++position) {
    fprintf(stdout, "argv[%d] = %s\n", position, argv[position]);
  }
}

/**
 * Print an okay message to stdout
 */
void printOkayMsg(void) { fprintf(stdout, "%s", OKAY_MSG); }

/**
 * Print an error message to stderr
 * @param msg
 */
void printErrMsg(char *msg) { fprintf(stderr, "%s", msg); }

/**
 * Print the usage documentation to stdout
 */
void printUsage(void) { fprintf(stdout, "%s", USAGE); }

/**
 * Validate the height of canvas
 * @param canvasX
 * @return valid
 */
bool validateHeight(struct canvas canvasX) {
  bool valid = true;

  if (canvasX.height > MAX_HEIGHT) {
    valid = false;
  }
  return valid;
}

/**
 * Validate the width of canvas
 * @param canvasX
 * @return valid
 */
bool validateWidth(struct canvas canvasX) {
  bool valid = true;

  if (canvasX.width > MAX_WIDTH) {
    valid = false;
  }
  return valid;
}

bool validateDimensionOptionFormat(char option[]) {
  bool valid = true;

  int firstCharHeight = (int)(option[1] - 48);
  printf("%d", firstCharHeight);
  int secondCharHeight;
  int firstCharWidth;
  int SecondCharWidth;

  return valid;
}

/**
 * Create a new empty canvas of dimension h x w;
 * @param h
 * @param w
 * @return newCanvas
 */
struct canvas createEmptyCanvas(int height, int width) {
  struct canvas canvasX;

  // The canvas dimension we explicitly choose
  canvasX.height = height;
  canvasX.width = width;
  // The pen style (look)
  canvasX.pen = '*';

  return canvasX;
}

/**
 * Print an empty canvas to stdout
 * @param h
 * @param w
 */
void printEmptyCanvas(struct canvas canvasX) {
  for (unsigned int i = 0; i < canvasX.height; i++) {
    fprintf(stdout, "\n");
    for (unsigned int j = 0; j < canvasX.width; j++) {
      fprintf(stdout, "%c", EMPTY);
    }
  }
  fprintf(stdout, "\n");
}

/**
 * Validate if the string in the first parameter is equal to the second one
 * @param argv
 * @param option
 * @return valid
 */
bool validateOption(char argv[], char option[]) {
  bool valid = true;

  if (strcmp(argv, option) == 0) {
    valid = false;
  }
  return valid;
}

// bool validateDimensionOptionFormat(char option[]) {}

/**
 * Return de height of a canvas
 * @param option
 * @return height
 */
int getCanvasHeight(char option[]) {
  char firstChar = option[0];
  char secondChar = option[1];
  int height;

  printf("%s", option);

  return height;
}

/**
 * Return de width of a canvas
 * @param option
 * @return width
 */
int getCanvasWidth(char option[]) {
  char firstChar = option[0];
  char secondChar = option[1];
  int width;

  printf("%s", option);

  return width;
}

//------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  // Code is 0 if there's no error, x∈ℕ\{0} otherwise
  int code = 0;

  printArguments(argc, argv);
  // If there's no explicit arguments other than the name of the program
  if (argc == 1) {
    printUsage();
    // If there's explicit arguments
  } else if (argc >= 2) {
    for (int position = 1; position < argc; position++) {
      // Validate if option_01 is equal to "-n"
      if (validateOption(OPTION_01, OPTION_N)) {
        if (!validateDimensionOptionFormat(OPTION_02)) {
          printErrMsg(ERR_MSG_05);
          return ERR_UNRECOGNIZED_OPTION;
        }
        int height = getCanvasHeight(OPTION_02);
        int width = getCanvasWidth(OPTION_02);
        struct canvas canvasX = createEmptyCanvas(height, width);
        if (!validateHeight(canvasX)) {
          printErrMsg(ERR_MSG_02);
          code = ERR_CANVAS_TOO_HIGH;
        } else if (!validateWidth(canvasX)) {
          printErrMsg(ERR_MSG_03);
          code = ERR_CANVAS_TOO_WIDE;
        }
        printEmptyCanvas(canvasX);
      } else {
        printErrMsg(ERR_MSG_05);
        code = ERR_UNRECOGNIZED_OPTION;
      }
    }
  } else {
    printErrMsg(ERR_MSG_07);
    code = ERR_WITH_VALUE;
  }
  printOkayMsg();

  return code;
}
