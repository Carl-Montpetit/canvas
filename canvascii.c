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
// Provides functions involving regex
#include <regex.h>
// Provides...
#include <errno.h>
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
typedef struct canvas {
  char pixels[MAX_HEIGHT][MAX_WIDTH]; // A matrix of pixels
  unsigned int width;                 // Its width
  unsigned int height;                // Its height
  char pen;                           // The character we are drawing with
} canvas;

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

// ∀functions prototypes (declarations) ⟹ see ∀definitions below ⬇︎
void printArguments(unsigned int argc, char *argv[]);
void printLineJump(void);
void printOkayMsg(void);
void printErrMsg(char *msg);
void printUsage(void);
void printEmptyCanvas(canvas canvasX);
void printCanvasFileStdin(void);
bool validateHeight(canvas canvasX);
bool validateWidth(canvas canvasX);
bool validateDimensionOptionFormat(char option[]);
bool validateOption(char option[], char str[]);
int convertCharacterNumberToInt(char numberChar);
int concatTwoIntNumber(int number1, int number2);
unsigned int getCanvasHeightOption(char option[]);
unsigned int getCanvasWidthOption(char option[]);
canvas createEmptyCanvas(int height, int width);

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
 * Print line jump("\n") to the terminal
 */
void printLineJump(void) { printf("\n"); }

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
 * Print an empty canvas to stdout
 * @param h
 * @param w
 */
void printEmptyCanvas(canvas canvasX) {
  for (unsigned int i = 1; i <= canvasX.height; i++) {
    if (i != 1)
      printLineJump();
    for (unsigned int j = 1; j <= canvasX.width; j++) {
      fprintf(stdout, "%c", EMPTY);
    }
  }
  printLineJump();
}

/**
 * Print a canvas (that's in a file) to the terminal and return 0 if there's
 * no reading errors
 * @param filePathOption
 */
void printCanvasFileStdin(void) {
  int code = OK;
  char line[80];

  while (fgets(line, sizeof(line), stdin) != NULL) {
    printf("%s", line);
  }
}

/**
 * Return true(1) if the height of the canvas is valid
 * @param canvasX
 * @return valid
 */
bool validateHeight(canvas canvasX) {
  bool valid = true;

  if (canvasX.height > MAX_HEIGHT) {
    valid = false;
  }
  return valid;
}

/**
 * Return true(1) if the width of the canvas is valid
 * @param canvasX
 * @return valid
 */
bool validateWidth(canvas canvasX) {
  bool valid = true;

  if (canvasX.width > MAX_WIDTH) {
    valid = false;
  }
  return valid;
}

/**
 * Return true(1) if option of the dimension is in valid format
 * @param option
 * @return valid
 */
bool validateDimensionOptionFormat(char option[]) {
  bool valid = false;
  char coma = ',';
  //  printf("option: %s\noption[0]: %c\noption[1]: %c\noption[2]:
  //  %c\noption[3]:"
  //         " %c\noption[4]: %c\n",
  //         option, option[0], option[1], option[2], option[3], option[4]);
  // Verify that the format is one of the 4 below⬇︎
  if ((option[2] == coma && strlen(option) == 5) ||
      (option[2] == coma && strlen(option) == 4) ||
      (option[1] == coma && strlen(option) == 4) ||
      (option[1] == coma && strlen(option) == 3)) {
    valid = true;
    //    fprintf(stdout, "✔︎ The format of dimension is valid!\n");
  } else {
    //    fprintf(stderr, "✗︎ Error, the format of dimension is not
    //    valid!\n");
  }
  return valid;
}

/**
 * Return true(1) if the string in the first parameter is equal to the second
 * one
 * @param argv
 * @param option
 * @return valid
 */
bool validateOption(char option[], char str[]) {
  //  printf("option: %s\nstr: %s\n", option, str);
  bool valid = true;

  if (strcmp(option, str) != 0) {
    valid = false;
  }
  return valid;
}

/**
 * Convert a number character to the integer version of it
 * @param numberChar
 * @return numberInt
 */
int convertCharacterNumberToInt(char numberChar) {
  int numberInt = (int)(numberChar - 48);
  return numberInt;
}

/**
 * Concatenate 2 integers to form a number formed of 2 numbers
 * Ex: 1 & 2 ⟹ 12
 * @param number1
 * @param number2
 * @return finalNumber
 */
int concatTwoIntNumber(int number1, int number2) {
  int finalNumber = number1 * 10 + number2;
  return finalNumber;
}

/**
 * Return the height of a canvas
 * @param option
 * @return height
 */
unsigned int getCanvasHeightOption(char option[]) {
  unsigned int height;
  unsigned int firstNumberHeight;
  unsigned int secondNumberHeight;
  char coma = ',';

  if (strlen(option) == 5 && option[2] == coma) {
    firstNumberHeight = convertCharacterNumberToInt(option[0]);
    secondNumberHeight = convertCharacterNumberToInt(option[1]);
    height = concatTwoIntNumber(firstNumberHeight, secondNumberHeight);
  } else if (strlen(option) == 4 && option[1] == coma) {
    firstNumberHeight = convertCharacterNumberToInt(option[0]);
    height = firstNumberHeight;
  } else if (strlen(option) == 4 && option[2] == coma) {
    firstNumberHeight = convertCharacterNumberToInt(option[0]);
    secondNumberHeight = convertCharacterNumberToInt(option[1]);
    height = concatTwoIntNumber(firstNumberHeight, secondNumberHeight);
  } else if (strlen(option) == 3 && option[1] == coma) {
    firstNumberHeight = convertCharacterNumberToInt(option[0]);
    height = firstNumberHeight;
  }

  return height;
}

/**
 * Return the width of a canvas
 * @param option
 * @return width
 */
unsigned int getCanvasWidthOption(char option[]) {
  unsigned int width;
  unsigned int firstNumberWidth;
  unsigned int secondNumberWidth;
  char coma = ',';

  if (strlen(option) == 5 && option[2] == coma) {
    firstNumberWidth = convertCharacterNumberToInt(option[3]);
    secondNumberWidth = convertCharacterNumberToInt(option[4]);
    width = concatTwoIntNumber(firstNumberWidth, secondNumberWidth);
  } else if (strlen(option) == 4 && option[1] == coma) {
    firstNumberWidth = convertCharacterNumberToInt(option[3]);
    secondNumberWidth = convertCharacterNumberToInt(option[4]);
    width = concatTwoIntNumber(firstNumberWidth, secondNumberWidth);
  } else if (strlen(option) == 4 && option[2] == coma) {
    firstNumberWidth = convertCharacterNumberToInt(option[3]);
    width = firstNumberWidth;
  } else if (strlen(option) == 3 && option[1] == coma) {
    firstNumberWidth = convertCharacterNumberToInt(option[2]);
    width = firstNumberWidth;
  }

  return width;
}

// bool validateDimensionOptionFormat(char option[]) {}

/**
 * Create a new empty canvas of dimension h x w;
 * @param h
 * @param w
 * @return newCanvas
 */
canvas createEmptyCanvas(int height, int width) {
  canvas canvasX;

  // The canvas dimensions explicitly choose
  canvasX.height = height;
  canvasX.width = width;
  // The pen style (look)
  canvasX.pen = '*';

  return canvasX;
}

//------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  // Code is 0 if there's no error, code take a value x∈ℕ\{0} otherwise
  unsigned int code = OK;

  //  printArguments(argc, argv);
  // If there's no explicit arguments other than the name of the program
  if (argc == 1) {
    printUsage();
    // If there's explicit options ⟹ argv[x > 0] where x is an integer
  } else if (argc > 1) {
    for (int position = 1; position < argc; position++) {
      // If the first option is "-n"
      if (validateOption(OPTION_01, OPTION_N) && position == 1) {
        // Validate if the format of dimension is the form "xx,xx" where x is a
        // positive integer
        if (!validateDimensionOptionFormat(OPTION_02)) {
          printErrMsg(ERR_MSG_05);
          code = ERR_UNRECOGNIZED_OPTION;

          return code;
        }
        // Getting the dimensions (height & width) of the argument
        int height = getCanvasHeightOption(OPTION_02);
        int width = getCanvasWidthOption(OPTION_02);
        //        printf("height: %d\nwidth: %d\n", height, width);
        // Creating a canvas with those dimensions
        canvas canvasX = createEmptyCanvas(height, width);
        // Vaditate the dimensions ⟹ positive(unsigned int) & MAX: 40=h,80=w
        if (!validateHeight(canvasX)) {
          printErrMsg(ERR_MSG_02);
          code = ERR_CANVAS_TOO_HIGH;

          return code;
        } else if (!validateWidth(canvasX)) {
          printErrMsg(ERR_MSG_03);
          code = ERR_CANVAS_TOO_WIDE;

          return code;
        }
        // Showing the canvas to the terminal
        printEmptyCanvas(canvasX);
        // If argument "-n" is not the first option
      } else if (validateOption(argv[position], OPTION_N) && position > 1) {
        printErrMsg(ERR_MSG_05);
        code = ERR_UNRECOGNIZED_OPTION;
        printf("✗ Error, '-n' is not the first option!\n");

        return code;
      }
      // If there's other arguments after "-n", they are ignored
      if (validateOption(OPTION_01, OPTION_N) && position > 1) {
        printf("%s\n", OPTION_01);
        code = OK;
        printf("✔︎ Arguments after './canvascii -n xx,xx' ignored!\n");
        printOkayMsg();

        return code;
      }

      // If the first option is "-s" ⟹ ignore other options after it
      if (validateOption(OPTION_01, OPTION_S) && position == 1) {
        printf("✔︎ There's a stdin empty canvas file to print!\n");
        printCanvasFileStdin();

        return code;
      } else {
        printf("✘\n︎");
        printf("OPTION_01: %s\nposition: %d\nargc: %d\n", OPTION_01, position,
               argc);
        printErrMsg(ERR_MSG_05);
        code = ERR_UNRECOGNIZED_OPTION;

        return code;
      }
    }
  }
  printOkayMsg();

  return code;
}
