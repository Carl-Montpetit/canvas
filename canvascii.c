/**
 * @file canvascii.c
 * @author Carl Montpetit (MONC08069000)
 * @brief A program that provides the functionality to draw on ASCII canvas
 * initially created on standard input or output
 * @version 2.0
 * @date 2021-10-06
 *
 * @copyright Copyright (c) 2021
 *
 */
//------------------------------------------------------------------------------
// Inclusions of libraries
//------------------------------------------------------------------------------
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
// Provides macros for reporting and retrieving error conditions using the
// symbol errno
#include <errno.h>
// Provides functions involving mathematics equations
#define MAX_HEIGHT 40
#define MAX_WIDTH 80
#define ERR_MSG_01 "Error: wrong pixel value #\n"
#define ERR_MSG_02 "Error: canvas is too high (max height: 40)\n"
#define ERR_MSG_03 "Error: canvas is too wide (max width: 80)\n"
#define ERR_MSG_04 "Error: canvas should be rectangular\n"
#define ERR_MSG_05 "Error: unrecognized option %s\n"
#define ERR_MSG_06 "Error: missing value with option %s\n"
#define ERR_MSG_07 "Error: incorrect value with option %s\n"
#define EXECUTABLE argumentsList[0]
#define OPTION_01 argumentsList[1]
#define OPTION_02 argumentsList[2]
#define OPTION_03 argumentsList[3]
#define OPTION_04 argumentsList[4]
#define OPTION_05 argumentsList[5]
#define OPTION_06 argumentsList[6]
#define OPTION_07 argumentsList[7]
#define OPTION_08 argumentsList[8]
#define OPTION_09 argumentsList[9]
#define OPTION_N "-n"
#define OPTION_S "-s"
#define OPTION_H "-h"
#define OPTION_V "-v"
#define OPTION_R "-r"
#define OPTION_L "-l"
#define OPTION_C "-c"
#define OPTION_P "-p"
#define OPTION_K "-k"
#define EXECUTABLE_NAME "./canvascii"
#define USAGE                                                                  \
  "\
Usage: %s [-n HEIGHT,WIDTH] [-s] [-k] [-p CHAR]\n\
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
//------------------------------------------------------------------------------
// Declarations of ∀types with docstrings
//------------------------------------------------------------------------------
typedef struct canvas {
  char pixels[MAX_HEIGHT][MAX_WIDTH]; // A matrix of pixels
  unsigned int width;                 // Its width
  unsigned int height;                // Its height
  char pen;                           // The character we are drawing with
} canvas;

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
//------------------------------------------------------------------------------
// ∀functions prototypes (declarations)
//------------------------------------------------------------------------------
/**
 * @brief Print the number of arguments and the arguments names to the terminal
 *
 * @param argc : number of arguments
 * @param argv : the list of arguments
 */
void printArguments(const unsigned int argc, char *argv[]);

/**
 * @brief Print line jump("\n") to the terminal
 */
void printLineJump(void);

/**
 * @brief Print an error message to the terminal
 *
 * @param msg
 * @param option
 */
void printErrMsg(char msg[], char option[]);

/**
 * @brief Print the usage documentation to the terminal
 */
void printUsage(char argument[]);

/**
 * @brief Print an empty canvas to the terminal (for option -n)
 *
 * @param canvasX
 */
void printEmptyCanvas(canvas canvasX);

/**
 * @brief Print a canvas from a file to the terminal (for option -s)
 */
void printCanvasFileStdin(void);

/**
 * @brief Print a canvas with horizontal line to the terminal (for option -h)
 *
 * @param canvasX
 * @param horizontalLine
 * @param pen
 */
void printCanvasHorizontalLine(canvas canvasX,
                               const unsigned int horizontalLinePosition,
                               const char pen);

/**
 * @brief Print an canvas with vertical line to the terminal (for option -v)
 *
 * @param canvasX
 * @param verticalLinePosition
 * @param pen
 */
void printCanvasVerticalLine(canvas canvasX,
                             const unsigned int verticalLinePosition,
                             const char pen);

/**
 * @brief Print a canvas with horizontal line to the terminal (for option -h)
 * that was initially in a file
 *
 * @param horizontalLinePosition
 * @param height
 * @param width
 * @param pen
 */
void printCanvasHorizontalLineFile(const unsigned int horizontalLinePosition,
                                   const unsigned height, const unsigned width,
                                   char pen);

/**
 * @brief Print a canvas with vertical line to the terminal (for option -h)
 * that was initially in a file
 *
 * @param verticalLinePosition
 * @param height
 * @param width
 * @param pen
 */
void printCanvasVerticalLineFile(const unsigned int verticalLinePosition,
                                 const unsigned height, const unsigned width,
                                 char pen);

/**
 * @brief Validate the height of a canvas
 *
 * @param canvasX
 * @return true : if 0 <= height <= 40
 * @return false : if 0 > height > 40
 */
bool validateHeight(canvas canvasX);

/**
 * @brief Validate the width of a canvas
 *
 * @param canvasX
 * @return true : if 0 <= width <= 80
 * @return false : if 0 > width > 80
 */
bool validateWidth(canvas canvasX);

/**
 * @brief Validate the format of the the dimension option of the option -n
 *
 * @param option
 * @return true : if the format is valid
 * @return false : if format is invalid
 */
bool validateDimensionOptionFormatForN(char option[]);

/**
 * @brief Validate the characters in the canvas
 *
 * @param file
 * @param index
 * @return true : if all characters are valid
 * @return false : if ar least one character is invalid
 */
bool validateCharactersInCanvas(char file[], unsigned int index);

/**
 * @brief Validate if the width of all lines are the same
 * false otherwise
 *
 * @return true : if all line has the same width
 * @return false : if at least one line is not the same width
 */
bool validateCanvasFileWidthAllSame(void);

/**
 * @brief Validate the canvas file width
 *
 * @return true : if 0 <= width <= 80
 * @return false : if 0 > width > 80
 */
bool validateWidthCanvasFile(void);

/**
 * @brief Validate if 2 strings are equal
 *
 * @param argv
 * @param option
 * @return true : if the 2 strings are equal
 * @return false : if the 2 strings are not equal
 */
bool validateOption(char option[], char str[]);

/**
 * @brief Validate the height of the file canvas
 *
 * @return true : if 0 <= height <= 40
 * @return false : if 0 > height > 40
 */
bool validateCanvasFileHeight(void);

/**
 * @brief Validate the width of the file canvas
 *
 * @return true : if 0 <= width <= 80
 * @return false : if 0 > width > 80
 */
bool validateCanvasFileWidth(void);

/**
 * @brief Convert a number character to the integer version of it
 *
 * @param numberChar
 * @return int
 */
int convertCharacterNumberToInt(const char numberChar);

/**
 * @brief Convert a string of numbers to the integer version of it
 *
 * @param numberChar
 * @return int
 */
int convertStringNumberToInt(char numberString[]);

/**
 * @brief Concatenate 2 integers to form a number formed of 2 numbers
 * Ex: 1 & 2 ⟹ 12
 * @param number1
 * @param number2
 * @return int
 */
int concatTwoIntNumber(const int number1, const int number2);

/**
 * @brief Calculate the nth power of an integer x^n
 *
 * @param number
 * @param power
 * @return int
 */
int calculatePowerForTen(int power);

/**
 * @brief Return a single character(letter) for a specific option
 * feature for the switch/case statement
 *
 * @param option
 * @return char
 */
char getOptionLetter(char option[]);

/**
 * @brief Return the height of a canvas
 *
 * @param option
 * @return unsigned int
 */
unsigned int getCanvasHeightOption(char option[]);

/**
 * @brief Return the width of a canvas
 *
 * @param option
 * @return unsigned int
 */
unsigned int getCanvasWidthOption(char option[]);

/**
 * @brief return the height of the file canvas
 *
 * @return unsigned int
 */
unsigned int getCanvasFileHeight(void);

/**
 * @brief get the ganvas file width object
 *
 * @return unsigned int
 */
unsigned int getCanvasFileWidth(void);

/**
 * @brief return the rectangle row option (for option -r)
 *
 * @param option
 * @return unsigned int
 */
// unsigned int getRectangleRowOption(char option[]);

/**
 * @brief return the rectangle column option (for option -r)
 *
 * @param option
 * @return unsigned int
 */

/**
 * @brief Return the rectangle column option (for option -r)
 *
 * @param option
 * @return unsigned int
 */
// unsigned int getRectangleColOption(char option[]);

/**
 * @brief Return the rectangle height option (for option -r)
 *
 * @param option
 * @return unsigned int
 */
// unsigned int getRectangleHeightOption(char option[]);

// unsigned int getRectanglewidthOption(char option[]);

/**
 * @brief Create a new empty canvas of dimension h x w
 * @param height
 * @param width
 * @return canvas
 */
canvas createEmptyCanvas(const unsigned int height, const unsigned int width);
//------------------------------------------------------------------------------
// ∀funtions definitions
//------------------------------------------------------------------------------
void printArguments(const unsigned int argc, char *argv[]) {
  fprintf(stdout, "# of arguments\t⇒\t%d\n", argc);
  for (unsigned int i = 0; i < argc; ++i) {
    fprintf(stdout, "argv[%d]\t\t⇒\t%s\n", i, argv[i]);
  }
}

void printLineJump(void) { printf("\n"); }

void printErrMsg(char msg[], char option[]) { fprintf(stderr, msg, option); }

void printUsage(char argument[]) { fprintf(stdout, USAGE, argument); }

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

void printCanvasFileStdin(void) {
  int counter = 1;
  char line[80];
  bool valid = true;

  rewind(stdin);
  fflush(stdin);
  while (fgets(line, sizeof(line), stdin) != NULL && counter <= 80) {
    for (unsigned int i = 0; i < strlen(line); i++) {
      valid = validateCharactersInCanvas(line, i);
      if (valid == false) {
        fprintf(stderr, "%s", ERR_MSG_01);
        printUsage(EXECUTABLE_NAME);

        exit(ERR_WRONG_PIXEL);
      }
      counter++;
    }
  }
  counter = 1;
  rewind(stdin);
  fflush(stdin);
  while (fgets(line, sizeof(line), stdin) != NULL && counter <= 80) {
    for (unsigned int j = 0; j < strlen(line); j++) {
      if (line[j] == '\0') {
        printLineJump();
      } else {
        printf("%c", line[j]);
      }
    }
    counter++;
  }
  rewind(stdin);
  fflush(stdin);
}

void printCanvasHorizontalLine(canvas canvasX,
                               const unsigned int horizontalLinePosition,
                               const char pen) {
  for (unsigned int i = 1; i <= canvasX.height; i++) {
    if (i != 1)
      printLineJump();
    for (unsigned int j = 1; j <= canvasX.width; j++) {
      if (i == horizontalLinePosition + 1) {
        fprintf(stdout, "%c", pen);
      } else {
        fprintf(stdout, "%c", EMPTY);
      }
    }
  }
  printLineJump();
}

void printCanvasVerticalLine(canvas canvasX,
                             const unsigned int verticalLinePosition,
                             const char pen) {
  for (unsigned int i = 1; i <= canvasX.height; i++) {
    if (i != 1)
      printLineJump();
    for (unsigned int j = 1; j <= canvasX.width; j++) {
      if (j == verticalLinePosition + 1) {
        fprintf(stdout, "%c", pen);
      } else {
        fprintf(stdout, "%c", EMPTY);
      }
    }
  }
  printLineJump();
}

void printCanvasHorizontalLineFile(const unsigned int horizontalLinePosition,
                                   const unsigned height, const unsigned width,
                                   const char pen) {
  for (unsigned int i = 1; i <= height; i++) {
    if (i != 1)
      printLineJump();
    for (unsigned int j = 1; j <= width; j++) {
      if (i == horizontalLinePosition + 1) {
        fprintf(stdout, "%c", pen);
      } else {
        fprintf(stdout, "%c", EMPTY);
      }
    }
  }
  printLineJump();
}

void printCanvasVerticalLineFile(const unsigned int verticalLinePosition,
                                 const unsigned height, const unsigned width,
                                 const char pen) {
  for (unsigned int i = 1; i <= height; i++) {
    if (i != 1)
      printLineJump();
    for (unsigned int j = 1; j <= width; j++) {
      if (j == verticalLinePosition + 1) {
        fprintf(stdout, "%c", pen);
      } else {
        fprintf(stdout, "%c", EMPTY);
      }
    }
  }
  printLineJump();
}

bool validateHeight(canvas canvasX) {
  bool valid = true;

  if (canvasX.height > MAX_HEIGHT) {
    valid = false;
  }
  return valid;
}

bool validateWidth(canvas canvasX) {
  bool valid = true;

  if (canvasX.width > MAX_WIDTH) {
    valid = false;
  }
  return valid;
}

bool validateCharactersInCanvas(char line[], unsigned int index) {
  bool valid = true;

  if (!(line[index] == '.' || line[index] == '\0' || line[index] == '\n' ||
        line[index] == '0' || line[index] == '1' || line[index] == '2' ||
        line[index] == '3' || line[index] == '4' || line[index] == '5' ||
        line[index] == '6' || line[index] == '7')) {
    valid = false;
  }
  return valid;
}

bool validateCanvasFileWidthAllSame(void) {
  bool valid = true;
  char line[80];
  unsigned int height = getCanvasFileHeight();
  unsigned int width = getCanvasFileWidth();
  unsigned int area = height * width;
  unsigned int numberOfCharacters = 0;

  rewind(stdin);
  fflush(stdin);
  while (fgets(line, sizeof(line), stdin) != NULL) {
    for (unsigned int i = 0; i < strlen(line); i++) {
      if (line[i] != '\0' && line[i] != '\n') {
        numberOfCharacters++;
      }
    }
  }
  rewind(stdin);
  fflush(stdin);
  // if the area not the same as the ∑ of all characters ⟹ lines are not all
  // equals
  if (area != numberOfCharacters) {
    valid = false;
  }
  return valid;
}

bool validateDimensionOptionFormat(char option[]) {
  bool valid = false;
  const char coma = ',';

  // Verify that the format is one of the 4 below⬇︎
  if ((option[2] == coma && strlen(option) == 5) ||
      (option[2] == coma && strlen(option) == 4) ||
      (option[1] == coma && strlen(option) == 4) ||
      (option[1] == coma && strlen(option) == 3)) {
    valid = true;
  }
  return valid;
}

bool validateOption(char option[], char str[]) {
  //  printf("option: %s\nstr: %s\n", option, str);
  bool valid = true;

  if (strcmp(option, str) != 0) {
    valid = false;
  }
  return valid;
}

bool validateCanvasFileHeight(void) {
  bool valid = true;
  unsigned int height = 0;
  int character = 0;
  char line[100];

  while (fgets(line, sizeof(line), stdin) != NULL) {
    height++;
  }

  // printf("Height of file\t⇒\t%d\n", height);
  if (height > 40) {
    valid = false;
  }
  rewind(stdin);

  return valid;
}

bool validateCanvasFileWidth(void) {
  bool valid = true;
  unsigned int width = 0;
  char line[100];

  width = strlen(fgets(line, sizeof(line), stdin)) - 1;
  if (width > 80) {
    valid = false;
  }
  rewind(stdin);

  return valid;
}

int convertCharacterNumberToInt(char numberChar) {
  const int numberInt = (int)(numberChar - 48);
  return numberInt;
}

int convertStringNumberToInt(char numberString[]) {
  int numberInt = 0;
  const int length = strlen(numberString);

  for (int i = 0; i < length; i++) {
    numberInt += convertCharacterNumberToInt(numberString[length - i - 1]) *
                 calculatePowerForTen(i);
  }

  return numberInt;
}

int concatTwoIntNumber(int number1, int number2) {
  int finalNumber = number1 * 10 + number2;
  return finalNumber;
}

int calculatePowerForTen(int power) {
  int result;

  if (power == 0) {
    return 1;
  } else {
    result = 10 * 10;
    for (int i = 0; i < power - 1; i++) {
      result *= 10;
    }
    return result;
  }
}

char getOptionLetter(char option[]) {
  char letter;
  if (validateOption(option, OPTION_N)) {
    letter = 'n';
  } else if (validateOption(option, OPTION_S)) {
    letter = 's';
  } else if (validateOption(option, OPTION_H)) {
    letter = 'h';
  } else if (validateOption(option, OPTION_V)) {
    letter = 'v';
  } else if (validateOption(option, OPTION_H)) {
    letter = 'h';
  } else if (validateOption(option, OPTION_R)) {
    letter = 'r';
  } else if (validateOption(option, OPTION_L)) {
    letter = 'l';
  } else if (validateOption(option, OPTION_C)) {
    letter = 'c';
  } else if (validateOption(option, OPTION_P)) {
    letter = 'p';
  } else if (validateOption(option, OPTION_K)) {
    letter = 'k';
  }
  return letter;
}

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
    firstNumberWidth = convertCharacterNumberToInt(option[2]);
    secondNumberWidth = convertCharacterNumberToInt(option[3]);
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

unsigned int getCanvasFileHeight(void) {
  unsigned int height = 0;
  int character = 0;
  char line[100];

  while (fgets(line, sizeof(line), stdin) != NULL) {
    height++;
  }
  rewind(stdin);

  return height;
}

unsigned int getCanvasFileWidth(void) {
  unsigned int width = 0;
  char line[100];

  width = strlen(fgets(line, sizeof(line), stdin)) - 1;
  rewind(stdin);

  return width;
}

unsigned int getRectangleRowOption(char option[]) {
  const char coma = ',';
  char numStr[3];
  unsigned int rowRect;

  if (option[1] == coma) {
    rowRect = convertCharacterNumberToInt(option[0]);
  } else if (option[2] == coma) {
    strncpy(numStr, option, 2);
    numStr[2] = '\0';
    rowRect = convertStringNumberToInt(numStr);
  }

  return rowRect;
}
// unsigned int getRectangleColOption(char option[]) {
// FIXME
//   const char coma = ',';
//   char numStr[3];
//   unsigned int colRect;

//   if (option[3] == coma) {
//     colRect = convertCharacterNumberToInt(option[2]);
//     printf("%d\n", colRect);
//   } else if (option[4] == coma) {
//     strncpy(numStr, option + 2, 2);
//     numStr[2] = '\0';
//     colRect = convertStringNumbersToInt(numStr);
//     printf("%d\n", colRect);
//   }

//   return colRect;
// }

// unsigned int getRectangleHeightOption(char option[]) {
// FIXME
//   const char coma = ',';
//   char numStr[3];
//   unsigned int heightRect;

//   if (option[3] == coma) {
//     heightRect = convertCharacterNumberToInt(option[2]);
//     printf("%d\n", heightRect);
//   } else if (option[4] == coma) {
//     strncpy(numStr, option + 4, 2);
//     numStr[2] = '\0';
//     heightRect = convertStringNumbersToInt(numStr);
//     printf("%d\n", heightRect);
//   }

//   return heightRect;
// }

// unsigned int getRectangleWidthOption(char option[]) {}

canvas createEmptyCanvas(const unsigned int height, const unsigned int width) {
  canvas canvasX;

  canvasX.height = height;
  canvasX.width = width;
  canvasX.pen = WHITE;

  return canvasX;
}

//------------------------------------------------------------------------------
// ☆ STARTING POINT FOR PROGRAM EXECUTION ☆
// ⚠️ Exit code = 0 if there's no error, code take a value x∈ℕ\{0}
// otherwise
//------------------------------------------------------------------------------
int main(int argumentsNumber, char *argumentsList[]) {
  char penFile = WHITE;
  // printArguments(argumentsNumber, argumentsList);
  // If there's no explicit arguments other than the executable (./canvascii)
  if (argumentsNumber == 1) {
    printUsage(EXECUTABLE);
    // If there's explicit options ⟹ argv[x > 0] where x is a integer
  } else if (argumentsNumber > 1) {
    // Analyse all the arguments of the program one by one
    switch (getOptionLetter(OPTION_01)) {
    case 'n':
      // Validate that there's canvas dimensions option
      if (argumentsNumber < 3) {
        printErrMsg(ERR_MSG_06, OPTION_N);
        printUsage(EXECUTABLE);

        exit(ERR_MISSING_VALUE);
      }
      // Validate if the format of dimension is the form "xx,xx" where x is a
      // positive integer
      if (!validateDimensionOptionFormat(OPTION_02)) {
        printErrMsg(ERR_MSG_07, OPTION_N);
        printUsage(EXECUTABLE);

        exit(ERR_WITH_VALUE);
      }
      const unsigned int height = getCanvasHeightOption(OPTION_02);
      const unsigned int width = getCanvasWidthOption(OPTION_02);
      const canvas canvasX = createEmptyCanvas(height, width);
      // Validate the dimensions ⟹ positive(unsigned int) & MAX: 40=h,80=w
      if (!validateHeight(canvasX)) {
        printErrMsg(ERR_MSG_07, OPTION_N);
        printUsage(EXECUTABLE);

        exit(ERR_WITH_VALUE);
      }
      if (!validateWidth(canvasX)) {
        printErrMsg(ERR_MSG_07, OPTION_N);
        printUsage(EXECUTABLE);

        exit(ERR_WITH_VALUE);
      }
      // Execute ∀ valid options after -n
      for (int i = 0; i < argumentsNumber; i++) {
        // Execution of the option -h if ∃
        if (validateOption(argumentsList[i], OPTION_H) && i > 2) {
          // Verify if the next option ∃
          if (argumentsList[i + 1] == NULL) {
            fprintf(stderr, ERR_MSG_06, OPTION_H);

            exit(ERR_MISSING_VALUE);
          }
          const unsigned int horizontalLinePosition =
              convertStringNumberToInt(argumentsList[i + 1]);
          // Validate if the horizontal line is valid
          if (horizontalLinePosition + 1 > height) {
            printErrMsg(ERR_MSG_07, OPTION_H);
            printUsage(EXECUTABLE);

            exit(ERR_WITH_VALUE);
          }
          printCanvasHorizontalLine(canvasX, horizontalLinePosition,
                                    canvasX.pen);

          exit(OK);
          // Execution of the option -v if ∃
        } else if (validateOption(argumentsList[i], OPTION_V) && i > 2) {
          // Verify if the next option ∃
          if (argumentsList[i + 1] == NULL) {
            printErrMsg(ERR_MSG_06, OPTION_V);
            printUsage(EXECUTABLE);

            exit(ERR_MISSING_VALUE);
          }
          const unsigned int verticalLinePosition =
              convertStringNumberToInt(argumentsList[i + 1]);
          // Validate if the vertical line is valid
          if (verticalLinePosition + 1 > width) {
            printErrMsg(ERR_MSG_07, OPTION_V);
            printUsage(EXECUTABLE);

            exit(ERR_WITH_VALUE);
          }
          printCanvasVerticalLine(canvasX, verticalLinePosition, canvasX.pen);

          exit(OK);
          // Execution of the option -r if ∃
        } else if (validateOption(argumentsList[i], OPTION_R) && i > 2) {
          // Verify if the next option ∃
          if (argumentsList[i + 1] == NULL) {
            // printErrMsg(ERR_MSG_06);
            // printErrMsg("✘\tError, missing an option after -r!\n");

            exit(ERR_MISSING_VALUE);
          }
          printf("HERE\n");
          // const unsigned int heightRectangle =
          // getRectangleRowOption(argumentsList[i + 1]);
          // const unsigned int widthRectangle =
          // getRectangleColOption(argumentsList[i + 1]);
          // TODO validate the rectangle option format
          // printEndOptionMsg('r');
          // printNotOkayMsg();
        } else if (!validateOption(argumentsList[i], OPTION_H) &&
                   !validateOption(argumentsList[i], OPTION_V) &&
                   !validateOption(argumentsList[i], OPTION_R) &&
                   !validateOption(argumentsList[i], OPTION_L) &&
                   !validateOption(argumentsList[i], OPTION_C) &&
                   !validateOption(argumentsList[i], OPTION_P) &&
                   !validateOption(argumentsList[i], OPTION_K) && i > 2) {
          printErrMsg(ERR_MSG_05, argumentsList[i]);
          printUsage(EXECUTABLE);

          exit(ERR_UNRECOGNIZED_OPTION);
        }
      }
      // Showing the canvas to the terminal
      printEmptyCanvas(canvasX);

      exit(OK);

      break;
      // If the first option is "-s"
    case 's':
      // ignore other options after "-s"
      if (!validateCanvasFileHeight()) {
        printErrMsg(ERR_MSG_02, OPTION_S);
        printUsage(EXECUTABLE);

        exit(ERR_CANVAS_TOO_HIGH);
      } else if (!validateCanvasFileWidth()) {
        printErrMsg(ERR_MSG_03, OPTION_S);
        printUsage(EXECUTABLE);

        exit(ERR_CANVAS_TOO_WIDE);
      } else if (!validateCanvasFileWidthAllSame()) {
        printErrMsg(ERR_MSG_04, OPTION_S);
        printUsage(EXECUTABLE);

        exit(ERR_CANVAS_NON_RECTANGULAR);
      }
      const unsigned int heightFile = getCanvasFileHeight();
      const unsigned int widthFile = getCanvasFileWidth();
      printCanvasFileStdin();

      exit(OK);

      break;
    // If the first option is "-h"
    case 'h':
      // validate the dimension of the canvas
      if (!validateCanvasFileHeight()) {
        printErrMsg(ERR_MSG_02, OPTION_H);

        exit(ERR_CANVAS_TOO_HIGH);
      } else if (!validateCanvasFileWidth()) {
        printErrMsg(ERR_MSG_03, OPTION_H);

        exit(ERR_CANVAS_TOO_WIDE);
      }
      const unsigned int heightFileHorizontal = getCanvasFileHeight();
      const unsigned int widthFileHorizontal = getCanvasFileWidth();
      // Verify if the next option ∃
      if (OPTION_02 == NULL) {
        printErrMsg(ERR_MSG_06, OPTION_H);

        exit(ERR_MISSING_VALUE);
      }
      const unsigned int horizontalLinePosition =
          convertStringNumberToInt(OPTION_02);
      // Validate if the horizontal line is valid
      if (horizontalLinePosition + 1 > heightFileHorizontal) {
        printErrMsg(ERR_MSG_07, OPTION_H);
        printUsage(EXECUTABLE);

        exit(ERR_WITH_VALUE);
      }
      printCanvasHorizontalLineFile(horizontalLinePosition,
                                    heightFileHorizontal, widthFileHorizontal,
                                    penFile);

      exit(OK);

      break;
    // If the first option is "-s"
    case 'v':
      if (!validateCanvasFileHeight()) {
        printErrMsg(ERR_MSG_02, OPTION_S);

        exit(ERR_CANVAS_TOO_HIGH);
      } else if (!validateCanvasFileWidth()) {
        printErrMsg(ERR_MSG_03, OPTION_S);

        exit(ERR_CANVAS_TOO_WIDE);
      }
      const unsigned int heightFileVertical = getCanvasFileHeight();
      const unsigned int widthFileVertical = getCanvasFileWidth();
      // Verify if the next option ∃
      if (OPTION_02 == NULL) {
        printErrMsg(ERR_MSG_06, OPTION_S);

        exit(ERR_MISSING_VALUE);
      }
      const unsigned int verticalLinePosition =
          convertStringNumberToInt(OPTION_02);
      // Validate if the horizontal line is valid
      if (verticalLinePosition + 1 > heightFileVertical) {
        printErrMsg(ERR_MSG_07, OPTION_S);
        printUsage(EXECUTABLE);

        exit(ERR_WITH_VALUE);
      }
      printCanvasVerticalLineFile(verticalLinePosition, heightFileVertical,
                                  widthFileVertical, penFile);

      exit(OK);
    }
  }

  exit(OK);
}