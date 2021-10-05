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
// Provides macros for reporting and retrieving error conditions using the
// symbol errno
#include <errno.h>
// Provides functions involving mathematics equations
#include <math.h>
// Declaration of constants
#define MAX_HEIGHT 40
#define MAX_WIDTH 80
#define OKAY_MSG "✔︎\tEverything is okay, end of the program!\n"
#define NOT_OKAY_MSG "✘\tSomething is wrong, end of the program!\n"
#define INFORMATIONS "\t\t☆ INFORMATIONS ABOUT THE PROGRAM ☆\n"
#define BEGIN_OPTION_N "✅\tBEGINNING OF OPTION ☞ -n\n"
#define BEGIN_OPTION_S "✅\tBEGINNING OF OPTION ☞ -s\n"
#define BEGIN_OPTION_H "✅\tBEGINNING OF OPTION ☞ -h\n"
#define BEGIN_OPTION_V "✅\tBEGINNING OF OPTION ☞ -v\n"
#define BEGIN_OPTION_R "✅\tBEGINNING OF OPTION ☞ -r\n"
#define BEGIN_OPTION_L "✅\tBEGINNING OF OPTION ☞ -l\n"
#define BEGIN_OPTION_C "✅\tBEGINNING OF OPTION ☞ -c\n"
#define BEGIN_OPTION_P "✅\tBEGINNING OF OPTION ☞ -p\n"
#define BEGIN_OPTION_K "✅\tBEGINNING OF OPTION ☞ -k\n"
#define END_OPTION_N "❌\tEND OF OPTION ☞ -n\n"
#define END_OPTION_S "❌\tEND OF OPTION ☞ -s\n"
#define END_OPTION_H "❌\tEND OF OPTION ☞ -h\n"
#define END_OPTION_V "❌\tEND OF OPTION ☞ -v\n"
#define END_OPTION_R "❌\tEND OF OPTION ☞ -r\n"
#define END_OPTION_L "❌\tEND OF OPTION ☞ -l\n"
#define END_OPTION_C "❌\tEND OF OPTION ☞ -c\n"
#define END_OPTION_P "❌\tEND OF OPTION ☞ -p\n"
#define END_OPTION_K "❌\tEND OF OPTION ☞ -k\n"
#define ERR_MSG_01 "✘\tError, wrong pixel value in canvas!\n"
#define ERR_MSG_02 "Error: canvas is too high (max height: 40)\n"
#define ERR_MSG_03 "Error: canvas is too wide (max width: 80)\n"
#define ERR_MSG_04 "✘\tError, canvas is non rectangular!\n"
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
#define LINE_SEPARATOR                                                         \
  "==========================================================================" \
  "======"                                                                     \
  "\n"
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
void printArguments(const unsigned int argc, char *argv[]);
void printLineJump(void);
void printSeparator(void);
void printOkayMsg(void);
void printNotOkayMsg(void);
void printInformations(void);
void printBeginningOptionMsg(const char option);
void printEndOptionMsg(const char option);
void printErrMsg(char *msg);
void printUsage(char argument[]);
void printEmptyCanvas(canvas canvasX);
void printCanvasFileStdin(void);
void printCanvasHorizontalLine(canvas canvasX,
                               const unsigned int horizontalLine,
                               const char pen);
void printCanvasVerticalLine(canvas canvasX, const unsigned int verticalLine,
                             const char pen);
bool validateHeight(canvas canvasX);
bool validateWidth(canvas canvasX);
bool validateDimensionOptionFormat(char option[]);
bool validateOption(char option[], char str[]);
bool validateCanvasFileHeight(void);
bool validateCanvasFileWidth(void);
int convertCharacterNumberToInt(const char numberChar);
int concatTwoIntNumber(const int number1, const int number2);
char getOptionLetter(char option[]);
unsigned int getCanvasHeightOption(char option[]);
unsigned int getCanvasWidthOption(char option[]);
unsigned int getCanvasFileHeight(void);
unsigned int getCanvasFileWidth(void);
// unsigned int getRectangleRowOption(char option[]);
// unsigned int getRectangleColOption(char option[]);
// unsigned int getRectangleHeightOption(char option[]);
// unsigned int getRectanglewidthOption(char option[]);
canvas createEmptyCanvas(const unsigned int height, const unsigned int width);

/**
 * @brief Print the number of arguments and the arguments names to the terminal
 * @param argc : number of arguments
 * @param argv : the list of arguments
 */
void printArguments(const unsigned int argc, char *argv[]) {
  fprintf(stdout, "# of arguments\t⇒\t%d\n", argc);
  for (unsigned int i = 0; i < argc; ++i) {
    fprintf(stdout, "argv[%d]\t\t⇒\t%s\n", i, argv[i]);
  }
}

/**
 * @brief Print line jump("\n") to the terminal
 */
void printLineJump(void) { printf("\n"); }

/**
 * @brief Print an okay message to the terminal
 */
void printOkayMsg(void) {
  printSeparator();
  fprintf(stdout, "%s", OKAY_MSG);
  printSeparator();
}

/**
 * @brief Print a NOT okay message to the terminal
 */
void printNotOkayMsg(void) {
  printSeparator();
  fprintf(stdout, "%s", NOT_OKAY_MSG);
  printSeparator();
}

/**
 * @brief Print a separator title for the informations of the program to the
 * terminal
 */
void printInformations(void) {
  printSeparator();
  printf(INFORMATIONS);
  printSeparator();
}

/**
 * @brief Print a beginning message for an option to the terminal
 * @param option
 */
void printBeginningOptionMsg(const char option) {
  switch (option) {
  case 'n':
    printSeparator();
    printf(BEGIN_OPTION_N);
    printSeparator();
    break;
  case 's':
    printSeparator();
    printf(BEGIN_OPTION_S);
    printSeparator();
    break;
  case 'h':
    printSeparator();
    printf(BEGIN_OPTION_H);
    printSeparator();
    break;
  case 'v':
    printSeparator();
    printf(BEGIN_OPTION_V);
    printSeparator();
    break;
  case 'r':
    printSeparator();
    printf(BEGIN_OPTION_R);
    printSeparator();
    break;
  case 'l':
    printSeparator();
    printf(BEGIN_OPTION_L);
    printSeparator();
    break;
  case 'c':
    printSeparator();
    printf(BEGIN_OPTION_C);
    printSeparator();
    break;
  case 'p':
    printSeparator();
    printf(BEGIN_OPTION_P);
    printSeparator();
    break;
  case 'k':
    printSeparator();
    printf(BEGIN_OPTION_K);
    printSeparator();
    break;
  default:
    printErrMsg("✘\tError, invalid option choice in begginning option "
                "message!\n");
    printErrMsg(ERR_MSG_07);
    printNotOkayMsg();
    exit(ERR_WITH_VALUE);
  }
}

/**
 * @brief Print an ending message for an option to the terminal
 * @param option
 */
void printEndOptionMsg(const char option) {
  switch (option) {
  case 'n':
    printSeparator();
    printf(END_OPTION_N);
    printSeparator();

    break;
  case 's':
    printSeparator();
    printf(END_OPTION_N);
    printSeparator();

    break;
  case 'h':
    printSeparator();
    printf(END_OPTION_H);
    printSeparator();

    break;
  case 'v':
    printSeparator();
    printf(END_OPTION_V);
    printSeparator();

    break;
  case 'r':
    printSeparator();
    printf(END_OPTION_R);
    printSeparator();

    break;
  case 'l':
    printSeparator();
    printf(END_OPTION_L);
    printSeparator();

    break;
  case 'c':
    printSeparator();
    printf(END_OPTION_C);
    printSeparator();

    break;
  case 'p':
    printSeparator();
    printf(END_OPTION_P);
    printSeparator();

    break;
  case 'k':
    printSeparator();
    printf(END_OPTION_K);
    printSeparator();

    break;
  default:
    printErrMsg("✘\tError, invalid option choice in end option "
                "message!\n");
    printErrMsg(ERR_MSG_07);
    printNotOkayMsg();
    exit(ERR_WITH_VALUE);
  }
}

/**
 * @brief Print an error message to the terminal
 * @param msg
 */
void printErrMsg(char *msg) { fprintf(stderr, "%s", msg); }

/**
 * @brief Print the usage documentation to the terminal
 */
void printUsage(char argument[]) {
  // printSeparator();
  // printf("\t\t☆USAGE INFORMATION☆\n");
  // printSeparator();
  fprintf(stdout, USAGE, argument);
  // printSeparator();
}

/**
 * @brief Print an empty canvas to the terminal (for option -n)
 * @param canvasX
 */
void printEmptyCanvas(canvas canvasX) {
  // printSeparator();
  // printf("\t\t☆This is the empty canvas (⬇)☆\n");
  // printSeparator();
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
 * @brief Print a canvas from a file to the terminal (for option -s)
 */
void printCanvasFileStdin(void) {
  int counter = 0;
  char line[80];

  // printSeparator();
  // printf("\t☆This is the canvas of the file (⬇)☆\n");
  // printSeparator();
  while (fgets(line, sizeof(line), stdin) != NULL && counter <= 80) {
    printf("%s", line);

    counter++;
  }
  rewind(stdin);
}

/**
 * @brief Print a canvas with horizontal line to the terminal (for option -h)
 * @param canvasX
 */
void printCanvasHorizontalLine(canvas canvasX,
                               const unsigned int horizontalLine,
                               const char pen) {
  // printSeparator();
  // printf("\t☆This is the canvas with horizontal line (⬇)☆\n");
  // printSeparator();
  for (unsigned int i = 1; i <= canvasX.height; i++) {
    if (i != 1)
      printLineJump();
    for (unsigned int j = 1; j <= canvasX.width; j++) {
      if (i == horizontalLine + 1) {
        fprintf(stdout, "%c", pen);
      } else {
        fprintf(stdout, "%c", EMPTY);
      }
    }
  }
  printLineJump();
}

/**
 * @brief Print an canvas with vertical line to the terminal (for option -v)
 * @param canvasX
 */
void printCanvasVerticalLine(canvas canvasX, const unsigned int verticalLine,
                             const char pen) {
  // printSeparator();
  // printf("\t☆This is the canvas with vertical line (⬇)☆\n");
  // printSeparator();
  for (unsigned int i = 1; i <= canvasX.height; i++) {
    if (i != 1)
      printLineJump();
    for (unsigned int j = 1; j <= canvasX.width; j++) {
      if (j == verticalLine + 1) {
        fprintf(stdout, "%c", pen);
      } else {
        fprintf(stdout, "%c", EMPTY);
      }
    }
  }
  printLineJump();
}

/**
 * Print a line of characters for readability
 */
void printSeparator(void) { printf(LINE_SEPARATOR); }

/**
 * @brief Return true(1) if the height of the canvas is valid
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
 * @brief Return true(1) if the width of the canvas is valid
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
 * @brief Return true(1) if option of the dimension is in valid format
 * @param option
 * @return valid
 */
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

/**
 * @brief Return true(1) if the string in the first parameter is equal to the
 * second one
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
 * @brief Validate the height of the file canvas
 * @return valid
 */
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

/**
 * @brief Validate the width of the file canvas
 * @return valid
 */
bool validateCanvasFileWidth(void) {
  bool valid = true;
  unsigned int width = 0;
  char line[100];

  width = strlen(fgets(line, sizeof(line), stdin)) - 1;
  if (width > 80) {
    valid = false;
  }
  // printf("Width of file\t⇒\t%d\n", width);
  rewind(stdin);

  return valid;
}

/**
 * @brief Convert a number character to the integer version of it
 * @param numberChar
 * @return numberInt
 */
int convertCharacterNumberToInt(char numberChar) {
  const int numberInt = (int)(numberChar - 48);
  return numberInt;
}

/**
 * @brief Convert a string of numbers to the integer version of it
 * @param numberChar
 * @return numberInt
 */
int convertStringNumbersToInt(char numberStr[]) {
  int numberInt = 0;
  const int length = strlen(numberStr);

  for (int i = 0; i < length; i++) {
    numberInt +=
        convertCharacterNumberToInt(numberStr[length - i - 1]) * pow(10, i);
  }

  return numberInt;
}

/**
 * @brief Concatenate 2 integers to form a number formed of 2 numbers
 * Ex: 1 & 2 ⟹ 12
 * @param number1
 * @param number2
 * @return finalNumber
 */
int concatTwoIntNumber(int number1, int number2) {
  const int finalNumber = number1 * 10 + number2;
  return finalNumber;
}

/**
 * @brief Return a single character(letter) for a specific option
 * feature for the switch/case statement
 * @param option
 * @return letter
 */
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

/**
 * @brief Return the height of a canvas
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
 * @brief Return the width of a canvas
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

/**
 * @brief return the height of the file canvas
 * @return height
 */
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

/**
 * @brief get the ganvas file width object
 *
 * @return unsigned int
 */
unsigned int getCanvasFileWidth(void) {
  unsigned int width = 0;
  char line[100];

  width = strlen(fgets(line, sizeof(line), stdin)) - 1;
  rewind(stdin);

  return width;
}

/**
 * @brief return the rectangle row option (for option -r)
 *
 * @param option
 * @return rowRect
 */
unsigned int getRectangleRowOption(char option[]) {
  const char coma = ',';
  char numStr[3];
  unsigned int rowRect;

  if (option[1] == coma) {
    rowRect = convertCharacterNumberToInt(option[0]);
  } else if (option[2] == coma) {
    strncpy(numStr, option, 2);
    numStr[2] = '\0';
    rowRect = convertStringNumbersToInt(numStr);
  }

  return rowRect;
}

/**
 * @brief Return the rectangle column option (for option -r)
 *
 * @param option
 * @return colRect
 */
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

/**
 * @brief Return the rectangle height option (for option -r)
 *
 * @param option
 * @return heightRect
 */
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

/**
 * @brief Create a new empty canvas of dimension h x w
 * @param h
 * @param w
 * @return newCanvas
 */
canvas createEmptyCanvas(const unsigned int height, const unsigned int width) {
  canvas canvasX;

  // The canvas dimensions explicitly choose
  canvasX.height = height;
  canvasX.width = width;
  // The pen style (look)
  canvasX.pen = WHITE;

  return canvasX;
}

//------------------------------------------------------------------------------
// ☆ STARTING POINT FOR PROGRAM EXECUTION ☆
//------------------------------------------------------------------------------
int main(int argumentsNumber, char *argumentsList[]) {
  // Code is 0 if there's no error, code take a value x∈ℕ\{0} otherwise
  // printInformations();
  // printArguments(argumentsNumber, argumentsList);
  // If there's no explicit arguments other than the name of the program
  if (argumentsNumber == 1) {
    printUsage(EXECUTABLE);
    // If there's explicit options ⟹ argv[x > 0] where x is an integer
  } else if (argumentsNumber > 1) {
    // Analyse all the arguments of the program one by one
    // Check what is the first option
    switch (getOptionLetter(OPTION_01)) {
      // If the first option is "-n"
    case 'n':
      // printBeginningOptionMsg('n');
      // Validate that there's canvas dimensions option
      if (argumentsNumber < 3) {
        fprintf(stderr, ERR_MSG_06, OPTION_N);
        printUsage(EXECUTABLE);
        // printErrMsg("✘\tError, missing dimensions for the canvas!\n");
        // printEndOptionMsg('n');

        exit(ERR_MISSING_VALUE);
      }
      // Validate if the format of dimension is the form "xx,xx" where x is a
      // positive integer
      if (!validateDimensionOptionFormat(OPTION_02)) {
        fprintf(stderr, ERR_MSG_07, OPTION_N);
        printUsage(EXECUTABLE);
        // printEndOptionMsg('n');
        // printSeparator();

        exit(ERR_WITH_VALUE);
      }
      // Getting the dimensions (height & width) of the argument
      const unsigned int height = getCanvasHeightOption(OPTION_02);
      const unsigned int width = getCanvasWidthOption(OPTION_02);
      // printf("height\t\t⇒\t%d\nwidth\t\t⇒\t%d\n", height, width);
      // Creating a canvas with those dimensions
      const canvas canvasX = createEmptyCanvas(height, width);
      // Validate the dimensions ⟹ positive(unsigned int) & MAX: 40=h,80=w
      if (!validateHeight(canvasX)) {
        fprintf(stderr, ERR_MSG_07, OPTION_N);
        printUsage(EXECUTABLE);

        exit(ERR_WITH_VALUE);
      } 
      if (!validateWidth(canvasX)) {
        fprintf(stderr, ERR_MSG_07, OPTION_N);
        printUsage(EXECUTABLE);
        // printEndOptionMsg('n');
        // printSeparator();

        exit(ERR_WITH_VALUE);
      }
      // Execute ∀ valid options after -n
      for (int i = 0; i < argumentsNumber; i++) {
        // Execution of the option -h
        if (validateOption(argumentsList[i], OPTION_H) && i > 2) {
          // printBeginningOptionMsg('h');
          // Verify if the next option ∃
          if (argumentsList[i + 1] == NULL) {
            printErrMsg(ERR_MSG_06);
            // printEndOptionMsg('h');
            printErrMsg("✘\tError, missing an option after -h!\n");
            // printNotOkayMsg();

            exit(ERR_MISSING_VALUE);
          }
          const unsigned int horizontalLine =
              convertStringNumbersToInt(argumentsList[i + 1]);
          printf("horizontal\t⇒\t%d\n", horizontalLine);
          // Validate if the horizontal line is valid
          if (horizontalLine + 1 > height) {
            printErrMsg(ERR_MSG_07);
            printf("✘\tError, %d for -h is higher than height + 1 = %d "
                   "or "
                   "negative!\n",
                   horizontalLine, height + 1);
            printEndOptionMsg('h');
            printUsage(EXECUTABLE);

            exit(ERR_WITH_VALUE);
          }
          printCanvasHorizontalLine(canvasX, horizontalLine, canvasX.pen);
          printEndOptionMsg('h');
          printOkayMsg();

          exit(OK);
          // Execution of the option -v
        } else if (validateOption(argumentsList[i], OPTION_V) && i > 2) {
          printBeginningOptionMsg('v');
          // Verify if the next option ∃
          if (argumentsList[i + 1] == NULL) {
            printErrMsg(ERR_MSG_06);
            printErrMsg("✘\tError, missing an option after -v!\n");
            printEndOptionMsg('v');
            printNotOkayMsg();

            exit(ERR_MISSING_VALUE);
          }
          const unsigned int verticalLine =
              convertStringNumbersToInt(argumentsList[i + 1]);
          // printf("vertical\t⇒\t%d\n", verticalLine);
          // Validate if the vertical line is valid
          if (verticalLine + 1 > width) {
            printErrMsg(ERR_MSG_07);
            // printf("✘\tError, %d for -v is higher than width + 1 = %d "
            //        "or "
            //        "negative!\n",
            //        verticalLine, width + 1);
            // printEndOptionMsg('v');
            printUsage(EXECUTABLE);

            exit(ERR_WITH_VALUE);
          }
          printCanvasVerticalLine(canvasX, verticalLine, canvasX.pen);
          // printEndOptionMsg('h');
          // printOkayMsg();

          exit(OK);
          // Execution of the option -r
        } else if (validateOption(argumentsList[i], OPTION_R) && i > 2) {
          printBeginningOptionMsg('r');
          // Verify if the next option ∃
          if (argumentsList[i + 1] == NULL) {
            printErrMsg(ERR_MSG_06);
            printErrMsg("✘\tError, missing an option after -r!\n");
            // printEndOptionMsg('r');
            // printNotOkayMsg();

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
          fprintf(stderr, ERR_MSG_05, argumentsList[i]);
          printUsage(EXECUTABLE);

          exit(ERR_UNRECOGNIZED_OPTION);
        }
      }
      // Showing the canvas to the terminal
      printEmptyCanvas(canvasX);
      // printEndOptionMsg('n');
      // printOkayMsg();

      exit(OK);

      break;
      // If the first option is "-s"
    case 's':
      // ignore other options after "-s"
      if (!validateCanvasFileHeight()) {
        printErrMsg(ERR_MSG_02);
        printUsage(EXECUTABLE);

        exit(ERR_CANVAS_TOO_HIGH);
      } else if (!validateCanvasFileWidth()) {
        printErrMsg(ERR_MSG_03);
        printUsage(EXECUTABLE);

        exit(ERR_CANVAS_TOO_WIDE);
      }
      const unsigned int heightFile = getCanvasFileHeight();
      const unsigned int widthFile = getCanvasFileWidth();
      printCanvasFileStdin();
      printOkayMsg();

      exit(OK);

      break;
    // If the first option is "-h"
    case 'h':
      if (!validateCanvasFileHeight()) {
        printErrMsg(ERR_MSG_02);

        exit(ERR_CANVAS_TOO_HIGH);
      } else if (!validateCanvasFileWidth()) {
        printErrMsg(ERR_MSG_03);

        exit(ERR_CANVAS_TOO_WIDE);
      }
      const unsigned int heightFileHorizontal = getCanvasFileHeight();
      const unsigned int widthFileHorizontal = getCanvasFileWidth();

      break;
    // If the first option is "-s"
    case 'v':
      if (!validateCanvasFileHeight()) {
        printErrMsg(ERR_MSG_02);

        exit(ERR_CANVAS_TOO_HIGH);
      } else if (!validateCanvasFileWidth()) {
        printErrMsg(ERR_MSG_03);

        exit(ERR_CANVAS_TOO_WIDE);
      }
      const unsigned int heightFileVertical = getCanvasFileHeight();
      const unsigned int widthFileVertical = getCanvasFileWidth();

      break;
    default:
      printErrMsg(ERR_MSG_05);

      exit(ERR_UNRECOGNIZED_OPTION);
    }
  }
  printOkayMsg();

  exit(OK);
}